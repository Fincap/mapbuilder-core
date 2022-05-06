#pragma once
#include <typeindex>
#include <unordered_map>
#include <any>
#include <memory>

namespace mbc
{
  struct Payload
  {
    virtual ~Payload() = 0;

    // Returns map of dervied class' payload values
    virtual PayloadValues unpack() = 0;
  };

  // Inline definition required as a derived class will call the destructor of its base class.
  inline Payload::~Payload() {}

  // Convenience typing
  using PayloadPtr = std::shared_ptr<Payload>;
  using PayloadTypeMap = std::unordered_map<std::type_index, PayloadPtr>;
  using PayloadValues = std::unordered_map<std::string, std::any>;
}