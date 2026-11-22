#include "triangle.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace ketov {
  Triangle::Triangle(point_t p1, point_t p2, point_t p3) : p1_(p1), p2_(p2), p3_(p3)
  {
    if (getArea() < 1e-9) {
      throw std::invalid_argument("invalid argument");
    }
  }

  double Triangle::getArea() const
  {
    return 0.5 * std::abs((p2_.x - p1_.x) * (p3_.y - p1_.y) - (p3_.x - p1_.x) * (p2_.y - p1_.y));
  }

  rectangle_t Triangle::getFrameRect() const
  {
    rectangle_t frame_rect;

    double x_max = std::max({p1_.x, p2_.x, p3_.x});
    double y_max = std::max({p1_.y, p2_.y, p3_.y});
    double x_min = std::min({p1_.x, p2_.x, p3_.x});
    double y_min = std::min({p1_.y, p2_.y, p3_.y});

    frame_rect.height = y_max - y_min;
    frame_rect.width = x_max - x_min;
    frame_rect.pos = {(x_max + x_min) / 2.0, (y_max + y_min) / 2.0};

    return frame_rect;
  }

  void Triangle::move(point_t new_pos)
  {
    point_t pos;

    pos = {(p1_.x + p2_.x + p3_.x) / 3.0, (p1_.y + p2_.y + p3_.y) / 3.0};
    double dx = new_pos.x - pos.x;
    double dy = new_pos.y - pos.y;

    move(dx, dy);
  }

  void Triangle::move(double dx, double dy)
  {
    p1_.x += dx;
    p1_.y += dy;
    p2_.x += dx;
    p2_.y += dy;
    p3_.x += dx;
    p3_.y += dy;
  }

  void Triangle::scale(double factor)
  {
    if (factor <= 0) {
      throw std::invalid_argument("invalid argument");
    }
    point_t pos = {(p1_.x + p2_.x + p3_.x) / 3.0, (p1_.y + p2_.y + p3_.y) / 3.0};

    p1_.x = pos.x + (p1_.x - pos.x) * factor;
    p1_.y = pos.y + (p1_.y - pos.y) * factor;
    p2_.x = pos.x + (p2_.x - pos.x) * factor;
    p2_.y = pos.y + (p2_.y - pos.y) * factor;
    p3_.x = pos.x + (p3_.x - pos.x) * factor;
    p3_.y = pos.y + (p3_.y - pos.y) * factor;
  }
} 
