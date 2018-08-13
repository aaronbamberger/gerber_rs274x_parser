#ifndef _FLASH_TEXT_ATTRIBUTE_H
#define _FLASH_TEXT_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"

#include <string>

class FlashTextAttribute : public FlashTextAttribute {
public:
	enum class TextType {
		BARCODE,
		CHARACTERS
	};

	enum class TextOrientation {
		NOT_SET,
		READABLE,
		MIRRORED
	};

	FlashTextAttribute(std::string name, std::string text, TextType text_type);
	virtual ~FlashTextAttribute();

	void set_font_name(std::string font_name);
	void set_font_size(unsigned int font_size);
	void set_comments(std::string comments);
	
private:
	std::string m_text;
	TextType m_text_type;
	std::string m_font_name;
	unsigned int m_font_size;
	std::string m_comments;
};

#endif // _FLASH_TEXT_ATTRIBUTE_H
