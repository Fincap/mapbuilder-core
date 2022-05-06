#pragma once
namespace mbc
{
  const int NUM_STAGES = 4;

  enum class PipelineStage
  {
    GENERATION = 0,
    MANIPULATION = 1,
    RENDER = 2,
    OUTPUT = 3
  };
}