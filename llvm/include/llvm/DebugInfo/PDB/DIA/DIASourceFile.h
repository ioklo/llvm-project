//===- DIASourceFile.h - DIA implementation of IPDBSourceFile ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIASOURCEFILE_H
#define LLVM_DEBUGINFO_PDB_DIA_DIASOURCEFILE_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBSourceFile.h"

namespace llvm {
namespace pdb {
class DIASession;

class DIASourceFile : public IPDBSourceFile {
public:
  LLVM_DEBUGINFOPDB_ABI explicit DIASourceFile(
      const DIASession &Session, CComPtr<IDiaSourceFile> DiaSourceFile);

  LLVM_DEBUGINFOPDB_ABI std::string getFileName() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getUniqueId() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getChecksum() const override;
  LLVM_DEBUGINFOPDB_ABI PDB_Checksum getChecksumType() const override;
  LLVM_DEBUGINFOPDB_ABI std::unique_ptr<IPDBEnumChildren<PDBSymbolCompiland>>
  getCompilands() const override;

  CComPtr<IDiaSourceFile> getDiaFile() const { return SourceFile; }

private:
  const DIASession &Session;
  CComPtr<IDiaSourceFile> SourceFile;
};
} // namespace pdb
} // namespace llvm

#endif
