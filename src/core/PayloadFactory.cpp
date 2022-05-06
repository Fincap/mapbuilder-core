#include "PayloadFactory.h"

namespace mbc
{
  void PayloadFactory::registerPayload(std::type_index typeIndex, PayloadCreatePtr payloadCreatePtr)
  {
    payloads_[typeIndex] = payloadCreatePtr;
  }

  PayloadPtr PayloadFactory::createPayload(std::type_index typeIndex)
  {
    PayloadPtr newPayload = payloads_[typeIndex]();
    return newPayload;
  }
}