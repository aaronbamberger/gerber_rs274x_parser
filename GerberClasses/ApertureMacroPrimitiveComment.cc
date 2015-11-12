#include "InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacroPrimitiveComment.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>
#include <string>

InstantiatedApertureMacroPrimitiveComment::InstantiatedApertureMacroPrimitiveComment(std::string& comment) : m_comment(comment)
{}

InstantiatedApertureMacroPrimitiveComment::~InstantiatedApertureMacroPrimitiveComment()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitiveComment::do_check_semantic_validity()
{
    // Comments are always semantically valid
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& InstantiatedApertureMacroPrimitiveComment::do_print(std::ostream& os) const
{
    os << "Instantiated Macro Primitive Comment: " << m_comment << std::endl;
    return os;
}

ApertureMacroPrimitiveComment::ApertureMacroPrimitiveComment(char* comment) : m_comment(comment)
{}

ApertureMacroPrimitiveComment::~ApertureMacroPrimitiveComment()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroPrimitiveComment::do_instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    return std::make_shared<InstantiatedApertureMacroPrimitiveComment>(m_comment);
}

std::ostream& ApertureMacroPrimitiveComment::do_print(std::ostream& os) const
{
	os << "Macro Primitive Comment: " << m_comment << std::endl;
	return os;
}
