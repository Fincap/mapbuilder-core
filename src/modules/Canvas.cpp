#include "MapBuilderCore\modules\Canvas.h"

namespace mbc
{
  Canvas::Canvas()
    : Module(PipelineStage::GENERATION, "canvas"),
    width(64), height(64)
  { }


  Canvas::Ptr Canvas::clone() const
  {
    auto copy = std::make_shared<Canvas>();
    copy->width = width;
    copy->height = height;
    return copy;
  }


  TypeIndexVector Canvas::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool Canvas::processPayloads(const PayloadTypeMap& payloads)
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