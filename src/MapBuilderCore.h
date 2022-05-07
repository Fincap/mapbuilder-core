#pragma once

// Core
#include "core\Module.h"
#include "core\Payload.h"
#include "core\Pipeline.h"
#include "core\PipelineStage.h"

// Payloads
#include "payloads\Heightmap.h"
#include "payloads\ColourSetPayload.h"

// Modules - Generation
#include "modules\Canvas.h"
#include "modules\PerlinGen.h"

// Modules - Manipulation
#include "modules\ElevationSlope.h"
#include "modules\GradientSquare.h"

// Modules - Render
#include "modules\ColourSetModule.h"

// Modules - Output
#include "modules\HeightmapOut.h"
#include "modules\CSVOut.h"
