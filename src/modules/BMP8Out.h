#pragma once
#include "APIExport.h"

#include <fstream>
#include <iostream>
#include <filesystem>

#include "core\Module.h"
#include "payloads\Heightmap.h"
#include "util\OutputValidation.h"

namespace mbc
{
  class MAPBUILDER_API BMP8Out : public Module
  {
  public:
    BMP8Out();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

    // Processing parameters
    const char* outputFilepath;

  private:
    void insertIntAsBytes(unsigned char*, int);
  };
}