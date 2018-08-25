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
