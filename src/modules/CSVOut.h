#pragma once
#include "APIExport.h"

#include <fstream>
#include <iostream>
#include <string>
#include <charconv>
#include <filesystem>

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\OutputValidation.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  class MAPBUILDER_API CSVOut : public Module
  {
  public:
    CSVOut();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    // Processing parameters
    char* outputFilepath;
  };
}