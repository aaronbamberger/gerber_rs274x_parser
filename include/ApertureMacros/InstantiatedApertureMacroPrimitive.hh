/*
 * InstantiatedApertureMacroPrimitive.h
 *
 *  Created on: Nov 8, 2015
 *      Author: abamberger
 */

#ifndef _INSTANTIATED_APERTURE_MACRO_PRIMITIVE_H
#define _INSTANTIATED_APERTURE_MACRO_PRIMITIVE_H

#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>

class InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitive();
    virtual ~InstantiatedApertureMacroPrimitive();

    Gerber::SemanticValidity check_semantic_validity(SemanticIssueList& issue_list);

    friend std::ostream& operator<<(std::ostream& os, const InstantiatedApertureMacroPrimitive& macro_primitive);

private:
    virtual Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list) = 0;
    virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _INSTANTIATED_APERTURE_MACRO_PRIMITIVE_H
