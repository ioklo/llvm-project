//===- NativeTypePointer.h - info about pointer type -------------*- C++-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEPOINTER_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEPOINTER_H

#include "llvm/DebugInfo/CodeView/TypeIndex.h"
#include "llvm/DebugInfo/CodeView/TypeRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBRawSymbol.h"
#include "llvm/DebugInfo/PDB/Native/NativeRawSymbol.h"
#include "llvm/DebugInfo/PDB/PDBTypes.h"

namespace llvm {
namespace pdb {

class NativeTypePointer : public NativeRawSymbol {
public:
  // Create a pointer record for a simple type.
  LLVM_DEBUGINFOPDB_ABI NativeTypePointer(NativeSession &Session, SymIndexId Id,
                                          codeview::TypeIndex TI);

  // Create a pointer record for a non-simple type.
  LLVM_DEBUGINFOPDB_ABI NativeTypePointer(NativeSession &Session, SymIndexId Id,
                                          codeview::TypeIndex TI,
                                          codeview::PointerRecord PR);
  LLVM_DEBUGINFOPDB_ABI ~NativeTypePointer() override;

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  LLVM_DEBUGINFOPDB_ABI SymIndexId getClassParentId() const override;
  LLVM_DEBUGINFOPDB_ABI bool isConstType() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getLength() const override;
  LLVM_DEBUGINFOPDB_ABI bool isReference() const override;
  LLVM_DEBUGINFOPDB_ABI bool isRValueReference() const override;
  LLVM_DEBUGINFOPDB_ABI bool isPointerToDataMember() const override;
  LLVM_DEBUGINFOPDB_ABI bool isPointerToMemberFunction() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI bool isRestrictedType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVolatileType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isUnalignedType() const override;

  LLVM_DEBUGINFOPDB_ABI bool isSingleInheritance() const override;
  LLVM_DEBUGINFOPDB_ABI bool isMultipleInheritance() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVirtualInheritance() const override;

protected:
  LLVM_DEBUGINFOPDB_ABI bool isMemberPointer() const;
  codeview::TypeIndex TI;
  std::optional<codeview::PointerRecord> Record;
};

} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEPOINTER_H
