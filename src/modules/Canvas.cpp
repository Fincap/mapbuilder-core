#include "Canvas.h"

namespace mbc
{
  Canvas::Canvas()
    : Module(PipelineStage::GENERATION),
    width(64), height(64)
  { }

  std::vector<std::type_index> Canvas::getInputTypes()
  {
    return std::vector<std::type_index>
    {
      // No inputs
    };
  }

  std::vector<std::type_index> Canvas::getOutputTypes()
  {
    return std::vector<std::type_index>
    {
      std::type_index(typeid(Heightmap))
    };
  }

  PayloadTypeMap Canvas::processPayloads(PayloadTypeMap)
  {
    PayloadTypeMap steve;
    return steve;
  }

}