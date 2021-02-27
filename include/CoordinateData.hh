/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _COORDINATE_DATA_H
#define _COORDINATE_DATA_H

#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>

class CoordinateData {
public:
	CoordinateData(int x, int y, int i, int j,
        bool x_valid, bool y_valid, bool i_valid, bool j_valid);

	CoordinateData(int x, int y, int i, int j,
        bool x_valid, bool y_valid, bool i_valid, bool j_valid,
        yy::location x_location, yy::location y_location,
        yy::location i_location, yy::location j_location);

	~CoordinateData();

	Gerber::SemanticValidity check_semantic_validity(const GraphicsState& graphics_state, SemanticIssueList& issue_list);

	bool x_valid();
	bool y_valid();
	bool i_valid();
	bool j_valid();

	yy::location i_loc();
    yy::location j_loc();
    yy::location ij_loc();

	friend std::ostream& operator<<(std::ostream& os, const CoordinateData& coord_data);

private:
	int m_x;
	int m_y;
	int m_i;
	int m_j;
	bool m_x_valid;
	bool m_y_valid;
	bool m_i_valid;
	bool m_j_valid;
	yy::location m_x_location;
	yy::location m_y_location;
	yy::location m_i_location;
	yy::location m_j_location;
};

#endif // _COORDINATE_DATA_H
