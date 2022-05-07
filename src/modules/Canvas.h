#pragma once
#ifdef MAPBUILDER_EXPORTS
#define MAPBUILDER_API __declspec(dllexport)
#else
#define MAPBUILDER_API __declspec(dllimport)
#endif

#include <vector>
#include <typeindex>

#include "..\core\Module.h"
#include "..\core\PipelineStage.h"
#include "..\payloads\Heightmap.h"

namespace mbc
{
  class MAPBUILDER_API Canvas : public Module
  {
  public:
    Canvas();

    // Inherit from base class - must be implemented
    std::vector<std::type_index> registerTypes(PayloadFactory&) override;
    bool processPayloads(PayloadTypeMap) override;

  private:
    // Processing parameters
    int width_, height_;

  };
}