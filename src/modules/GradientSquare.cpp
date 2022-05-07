#include "GradientSquare.h"

namespace mbc
{
  GradientSquare::GradientSquare()
    : Module(PipelineStage::MANIPULATION),
    fullness_(3.0), size_(2.2)
  { }

  std::vector<std::type_index> GradientSquare::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool GradientSquare::processPayloads(PayloadTypeMap payloads)
  {

    // Get Heightmap payload
    PayloadPtr payloadPtr = payloads[std::type_index(typeid(Heightmap))];

    // Cast generic Payload pointer to Heightmap pointer
    std::shared_ptr<Heightmap> heightmapPtr = std::dynamic_pointer_cast<Heightmap>(payloadPtr);

    // Get Heightmap values
    int width = heightmapPtr->width;
    int height = heightmapPtr->height;
    int heightmapSize = width * height;

    // Generate gradient points
    auto gradientPoints = generateGradient(width, height);

    // Iterate through map and apply gradient to each point
    for (int i = 0; i < heightmapSize; i++)
    {
      auto point = heightmapPtr->points[i] / 255.;        // Convert height to fraction
      auto gradient = gradientPoints.at(i);               // Get gradient at point
      point = std::clamp(point -= gradient, 0.0, 1.0);    // Apply gradient to point
      unsigned char newPoint = point * 255;               // Convert back to height

      heightmapPtr->points[i] = newPoint;
    }

    return true;
  }

  // This function generates the gradient that is applied to the Heightmap payload.
  std::vector<double> GradientSquare::generateGradient(int width, int height)
  {
    std::vector<double> points;
    int vectorSize = width * height;
    points.resize(vectorSize);

    for (int y = 0; y < width; y++)
    {
      for (int x = 0; x < height; x++)
      {
        // Generate gradient points
        double i = x / (double)width * 2 - 1;
        double j = y / (double)height  * 2 - 1;

        // Find nearest edge
        double value = std::max(abs(i), abs(j));

        // Apply curve to gradient
        double gradient = pow(value, fullness_) / (pow(value, fullness_) + pow(size_ - size_ * value, fullness_));

        int index = (y * height) + x;
        points.at(index) = gradient;
      }
    }

    return points;
  }

}