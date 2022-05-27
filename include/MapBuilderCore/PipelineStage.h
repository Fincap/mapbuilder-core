#pragma once
#include "MapBuilderCore\APIExport.h"

namespace mbc
{
  enum class MAPBUILDER_API PipelineStage
  {
    GENERATION = 0,
    MANIPULATION = 1,
    RENDER = 2,
    OUTPUT = 3
  };
}