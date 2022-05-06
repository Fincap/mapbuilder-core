#include <iostream>
#include <string>
#include <memory>

#include "MapBuilderCore.h"

int main(int argc, char* argv)
{
	// Create Pipeline
	mbc::Pipeline pipe;

	// Register heightmap payload
	pipe.registerPayload(std::type_index(typeid(mbc::Heightmap)), &mbc::Heightmap::create);

	// Create canvas module
	std::shared_ptr<mbc::Canvas> canvas = std::make_shared<mbc::Canvas>();
	std::shared_ptr<mbc::Canvas> canvas2 = std::make_shared<mbc::Canvas>();

	pipe.addModule(canvas);
	pipe.addModule(canvas2);

}