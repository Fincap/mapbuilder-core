#pragma once
#include "APIExport.h"

#ifdef _DEBUG
#include <chrono>
#endif

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
  class MAPBUILDER_API Pipeline
  {
  public:
    Pipeline();
    ~Pipeline();

    bool execute();
    bool addModule(ModulePtr);

  private:
    std::vector<ModulePtr>* modules_;

    PayloadFactory* payloadFactory_;

    PayloadTypeMap* payloads_;

  };
}
