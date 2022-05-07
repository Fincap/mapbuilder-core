#include <iostream>
#include <string>
#include <memory>

#include "MapBuilderCore.h"

int main(int argc, char* argv)
{
	// Create Pipeline
	mbc::Pipeline pipe;

	// Create canvas module
	auto canvas = std::make_shared<mbc::Canvas>();
	pipe.addModule(canvas);

	// Create perlin module
	auto perlin = std::make_shared<mbc::PerlinGen>();
	pipe.addModule(perlin);

	// Create heightmap output module
	auto heightmapOutput = std::make_shared<mbc::HeightmapOut>();
	pipe.addModule(heightmapOutput);

	// Create csv output module
	auto csvOutput = std::make_shared<mbc::CSVOut>();
	pipe.addModule(csvOutput);

	// Create slope module
	auto slope = std::make_shared<mbc::ElevationSlope>();
	pipe.addModule(slope);

	pipe.execute();

	return 0;

}