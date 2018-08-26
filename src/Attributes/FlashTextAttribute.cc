#include "Attributes/FlashTextAttribute.hh"

FlashTextAttribute::FlashTextAttribute(ValueWithLocation<std::string> name,
									   ValueWithLocation<std::string> text,
									   ValueWithLocation<TextType> text_type) :
	StandardAttribute(name), m_text(text), m_text_type(text_type),
	m_text_orientation(TextOrientation::NOT_SET), m_font_name(""),
	m_font_size(0), m_comments("")
{}

FlashTextAttribute::~FlashTextAttribute()
{}

void FlashTextAttribute::set_text_orientation(ValueWithLocation<TextOrientation> text_orientation)
{
	m_text_orientation = text_orientation;
}

void FlashTextAttribute::set_font_name(ValueWithLocation<std::string> font_name)
{
	m_font_name = font_name;
}

void FlashTextAttribute::set_font_size(ValueWithLocation<unsigned int> font_size)
{
	m_font_size = font_size;
}

void FlashTextAttribute::set_comments(ValueWithLocation<std::string> comments)
{
	m_comments = comments;
}

