#pragma once
#include "..\APIExport.h"

namespace mbc
{
#ifdef MAPBUILDER_EXPORTS
  MAPBUILDER_API const int NUM_STAGES = 4;
#else
  MAPBUILDER_API extern const int NUM_STAGES;
#endif

  enum class MAPBUILDER_API PipelineStage
  {
    GENERATION = 0,
    MANIPULATION = 1,
    RENDER = 2,
    OUTPUT = 3
  };
}