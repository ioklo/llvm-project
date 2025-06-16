//===- NativeSymbolEnumerator.h - info about enumerator values --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVESYMBOLENUMERATOR_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVESYMBOLENUMERATOR_H

#include "llvm/DebugInfo/CodeView/TypeRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBRawSymbol.h"
#include "llvm/DebugInfo/PDB/Native/NativeRawSymbol.h"
#include "llvm/DebugInfo/PDB/PDBTypes.h"

namespace llvm {

class raw_ostream;
namespace pdb {
class NativeSession;
class NativeTypeEnum;

class NativeSymbolEnumerator : public NativeRawSymbol {
public:
  LLVM_DEBUGINFOPDB_ABI
  NativeSymbolEnumerator(NativeSession &Session, SymIndexId Id,
                         const NativeTypeEnum &Parent,
                         codeview::EnumeratorRecord Record);

  LLVM_DEBUGINFOPDB_ABI ~NativeSymbolEnumerator() override;

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  LLVM_DEBUGINFOPDB_ABI SymIndexId getClassParentId() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getLexicalParentId() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getName() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_DataKind getDataKind() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_LocType getLocationType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isConstType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVolatileType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isUnalignedType() const override;
  LLVM_DEBUGINFOPDB_ABI Variant getValue() const override;

protected:
  const NativeTypeEnum &Parent;
  codeview::EnumeratorRecord Record;
};

} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_NATIVE_NATIVESYMBOLENUMERATOR_H
