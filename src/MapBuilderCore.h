#pragma once
#include "APIExport.h"

// Core
#include "core\Module.h"
#include "core\Payload.h"
#include "core\Pipeline.h"
#include "core\PipelineStage.h"
#include "core\StageMap.h"

// Payloads
#include "payloads\Heightmap.h"
#include "payloads\ColourSetPayload.h"
#include "payloads\ColouredHeightmap.h"

// Modules - Generation
#include "modules\Canvas.h"
#include "modules\PerlinGen.h"

// Modules - Manipulation
#include "modules\ElevationSlope.h"
#include "modules\GradientSquare.h"

// Modules - Render
#include "modules\ColourSetModule.h"
#include "modules\ColourHeightmapRenderer.h"

// Modules - Output
#include "modules\HeightmapOut.h"
#include "modules\CSVOut.h"
#include "modules\PNGOut.h"
#include "modules\BMP8Out.h"
