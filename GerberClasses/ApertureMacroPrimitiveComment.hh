#ifndef _APERTURE_MACRO_PRIMITIVE_COMMENT_H
#define _APERTURE_MACRO_PRIMITIVE_COMMENT_H

#include "ApertureMacroPrimitive.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>
#include <string>

class InstantiatedApertureMacroPrimitiveComment : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitiveComment(std::string& comment);

    virtual ~InstantiatedApertureMacroPrimitiveComment();

private:
    Gerber::SemanticValidity do_check_semantic_validity();

    std::string m_comment;
};

class ApertureMacroPrimitiveComment : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveComment(char* comment);

	virtual ~ApertureMacroPrimitiveComment();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	std::string m_comment;
};

#endif // _APERTURE_MACRO_PRIMITIVE_COMMENT_H
