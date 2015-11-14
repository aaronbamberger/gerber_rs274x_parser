#ifndef _COORDINATE_DATA_H
#define _COORDINATE_DATA_H

#include "../location.hh"

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

	bool x_valid();
	bool y_valid();
	bool i_valid();
	bool j_valid();

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
