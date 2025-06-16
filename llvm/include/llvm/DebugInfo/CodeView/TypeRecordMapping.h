//===- TypeRecordMapping.h --------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_CODEVIEW_TYPERECORDMAPPING_H
#define LLVM_DEBUGINFO_CODEVIEW_TYPERECORDMAPPING_H

#include "llvm/DebugInfo/CodeView/CVRecord.h"
#include "llvm/DebugInfo/CodeView/CodeView.h"
#include "llvm/DebugInfo/CodeView/CodeViewRecordIO.h"
#include "llvm/DebugInfo/CodeView/DebugInfoCodeViewConfig.h"
#include "llvm/DebugInfo/CodeView/TypeVisitorCallbacks.h"
#include "llvm/Support/Error.h"
#include <optional>

namespace llvm {
class BinaryStreamReader;
class BinaryStreamWriter;

namespace codeview {
class TypeIndex;
struct CVMemberRecord;
class TypeRecordMapping : public TypeVisitorCallbacks {
public:
  explicit TypeRecordMapping(BinaryStreamReader &Reader) : IO(Reader) {}
  explicit TypeRecordMapping(BinaryStreamWriter &Writer) : IO(Writer) {}
  explicit TypeRecordMapping(CodeViewRecordStreamer &Streamer) : IO(Streamer) {}

  using TypeVisitorCallbacks::visitTypeBegin;
  LLVM_DEBUGINFOCODEVIEW_ABI Error visitTypeBegin(CVType &Record) override;
  LLVM_DEBUGINFOCODEVIEW_ABI Error visitTypeBegin(CVType &Record,
                                                  TypeIndex Index) override;
  LLVM_DEBUGINFOCODEVIEW_ABI Error visitTypeEnd(CVType &Record) override;

  LLVM_DEBUGINFOCODEVIEW_ABI Error
  visitMemberBegin(CVMemberRecord &Record) override;
  LLVM_DEBUGINFOCODEVIEW_ABI Error
  visitMemberEnd(CVMemberRecord &Record) override;

#define TYPE_RECORD(EnumName, EnumVal, Name)                                   \
  LLVM_DEBUGINFOCODEVIEW_ABI Error visitKnownRecord(                           \
      CVType &CVR, Name##Record &Record) override;
#define MEMBER_RECORD(EnumName, EnumVal, Name)                                 \
  LLVM_DEBUGINFOCODEVIEW_ABI Error visitKnownMember(                           \
      CVMemberRecord &CVR, Name##Record &Record) override;
#define TYPE_RECORD_ALIAS(EnumName, EnumVal, Name, AliasName)
#define MEMBER_RECORD_ALIAS(EnumName, EnumVal, Name, AliasName)
#include "llvm/DebugInfo/CodeView/CodeViewTypes.def"

private:
  std::optional<TypeLeafKind> TypeKind;
  std::optional<TypeLeafKind> MemberKind;

  CodeViewRecordIO IO;
};
} // namespace codeview
} // namespace llvm

#endif
