//===- DIADataStream.h - DIA implementation of IPDBDataStream ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIADATASTREAM_H
#define LLVM_DEBUGINFO_PDB_DIA_DIADATASTREAM_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/DebugInfoPDBConfig.h"
#include "llvm/DebugInfo/PDB/IPDBDataStream.h"

namespace llvm {
namespace pdb {
class DIADataStream : public IPDBDataStream {
public:
  LLVM_DEBUGINFOPDB_ABI explicit DIADataStream(CComPtr<IDiaEnumDebugStreamData> DiaStreamData);

  LLVM_DEBUGINFOPDB_ABI uint32_t getRecordCount() const override;
  LLVM_DEBUGINFOPDB_ABI std::string getName() const override;
  LLVM_DEBUGINFOPDB_ABI std::optional<RecordType> getItemAtIndex(uint32_t Index) const override;
  LLVM_DEBUGINFOPDB_ABI bool getNext(RecordType &Record) override;
  LLVM_DEBUGINFOPDB_ABI void reset() override;

private:
  CComPtr<IDiaEnumDebugStreamData> StreamData;
};
}
}

#endif
