#include <iostream>
#include <string>
#include <memory>

#include "MapBuilderCore.h"

int main(int argc, char* argv)
{
	// Create Pipeline
	mbc::Pipeline pipe;

	// Create canvas module
	pipe.addModule(std::make_shared<mbc::Canvas>());

	// Create perlin module
	pipe.addModule(std::make_shared<mbc::PerlinGen>());

	// Create heightmap output module
	pipe.addModule(std::make_shared<mbc::HeightmapOut>());

	// Create csv output module
	pipe.addModule(std::make_shared<mbc::CSVOut>());

	// Create gradient module
	pipe.addModule(std::make_shared<mbc::GradientSquare>());

	// Create slope module
	pipe.addModule(std::make_shared<mbc::ElevationSlope>());

	pipe.execute();

	return 0;

}