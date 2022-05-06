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

  private:
    std::vector<ModulePtr> modules_[NUM_STAGES];

    PayloadFactory payloadFactory_;

    PayloadTypeMap payloads_;

  };
}
