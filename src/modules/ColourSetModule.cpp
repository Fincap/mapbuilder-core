#include "MapBuilderCore\modules\ColourSetModule.h"

namespace mbc
{
  ColourSetModule::ColourSetModule()
    : Module(PipelineStage::RENDER, "colour_set_module")
  {
    /*
    * Zone      Max   R,G,B
    * Sea level 38	  0, 115, 170
    * #Beach	  43	  N / A
    * Grass		  102	  0, 70, 15
    * Hills		  140	  128, 128, 128
    * Peaks		  255	  200, 200, 200
    */

    colourRanges = new std::map<unsigned char, uint32_t>{
      {38,  0x0073aa},   // Sea level
      {102, 0x00460f},   // Grass
      {140, 0x808080},   // Hills
      {255, 0xc8c8c8},   // Peaks
    };
  }


  ColourSetModule::~ColourSetModule()
  {
    delete colourRanges;
  }


  ColourSetModule::Ptr ColourSetModule::clone() const
  {
    auto copy = std::make_shared<ColourSetModule>();
    *copy->colourRanges = std::map<unsigned char, uint32_t>(*colourRanges);
    return copy;
  }


  TypeIndexVector ColourSetModule::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<ColouredHeightmap, Heightmap>(factory);
  }

  bool ColourSetModule::processPayloads(const PayloadTypeMap& payloads)
  {

    // Get Heightmap payload
    auto heightmapPtr = util::getPtrToPayload<Heightmap>(payloads);

    // Get ColouredHeightmap payload
    auto colouredHeightmapPtr = util::getPtrToPayload<ColouredHeightmap>(payloads);

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
      for (const auto& pair : *colourRanges)
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