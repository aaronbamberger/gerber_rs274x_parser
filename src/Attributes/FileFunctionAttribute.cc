/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/FileFunctionAttribute.hh"

FileFunctionAttribute::FileFunctionAttribute(ValueWithLocation<FileFunction> function, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".FileFunction", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_FILE_FUNCTION),
	m_function(function),
	m_layer_num(0),
	m_layer_type(LayerType::NOT_SET),
	m_copper_type(CopperType::NOT_SET),
	m_drill_type(DrillType::NOT_SET),
	m_drill_route_type(DrillRouteType::NOT_SET),
	m_edge_plate_type(EdgePlateType::NOT_SET),
	m_mask_index(0),
	m_other_description("")
{}

FileFunctionAttribute::~FileFunctionAttribute()
{}

void FileFunctionAttribute::set_layer_num(ValueWithLocation<unsigned int> layer_num)
{
	m_layer_num = layer_num;
}

void FileFunctionAttribute::set_layer_type(ValueWithLocation<LayerType> layer_type)
{
	m_layer_type = layer_type;
}

void FileFunctionAttribute::set_copper_type(ValueWithLocation<CopperType> copper_type)
{
	m_copper_type = copper_type;
}

void FileFunctionAttribute::set_drill_type(ValueWithLocation<DrillType> drill_type)
{
	m_drill_type = drill_type;
}

void FileFunctionAttribute::set_drill_route_type(ValueWithLocation<DrillRouteType> drill_route_type)
{
	m_drill_route_type = drill_route_type;
}

void FileFunctionAttribute::set_edge_plate_type(ValueWithLocation<EdgePlateType> edge_plate_type)
{
	m_edge_plate_type = edge_plate_type;
}

void FileFunctionAttribute::set_mask_index(ValueWithLocation<unsigned int> mask_index)
{
	m_mask_index = mask_index;
}

void FileFunctionAttribute::set_other_description(ValueWithLocation<std::string> other_description)
{
	m_other_description = other_description;
}

