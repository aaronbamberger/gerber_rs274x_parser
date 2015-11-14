#include "CoordinateData.hh"

#include <iostream>

CoordinateData::CoordinateData(int x, int y, int i, int j,
    bool x_valid, bool y_valid, bool i_valid, bool j_valid) :
	    m_x(x), m_y(y), m_i(i), m_j(j), m_x_valid(x_valid),
	    m_y_valid(y_valid), m_i_valid(i_valid), m_j_valid (j_valid)
{}

CoordinateData::CoordinateData(int x, int y, int i, int j,
    bool x_valid, bool y_valid, bool i_valid, bool j_valid,
    yy::location x_location, yy::location y_location,
    yy::location i_location, yy::location j_location) :
        m_x(x), m_y(y), m_i(i), m_j(j), m_x_valid(x_valid),
        m_y_valid(y_valid), m_i_valid(i_valid), m_j_valid (j_valid),
        m_x_location(x_location), m_y_location(y_location),
        m_i_location(i_location), m_j_location(j_location)
{}

CoordinateData::~CoordinateData()
{}

bool CoordinateData::x_valid()
{
    return m_x_valid;
}

bool CoordinateData::y_valid()
{
    return m_y_valid;
}

bool CoordinateData::i_valid()
{
    return m_i_valid;
}

bool CoordinateData::j_valid()
{
    return m_j_valid;
}

std::ostream& operator<<(std::ostream& os, const CoordinateData& coord_data)
{
	os << "Coordinate Data(";
	os << "X: ";
	if (coord_data.m_x_valid) {
		os << coord_data.m_x << " @" << coord_data.m_x_location;
	} else {
		os << "None";
	}
	os << ", Y: ";
	if (coord_data.m_y_valid) {
		os << coord_data.m_y << " @" << coord_data.m_y_location;
	} else {
		os << "None";
	}
	os << ", I: ";
	if (coord_data.m_i_valid) {
		os << coord_data.m_i << " @" << coord_data.m_i_location;
	} else {
		os << "None";
	}
	os << ", J: ";
	if (coord_data.m_j_valid) {
		os << coord_data.m_j << " @" << coord_data.m_j_location;
	} else {
		os << "None";
	}
	os << ")" << std::endl;
	return os;
}
