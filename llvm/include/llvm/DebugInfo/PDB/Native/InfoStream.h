//===- InfoStream.h - PDB Info Stream (Stream 1) Access ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_INFOSTREAM_H
#define LLVM_DEBUGINFO_PDB_NATIVE_INFOSTREAM_H

#include "llvm/ADT/StringMap.h"
#include "llvm/DebugInfo/CodeView/GUID.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/Native/NamedStreamMap.h"
#include "llvm/DebugInfo/PDB/Native/RawConstants.h"
#include "llvm/Support/BinaryStream.h"
#include "llvm/Support/BinaryStreamRef.h"

#include "llvm/Support/Error.h"

namespace llvm {
namespace pdb {
struct InfoStreamHeader;
class InfoStream {
  friend class InfoStreamBuilder;

public:
  LLVM_DEBUGINFOPDB_ABI InfoStream(std::unique_ptr<BinaryStream> Stream);

  LLVM_DEBUGINFOPDB_ABI Error reload();

  LLVM_DEBUGINFOPDB_ABI uint32_t getStreamSize() const;

  const InfoStreamHeader *getHeader() const { return Header; }

  LLVM_DEBUGINFOPDB_ABI bool containsIdStream() const;
  LLVM_DEBUGINFOPDB_ABI PdbRaw_ImplVer getVersion() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t getSignature() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAge() const;
  LLVM_DEBUGINFOPDB_ABI codeview::GUID getGuid() const;
  LLVM_DEBUGINFOPDB_ABI uint32_t getNamedStreamMapByteSize() const;

  LLVM_DEBUGINFOPDB_ABI PdbRaw_Features getFeatures() const;
  LLVM_DEBUGINFOPDB_ABI ArrayRef<PdbRaw_FeatureSig>
  getFeatureSignatures() const;

  LLVM_DEBUGINFOPDB_ABI const NamedStreamMap &getNamedStreams() const;

  LLVM_DEBUGINFOPDB_ABI BinarySubstreamRef getNamedStreamsBuffer() const;

  LLVM_DEBUGINFOPDB_ABI Expected<uint32_t>
  getNamedStreamIndex(llvm::StringRef Name) const;
  LLVM_DEBUGINFOPDB_ABI StringMap<uint32_t> named_streams() const;

private:
  std::unique_ptr<BinaryStream> Stream;

  const InfoStreamHeader *Header;

  BinarySubstreamRef SubNamedStreams;

  std::vector<PdbRaw_FeatureSig> FeatureSignatures;
  PdbRaw_Features Features = PdbFeatureNone;

  uint32_t NamedStreamMapByteSize = 0;

  NamedStreamMap NamedStreams;
};
} // namespace pdb
} // namespace llvm

#endif
