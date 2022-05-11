#pragma once
#include "APIExport.h"

#include <typeindex>
#include <unordered_map>
#include <any>
#include <memory>

namespace mbc
{
  struct MAPBUILDER_API Payload
  {
    virtual ~Payload() = 0;
  };

  // Inline definition required as a derived class will call the destructor of its base class.
  inline Payload::~Payload() {}

  // Convenience typing
  using PayloadPtr = std::shared_ptr<Payload>;
  using PayloadTypeMap = std::unordered_map<std::type_index, PayloadPtr>;\

}