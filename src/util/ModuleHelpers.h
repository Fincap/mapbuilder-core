#pragma once
#include <memory>

#include "core\Payload.h"

namespace mbc::util
{
  /*
  Returns a shared_ptr to T in a PayloadTypeMap, where T is a type of Module.
  */
  template <typename T>
  std::shared_ptr<T> getPtrToPayload(const PayloadTypeMap& payloads);

  template<typename T>
  inline std::shared_ptr<T> getPtrToPayload(const PayloadTypeMap& payloads)
  {
    // T must derive fom Payload
    static_assert(std::is_convertible<T*, Payload*>::value, "Type must publicly inherit Payload");

    // Create generic pointer to the payload within the payloads map
    auto payload = payloads.at(std::type_index(typeid(T)));

    // Cast generic pointer to type T and return
    return std::dynamic_pointer_cast<T>(payload);
  }
}