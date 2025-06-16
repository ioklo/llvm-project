//===- NativePublicSymbol.h - info about public symbols ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVEPUBLICSYMBOL_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVEPUBLICSYMBOL_H

#include "llvm/DebugInfo/CodeView/SymbolRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/Native/NativeRawSymbol.h"

namespace llvm {

class raw_ostream;
namespace pdb {
class NativeSession;

class NativePublicSymbol : public NativeRawSymbol {
public:
  LLVM_DEBUGINFOPDB_ABI NativePublicSymbol(NativeSession &Session,
                                           SymIndexId Id,
                                           const codeview::PublicSym32 &Sym);

  LLVM_DEBUGINFOPDB_ABI ~NativePublicSymbol() override;

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressOffset() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressSection() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getName() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getRelativeVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getVirtualAddress() const override;

protected:
  const codeview::PublicSym32 Sym;
};

} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_NATIVE_NATIVEPUBLICSYMBOL_H
