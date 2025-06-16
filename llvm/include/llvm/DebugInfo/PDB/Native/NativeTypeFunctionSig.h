//===- NativeTypeFunctionSig.h - info about function signature ---*- C++-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEFUNCTIONSIG_H
#define LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEFUNCTIONSIG_H

#include "llvm/DebugInfo/CodeView/TypeIndex.h"
#include "llvm/DebugInfo/CodeView/TypeRecord.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBRawSymbol.h"
#include "llvm/DebugInfo/PDB/Native/NativeRawSymbol.h"
#include "llvm/DebugInfo/PDB/PDBTypes.h"

namespace llvm {
namespace pdb {

class NativeTypeFunctionSig : public NativeRawSymbol {
protected:
  LLVM_DEBUGINFOPDB_ABI void initialize() override;

public:
  LLVM_DEBUGINFOPDB_ABI NativeTypeFunctionSig(NativeSession &Session,
                                              SymIndexId Id,
                                              codeview::TypeIndex TI,
                                              codeview::ProcedureRecord Proc);

  LLVM_DEBUGINFOPDB_ABI
  NativeTypeFunctionSig(NativeSession &Session, SymIndexId Id,
                        codeview::TypeIndex TI,
                        codeview::MemberFunctionRecord MemberFunc);

  LLVM_DEBUGINFOPDB_ABI ~NativeTypeFunctionSig() override;

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findChildren(PDB_SymType Type) const override;

  LLVM_DEBUGINFOPDB_ABI SymIndexId getClassParentId() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_CallingConv getCallingConvention() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getCount() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI int32_t getThisAdjust() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasConstructor() const override;
  LLVM_DEBUGINFOPDB_ABI bool isConstType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isConstructorVirtualBase() const override;
  LLVM_DEBUGINFOPDB_ABI bool isCxxReturnUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isUnalignedType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVolatileType() const override;

private:
  void initializeArgList(codeview::TypeIndex ArgListTI);

  union {
    codeview::MemberFunctionRecord MemberFunc;
    codeview::ProcedureRecord Proc;
  };

  SymIndexId ClassParentId = 0;
  codeview::TypeIndex Index;
  codeview::ArgListRecord ArgList;
  bool IsMemberFunction = false;
};

} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_NATIVE_NATIVETYPEFUNCTIONSIG_H
