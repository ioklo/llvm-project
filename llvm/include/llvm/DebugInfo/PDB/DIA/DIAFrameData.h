//===- DIAFrameData.h - DIA Impl. of IPDBFrameData ---------------- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIAFRAMEDATA_H
#define LLVM_DEBUGINFO_PDB_DIA_DIAFRAMEDATA_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBFrameData.h"

namespace llvm {
namespace pdb {

class DIASession;

class DIAFrameData : public IPDBFrameData {
public:
  LLVM_DEBUGINFOPDB_ABI explicit DIAFrameData(
      CComPtr<IDiaFrameData> DiaFrameData);

  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressOffset() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getAddressSection() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getLengthBlock() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getProgram() const override;
  LLVM_DEBUGINFOPDB_ABI uint32_t getRelativeVirtualAddress() const override;
  LLVM_DEBUGINFOPDB_ABI uint64_t getVirtualAddress() const override;

private:
  CComPtr<IDiaFrameData> FrameData;
};

} // namespace pdb
} // namespace llvm

#endif
