#ifndef _STANDARD_APERTURE_CIRCLE_H
#define _STANDARD_APERTURE_CIRCLE_H

#include "StandardAperture.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

class StandardApertureCircle : public StandardAperture {
public:
	StandardApertureCircle(double diameter, double hole_diameter);
	StandardApertureCircle(double diameter);
	virtual ~StandardApertureCircle();

private:
	Gerber::SemanticValidity do_check_semantic_validity();
	std::ostream& do_print(std::ostream& os) const;
	std::shared_ptr<StandardAperture> do_clone();

	double m_diameter;
	double m_hole_diameter;
	bool m_has_hole;
};

#endif // _STANDARD_APERTURE_CIRCLE_H
