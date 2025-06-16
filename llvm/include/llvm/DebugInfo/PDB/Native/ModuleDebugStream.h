//===- ModuleDebugStream.h - PDB Module Info Stream Access ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_MODULEDEBUGSTREAM_H
#define LLVM_DEBUGINFO_PDB_NATIVE_MODULEDEBUGSTREAM_H

#include "llvm/ADT/iterator_range.h"
#include "llvm/DebugInfo/CodeView/CVRecord.h"
#include "llvm/DebugInfo/CodeView/DebugSubsectionRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/Native/DbiModuleDescriptor.h"
#include "llvm/Support/BinaryStreamRef.h"
#include "llvm/Support/Error.h"
#include <cstdint>
#include <memory>

namespace llvm {
class BinaryStreamReader;
namespace codeview {
class DebugChecksumsSubsectionRef;
}
namespace msf {
class MappedBlockStream;
}
namespace pdb {

class ModuleDebugStreamRef {
  using DebugSubsectionIterator = codeview::DebugSubsectionArray::Iterator;

public:
  LLVM_DEBUGINFOPDB_ABI
  ModuleDebugStreamRef(const DbiModuleDescriptor &Module,
                       std::unique_ptr<msf::MappedBlockStream> Stream);
  ModuleDebugStreamRef(ModuleDebugStreamRef &&Other) = default;
  ModuleDebugStreamRef(const ModuleDebugStreamRef &Other) = default;
  LLVM_DEBUGINFOPDB_ABI ~ModuleDebugStreamRef();

  LLVM_DEBUGINFOPDB_ABI Error reload();

  uint32_t signature() const { return Signature; }

  iterator_range<codeview::CVSymbolArray::Iterator>
      LLVM_DEBUGINFOPDB_ABI symbols(bool *HadError) const;

  const codeview::CVSymbolArray &getSymbolArray() const { return SymbolArray; }
  const codeview::CVSymbolArray LLVM_DEBUGINFOPDB_ABI
  getSymbolArrayForScope(uint32_t ScopeBegin) const;

  LLVM_DEBUGINFOPDB_ABI BinarySubstreamRef getSymbolsSubstream() const;
  LLVM_DEBUGINFOPDB_ABI BinarySubstreamRef getC11LinesSubstream() const;
  LLVM_DEBUGINFOPDB_ABI BinarySubstreamRef getC13LinesSubstream() const;
  LLVM_DEBUGINFOPDB_ABI BinarySubstreamRef getGlobalRefsSubstream() const;

  ModuleDebugStreamRef &operator=(ModuleDebugStreamRef &&Other) = delete;

  LLVM_DEBUGINFOPDB_ABI codeview::CVSymbol
  readSymbolAtOffset(uint32_t Offset) const;

  LLVM_DEBUGINFOPDB_ABI iterator_range<DebugSubsectionIterator>
  subsections() const;
  codeview::DebugSubsectionArray getSubsectionsArray() const {
    return Subsections;
  }

  LLVM_DEBUGINFOPDB_ABI bool hasDebugSubsections() const;

  LLVM_DEBUGINFOPDB_ABI Error commit();

  LLVM_DEBUGINFOPDB_ABI Expected<codeview::DebugChecksumsSubsectionRef>
  findChecksumsSubsection() const;

private:
  Error reloadSerialize(BinaryStreamReader &Reader);

  DbiModuleDescriptor Mod;

  uint32_t Signature;

  std::shared_ptr<msf::MappedBlockStream> Stream;

  codeview::CVSymbolArray SymbolArray;

  BinarySubstreamRef SymbolsSubstream;
  BinarySubstreamRef C11LinesSubstream;
  BinarySubstreamRef C13LinesSubstream;
  BinarySubstreamRef GlobalRefsSubstream;

  codeview::DebugSubsectionArray Subsections;
};

} // end namespace pdb
} // end namespace llvm

#endif // LLVM_DEBUGINFO_PDB_NATIVE_MODULEDEBUGSTREAM_H
