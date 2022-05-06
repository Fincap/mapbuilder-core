#pragma once
#include <vector>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <iostream>

#include "Module.h"
#include "Payload.h"
#include "PayloadFactory.h"

namespace mbc
{
  class Pipeline
  {
  public:    
    bool execute();
    bool addModule(ModulePtr);

    template <typename T>
    void registerPayload();

  private:
    std::vector<ModulePtr> modules_[NUM_STAGES];

    PayloadFactory payloadFactory_;

    PayloadTypeMap payloads_;

  };

  template <typename T>
  inline void Pipeline::registerPayload()   // Payloads must be registered
  {
    payloadFactory_.registerPayload<T>();
  }
}
