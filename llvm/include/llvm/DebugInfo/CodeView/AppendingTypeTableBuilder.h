//===- AppendingTypeTableBuilder.h -------------------------------*- C++-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_CODEVIEW_APPENDINGTYPETABLEBUILDER_H
#define LLVM_DEBUGINFO_CODEVIEW_APPENDINGTYPETABLEBUILDER_H

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/DebugInfo/CodeView/CVRecord.h"
#include "llvm/DebugInfo/CodeView/DebugInfoCodeViewConfig.h"
#include "llvm/DebugInfo/CodeView/SimpleTypeSerializer.h"
#include "llvm/DebugInfo/CodeView/TypeCollection.h"
#include "llvm/DebugInfo/CodeView/TypeIndex.h"
#include "llvm/Support/Allocator.h"
#include <cstdint>

namespace llvm {
namespace codeview {

class ContinuationRecordBuilder;

class AppendingTypeTableBuilder : public TypeCollection {

  BumpPtrAllocator &RecordStorage;
  SimpleTypeSerializer SimpleSerializer;

  /// Contains a list of all records indexed by TypeIndex.toArrayIndex().
  SmallVector<ArrayRef<uint8_t>, 2> SeenRecords;

public:
  LLVM_DEBUGINFOCODEVIEW_ABI explicit AppendingTypeTableBuilder(
      BumpPtrAllocator &Storage);
  LLVM_DEBUGINFOCODEVIEW_ABI ~AppendingTypeTableBuilder();

  // TypeCollection overrides
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

  // public interface
  LLVM_DEBUGINFOCODEVIEW_ABI void reset();
  LLVM_DEBUGINFOCODEVIEW_ABI TypeIndex nextTypeIndex() const;

  BumpPtrAllocator &getAllocator() { return RecordStorage; }

  LLVM_DEBUGINFOCODEVIEW_ABI ArrayRef<ArrayRef<uint8_t>> records() const;
  LLVM_DEBUGINFOCODEVIEW_ABI TypeIndex
  insertRecordBytes(ArrayRef<uint8_t> &Record);
  LLVM_DEBUGINFOCODEVIEW_ABI TypeIndex
  insertRecord(ContinuationRecordBuilder &Builder);

  template <typename T> TypeIndex writeLeafType(T &Record) {
    ArrayRef<uint8_t> Data = SimpleSerializer.serialize(Record);
    return insertRecordBytes(Data);
  }
};

} // end namespace codeview
} // end namespace llvm

#endif // LLVM_DEBUGINFO_CODEVIEW_APPENDINGTYPETABLEBUILDER_H
