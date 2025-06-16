//===- DIASectionContrib.h - DIA Impl. of IPDBSectionContrib ------ C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIASECTIONCONTRIB_H
#define LLVM_DEBUGINFO_PDB_DIA_DIASECTIONCONTRIB_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBSectionContrib.h"

namespace llvm {
namespace pdb {
class DIASession;

class DIASectionContrib : public IPDBSectionContrib {
public:
  LLVM_DEBUGINFOPDB_ABI explicit DIASectionContrib(
      const DIASession &PDBSession, CComPtr<IDiaSectionContrib> DiaSection);

  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<PDBSymbolCompiland>
  getCompiland() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressSection() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressOffset() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getRelativeVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getLength() const override;
  LLVM_DEBUGINFOPDB_ABI bool isNotPaged() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasCode() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasCode16Bit() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasInitializedData() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasUninitializedData() const override;
  LLVM_DEBUGINFOPDB_ABI bool isRemoved() const override;
  LLVM_DEBUGINFOPDB_ABI bool hasComdat() const override;
  LLVM_DEBUGINFOPDB_ABI bool isDiscardable() const override;
  LLVM_DEBUGINFOPDB_ABI bool isNotCached() const override;
  LLVM_DEBUGINFOPDB_ABI bool isShared() const override;
  LLVM_DEBUGINFOPDB_ABI bool isExecutable() const override;
  LLVM_DEBUGINFOPDB_ABI bool isReadable() const override;
  LLVM_DEBUGINFOPDB_ABI bool isWritable() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getDataCrc32() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getRelocationsCrc32() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getCompilandId() const override;

private:
  const DIASession &Session;
  CComPtr<IDiaSectionContrib> Section;
};
} // namespace pdb
} // namespace llvm

#endif // LLVM_DEBUGINFO_PDB_DIA_DIASECTIONCONTRIB_H
