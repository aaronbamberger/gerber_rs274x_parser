/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _FILE_FUNCTION_ATTRIBUTE
#define _FILE_FUNCTION_ATTRIBUTE

#include "Util/ValueWithLocation.hh"
#include "Attributes/StandardAttribute.hh"
#include "location.hh"

#include <string>

class FileFunctionAttribute : public StandardAttribute {
public:
	enum class FileFunction {
		COPPER,
		PLATED,
		NON_PLATED,
		PROFILE,
		SOLDER_MASK,
		LEGEND,
		PASTE,
		GLUE,
		CARBON_MASK,
		GOLD_MASK,
		HEATSINK_MASK,
		PEELABLE_MASK,
		SILVER_MASK,
		TIN_MASK,
		DEPTH_ROUT,
		V_CUT,
		VIA_FILL,
		ARRAY_DRAWING,
		ASSEMBLY_DRAWING,
		DRILL_MAP,
		FABRICATION_DRAWING,
		V_CUT_MAP,
		OTHER_DRAWING,
		PADS,
		OTHER
	};
	
	enum class LayerType {
		NOT_SET,
		TOP,
		INNER,
		BOTTOM
	};

	enum class CopperType {
		NOT_SET,
		PLANE,
		SIGNAL,
		MIXED,
		HATCHED
	};

	enum class DrillType {
		NOT_SET,
		PLATED_THROUGH_HOLE,
		NON_PLATED_THROUGH_HOLE,
		BLIND,
		BURIED	
	};

	enum class DrillRouteType {
		NOT_SET,
		DRILL,
		ROUTE,
		MIXED
	};

	enum class EdgePlateType {
		NOT_SET,
		PLATED,
		NON_PLATED
	};

	FileFunctionAttribute(ValueWithLocation<FileFunction> function, yy::location name_location = yy::location());
	virtual ~FileFunctionAttribute();

	void set_layer_num(ValueWithLocation<unsigned int> layer_num);
	void set_layer_type(ValueWithLocation<LayerType> layer_type);
	void set_copper_type(ValueWithLocation<CopperType> copper_type);
	void set_drill_type(ValueWithLocation<DrillType> drill_type);
	void set_drill_route_type(ValueWithLocation<DrillRouteType> drill_route_type);
	void set_edge_plate_type(ValueWithLocation<EdgePlateType> edge_plate_type);
	void set_mask_index(ValueWithLocation<unsigned int> mask_index);
	void set_other_description(ValueWithLocation<std::string> other_description);

private:
	ValueWithLocation<FileFunction> m_function;
	ValueWithLocation<unsigned int> m_layer_num;
	ValueWithLocation<LayerType> m_layer_type;
	ValueWithLocation<CopperType> m_copper_type;
	ValueWithLocation<DrillType> m_drill_type;
	ValueWithLocation<DrillRouteType> m_drill_route_type;
	ValueWithLocation<EdgePlateType> m_edge_plate_type;
	ValueWithLocation<unsigned int> m_mask_index;
	ValueWithLocation<std::string> m_other_description;
};

#endif // _FILE_FUNCTION_ATTRIBUTE
