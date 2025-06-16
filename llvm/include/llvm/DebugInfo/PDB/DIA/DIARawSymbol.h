//===- DIARawSymbol.h - DIA implementation of IPDBRawSymbol ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIARAWSYMBOL_H
#define LLVM_DEBUGINFO_PDB_DIA_DIARAWSYMBOL_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBRawSymbol.h"

namespace llvm {
namespace pdb {
class DIASession;
class DIARawSymbol : public IPDBRawSymbol {
public:
  LLVM_DEBUGINFOPDB_ABI DIARawSymbol(const DIASession &PDBSession,
                                     CComPtr<IDiaSymbol> DiaSymbol);

  LLVM_DEBUGINFOPDB_ABI void
  dump(raw_ostream &OS, int Indent, PdbSymbolIdField ShowIdFields,
       PdbSymbolIdField RecurseIdFields) const override;

  CComPtr<IDiaSymbol> getDiaSymbol() const { return Symbol; }

  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findChildren(PDB_SymType Type) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findChildren(PDB_SymType Type, StringRef Name,
               PDB_NameSearchFlags Flags) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findChildrenByAddr(PDB_SymType Type, StringRef Name,
                     PDB_NameSearchFlags Flags, uint32_t Section,
                     uint32_t Offset) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findChildrenByVA(PDB_SymType Type, StringRef Name, PDB_NameSearchFlags Flags,
                   uint64_t VA) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findChildrenByRVA(PDB_SymType Type, StringRef Name, PDB_NameSearchFlags Flags,
                    uint32_t RVA) const override;

  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findInlineFramesByAddr(uint32_t Section, uint32_t Offset) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findInlineFramesByRVA(uint32_t RVA) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumSymbols>
  findInlineFramesByVA(uint64_t VA) const override;

  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumLineNumbers>
  findInlineeLines() const override;
  std::unique_ptr<IPDBEnumLineNumbers> LLVM_DEBUGINFOPDB_ABI
  findInlineeLinesByAddr(uint32_t Section, uint32_t Offset,
                         uint32_t Length) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumLineNumbers>
  findInlineeLinesByRVA(uint32_t RVA, uint32_t Length) const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumLineNumbers>
  findInlineeLinesByVA(uint64_t VA, uint32_t Length) const override;

  LLVM_DEBUGINFOPDB_ABI void
  getDataBytes(llvm::SmallVector<uint8_t, 32> &bytes) const override;
  LLVM_DEBUGINFOPDB_ABI void
  getFrontEndVersion(VersionInfo &Version) const override;
  LLVM_DEBUGINFOPDB_ABI void
  getBackEndVersion(VersionInfo &Version) const override;
  LLVM_DEBUGINFOPDB_ABI PDB_MemberAccess getAccess() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressOffset() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressSection() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAge() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getArrayIndexTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getBaseDataOffset() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getBaseDataSlot() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getBaseSymbolId() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_BuiltinType getBuiltinType() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getBitPosition() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_CallingConv getCallingConvention() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getClassParentId() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getCompilerName() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getCount() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getCountLiveRanges() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_Lang getLanguage() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getLexicalParentId() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getLibraryName() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t
  getLiveRangeStartAddressOffset() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t
  getLiveRangeStartAddressSection() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t
  getLiveRangeStartRelativeVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI codeview::RegisterId
  getLocalBasePointerRegisterId() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getLowerBoundId() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getMemorySpaceKind() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getName() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t
  getNumberOfAcceleratorPointerTags() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getNumberOfColumns() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getNumberOfModifiers() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getNumberOfRegisterIndices() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getNumberOfRows() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getObjectFileName() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getOemId() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getOemSymbolId() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getOffsetInUdt() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_Cpu getPlatform() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getRank() const override;
  LLVM_DEBUGINFOPDB_ABI codeview::RegisterId getRegisterId() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getRegisterType() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getRelativeVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getSamplerSlot() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getSignature() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getSizeInUdt() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getSlot() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getSourceFileName() const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBLineNumber>
  getSrcLineOnTypeDefn() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getStride() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getSubTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getSymbolsFileName() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getSymIndexId() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getTargetOffset() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t
  getTargetRelativeVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getTargetVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getTargetSection() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getTextureSlot() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getTimeStamp() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getToken() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getUavSlot() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getUndecoratedName() const override;
  LLVM_DEBUGINFOPDB_ABI std::string
  getUndecoratedNameEx(PDB_UndnameFlags Flags) const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getUnmodifiedTypeId() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getUpperBoundId() const override;
  LLVM_DEBUGINFOPDB_ABI Variant getValue() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getVirtualBaseDispIndex() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getVirtualBaseOffset() const override;
  LLVM_DEBUGINFOPDB_ABI SymIndexId getVirtualTableShapeId() const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<PDBSymbolTypeBuiltin>
      LLVM_DEBUGINFOPDB_ABI getVirtualBaseTableType() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_DataKind getDataKind() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_SymType getSymTag() const override;
  LLVM_DEBUGINFOPDB_ABI codeview::GUID getGuid() const override;
  LLVM_DEBUGINFOPDB_ABI int32_t getOffset() const override;
  LLVM_DEBUGINFOPDB_ABI int32_t getThisAdjust() const override;
  LLVM_DEBUGINFOPDB_ABI int32_t getVirtualBasePointerOffset() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_LocType getLocationType() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_Machine getMachineType() const override;
  LLVM_DEBUGINFOPDB_ABI codeview::ThunkOrdinal getThunkOrdinal() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getLength() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getLiveRangeLength() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_UdtType getUdtKind() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasConstructor() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasCustomCallingConvention() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasFarReturn() const override;
  LLVM_DEBUGINFOPDB_ABI bool isCode() const override;
  LLVM_DEBUGINFOPDB_ABI bool isCompilerGenerated() const override;
  LLVM_DEBUGINFOPDB_ABI bool isConstType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isEditAndContinueEnabled() const override;
  LLVM_DEBUGINFOPDB_ABI bool isFunction() const override;
  LLVM_DEBUGINFOPDB_ABI bool getAddressTaken() const override;
  LLVM_DEBUGINFOPDB_ABI bool getNoStackOrdering() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasAlloca() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasAssignmentOperator() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasCTypes() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasCastOperator() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasDebugInfo() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasEH() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasEHa() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasInlAsm() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasInlineAttribute() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasInterruptReturn() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasFramePointer() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasLongJump() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasManagedCode() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasNestedTypes() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasNoInlineAttribute() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasNoReturnAttribute() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasOptimizedCodeDebugInfo() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasOverloadedOperator() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasSEH() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasSecurityChecks() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasSetJump() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasStrictGSCheck() const override;
  LLVM_DEBUGINFOPDB_ABI bool isAcceleratorGroupSharedLocal() const override;
  LLVM_DEBUGINFOPDB_ABI bool isAcceleratorPointerTagLiveRange() const override;
  LLVM_DEBUGINFOPDB_ABI bool isAcceleratorStubFunction() const override;
  LLVM_DEBUGINFOPDB_ABI bool isAggregated() const override;
  LLVM_DEBUGINFOPDB_ABI bool isIntroVirtualFunction() const override;
  LLVM_DEBUGINFOPDB_ABI bool isCVTCIL() const override;
  LLVM_DEBUGINFOPDB_ABI bool isConstructorVirtualBase() const override;
  LLVM_DEBUGINFOPDB_ABI bool isCxxReturnUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isDataAligned() const override;
  LLVM_DEBUGINFOPDB_ABI bool isHLSLData() const override;
  LLVM_DEBUGINFOPDB_ABI bool isHotpatchable() const override;
  LLVM_DEBUGINFOPDB_ABI bool isIndirectVirtualBaseClass() const override;
  LLVM_DEBUGINFOPDB_ABI bool isInterfaceUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isIntrinsic() const override;
  LLVM_DEBUGINFOPDB_ABI bool isLTCG() const override;
  LLVM_DEBUGINFOPDB_ABI bool isLocationControlFlowDependent() const override;
  LLVM_DEBUGINFOPDB_ABI bool isMSILNetmodule() const override;
  LLVM_DEBUGINFOPDB_ABI bool isMatrixRowMajor() const override;
  LLVM_DEBUGINFOPDB_ABI bool isManagedCode() const override;
  LLVM_DEBUGINFOPDB_ABI bool isMSILCode() const override;
  LLVM_DEBUGINFOPDB_ABI bool isMultipleInheritance() const override;
  LLVM_DEBUGINFOPDB_ABI bool isNaked() const override;
  LLVM_DEBUGINFOPDB_ABI bool isNested() const override;
  LLVM_DEBUGINFOPDB_ABI bool isOptimizedAway() const override;
  LLVM_DEBUGINFOPDB_ABI bool isPacked() const override;
  LLVM_DEBUGINFOPDB_ABI bool isPointerBasedOnSymbolValue() const override;
  LLVM_DEBUGINFOPDB_ABI bool isPointerToDataMember() const override;
  LLVM_DEBUGINFOPDB_ABI bool isPointerToMemberFunction() const override;
  LLVM_DEBUGINFOPDB_ABI bool isPureVirtual() const override;
  LLVM_DEBUGINFOPDB_ABI bool isRValueReference() const override;
  LLVM_DEBUGINFOPDB_ABI bool isRefUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isReference() const override;
  LLVM_DEBUGINFOPDB_ABI bool isRestrictedType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isReturnValue() const override;
  LLVM_DEBUGINFOPDB_ABI bool isSafeBuffers() const override;
  LLVM_DEBUGINFOPDB_ABI bool isScoped() const override;
  LLVM_DEBUGINFOPDB_ABI bool isSdl() const override;
  LLVM_DEBUGINFOPDB_ABI bool isSingleInheritance() const override;
  LLVM_DEBUGINFOPDB_ABI bool isSplitted() const override;
  LLVM_DEBUGINFOPDB_ABI bool isStatic() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasPrivateSymbols() const override;
  LLVM_DEBUGINFOPDB_ABI bool isUnalignedType() const override;
  LLVM_DEBUGINFOPDB_ABI bool isUnreached() const override;
  LLVM_DEBUGINFOPDB_ABI bool isValueUdt() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVirtual() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVirtualBaseClass() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVirtualInheritance() const override;
  LLVM_DEBUGINFOPDB_ABI bool isVolatileType() const override;
  LLVM_DEBUGINFOPDB_ABI bool wasInlined() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getUnused() const override;

private:
  const DIASession &Session;
  CComPtr<IDiaSymbol> Symbol;
};
} // namespace pdb
} // namespace llvm

#endif
