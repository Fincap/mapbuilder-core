#include "Canvas.h"

namespace mbc
{
  Canvas::Canvas()
    : Module(PipelineStage::GENERATION),
    width_(64), height_(64)
  { }

  std::vector<std::type_index> Canvas::registerTypes(PayloadFactory& factory)
  {
    std::vector<std::type_index> newPayloads;

    if (!factory.hasPayload<Heightmap>())
    {
      factory.registerPayload<Heightmap>();
      newPayloads.push_back(std::type_index(typeid(Heightmap)));
    }

    return newPayloads;
  }

  bool Canvas::processPayloads(PayloadTypeMap payloads)
  {
    
    // Get Heightmap payload
    PayloadPtr payloadPtr = payloads[std::type_index(typeid(Heightmap))];

    // Cast generic Payload pointer to Heightmap pointer
    std::shared_ptr<Heightmap> heightmapPtr = std::dynamic_pointer_cast<Heightmap>(payloadPtr);

    // Update Heightmap values
    heightmapPtr->width = width_;
    heightmapPtr->height = height_;
    heightmapPtr->points = new unsigned char[width_ * height_];

    // Iterate through map and set each point to white
    for (int y = 0; y < width_; y++)
    {
      for (int x = 0; x < height_; x++)
      {
        // (x,y) to 1D index: (y * height) + x
        heightmapPtr->points[(y * height_) + x] = 255;
      }
    }

    return true;
  }

}