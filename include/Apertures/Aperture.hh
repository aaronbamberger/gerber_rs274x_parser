/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_H
#define _APERTURE_H

#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

class Aperture {
public:
    Aperture();
    virtual ~Aperture();

    Gerber::SemanticValidity check_semantic_validity(SemanticIssueList& issue_list);

private:
    virtual Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list) = 0;
};

#endif // _APERTURE_H
