#ifndef _APER_FUNCTION_ATTRIBUTE_H
#define _APER_FUNCTION_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"

#include <string>

class AperFunctionAttribute : public StandardAttribute {
public:
	enum class AperFunction {
		VIA_DRILL,
		BACK_DRILL,
		COMPONENT_DRILL,
		MECHANICAL_DRILL,
		CASTELLATED_DRILL,
		CUT_OUT,
		SLOT,
		CAVITY,
		OTHER_DRILL,
		COMPONENT_PAD,
		SMD_PAD,
		BGA_PAD,
		CONNECTOR_PAD,
		HEATSINK_PAD,
		VIA_PAD,
		TEST_PAD,
		CASTELLATED_PAD,
		FIDUCIAL_PAD,
		THERMAL_RELIEF_PAD,
		WASHER_PAD,
		ANTI_PAD,
		OTHER_PAD,
		CONDUCTOR,
		ETCHED_COMPONENT,
		NON_CONDUCTOR,
		COPPER_BALANCING,
		BORDER,
		OTHER_COPPER,
		PROFILE,
		NON_MATERIAL,
		MATERIAL,
		OTHER
	};

	enum class ViaDrillType {
		NOT_SET,
		FILLED,
		NOT_FILLED
	};

	enum class ComponentDrillType {
		NOT_SET,
		PRESS_FIT
	};

	enum class MechanicalDrillType {
		NOT_SET,
		TOOLING,
		BREAKOUT,
		OTHER
	};

	enum class PadDefinitionType {
		NOT_SET,
		COPPER_DEFINED,
		SOLDER_MASK_DEFINED
	};

	enum class FiducialType {
		NOT_SET,
		GLOBAL,
		LOCAL
	};

	AperFunctionAttribute(std::string name, AperFunction aper_function);
	virtual ~AperFunctionAttribute();

	void set_via_drill_type(ViaDrillType via_drill_type);
	void set_component_drill_type(ComponentDrillType component_drill_type);
	void set_mechanical_drill_type(MechanicalDrillType mechanical_drill_type);
	void set_pad_definition_type(PadDefinitionType pad_definition_type);
	void set_fiducial_type(FiducialType fiducial_type);
	void set_other_description(std::string other_description);

private:
	ViaDrillType m_via_drill_type;
	ComponentDrillType m_component_drill_type;
	MechanicalDrillType m_mechanical_drill_type;
	PadDefinitionType m_pad_definition_type;
	FiducialType m_fiducial_type;
	std::string m_other_description;
};

#endif // _APER_FUNCTION_ATTRIBUTE_H
