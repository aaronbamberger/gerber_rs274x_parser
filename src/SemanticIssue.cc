/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "SemanticIssue.hh"
#include "GlobalDefs.hh"
#include "location.hh"

#include <string>
#include <iostream>

SemanticIssue::SemanticIssue(Gerber::SemanticValidity severity, yy::location location, std::string error_msg) :
    m_severity(severity), m_location(location), m_error_msg(error_msg)
{}

SemanticIssue::~SemanticIssue()
{}

Gerber::SemanticValidity SemanticIssue::severity()
{
    return m_severity;
}

std::ostream& operator<<(std::ostream& os, const SemanticIssue& issue)
{
    os << "Semantic Issue of Severity ";
    switch (issue.m_severity) {
    case Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL:
        os << "Fatal:" << "\n";
        break;

    case Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING:
        os << "Warning:" << "\n";
        break;

    case Gerber::SemanticValidity::SEMANTIC_VALIDITY_DEPRECATED:
        os << "Deprecation:" << "\n";
        break;

    case Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK:
        os << "None:" << "\n";
        break;
    }

    os << "\tLocation: @" << issue.m_location << "\n";
    os << "\tReason: " << issue.m_error_msg << std::endl;

    return os;
}
