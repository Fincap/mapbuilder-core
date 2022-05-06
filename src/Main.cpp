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

	pipe.execute();

}