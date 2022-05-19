#include "Canvas.h"

namespace mbc
{
  Canvas::Canvas()
    : Module(PipelineStage::GENERATION, "canvas"),
    width(64), height(64)
  { }

  std::vector<std::type_index> Canvas::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool Canvas::processPayloads(PayloadTypeMap payloads)
  {
    
    // Get Heightmap payload
    auto heightmapPtr = util::getPtrToPayload<Heightmap>(payloads);

    // Update Heightmap values
    heightmapPtr->width = width;
    heightmapPtr->height = height;
    heightmapPtr->points = new unsigned char[width * height];

    // Iterate through map and set each point to white
    for (int y = 0; y < width; y++)
    {
      for (int x = 0; x < height; x++)
      {
        // (x,y) to 1D index: (y * height) + x
        heightmapPtr->points[(y * height) + x] = 255;
      }
    }

    return true;
  }

}