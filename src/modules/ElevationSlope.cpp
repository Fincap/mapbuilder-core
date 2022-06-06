#include "MapBuilderCore\modules\ElevationSlope.h"
namespace mbc
{
  ElevationSlope::ElevationSlope()
    : Module(PipelineStage::MANIPULATION, "elevation_slope"),
    slope(2.5)
  { }


  ElevationSlope::Ptr ElevationSlope::clone() const
  {
    auto copy = std::make_shared<ElevationSlope>();
    copy->slope = slope;
    return copy;
  }


  TypeIndexVector ElevationSlope::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool ElevationSlope::processPayloads(const PayloadTypeMap& payloads)
  {

    // Get Heightmap payload
    auto heightmapPtr = util::getPtrToPayload<Heightmap>(payloads);

    // Apply slope to every point in heightmap
    int heightmapSize = heightmapPtr->width * heightmapPtr->height;
    for (int i = 0; i < heightmapSize; i++)
    {
      double point = heightmapPtr->points[i] / 255.;   // Convert height to fraction
      double slopedPoint = pow(point, slope);        // Apply slope to height fraction
      unsigned char newPoint = static_cast<unsigned char>(slopedPoint * 255);     // Convert back to height

      heightmapPtr->points[i] = newPoint;
    }

    return true;
  }
}