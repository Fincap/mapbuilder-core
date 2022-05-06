#pragma once
#include "PerlinNoise.h"

#include "..\core\Module.h"
#include "..\payloads\Heightmap.h"

namespace mbc
{
  class PerlinGen : public Module
  {
  public:
    PerlinGen();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> getInputTypes() override;
    std::vector<std::type_index> getOutputTypes() override;
    bool processPayloads(PayloadTypeMap) override;

  private:
    // Processing parameters
    uint32_t seed_;
    double frequency_;
    uint32_t octaves_;

  };
}