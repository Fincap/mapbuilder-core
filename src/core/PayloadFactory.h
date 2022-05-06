#pragma once
#include <typeindex>
#include <unordered_map>
#include <memory>
#include <type_traits>

#include "Payload.h"

namespace mbc
{
  class PayloadFactory
  {
  public:
    // Convenience typing
    using PayloadCreatePtr = PayloadPtr(*)();

    template <typename T>
    void registerPayload();   

    // Returns pointer to a new instance of Payload from type_index
    PayloadPtr createPayload(std::type_index);

  private:
    std::unordered_map<std::type_index, PayloadCreatePtr> payloads_;
  };

  template <typename T>
  inline void PayloadFactory::registerPayload()
  {
    // T must derive fom Payload
    static_assert(std::is_convertible<T*, Payload*>::value, "Registered class must publicly inherit Payload");

    // Map key is set to the type_index of the registered payload class
    // Map value is a lambda function that returns a shared pointer to
    // a new instance of the payload class T.
    payloads_[std::type_index(typeid(T))] = []() -> PayloadPtr
    { return std::make_shared<T>(); };
  }
}