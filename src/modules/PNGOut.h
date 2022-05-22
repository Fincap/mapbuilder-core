#pragma once
#include "APIExport.h"

#include <iostream>
#include <filesystem>

#include <png++\png.hpp>

#include "core\Module.h"
#include "payloads\ColouredHeightmap.h"
#include "util\OutputValidation.h"
#include "util\ModuleHelpers.h"

namespace mbc
{
  class MAPBUILDER_API PNGOut : public Module
  {
  public:
    PNGOut();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(const PayloadTypeMap&) override;

    // Processing parameters
    char* outputFilepath;

  };
}