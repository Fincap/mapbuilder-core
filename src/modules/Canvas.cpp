#include "Canvas.h"

namespace mbc
{
  Canvas::Canvas()
    : Module(PipelineStage::GENERATION)
  { }

  std::vector<std::type_index> Canvas::getInputTypes()
  {
    std::vector<std::type_index> steve;
    return steve;
  }

  std::vector<std::type_index> Canvas::getOutputTypes()
  {
    std::vector<std::type_index> steve;
    return steve;
  }

  PayloadTypeMap Canvas::processPayloads(PayloadTypeMap)
  {
    PayloadTypeMap steve;
    return steve;
  }

}