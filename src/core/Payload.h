#pragma once
#ifdef MAPBUILDER_EXPORTS
#define MAPBUILDER_API __declspec(dllexport)
#else
#define MAPBUILDER_API __declspec(dllimport)
#endif

#include <typeindex>
#include <unordered_map>
#include <any>
#include <memory>

namespace mbc
{
  using PayloadValues = std::unordered_map<std::string, std::any>;

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