#include "MapBuilderCore\modules\ColourHeightmapRenderer.h"
namespace mbc
{
  ColourHeightmapRenderer::ColourHeightmapRenderer()
    : Module(PipelineStage::RENDER, "colour_heightmap_renderer")
  { }

  TypeIndexVector ColourHeightmapRenderer::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap, ColouredHeightmap, ColourSetPayload>(factory);
  }

  bool ColourHeightmapRenderer::processPayloads(const PayloadTypeMap& payloads)
  {
    // Get Heightmap payload
    auto heightmapPtr = util::getPtrToPayload<Heightmap>(payloads);

    // Get ColouredHeightmap payload
    auto colouredHeightmapPtr = util::getPtrToPayload<ColouredHeightmap>(payloads);

    // Get ColourSet payload
    auto colourSetPtr = util::getPtrToPayload<ColourSetPayload>(payloads);

    // Get width and height from heightmap
    int width = heightmapPtr->width;
    int height = heightmapPtr->height;

    // Initialize coloured heightmap
    colouredHeightmapPtr->width = width;
    colouredHeightmapPtr->height = height;
    colouredHeightmapPtr->colouredPoints = new uint32_t[width * height];

    // Iterate through each height value, find the appropriate colour
    // from the colour set, and then add that colour to the coloured
    // heightmap points.
    for (int i = 0; i < width * height; i++)
    {
      for (const auto& pair : colourSetPtr->colourRanges)
      {
        if (heightmapPtr->points[i] <= pair.first)  // Check for next range
        {
          colouredHeightmapPtr->colouredPoints[i] = pair.second;
          break;  // Continue to next point
        }
      }
    }

    return true;

  }
}