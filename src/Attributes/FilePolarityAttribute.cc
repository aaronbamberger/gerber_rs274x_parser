#include "Attributes/FilePolarityAttribute.hh"

FilePolarityAttribute::FilePolarityAttribute(ValueWithLocation<std::string> name, ValueWithLocation<Polarity> polarity) :
	StandardAttribute(name), m_polarity(polarity)
{}

FilePolarityAttribute::~FilePolarityAttribute()
{}
