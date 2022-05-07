#pragma once
#include <fstream>
#include <iostream>

#include "..\core\Module.h"
#include "..\payloads\Heightmap.h"

namespace mbc
{
  class CSVOut : public Module
  {
  public:
    CSVOut();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

  private:
    // Processing parameters
    std::string outputFilepath_;
  };
}