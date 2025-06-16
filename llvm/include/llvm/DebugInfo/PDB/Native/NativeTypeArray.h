//===- NativeTypeArray.h ------------------------------------------ C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEARRAY_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEARRAY_H

#include "llvm/DebugInfo/CodeView/TypeRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/Native/NativeRawSymbol.h"
#include "llvm/DebugInfo/PDB/PDBTypes.h"

namespace llvm {
namespace pdb {

class NativeSession;

class NativeTypeArray : public NativeRawSymbol {
public:
  LLVM_DEBUGINFOPDB_ABI NativeTypeArray(NativeSession &Session, SymIndexId Id,
                                        codeview::TypeIndex TI,
                                        codeview::ArrayRecord Record);
  LLVM_DEBUGINFOPDB_ABI ~NativeTypeArray() override;

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  LLVM_DEBUGINFOPDB_ABI SymIndexId getArrayIndexTypeId() const override;

  LLVM_DEBUGINFOPDB_ABI bool isConstType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isUnalignedType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVolatileType() const override;

  LLVM_DEBUGINFOPDB_ABI uint32_t getCount() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getLength() const override;

protected:
  codeview::ArrayRecord Record;
  codeview::TypeIndex Index;
};

} // namespace pdb
} // namespace llvm

#endif
