//==- DIAEnumSourceFiles.h - DIA Source File Enumerator impl -----*- C++ -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIAENUMSOURCEFILES_H
#define LLVM_DEBUGINFO_PDB_DIA_DIAENUMSOURCEFILES_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBEnumChildren.h"
#include "llvm/DebugInfo/PDB/IPDBSourceFile.h"

namespace llvm {
namespace pdb {
class DIASession;

class DIAEnumSourceFiles : public IPDBEnumChildren<IPDBSourceFile> {
public:
  LLVM_DEBUGINFOPDB_ABI explicit DIAEnumSourceFiles(
      const DIASession &PDBSession, CComPtr<IDiaEnumSourceFiles> DiaEnumerator);

  LLVM_DEBUGINFOPDB_ABI uint32_t getChildCount() const override;
  LLVM_DEBUGINFOPDB_ABI ChildTypePtr
  getChildAtIndex(uint32_t Index) const override;
  LLVM_DEBUGINFOPDB_ABI ChildTypePtr getNext() override;
  LLVM_DEBUGINFOPDB_ABI void reset() override;

private:
  const DIASession &Session;
  CComPtr<IDiaEnumSourceFiles> Enumerator;
};
} // namespace pdb
} // namespace llvm

#endif
