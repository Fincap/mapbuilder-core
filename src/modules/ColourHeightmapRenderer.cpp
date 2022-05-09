#include "ColourHeightmapRenderer.h"
namespace mbc
{
  ColourHeightmapRenderer::ColourHeightmapRenderer()
    : Module(PipelineStage::RENDER, "colour_heightmap_renderer")
  { }

  TypeIndexVector ColourHeightmapRenderer::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap, ColouredHeightmap, ColourSetPayload>(factory);
  }

  bool ColourHeightmapRenderer::processPayloads(PayloadTypeMap payloads)
  {
    // Get Heightmap payload
    auto heightmapPtr = std::dynamic_pointer_cast<Heightmap>(
      payloads[std::type_index(typeid(Heightmap))]
    );

    // Get ColouredHeightmap payload
    auto colouredHeightmapPtr = std::dynamic_pointer_cast<ColouredHeightmap>(
      payloads[std::type_index(typeid(ColouredHeightmap))]
    );

    // Get ColourSet payload
    auto colourSetPtr = std::dynamic_pointer_cast<ColourSetPayload>(
      payloads[std::type_index(typeid(ColourSetPayload))]
    );

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