//===- TypeTableCollection.h ---------------------------------- *- C++ --*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_CODEVIEW_TYPETABLECOLLECTION_H
#define LLVM_DEBUGINFO_CODEVIEW_TYPETABLECOLLECTION_H

#include "llvm/DebugInfo/CodeView/DebugInfoCodeViewConfig.h"
#include "llvm/DebugInfo/CodeView/TypeCollection.h"
#include "llvm/Support/StringSaver.h"

#include <vector>

namespace llvm {
namespace codeview {

class TypeTableCollection : public TypeCollection {
public:
  explicit TypeTableCollection(ArrayRef<ArrayRef<uint8_t>> Records);

  LLVM_DEBUGINFOCODEVIEW_ABI std::optional<TypeIndex> getFirst() override;
  LLVM_DEBUGINFOCODEVIEW_ABI std::optional<TypeIndex>
  getNext(TypeIndex Prev) override;

  LLVM_DEBUGINFOCODEVIEW_ABI CVType getType(TypeIndex Index) override;
  LLVM_DEBUGINFOCODEVIEW_ABI StringRef getTypeName(TypeIndex Index) override;
  LLVM_DEBUGINFOCODEVIEW_ABI bool contains(TypeIndex Index) override;
  LLVM_DEBUGINFOCODEVIEW_ABI uint32_t size() override;
  LLVM_DEBUGINFOCODEVIEW_ABI uint32_t capacity() override;
  LLVM_DEBUGINFOCODEVIEW_ABI bool replaceType(TypeIndex &Index, CVType Data,
                                              bool Stabilize) override;

private:
  BumpPtrAllocator Allocator;
  StringSaver NameStorage;
  std::vector<StringRef> Names;
  ArrayRef<ArrayRef<uint8_t>> Records;
};
} // namespace codeview
} // namespace llvm

#endif
