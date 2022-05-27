#pragma once

#include <typeindex>
#include <unordered_map>
#include <any>
#include <memory>

#include "MapBuilderCore\APIExport.h"

namespace mbc
{
  /*
  Interface that all Payloads must implement. Does not define any shared member
  functions or attributes.
  */
  struct MAPBUILDER_API Payload
  {
    virtual ~Payload() = 0;

    // Convenience typing - shared_ptr to Payload.
    using Ptr = std::shared_ptr<Payload>;
  };

  // Inline definition required as a derived class will call the destructor of its base class.
  inline Payload::~Payload() {}

  // Convenience typing - Unordered map of <type_index, shared_ptr to Payload>.
  using PayloadTypeMap = std::unordered_map<std::type_index, Payload::Ptr>;

}