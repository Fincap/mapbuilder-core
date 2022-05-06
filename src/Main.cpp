#include <iostream>
#include <string>
#include <memory>

#include "MapBuilderCore.h"

int main(int argc, char* argv)
{
	// Create Pipeline
	mbc::Pipeline pipe;

	// Register heightmap payload
	pipe.registerPayload<mbc::Heightmap>();

	// Create canvas module
	auto canvas = std::make_shared<mbc::Canvas>();
	pipe.addModule(canvas);

	// Create perlin module
	auto perlin = std::make_shared<mbc::PerlinGen>();
	pipe.addModule(perlin);

	pipe.execute();

}