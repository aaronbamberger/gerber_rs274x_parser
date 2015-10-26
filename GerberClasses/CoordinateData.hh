#ifndef _COORDINATE_DATA_H
#define _COORDINATE_DATA_H

#include <iostream>

class CoordinateData {
public:
	CoordinateData(int x, int y, int i, int j, bool x_valid, bool y_valid, bool i_valid, bool j_valid);
	~CoordinateData();

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
};

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

#endif // _COORDINATE_DATA_H