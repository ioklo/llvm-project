//===- PDBFile.h - Low level interface to a PDB file ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_PDBFILE_H
#define LLVM_DEBUGINFO_PDB_NATIVE_PDBFILE_H

#include "llvm/DebugInfo/MSF/IMSFFile.h"
#include "llvm/DebugInfo/MSF/MSFCommon.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Support/BinaryStreamRef.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/Error.h"

#include <memory>

namespace llvm {

class BinaryStream;

namespace msf {
class MappedBlockStream;
}

namespace pdb {
class DbiStream;
class GlobalsStream;
class InfoStream;
class InjectedSourceStream;
class PDBStringTable;
class PDBFileBuilder;
class PublicsStream;
class SymbolStream;
class TpiStream;

class PDBFile : public msf::IMSFFile {
  friend PDBFileBuilder;

public:
  LLVM_DEBUGINFOPDB_ABI PDBFile(StringRef Path,
                                std::unique_ptr<BinaryStream> PdbFileBuffer,
                                BumpPtrAllocator &Allocator);
  LLVM_DEBUGINFOPDB_ABI ~PDBFile() override;

  LLVM_DEBUGINFOPDB_ABI StringRef getFileDirectory() const;
  LLVM_DEBUGINFOPDB_ABI StringRef getFilePath() const;

  LLVM_DEBUGINFOPDB_ABI uint32_t getFreeBlockMapBlock() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t getUnknown1() const;

  LLVM_DEBUGINFOPDB_ABI uint32_t getBlockSize() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getBlockCount() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getNumDirectoryBytes() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t getBlockMapIndex() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t getNumDirectoryBlocks() const;
  LLVM_DEBUGINFOPDB_ABI uint64_t getBlockMapOffset() const;

  LLVM_DEBUGINFOPDB_ABI uint32_t getNumStreams() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getMaxStreamSize() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t
  getStreamByteSize(uint32_t StreamIndex) const override;
  LLVM_DEBUGINFOPDB_ABI ArrayRef<support::ulittle32_t>
  getStreamBlockList(uint32_t StreamIndex) const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getFileSize() const;

  LLVM_DEBUGINFOPDB_ABI Expected<ArrayRef<uint8_t>>
  getBlockData(uint32_t BlockIndex, uint32_t NumBytes) const override;
  LLVM_DEBUGINFOPDB_ABI Error
  setBlockData(uint32_t BlockIndex, uint32_t Offset,
               ArrayRef<uint8_t> Data) const override;

  ArrayRef<support::ulittle32_t> getStreamSizes() const {
    return ContainerLayout.StreamSizes;
  }
  ArrayRef<ArrayRef<support::ulittle32_t>> getStreamMap() const {
    return ContainerLayout.StreamMap;
  }

  const msf::MSFLayout &getMsfLayout() const { return ContainerLayout; }
  BinaryStreamRef getMsfBuffer() const { return *Buffer; }

  LLVM_DEBUGINFOPDB_ABI ArrayRef<support::ulittle32_t>
  getDirectoryBlockArray() const;

  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<msf::MappedBlockStream>
  createIndexedStream(uint16_t SN) const;
  LLVM_DEBUGINFOPDB_ABI Expected<std::unique_ptr<msf::MappedBlockStream>>
  safelyCreateIndexedStream(uint32_t StreamIndex) const;
  LLVM_DEBUGINFOPDB_ABI Expected<std::unique_ptr<msf::MappedBlockStream>>
  safelyCreateNamedStream(StringRef Name);

  LLVM_DEBUGINFOPDB_ABI msf::MSFStreamLayout
  getStreamLayout(uint32_t StreamIdx) const;
  LLVM_DEBUGINFOPDB_ABI msf::MSFStreamLayout getFpmStreamLayout() const;

  LLVM_DEBUGINFOPDB_ABI Error parseFileHeaders();
  LLVM_DEBUGINFOPDB_ABI Error parseStreamData();

  LLVM_DEBUGINFOPDB_ABI Expected<InfoStream &> getPDBInfoStream();
  LLVM_DEBUGINFOPDB_ABI Expected<DbiStream &> getPDBDbiStream();
  LLVM_DEBUGINFOPDB_ABI Expected<GlobalsStream &> getPDBGlobalsStream();
  LLVM_DEBUGINFOPDB_ABI Expected<TpiStream &> getPDBTpiStream();
  LLVM_DEBUGINFOPDB_ABI Expected<TpiStream &> getPDBIpiStream();
  LLVM_DEBUGINFOPDB_ABI Expected<PublicsStream &> getPDBPublicsStream();
  LLVM_DEBUGINFOPDB_ABI Expected<SymbolStream &> getPDBSymbolStream();
  LLVM_DEBUGINFOPDB_ABI Expected<PDBStringTable &> getStringTable();
  LLVM_DEBUGINFOPDB_ABI Expected<InjectedSourceStream &>
  getInjectedSourceStream();

  BumpPtrAllocator &getAllocator() { return Allocator; }

  LLVM_DEBUGINFOPDB_ABI bool hasPDBDbiStream() const;
  LLVM_DEBUGINFOPDB_ABI bool hasPDBGlobalsStream();
  LLVM_DEBUGINFOPDB_ABI bool hasPDBInfoStream() const;
  LLVM_DEBUGINFOPDB_ABI bool hasPDBIpiStream() const;
  LLVM_DEBUGINFOPDB_ABI bool hasPDBPublicsStream();
  LLVM_DEBUGINFOPDB_ABI bool hasPDBSymbolStream();
  LLVM_DEBUGINFOPDB_ABI bool hasPDBTpiStream() const;
  LLVM_DEBUGINFOPDB_ABI bool hasPDBStringTable();
  LLVM_DEBUGINFOPDB_ABI bool hasPDBInjectedSourceStream();

  LLVM_DEBUGINFOPDB_ABI uint32_t getPointerSize();

private:
  std::string FilePath;
  BumpPtrAllocator &Allocator;

  std::unique_ptr<BinaryStream> Buffer;

  msf::MSFLayout ContainerLayout;

  std::unique_ptr<GlobalsStream> Globals;
  std::unique_ptr<InfoStream> Info;
  std::unique_ptr<DbiStream> Dbi;
  std::unique_ptr<TpiStream> Tpi;
  std::unique_ptr<TpiStream> Ipi;
  std::unique_ptr<PublicsStream> Publics;
  std::unique_ptr<SymbolStream> Symbols;
  std::unique_ptr<msf::MappedBlockStream> DirectoryStream;
  std::unique_ptr<msf::MappedBlockStream> StringTableStream;
  std::unique_ptr<InjectedSourceStream> InjectedSources;
  std::unique_ptr<PDBStringTable> Strings;
};
} // namespace pdb
} // namespace llvm

#endif
