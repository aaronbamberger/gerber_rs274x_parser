#ifndef _FILE_POLARITY_ATTRIBUTE
#define _FILE_POLARITY_ATTRIBUTE

#include "Attributes/StandardAttribute.hh"

#include <string>

class FilePolarityAttribute : public StandardAttribute {
public:
	enum class Polarity {
		POSITIVE,
		NEGATIVE
	};

	FilePolarityAttribute(std::string name, Polarity polarity);
	virtual ~FilePolarityAttribute();

private:
	Polarity m_polarity;
};

#endif // _FILE_POLARITY_ATTRIBUTE
