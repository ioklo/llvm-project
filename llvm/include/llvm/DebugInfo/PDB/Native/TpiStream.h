//===- TpiStream.cpp - PDB Type Info (TPI) Stream 2 Access ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_TPISTREAM_H
#define LLVM_DEBUGINFO_PDB_NATIVE_TPISTREAM_H

#include "llvm/DebugInfo/CodeView/CVRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/Native/HashTable.h"
#include "llvm/DebugInfo/PDB/Native/RawConstants.h"
#include "llvm/Support/BinaryStreamArray.h"
#include "llvm/Support/BinaryStreamRef.h"
#include "llvm/Support/Error.h"

namespace llvm {
class BinaryStream;
namespace codeview {
class TypeIndex;
struct TypeIndexOffset;
class LazyRandomTypeCollection;
} // namespace codeview
namespace msf {
class MappedBlockStream;
}
namespace pdb {
struct TpiStreamHeader;
class PDBFile;

class TpiStream {
  friend class TpiStreamBuilder;

public:
  LLVM_DEBUGINFOPDB_ABI
  TpiStream(PDBFile &File, std::unique_ptr<msf::MappedBlockStream> Stream);
  LLVM_DEBUGINFOPDB_ABI ~TpiStream();
  LLVM_DEBUGINFOPDB_ABI Error reload();

  LLVM_DEBUGINFOPDB_ABI PdbRaw_TpiVer getTpiVersion() const;

  LLVM_DEBUGINFOPDB_ABI uint32_t TypeIndexBegin() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t TypeIndexEnd() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t getNumTypeRecords() const;
  LLVM_DEBUGINFOPDB_ABI uint16_t getTypeHashStreamIndex() const;
  LLVM_DEBUGINFOPDB_ABI uint16_t getTypeHashStreamAuxIndex() const;

  LLVM_DEBUGINFOPDB_ABI uint32_t getHashKeySize() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t getNumHashBuckets() const;
  LLVM_DEBUGINFOPDB_ABI FixedStreamArray<support::ulittle32_t>
  getHashValues() const;
  LLVM_DEBUGINFOPDB_ABI FixedStreamArray<codeview::TypeIndexOffset>
  getTypeIndexOffsets() const;
  LLVM_DEBUGINFOPDB_ABI HashTable<support::ulittle32_t> &getHashAdjusters();

  LLVM_DEBUGINFOPDB_ABI codeview::CVTypeRange types(bool *HadError) const;
  const codeview::CVTypeArray &typeArray() const { return TypeRecords; }

  codeview::LazyRandomTypeCollection &typeCollection() { return *Types; }

  LLVM_DEBUGINFOPDB_ABI Expected<codeview::TypeIndex>
  findFullDeclForForwardRef(codeview::TypeIndex ForwardRefTI) const;

  LLVM_DEBUGINFOPDB_ABI std::vector<codeview::TypeIndex>
  findRecordsByName(StringRef Name) const;

  LLVM_DEBUGINFOPDB_ABI codeview::CVType getType(codeview::TypeIndex Index);

  LLVM_DEBUGINFOPDB_ABI BinarySubstreamRef getTypeRecordsSubstream() const;

  LLVM_DEBUGINFOPDB_ABI Error commit();

  LLVM_DEBUGINFOPDB_ABI void buildHashMap();

  LLVM_DEBUGINFOPDB_ABI bool supportsTypeLookup() const;

private:
  PDBFile &Pdb;
  std::unique_ptr<msf::MappedBlockStream> Stream;

  std::unique_ptr<codeview::LazyRandomTypeCollection> Types;

  BinarySubstreamRef TypeRecordsSubstream;

  codeview::CVTypeArray TypeRecords;

  std::unique_ptr<BinaryStream> HashStream;
  FixedStreamArray<support::ulittle32_t> HashValues;
  FixedStreamArray<codeview::TypeIndexOffset> TypeIndexOffsets;
  HashTable<support::ulittle32_t> HashAdjusters;

  std::vector<std::vector<codeview::TypeIndex>> HashMap;

  const TpiStreamHeader *Header;
};
} // namespace pdb
} // namespace llvm

#endif
