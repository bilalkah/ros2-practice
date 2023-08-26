/**
 * @file regular_polygon.hpp
 * @author Bilal Kahraman (kahramannbilal@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef POLYGON_BASE_REGULAR_POLYGON_HPP
#define POLYGON_BASE_REGULAR_POLYGON_HPP

namespace polygon_base {

class RegularPolygon {
public:
  virtual void initialize(double side_length) = 0;
  virtual double area() = 0;
  virtual ~RegularPolygon() {}

protected:
  RegularPolygon() {}
};

} // namespace polygon_base

#endif // POLYGON_BASE_REGULAR_POLYGON_HPP