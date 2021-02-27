/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _SEMANTIC_ISSUE_LIST_H
#define _SEMANTIC_ISSUE_LIST_H

#include "SemanticIssue.hh"

#include <list>
#include <iostream>

class SemanticIssueList {
public:
    SemanticIssueList();
    virtual ~SemanticIssueList();

    void add_issue(const SemanticIssue& issue);

    friend std::ostream& operator<<(std::ostream& os, const SemanticIssueList& issue_list);

private:
    std::list<SemanticIssue> m_issue_list;
};

#endif // _SEMANTIC_ISSUE_LIST
