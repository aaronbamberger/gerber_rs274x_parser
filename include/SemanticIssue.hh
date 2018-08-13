/*
 * SemanticIssue.hh
 *
 *  Created on: Nov 14, 2015
 *      Author: abamberger
 */

#ifndef _SEMANTIC_ISSUE_H
#define _SEMANTIC_ISSUE_H

#include "GlobalDefs.hh"
#include "location.hh"

#include <string>
#include <iostream>

class SemanticIssue {
public:
    SemanticIssue(Gerber::SemanticValidity severity, yy::location location, std::string error_msg);
    ~SemanticIssue();
    Gerber::SemanticValidity severity();

    friend std::ostream& operator<<(std::ostream& os, const SemanticIssue& issue);

private:
    Gerber::SemanticValidity m_severity;
    yy::location m_location;
    std::string m_error_msg;
};

#endif // _SEMANTIC_ISSUE_H
