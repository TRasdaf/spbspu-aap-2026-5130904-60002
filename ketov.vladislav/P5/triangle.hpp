#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace ketov {
  class Triangle: public Shape {
  public:
    virtual ~Triangle() = default;
    Triangle(point_t p1, point_t p2, point_t p3);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t new_pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t p1_;
    point_t p2_;
    point_t p3_;
  };
} 

#endif 
