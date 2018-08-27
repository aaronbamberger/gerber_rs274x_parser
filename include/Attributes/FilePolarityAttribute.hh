#ifndef _FILE_POLARITY_ATTRIBUTE
#define _FILE_POLARITY_ATTRIBUTE

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

#include <string>

class FilePolarityAttribute : public StandardAttribute {
public:
	enum class Polarity {
		POSITIVE,
		NEGATIVE
	};

	FilePolarityAttribute(ValueWithLocation<Polarity> polarity, yy::location name_location = yy::location());
	virtual ~FilePolarityAttribute();

private:
	ValueWithLocation<Polarity> m_polarity;
};

#endif // _FILE_POLARITY_ATTRIBUTE
