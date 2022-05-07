#include "ElevationSlope.h"
namespace mbc
{
  ElevationSlope::ElevationSlope()
    : Module(PipelineStage::MANIPULATION),
    slope_(2.5)
  { }

  std::vector<std::type_index> ElevationSlope::registerTypes(PayloadFactory& factory)
  {
    std::vector<std::type_index> newPayloads;

    if (!factory.hasPayload<Heightmap>())
    {
      factory.registerPayload<Heightmap>();
      newPayloads.push_back(std::type_index(typeid(Heightmap)));
    }

    return newPayloads;
  }

  bool ElevationSlope::processPayloads(PayloadTypeMap payloads)
  {

    // Get Heightmap payload
    PayloadPtr payloadPtr = payloads[std::type_index(typeid(Heightmap))];

    // Cast generic Payload pointer to Heightmap pointer
    std::shared_ptr<Heightmap> heightmapPtr = std::dynamic_pointer_cast<Heightmap>(payloadPtr);

    // Apply slope to every point in heightmap
    int heightmapSize = heightmapPtr->width * heightmapPtr->height;
    for (int i = 0; i < heightmapSize; i++)
    {
      double point = heightmapPtr->points[i] / 255.;   // Convert height to fraction
      double slopedPoint = pow(point, slope_);        // Apply slope to height fraction
      unsigned char newPoint = slopedPoint * 255;     // Convert back to height

      heightmapPtr->points[i] = newPoint;
    }

    return true;
  }
}