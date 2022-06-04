#pragma once
#include "APIExport.h"

// Core
#include "MapBuilderCore\Module.h"
#include "MapBuilderCore\Payload.h"
#include "MapBuilderCore\Pipeline.h"
#include "MapBuilderCore\PipelineStage.h"
#include "MapBuilderCore\StageMap.h"

// Payloads
#include "MapBuilderCore\payloads\Heightmap.h"
#include "MapBuilderCore\payloads\ColouredHeightmap.h"

// Modules - Generation
#include "MapBuilderCore\modules\Canvas.h"
#include "MapBuilderCore\modules\PerlinGen.h"

// Modules - Manipulation
#include "MapBuilderCore\modules\ElevationSlope.h"
#include "MapBuilderCore\modules\GradientSquare.h"

// Modules - Render
#include "MapBuilderCore\modules\ColourSetModule.h"

// Modules - Output
#include "MapBuilderCore\modules\HeightmapOut.h"
#include "MapBuilderCore\modules\CSVOut.h"
#include "MapBuilderCore\modules\PNGOut.h"
#include "MapBuilderCore\modules\BMP8Out.h"
