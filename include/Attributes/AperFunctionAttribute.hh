/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APER_FUNCTION_ATTRIBUTE_H
#define _APER_FUNCTION_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

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

	AperFunctionAttribute(ValueWithLocation<AperFunction> aper_function, yy::location name_location = yy::location());
	virtual ~AperFunctionAttribute();

	void set_via_drill_type(ValueWithLocation<ViaDrillType> via_drill_type);
	void set_component_drill_type(ValueWithLocation<ComponentDrillType> component_drill_type);
	void set_mechanical_drill_type(ValueWithLocation<MechanicalDrillType> mechanical_drill_type);
	void set_pad_definition_type(ValueWithLocation<PadDefinitionType> pad_definition_type);
	void set_fiducial_type(ValueWithLocation<FiducialType> fiducial_type);
	void set_other_description(ValueWithLocation<std::string> other_description);

private:
	ValueWithLocation<AperFunction> m_aper_function;
	ValueWithLocation<ViaDrillType> m_via_drill_type;
	ValueWithLocation<ComponentDrillType> m_component_drill_type;
	ValueWithLocation<MechanicalDrillType> m_mechanical_drill_type;
	ValueWithLocation<PadDefinitionType> m_pad_definition_type;
	ValueWithLocation<FiducialType> m_fiducial_type;
	ValueWithLocation<std::string> m_other_description;
};

#endif // _APER_FUNCTION_ATTRIBUTE_H
