//===- NativeTypeUDT.h - info about class/struct type ------------*- C++-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEUDT_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEUDT_H

#include "llvm/DebugInfo/CodeView/TypeIndex.h"
#include "llvm/DebugInfo/CodeView/TypeRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBRawSymbol.h"
#include "llvm/DebugInfo/PDB/Native/NativeRawSymbol.h"
#include "llvm/DebugInfo/PDB/PDBTypes.h"

namespace llvm {

class raw_ostream;
namespace pdb {
class NativeSession;

class NativeTypeUDT : public NativeRawSymbol {
public:
  LLVM_DEBUGINFOPDB_ABI NativeTypeUDT(NativeSession &Session, SymIndexId Id,
                                      codeview::TypeIndex TI,
                                      codeview::ClassRecord Class);

  LLVM_DEBUGINFOPDB_ABI NativeTypeUDT(NativeSession &Session, SymIndexId Id,
                                      codeview::TypeIndex TI,
                                      codeview::UnionRecord Union);

  LLVM_DEBUGINFOPDB_ABI NativeTypeUDT(NativeSession &Session, SymIndexId Id,
                                      NativeTypeUDT &UnmodifiedType,
                                      codeview::ModifierRecord Modifier);

  LLVM_DEBUGINFOPDB_ABI ~NativeTypeUDT() override;

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  LLVM_DEBUGINFOPDB_ABI std::string getName() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getLexicalParentId() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getUnmodifiedTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getVirtualTableShapeId() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getLength() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_UdtType getUdtKind() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasConstructor() const override;
  LLVM_DEBUGINFOPDB_ABI bool isConstType() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasAssignmentOperator() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasCastOperator() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasNestedTypes() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasOverloadedOperator() const override;
  LLVM_DEBUGINFOPDB_ABI bool isInterfaceUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isIntrinsic() const override;
  LLVM_DEBUGINFOPDB_ABI bool isNested() const override;
  LLVM_DEBUGINFOPDB_ABI bool isPacked() const override;
  LLVM_DEBUGINFOPDB_ABI bool isRefUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isScoped() const override;
  LLVM_DEBUGINFOPDB_ABI bool isValueUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isUnalignedType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVolatileType() const override;

protected:
  codeview::TypeIndex Index;

  std::optional<codeview::ClassRecord> Class;
  std::optional<codeview::UnionRecord> Union;
  NativeTypeUDT *UnmodifiedType = nullptr;
  codeview::TagRecord *Tag = nullptr;
  std::optional<codeview::ModifierRecord> Modifiers;
};

} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEUDT_H
