#ifndef _APERTURE_MACRO_PRIMITIVE_COMMENT_H
#define _APERTURE_MACRO_PRIMITIVE_COMMENT_H

#include "ApertureMacroPrimitive.hh"

#include <iostream>
#include <string>

class ApertureMacroPrimitiveComment : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveComment(char* comment);

	virtual ~ApertureMacroPrimitiveComment();

private:
	std::ostream& do_print(std::ostream& os) const;

	std::string m_comment;
};

#endif // _APERTURE_MACRO_PRIMITIVE_COMMENT_H