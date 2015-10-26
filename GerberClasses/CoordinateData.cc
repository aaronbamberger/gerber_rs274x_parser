#include "CoordinateData.hh"

#include <iostream>

CoordinateData::CoordinateData(int x, int y, int i, int j, bool x_valid, bool y_valid, bool i_valid, bool j_valid) :
	m_x(x), m_y(y), m_i(i), m_j(j), m_x_valid(x_valid), m_y_valid(y_valid), m_i_valid(i_valid), m_j_valid (j_valid)
{}

CoordinateData::~CoordinateData()
{
	std::cout << "Coordinate data destroyed" << std::endl;
}