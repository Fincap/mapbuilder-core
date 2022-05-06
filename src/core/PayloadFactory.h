#pragma once
#include <typeindex>
#include <unordered_map>
#include <memory>

#include "Payload.h"

namespace mbc
{
  class PayloadFactory
  {
  public:
    using PayloadCreatePtr = PayloadPtr(*)();

    void registerPayload(std::type_index, PayloadCreatePtr);
    PayloadPtr createPayload(std::type_index);

  private:
    std::unordered_map<std::type_index, PayloadCreatePtr> payloads_;
  };
}
