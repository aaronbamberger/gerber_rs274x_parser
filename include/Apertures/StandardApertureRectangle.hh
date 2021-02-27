/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _STANDARD_APERTURE_RECTANGLE_H
#define _STANDARD_APERTURE_RECTANGLE_H

#include "Apertures/StandardAperture.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "location.hh"

#include <iostream>
#include <memory>

class StandardApertureRectangle : public StandardAperture {
public:
	StandardApertureRectangle(double x_size, double y_size, double hole_diameter);
	StandardApertureRectangle(double x_size, double y_size);
	StandardApertureRectangle(double x_size, double y_size, double hole_diameter,
        yy::location x_size_location, yy::location y_size_location,
        yy::location hole_diameter_location, yy::location location);
    StandardApertureRectangle(double x_size, double y_size,
        yy::location x_size_location, yy::location y_size_location, yy::location location);
	virtual ~StandardApertureRectangle();

private:
	Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
	std::ostream& do_print(std::ostream& os) const;
	std::shared_ptr<StandardAperture> do_clone();

	double m_x_size;
	double m_y_size;
	double m_hole_diameter;
	bool m_has_hole;
	yy::location m_x_size_location;
    yy::location m_y_size_location;
    yy::location m_hole_diameter_location;
    yy::location m_location;
};

#endif // _STANDARD_APERTURE_RECTANGLE_H
