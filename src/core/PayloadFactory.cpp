#include "PayloadFactory.h"

namespace mbc
{
  PayloadPtr PayloadFactory::createPayload(std::type_index typeIndex)
  {
    // Return nullptr if payload type not registered
    if (payloads_.count(typeIndex) == 0)
      return nullptr;

    // Executes lambda function created by registerPayload method
    // and returns pointer to newly created Payload
    return payloads_[typeIndex]();
  }
}