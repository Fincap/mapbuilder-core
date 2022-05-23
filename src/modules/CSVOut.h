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
  /*
  Module that produces a CSV file at the given filepath where each value is the
  raw height (0-255) of its corresponding point on the heightmap.
  */
  class MAPBUILDER_API CSVOut : public Module
  {
  public:
    CSVOut();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    // Processing parameters
    char* outputFilepath;
  };
}