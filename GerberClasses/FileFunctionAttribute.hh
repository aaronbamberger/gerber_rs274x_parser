#ifndef _FILE_FUNCTION_ATTRIBUTE
#define _FILE_FUNCTION_ATTRIBUTE

#include "StandardAttribute.hh"

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

	FileFunctionAttribute(std::string name, FileFunction function);
	virtual ~FileFunctionAttribute();

	void set_layer_num(unsigned int layer_num);
	void set_layer_type(LayerType layer_type);
	void set_copper_type(CopperType copper_type);
	void set_drill_type(DrillType drill_type);
	void set_drill_route_type(DrillRouteType drill_route_type);
	void set_edge_plate_type(EdgePlateType edge_plate_type);
	void set_mask_index(unsigned int mask_index);
	void set_other_description(std::string other_description)

private:
	unsigned int m_layer_num;
	LayerType m_layer_type;
	CopperType m_copper_type;
	DrillType m_drill_type;
	DrillRouteType m_drill_route_type;
	EdgePlateType m_edge_plate_type;
	unsigned int m_mask_index;
	std::string m_other_description;
};

#endif // _FILE_FUNCTION_ATTRIBUTE
