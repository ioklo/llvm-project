//===- NativeCompilandSymbol.h - native impl for compiland syms -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVECOMPILANDSYMBOL_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVECOMPILANDSYMBOL_H

#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/Native/DbiModuleDescriptor.h"
#include "llvm/DebugInfo/PDB/Native/NativeRawSymbol.h"

namespace llvm {
namespace pdb {

class NativeCompilandSymbol : public NativeRawSymbol {
public:
  LLVM_DEBUGINFOPDB_ABI NativeCompilandSymbol(NativeSession &Session,
                                              SymIndexId SymbolId,
                                              DbiModuleDescriptor MI);

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  LLVM_DEBUGINFOPDB_ABI PDB_SymType getSymTag() const override;
  LLVM_DEBUGINFOPDB_ABI bool isEditAndContinueEnabled() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getLexicalParentId() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getLibraryName() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getName() const override;

private:
  DbiModuleDescriptor Module;
};

} // namespace pdb
} // namespace llvm

#endif
