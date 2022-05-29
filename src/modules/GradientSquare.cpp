#include "MapBuilderCore\modules\GradientSquare.h"

namespace mbc
{
  GradientSquare::GradientSquare()
    : Module(PipelineStage::MANIPULATION, "gradient_square"),
    fullness(3.0), size(2.2)
  { }


  GradientSquare::Ptr GradientSquare::clone() const
  {
    auto copy = std::make_shared<GradientSquare>();
    copy->fullness = fullness;
    copy->size = size;
    return copy;
  }


  TypeIndexVector GradientSquare::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool GradientSquare::processPayloads(const PayloadTypeMap& payloads)
  {

    // Get Heightmap payload
    auto heightmapPtr = util::getPtrToPayload<Heightmap>(payloads);

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
        double gradient = pow(value, fullness) / (pow(value, fullness) + pow(size - size * value, fullness));

        int index = (y * height) + x;
        points.at(index) = gradient;
      }
    }

    return points;
  }

}