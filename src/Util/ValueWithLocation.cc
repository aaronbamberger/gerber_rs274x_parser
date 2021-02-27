/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Util/ValueWithLocation.hh"

template<typename T>
ValueWithLocation<T>::ValueWithLocation()
{}

template<typename T>
ValueWithLocation<T>::ValueWithLocation(T value, yy::location location) :
	m_location(location), m_value(value)
{}

template<typename T>
ValueWithLocation<T>::~ValueWithLocation()
{}

template<typename T>
T& ValueWithLocation<T>::get_value()
{
	return m_value;
}
