#ifndef _POINT_H
#define _POINT_H

template <typename T> struct Point {
    Point()
    {}

	Point(T x_coord, T y_coord) : x(x_coord), y(y_coord)
	{}

	T x;
	T y;
};

#endif // _POINT_H
