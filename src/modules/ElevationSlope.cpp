#include "ElevationSlope.h"
namespace mbc
{
  ElevationSlope::ElevationSlope()
    : Module(PipelineStage::MANIPULATION, "elevation_slope"),
    slope(2.5)
  { }

  std::vector<std::type_index> ElevationSlope::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
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
      double slopedPoint = pow(point, slope);        // Apply slope to height fraction
      unsigned char newPoint = slopedPoint * 255;     // Convert back to height

      heightmapPtr->points[i] = newPoint;
    }

    return true;
  }
}