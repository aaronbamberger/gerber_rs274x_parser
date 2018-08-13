#ifndef _STANDARD_APERTURE_CIRCLE_H
#define _STANDARD_APERTURE_CIRCLE_H

#include "Apertures/StandardAperture.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "location.hh"

#include <iostream>
#include <memory>

class StandardApertureCircle : public StandardAperture {
public:
	StandardApertureCircle(double diameter, double hole_diameter);
	StandardApertureCircle(double diameter);
	StandardApertureCircle(double diameter, double hole_diameter, yy::location diameter_location,
        yy::location hole_location, yy::location location);
    StandardApertureCircle(double diameter, yy::location diameter_location, yy::location location);
	virtual ~StandardApertureCircle();

private:
	Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
	std::ostream& do_print(std::ostream& os) const;
	std::shared_ptr<StandardAperture> do_clone();

	double m_diameter;
	double m_hole_diameter;
	bool m_has_hole;
	yy::location m_diameter_location;
	yy::location m_hole_diameter_location;
	yy::location m_location;
};

#endif // _STANDARD_APERTURE_CIRCLE_H
