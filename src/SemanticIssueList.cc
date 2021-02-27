/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
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
