#include "PerlinGen.h"
namespace mbc
{
  PerlinGen::PerlinGen()
    : Module(PipelineStage::GENERATION),
    seed(12345), frequency(4.0), octaves(6)
  { }

  std::vector<std::type_index> PerlinGen::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool PerlinGen::processPayloads(PayloadTypeMap payloads)
  {

    // Get Heightmap payload
    PayloadPtr payloadPtr = payloads[std::type_index(typeid(Heightmap))];

    // Cast generic Payload pointer to Heightmap pointer
    std::shared_ptr<Heightmap> heightmapPtr = std::dynamic_pointer_cast<Heightmap>(payloadPtr);

    // Seed perlin noise
    siv::PerlinNoise perlin(seed);

    // Calculate frequencies
    const double fx = heightmapPtr->width / frequency;
    const double fy = heightmapPtr->height / frequency;

    // Generate noise
    for (int y = 0; y < heightmapPtr->height; y++)
    {
      for (int x = 0; x < heightmapPtr->width; x++)
      {
        double noiseLevel = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves);
        int index = (y * heightmapPtr->height) + x;
        heightmapPtr->points[index] *= noiseLevel;
      }
    }

    return true;
  }
}