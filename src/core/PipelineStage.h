#pragma once
#pragma once
#ifdef MAPBUILDER_EXPORTS
#define MAPBUILDER_API __declspec(dllexport)
#else
#define MAPBUILDER_API __declspec(dllimport)
#endif

namespace mbc
{
  const MAPBUILDER_API int NUM_STAGES = 4;

  enum class MAPBUILDER_API PipelineStage
  {
    GENERATION = 0,
    MANIPULATION = 1,
    RENDER = 2,
    OUTPUT = 3
  };
}