#ifndef COMPLEXQUAD_HPP
#define COMPLEXQUAD_HPP

#include "shape.hpp"

namespace ketov {
  class Complexquad: public Shape {
  public:
    virtual ~Complexquad() = default;
    Complexquad(point_t p1, point_t p2, point_t p3, point_t p4);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t new_pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t p1_;
    point_t p2_;
    point_t p3_;
    point_t p4_;
    point_t pos_;
    bool cross1_;
  };
}

#endif 
