#include "PayloadFactory.h"

namespace mbc
{
  PayloadPtr PayloadFactory::createPayload(std::type_index typeIndex)
  {
    // Return nullptr if payload type not registered
    if (!hasPayload(typeIndex))
      return nullptr;

    // Executes lambda function created by registerPayload method
    // and returns pointer to newly created Payload
    return payloads_[typeIndex]();
  }

  bool PayloadFactory::hasPayload(std::type_index typeIndex)
  {
    return payloads_.count(typeIndex) != 0;
  }

}