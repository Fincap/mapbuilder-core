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
    // Modules by stage - TODO combine into one map
    std::vector<ModulePtr> generationModules_;
    std::vector<ModulePtr> manipulationModules_;
    std::vector<ModulePtr> renderModules_;
    std::vector<ModulePtr> outputModules_;

    PayloadFactory payloadFactory_;

    PayloadTypeMap payloads_;

  };

  template <typename T>
  inline void Pipeline::registerPayload()   // Payloads must be registered
  {
    payloadFactory_.registerPayload<T>();
  }
}
