#include "PerlinGen.h"
namespace mbc
{
  PerlinGen::PerlinGen()
    : Module(PipelineStage::GENERATION, "perlin_gen"),
    seed(12345), frequency(4.0), octaves(6)
  { }

  std::vector<std::type_index> PerlinGen::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool PerlinGen::processPayloads(const PayloadTypeMap& payloads)
  {

    // Get Heightmap payload
    auto heightmapPtr = util::getPtrToPayload<Heightmap>(payloads);

    int width = heightmapPtr->width;
    int height = heightmapPtr->height;

    // Calculate frequencies
    const double fx = width / frequency;
    const double fy = height / frequency;

    // Get boundaries of array
    auto begin = &heightmapPtr->points[0];
    auto size = width * height;

    // Arbitrary cutoff
    if (size <= 1024)
    {
      computePerlinGrid(begin, begin + size, fx, fy, octaves, 0, width, seed);
      return true;
    }

    // Divide grid into 4 and make async calls to compute perlin grid.
    int index = 0;
    auto f0 = std::async(computePerlinGrid,
      begin, begin + size / 4, fx, fy, octaves, index, width, seed);

    index += (size / 4) - 1;
    auto f1 = std::async(computePerlinGrid,
      begin + size / 4, begin + size / 2, fx, fy, octaves, index, width, seed);

    index += (size / 4) - 1;
    auto f2 = std::async(computePerlinGrid,
      begin + size / 2, begin + size * 3/4, fx, fy, octaves, index, width, seed);

    index += (size / 4) - 1;
    auto f3 = std::async(computePerlinGrid,
      begin + size * 3 / 4, begin + size, fx, fy, octaves, index, width, seed);

    f0.wait();
    f1.wait();
    f2.wait();
    f3.wait();

    return true;
  }


  void mbc::computePerlinGrid(unsigned char* begin, unsigned char* end, 
    const double& fx, const double& fy, const uint32_t& oct, 
    const int& startIndex, const int&  width, const uint32_t& seed)
  {
    // Seed perlin noise
    siv::PerlinNoise perlin(seed);

    int iters = 0;
    while (begin != end)
    {
      // Calculate index, x, and y
      int index = startIndex + iters;
      int x = index % width;
      int y = index / width;

      // Generate noise
      double noiseLevel = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, oct);
      *begin *= noiseLevel;

      iters++;
      begin++;
    }
  }
}