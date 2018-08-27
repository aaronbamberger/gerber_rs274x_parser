#include "Attributes/FilePolarityAttribute.hh"

FilePolarityAttribute::FilePolarityAttribute(ValueWithLocation<Polarity> polarity, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".FilePolarity", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_FILE_POLARITY),
	m_polarity(polarity)
{}

FilePolarityAttribute::~FilePolarityAttribute()
{}
