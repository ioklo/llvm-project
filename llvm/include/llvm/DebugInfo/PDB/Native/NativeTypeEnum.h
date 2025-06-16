//===- NativeTypeEnum.h - info about enum type ------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEENUM_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEENUM_H

#include "llvm/DebugInfo/CodeView/TypeIndex.h"
#include "llvm/DebugInfo/CodeView/TypeRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBRawSymbol.h"
#include "llvm/DebugInfo/PDB/Native/NativeRawSymbol.h"
#include "llvm/DebugInfo/PDB/PDBTypes.h"

namespace llvm {
class raw_ostream;
namespace pdb {

class NativeTypeBuiltin;

class NativeTypeEnum : public NativeRawSymbol {
public:
  LLVM_DEBUGINFOPDB_ABI NativeTypeEnum(NativeSession &Session, SymIndexId Id,
                                       codeview::TypeIndex TI,
                                       codeview::EnumRecord Record);

  LLVM_DEBUGINFOPDB_ABI NativeTypeEnum(NativeSession &Session, SymIndexId Id,
                                       NativeTypeEnum &UnmodifiedType,
                                       codeview::ModifierRecord Modifier);
  LLVM_DEBUGINFOPDB_ABI ~NativeTypeEnum() override;

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findChildren(PDB_SymType Type) const override;

  LLVM_DEBUGINFOPDB_ABI PDB_BuiltinType getBuiltinType() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_SymType getSymTag() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getUnmodifiedTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasConstructor() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasAssignmentOperator() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasCastOperator() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getLength() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getName() const override;
  LLVM_DEBUGINFOPDB_ABI bool isConstType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVolatileType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isUnalignedType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isNested() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasOverloadedOperator() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasNestedTypes() const override;
  LLVM_DEBUGINFOPDB_ABI bool isIntrinsic() const override;
  LLVM_DEBUGINFOPDB_ABI bool isPacked() const override;
  LLVM_DEBUGINFOPDB_ABI bool isScoped() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI bool isRefUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isValueUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isInterfaceUdt() const override;

  LLVM_DEBUGINFOPDB_ABI const NativeTypeBuiltin &
  getUnderlyingBuiltinType() const;
  const codeview::EnumRecord &getEnumRecord() const { return *Record; }

protected:
  codeview::TypeIndex Index;
  std::optional<codeview::EnumRecord> Record;
  NativeTypeEnum *UnmodifiedType = nullptr;
  std::optional<codeview::ModifierRecord> Modifiers;
};

} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEENUM_H
