/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_MACRO_PRIMITIVE_COMMENT_H
#define _APERTURE_MACRO_PRIMITIVE_COMMENT_H

#include "ApertureMacros/ApertureMacroPrimitive.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>
#include <memory>
#include <string>

class InstantiatedApertureMacroPrimitiveComment : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitiveComment(std::string comment);

    virtual ~InstantiatedApertureMacroPrimitiveComment();

private:
    Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
    std::ostream& do_print(std::ostream& os) const;

    std::string m_comment;
};

class ApertureMacroPrimitiveComment : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveComment(std::string comment);

	virtual ~ApertureMacroPrimitiveComment();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	std::string m_comment;
};

#endif // _APERTURE_MACRO_PRIMITIVE_COMMENT_H
