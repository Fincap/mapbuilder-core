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

  PayloadTypeMap Canvas::processPayloads(PayloadTypeMap payloads)
  {
    
    // Get Heightmap payload
    PayloadPtr heightmapPtr = payloads[std::type_index(typeid(Heightmap))];
    PayloadValues heightmapPayload = heightmapPtr->unpack();
    int* heightmapWidth = std::any_cast<int*>(heightmapPayload["width"]);
    int* heightmapHeight = std::any_cast<int*>(heightmapPayload["height"]);
    unsigned char* heightmapPoints = std::any_cast<unsigned char*>(heightmapPayload["points"]);

    // Iterate through map and set each point to white
    for (int y = 0; y < *heightmapHeight; y++)
    {
      for (int x = 0; x < *heightmapWidth; x++)
      {
        // (x,y) to 1D index: (y * height) + x
        heightmapPoints[(y * *heightmapHeight) + x];
      }
    }

    return PayloadTypeMap();
  }

}