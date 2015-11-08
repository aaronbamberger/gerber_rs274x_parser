#include "CoordinateData.hh"

#include <iostream>

CoordinateData::CoordinateData(int x, int y, int i, int j, bool x_valid, bool y_valid, bool i_valid, bool j_valid) :
	m_x(x), m_y(y), m_i(i), m_j(j), m_x_valid(x_valid), m_y_valid(y_valid), m_i_valid(i_valid), m_j_valid (j_valid)
{}

CoordinateData::~CoordinateData()
{
	//std::cout << "Coordinate data destroyed" << std::endl;
}

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
		os << coord_data.m_x;
	} else {
		os << "None";
	}
	os << ", Y: ";
	if (coord_data.m_y_valid) {
		os << coord_data.m_y;
	} else {
		os << "None";
	}
	os << ", I: ";
	if (coord_data.m_i_valid) {
		os << coord_data.m_i;
	} else {
		os << "None";
	}
	os << ", J: ";
	if (coord_data.m_j_valid) {
		os << coord_data.m_j;
	} else {
		os << "None";
	}
	os << ")" << std::endl;
	return os;
}
