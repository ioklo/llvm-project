//==- NativeEnumGlobals.h - Native Global Enumerator impl --------*- C++ -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVEENUMGLOBALS_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVEENUMGLOBALS_H

#include "llvm/DebugInfo/CodeView/CodeView.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBEnumChildren.h"
#include "llvm/DebugInfo/PDB/PDBSymbol.h"

#include <vector>

namespace llvm {
namespace pdb {

class NativeSession;

class NativeEnumGlobals : public IPDBEnumChildren<PDBSymbol> {
public:
  LLVM_DEBUGINFOPDB_ABI
  NativeEnumGlobals(NativeSession &Session,
                    std::vector<codeview::SymbolKind> Kinds);

  LLVM_DEBUGINFOPDB_ABI uint32_t getChildCount() const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<PDBSymbol>
  getChildAtIndex(uint32_t Index) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<PDBSymbol> getNext() override;
  LLVM_DEBUGINFOPDB_ABI void reset() override;

private:
  std::vector<uint32_t> MatchOffsets;
  uint32_t Index;
  NativeSession &Session;
};

} // namespace pdb
} // namespace llvm

#endif
