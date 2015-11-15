/*
 * SemanticIssueList.cc
 *
 *  Created on: Nov 14, 2015
 *      Author: abamberger
 */

#include "SemanticIssueList.hh"
#include "SemanticIssue.hh"

#include <iostream>

SemanticIssueList::SemanticIssueList()
{}

SemanticIssueList::~SemanticIssueList()
{}

void SemanticIssueList::add_issue(const SemanticIssue& issue)
{
    m_issue_list.push_back(issue);
}

std::ostream& operator<<(std::ostream& os, const SemanticIssueList& issue_list)
{
    for (auto issue : issue_list.m_issue_list) {
        os << issue;
    }

    return os;
}
