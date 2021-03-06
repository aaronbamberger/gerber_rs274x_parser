/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _INSTANTIATED_APERTURE_MACRO_H
#define _INSTANTIATED_APERTURE_MACRO_H

#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "Apertures/Aperture.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <memory>
#include <list>

class InstantiatedApertureMacro : public Aperture {
public:
    InstantiatedApertureMacro();
    virtual ~InstantiatedApertureMacro();

    void add_instantiated_macro_content(std::shared_ptr<InstantiatedApertureMacroPrimitive> instantiated_primitive);

private:
    virtual Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);

    std::list<std::shared_ptr<InstantiatedApertureMacroPrimitive> > m_macro_content;
};

#endif // _INSTANTIATED_APERTURE_MACRO_H
