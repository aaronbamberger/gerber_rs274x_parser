#ifndef _APERTURE_MACRO_PRIMITIVE_POLYGON_H
#define _APERTURE_MACRO_PRIMITIVE_POLYGON_H

#include "ApertureMacroPrimitive.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>
#include <memory>

template <typename T> struct Polygon {
    Polygon(T exposure, T num_vertices, T center_x, T center_y, T diameter, T rotation) :
        m_exposure(exposure), m_num_vertices(num_vertices), m_center_x(center_x),
        m_center_y(center_y), m_diameter(diameter), m_rotation(rotation), m_has_rotation(true)
    {}

    Polygon(T exposure, T num_vertices, T center_x, T center_y, T diameter) :
        m_exposure(exposure), m_num_vertices(num_vertices), m_center_x(center_x),
        m_center_y(center_y), m_diameter(diameter), m_has_rotation(false)
    {}

    ~Polygon()
    {}

    T m_exposure;
    T m_num_vertices;
    T m_center_x;
    T m_center_y;
    T m_diameter;
    T m_rotation;
    bool m_has_rotation;
};

class InstantiatedApertureMacroPrimitivePolygon : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitivePolygon(double exposure,
        double num_vertices,
        double center_x,
        double center_y,
        double diameter,
        double rotation);

    InstantiatedApertureMacroPrimitivePolygon(double exposure,
        double num_vertices,
        double center_x,
        double center_y,
        double diameter);

    virtual ~InstantiatedApertureMacroPrimitivePolygon();

private:
    Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
    std::ostream& do_print(std::ostream& os) const;

    Polygon<double> m_polygon;
};

class ApertureMacroPrimitivePolygon : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitivePolygon(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_vertices,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> diameter,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitivePolygon(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_vertices,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> diameter);

	virtual ~ApertureMacroPrimitivePolygon();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	Polygon<std::shared_ptr<ArithmeticExpressionElement> > m_polygon;
};

#endif // _APERTURE_MACRO_PRIMITIVE_POLYGON_H
