#include "MapBuilderCore\modules\GradientCircle.h"

namespace mbc
{
  GradientCircle::GradientCircle()
    : Module(PipelineStage::MANIPULATION, "gradient_circle"),
    fullness(3.0), size(2.2)
  { }


  GradientCircle::Ptr GradientCircle::clone() const
  {
    auto copy = std::make_shared<GradientCircle>();
    copy->fullness = fullness;
    copy->size = size;
    return copy;
  }


  TypeIndexVector GradientCircle::registerTypes(PayloadFactory& factory)
  {
    return registerWithFactory<Heightmap>(factory);
  }

  bool GradientCircle::processPayloads(const PayloadTypeMap& payloads)
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
      unsigned char newPoint = static_cast<unsigned char>(point * 255); // Convert back to height

      heightmapPtr->points[i] = newPoint;
    }

    return true;
  }

  // This function generates the gradient that is applied to the Heightmap payload.
  std::vector<double> GradientCircle::generateGradient(int width, int height)
  {
    std::vector<double> points;
    int vectorSize = width * height;
    points.resize(vectorSize);

    // Calculate midpoints
    double centerX = width / 2.0;
    double centerY = height / 2.0;

    int r = static_cast<int>(std::min(centerX, centerY));	// Radius should be half the screen size

    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        // Calculate distance from midpoint
        double d = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));

        // Get ratio of point distance out of total radius
        double value = 1;
        if (d < r) {
          value = (d / r);
        }

        // Apply curve to gradient
        double gradient = pow(value, fullness) / (pow(value, fullness) + pow(size - size * value, fullness));

        int index = (y * width) + x;
        points.at(index) = gradient;
      }
    }

    return points;
  }

}