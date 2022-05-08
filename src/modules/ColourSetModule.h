#pragma once
#include "..\APIExport.h"

#include <vector>
#include <typeindex>
#include <map>

#include "..\core\Module.h"
#include "..\core\PipelineStage.h"
#include "..\payloads\ColourSetPayload.h"

namespace mbc
{
  class MAPBUILDER_API ColourSetModule : public Module
  {
  public:
    ColourSetModule();

    // Inherit from base class - must be implemented
    TypeIndexVector registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

  private:
    // Processing parameters
    std::map<unsigned char, uint32_t>* colourRanges_;

  };
}