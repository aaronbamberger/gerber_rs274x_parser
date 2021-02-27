/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

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
