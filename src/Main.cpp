#include <iostream>

#include "MapBuilderCore.h"

int main(int argc, char* argv)
{
	// Create Pipeline
	mbc::Pipeline pipe;

	// Create heightmap payload
	mbc::Heightmap* heightmap = new mbc::Heightmap();

	// Create canvas module
	mbc::Canvas* canvas = new mbc::Canvas();
	std::cout << static_cast<int>(canvas->getPipelineStage()) << std::endl;

}