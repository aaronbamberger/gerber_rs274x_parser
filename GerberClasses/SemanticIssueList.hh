/*
 * SemanticIssueList.hh
 *
 *  Created on: Nov 14, 2015
 *      Author: abamberger
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
