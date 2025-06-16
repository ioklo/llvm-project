//===--------------- OrcError.h - Orc Error Types ---------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Define an error category, error codes, and helper utilities for Orc.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_EXECUTIONENGINE_ORC_SHARED_ORCERROR_H
#define LLVM_EXECUTIONENGINE_ORC_SHARED_ORCERROR_H

#include "llvm/ExecutionEngine/Orc/Shared/OrcSharedConfig.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/raw_ostream.h"
#include <string>
#include <system_error>

namespace llvm {
namespace orc {

enum class OrcErrorCode : int {
  // RPC Errors
  UnknownORCError = 1,
  DuplicateDefinition,
  JITSymbolNotFound,
  RemoteAllocatorDoesNotExist,
  RemoteAllocatorIdAlreadyInUse,
  RemoteMProtectAddrUnrecognized,
  RemoteIndirectStubsOwnerDoesNotExist,
  RemoteIndirectStubsOwnerIdAlreadyInUse,
  RPCConnectionClosed,
  RPCCouldNotNegotiateFunction,
  RPCResponseAbandoned,
  UnexpectedRPCCall,
  UnexpectedRPCResponse,
  UnknownErrorCodeFromRemote,
  UnknownResourceHandle,
  MissingSymbolDefinitions,
  UnexpectedSymbolDefinitions,
};

LLVM_ORCSHARED_ABI std::error_code orcError(OrcErrorCode ErrCode);

class DuplicateDefinition : public ErrorInfo<DuplicateDefinition> {
public:
  LLVM_ORCSHARED_ABI static char ID;

  LLVM_ORCSHARED_ABI DuplicateDefinition(std::string SymbolName);
  LLVM_ORCSHARED_ABI std::error_code convertToErrorCode() const override;
  LLVM_ORCSHARED_ABI void log(raw_ostream &OS) const override;
  LLVM_ORCSHARED_ABI const std::string &getSymbolName() const;

private:
  std::string SymbolName;
};

class JITSymbolNotFound : public ErrorInfo<JITSymbolNotFound> {
public:
  LLVM_ORCSHARED_ABI static char ID;

  LLVM_ORCSHARED_ABI JITSymbolNotFound(std::string SymbolName);
  LLVM_ORCSHARED_ABI std::error_code convertToErrorCode() const override;
  LLVM_ORCSHARED_ABI void log(raw_ostream &OS) const override;
  LLVM_ORCSHARED_ABI const std::string &getSymbolName() const;

private:
  std::string SymbolName;
};

} // End namespace orc.
} // End namespace llvm.

#endif // LLVM_EXECUTIONENGINE_ORC_SHARED_ORCERROR_H
