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

#endif // _COORDINATE_DATA_H