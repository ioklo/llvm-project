//==- NativeEnumModules.h - Native Module Enumerator impl --------*- C++ -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVEENUMMODULES_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVEENUMMODULES_H

#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBEnumChildren.h"
#include "llvm/DebugInfo/PDB/PDBSymbol.h"
namespace llvm {
namespace pdb {

class NativeSession;

class NativeEnumModules : public IPDBEnumChildren<PDBSymbol> {
public:
  LLVM_DEBUGINFOPDB_ABI NativeEnumModules(NativeSession &Session,
                                          uint32_t Index = 0);

  LLVM_DEBUGINFOPDB_ABI uint32_t getChildCount() const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<PDBSymbol>
  getChildAtIndex(uint32_t Index) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<PDBSymbol> getNext() override;
  LLVM_DEBUGINFOPDB_ABI void reset() override;

private:
  NativeSession &Session;
  uint32_t Index;
};
} // namespace pdb
} // namespace llvm

#endif
