#include "ColourSetModule.h"

namespace mbc
{
  ColourSetModule::ColourSetModule()
    : Module(PipelineStage::RENDER)
  {
    /*
    * Zone      Max   R,G,B
    * Sea level 38	  0, 115, 170
    * #Beach	  43	  N / A
    * Grass		  102	  0, 70, 15
    * Hills		  140	  128, 128, 128
    * Peaks		  255	  200, 200, 200
    */

    colourRanges_ = new std::map<unsigned char, uint32_t>{
      {38,  0x0073aa},   // Sea level
      {102, 0x00460f},   // Grass
      {140, 0x808080},   // Hills
      {255, 0xc8c8c8},   // Peaks
    };
  }

  TypeIndexVector ColourSetModule::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<ColourSetPayload>(factory);
  }

  bool ColourSetModule::processPayloads(PayloadTypeMap payloads)
  {

    // Get Colour set payload
    PayloadPtr payloadPtr = payloads[std::type_index(typeid(ColourSetPayload))];

    // Cast generic Payload pointer to Colour set pointer
    std::shared_ptr<ColourSetPayload> setPtr = std::dynamic_pointer_cast<ColourSetPayload>(payloadPtr);

    // Update colour set values to processing values
    setPtr->colourRanges = *colourRanges_;

    return true;
  }

}