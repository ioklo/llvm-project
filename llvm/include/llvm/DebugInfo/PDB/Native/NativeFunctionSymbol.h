//===- NativeFunctionSymbol.h - info about function symbols -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVEFUNCTIONSYMBOL_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVEFUNCTIONSYMBOL_H

#include "llvm/DebugInfo/CodeView/SymbolRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBRawSymbol.h"
#include "llvm/DebugInfo/PDB/Native/NativeRawSymbol.h"
#include "llvm/DebugInfo/PDB/PDBTypes.h"

namespace llvm {
class raw_ostream;
namespace pdb {

class NativeSession;

class NativeFunctionSymbol : public NativeRawSymbol {
public:
  LLVM_DEBUGINFOPDB_ABI NativeFunctionSymbol(NativeSession &Session,
                                             SymIndexId Id,
                                             const codeview::ProcSym &Sym,
                                             uint32_t RecordOffset);

  LLVM_DEBUGINFOPDB_ABI ~NativeFunctionSymbol() override;

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressOffset() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressSection() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getName() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getLength() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getRelativeVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getVirtualAddress() const override;
  std::unique_ptr<IPDBEnumSymbols>
      LLVM_DEBUGINFOPDB_ABI findInlineFramesByVA(uint64_t VA) const override;

protected:
  const codeview::ProcSym Sym;
  uint32_t RecordOffset = 0;
};

} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_NATIVE_NATIVEFUNCTIONSYMBOL_H
