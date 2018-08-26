#include "Attributes/AperFunctionAttribute.hh"

AperFunctionAttribute::AperFunctionAttribute(ValueWithLocation<std::string> name, ValueWithLocation<AperFunction> aper_function) :
	StandardAttribute(name), m_aper_function(aper_function), m_via_drill_type(ViaDrillType::NOT_SET),
	m_component_drill_type(ComponentDrillType::NOT_SET), m_mechanical_drill_type(MechanicalDrillType::NOT_SET),
	m_pad_definition_type(PadDefinitionType::NOT_SET), m_fiducial_type(FiducialType::NOT_SET),
	m_other_description("")
{}

AperFunctionAttribute::~AperFunctionAttribute()
{}

void AperFunctionAttribute::set_via_drill_type(ValueWithLocation<ViaDrillType> via_drill_type)
{
	m_via_drill_type = via_drill_type;
}

void AperFunctionAttribute::set_component_drill_type(ValueWithLocation<ComponentDrillType> component_drill_type)
{
	m_component_drill_type = component_drill_type;
}

void AperFunctionAttribute::set_mechanical_drill_type(ValueWithLocation<MechanicalDrillType> mechanical_drill_type)
{
	m_mechanical_drill_type = mechanical_drill_type;
}

void AperFunctionAttribute::set_pad_definition_type(ValueWithLocation<PadDefinitionType> pad_definition_type)
{
	m_pad_definition_type = pad_definition_type;
}

void AperFunctionAttribute::set_fiducial_type(ValueWithLocation<FiducialType> fiducial_type)
{
	m_fiducial_type = fiducial_type;
}

void AperFunctionAttribute::set_other_description(ValueWithLocation<std::string> other_description)
{
	m_other_description = other_description;
}

