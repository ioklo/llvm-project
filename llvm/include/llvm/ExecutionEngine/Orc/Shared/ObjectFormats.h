//===------ ObjectFormats.h - Object format details for ORC -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// ORC-specific object format details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_EXECUTIONENGINE_ORC_SHARED_OBJECTFORMATS_H
#define LLVM_EXECUTIONENGINE_ORC_SHARED_OBJECTFORMATS_H

#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/Orc/Shared/MachOObjectFormat.h"
#include "llvm/ExecutionEngine/Orc/Shared/OrcSharedConfig.h"

namespace llvm {
namespace orc {

// ELF section names.
LLVM_ORCSHARED_ABI extern StringRef ELFEHFrameSectionName;

LLVM_ORCSHARED_ABI extern StringRef ELFInitArrayFuncSectionName;
LLVM_ORCSHARED_ABI extern StringRef ELFInitFuncSectionName;
LLVM_ORCSHARED_ABI extern StringRef ELFFiniArrayFuncSectionName;
LLVM_ORCSHARED_ABI extern StringRef ELFFiniFuncSectionName;
LLVM_ORCSHARED_ABI extern StringRef ELFCtorArrayFuncSectionName;
LLVM_ORCSHARED_ABI extern StringRef ELFDtorArrayFuncSectionName;

LLVM_ORCSHARED_ABI extern StringRef ELFInitSectionNames[3];

LLVM_ORCSHARED_ABI extern StringRef ELFThreadBSSSectionName;
LLVM_ORCSHARED_ABI extern StringRef ELFThreadDataSectionName;

LLVM_ORCSHARED_ABI bool isELFInitializerSection(StringRef SecName);

LLVM_ORCSHARED_ABI bool isCOFFInitializerSection(StringRef Name);

} // end namespace orc
} // end namespace llvm

#endif // LLVM_EXECUTIONENGINE_ORC_SHARED_OBJECTFORMATS_H
