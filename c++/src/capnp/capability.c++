// Copyright (c) 2013, Kenton Varda <temporal@gmail.com>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "capability.h"
#include <kj/debug.h>

namespace capnp {

kj::Promise<void> Capability::Server::internalUnimplemented(
    const char* actualInterfaceName, uint64_t requestedTypeId) {
  KJ_FAIL_REQUIRE("Requested interface not implemented.", actualInterfaceName, requestedTypeId) {
    // Recoverable exception will be caught by promise framework.
    return kj::READY_NOW;
  }
}

kj::Promise<void> Capability::Server::internalUnimplemented(
    const char* interfaceName, uint64_t typeId, uint16_t methodId) {
  KJ_FAIL_REQUIRE("Method not implemented.", interfaceName, typeId, methodId) {
    // Recoverable exception will be caught by promise framework.
    return kj::READY_NOW;
  }
}

kj::Promise<void> Capability::Server::internalUnimplemented(
    const char* interfaceName, const char* methodName, uint64_t typeId, uint16_t methodId) {
  KJ_FAIL_REQUIRE("Method not implemented.", interfaceName, typeId, methodName, methodId) {
    // Recoverable exception will be caught by promise framework.
    return kj::READY_NOW;
  }
}

TypelessResults::Pipeline TypelessResults::Pipeline::getPointerField(
    uint16_t pointerIndex) const {
  auto newOps = kj::heapArray<PipelineOp>(ops.size() + 1);
  for (auto i: kj::indices(ops)) {
    newOps[i] = ops[i];
  }
  auto& newOp = newOps[ops.size()];
  newOp.type = PipelineOp::GET_POINTER_FIELD;
  newOp.pointerIndex = pointerIndex;

  return Pipeline(hook->addRef(), kj::mv(newOps));
}

}  // namespace capnp
