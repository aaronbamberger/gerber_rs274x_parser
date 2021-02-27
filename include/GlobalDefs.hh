/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _GLOBAL_DEFS_H
#define _GLOBAL_DEFS_H

namespace Gerber {
	enum class SemanticValidity {
		SEMANTIC_VALIDITY_OK,
		SEMANTIC_VALIDITY_DEPRECATED,
		SEMANTIC_VALIDITY_WARNING,
		SEMANTIC_VALIDITY_FATAL
	};

	enum class QuadrantMode {
		QUADRANT_MODE_UNDEFINED,
		QUADRANT_MODE_SINGLE,
		QUADRANT_MODE_MULTI
	};

	enum class InterpolationMode {
		INTERPOLATION_MODE_UNDEFINED,
		INTERPOLATION_MODE_LINEAR,
		INTERPOLATION_MODE_CW_CIRCULAR,
		INTERPOLATION_MODE_CCW_CIRCULAR
	};

	enum class RegionModeState {
		REGION_MODE_ON,
		REGION_MODE_OFF
	};

	enum class LevelPolarityType {
        LEVEL_POLARITY_DARK,
        LEVEL_POLARITY_CLEAR
    };

	enum class UnitType {
        UNIT_TYPE_UNDEFINED,
        UNIT_TYPE_IN,
        UNIT_TYPE_MM
    };
}

#endif // _GLOBAL_DEFS_H
