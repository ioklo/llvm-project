//===- PDBSymDumper.h - base interface for PDB symbol dumper *- C++ -----*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_PDBSYMDUMPER_H
#define LLVM_DEBUGINFO_PDB_PDBSYMDUMPER_H

#include "PDBTypes.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"

namespace llvm {

class raw_ostream;
namespace pdb {

class PDBSymDumper {
public:
  LLVM_DEBUGINFOPDB_ABI PDBSymDumper(bool ShouldRequireImpl);
  LLVM_DEBUGINFOPDB_ABI virtual ~PDBSymDumper();

  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolAnnotation &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolBlock &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolCompiland &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void
  dump(const PDBSymbolCompilandDetails &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolCompilandEnv &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolCustom &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolData &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolExe &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolFunc &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolFuncDebugEnd &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void
  dump(const PDBSymbolFuncDebugStart &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolLabel &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolPublicSymbol &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolThunk &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeArray &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeBaseClass &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeBuiltin &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeCustom &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeDimension &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeEnum &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeFriend &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void
  dump(const PDBSymbolTypeFunctionArg &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void
  dump(const PDBSymbolTypeFunctionSig &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeManaged &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypePointer &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeTypedef &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeUDT &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolTypeVTable &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void
  dump(const PDBSymbolTypeVTableShape &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void dump(const PDBSymbolUnknown &Symbol);
  LLVM_DEBUGINFOPDB_ABI virtual void
  dump(const PDBSymbolUsingNamespace &Symbol);

  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeArray &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeBaseClass &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeBuiltin &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeCustom &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeDimension &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeEnum &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeFriend &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeFunctionArg &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeFunctionSig &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeManaged &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypePointer &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeTypedef &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void dumpRight(const PDBSymbolTypeUDT &Symbol) {
  }
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeVTable &Symbol) {}
  LLVM_DEBUGINFOPDB_ABI virtual void
  dumpRight(const PDBSymbolTypeVTableShape &Symbol) {}

private:
  bool RequireImpl;
};
} // namespace pdb
} // namespace llvm

#endif
