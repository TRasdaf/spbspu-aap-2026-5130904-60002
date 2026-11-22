#include "complexquad.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "triangle.hpp"

namespace ketov {
  Complexquad::Complexquad(point_t p1, point_t p2, point_t p3, point_t p4) :
    p1_(p1),
    p2_(p2),
    p3_(p3),
    p4_(p4),
    pos_{0.0, 0.0}
  {
    const double eps = 1e-9;

    bool cross1 = false;
    point_t inter1{};
    double denom1 = (p2_.x - p1_.x) * (p4_.y - p3_.y) - (p2_.y - p1_.y) * (p4_.x - p3_.x);
    if (std::abs(denom1) >= eps) {
      double t1 = ((p3_.x - p1_.x) * (p4_.y - p3_.y) - (p3_.y - p1_.y) * (p4_.x - p3_.x)) / denom1;
      double u1 = ((p3_.x - p1_.x) * (p2_.y - p1_.y) - (p3_.y - p1_.y) * (p2_.x - p1_.x)) / denom1;
      if (t1 > eps && t1 < 1.0 - eps && u1 > eps && u1 < 1.0 - eps) {
        cross1 = true;
        inter1.x = p1_.x + t1 * (p2_.x - p1_.x);
        inter1.y = p1_.y + t1 * (p2_.y - p1_.y);
      }
    }

    bool cross2 = false;
    point_t inter2{};
    double denom2 = (p3_.x - p2_.x) * (p1_.y - p4_.y) - (p3_.y - p2_.y) * (p1_.x - p4_.x);
    if (std::abs(denom2) >= eps) {
      double t2 = ((p4_.x - p2_.x) * (p1_.y - p4_.y) - (p4_.y - p2_.y) * (p1_.x - p4_.x)) / denom2;
      double u2 = ((p4_.x - p2_.x) * (p3_.y - p2_.y) - (p4_.y - p2_.y) * (p3_.x - p2_.x)) / denom2;
      if (t2 > eps && t2 < 1.0 - eps && u2 > eps && u2 < 1.0 - eps) {
        cross2 = true;
        inter2.x = p2_.x + t2 * (p3_.x - p2_.x);
        inter2.y = p2_.y + t2 * (p3_.y - p2_.y);
      }
    }

    if (cross1 == cross2) {
      throw std::invalid_argument("Points do not form a self-intersecting quadrilateral");
    }

    pos_ = cross1 ? inter1 : inter2;

    double area1 = 0.0;
    double area2 = 0.0;
    if (cross1) {
      area1 = 0.5 * std::abs((pos_.x - p1_.x) * (p4_.y - p1_.y) - (p4_.x - p1_.x) * (pos_.y - p1_.y));
      area2 = 0.5 * std::abs((p3_.x - p2_.x) * (pos_.y - p2_.y) - (pos_.x - p2_.x) * (p3_.y - p2_.y));
    } else {
      area1 = 0.5 * std::abs((p2_.x - p1_.x) * (pos_.y - p1_.y) - (pos_.x - p1_.x) * (p2_.y - p1_.y));
      area2 = 0.5 * std::abs((p4_.x - p3_.x) * (pos_.y - p3_.y) - (pos_.x - p3_.x) * (p4_.y - p3_.y));
    }

    if (area1 < eps || area2 < eps) {
      throw std::invalid_argument("Degenerate complexquad");
    }

    cross1_ = cross1;
  }

  double Complexquad::getArea() const
  {
    if (cross1_) {
      Triangle tr1(p1_, p4_, pos_);
      Triangle tr2(p2_, p3_, pos_);
      return tr1.getArea() + tr2.getArea();
    }
    Triangle tr1(p1_, p2_, pos_);
    Triangle tr2(p3_, p4_, pos_);
    return tr1.getArea() + tr2.getArea();
  }

  void Complexquad::move(point_t new_pos)
  {
    double dx = new_pos.x - pos_.x;
    double dy = new_pos.y - pos_.y;
    move(dx, dy);
    pos_ = new_pos;
  }

  void Complexquad::move(double dx, double dy)
  {
    p1_.x += dx;
    p1_.y += dy;
    p2_.x += dx;
    p2_.y += dy;
    p3_.x += dx;
    p3_.y += dy;
    p4_.x += dx;
    p4_.y += dy;
    pos_.x += dx;
    pos_.y += dy;
  }

  void Complexquad::scale(double factor)
  {
    if (factor <= 0) {
      throw std::invalid_argument("Scale factor must be greater than 0");
    }

    p1_.x = pos_.x + (p1_.x - pos_.x) * factor;
    p1_.y = pos_.y + (p1_.y - pos_.y) * factor;
    p2_.x = pos_.x + (p2_.x - pos_.x) * factor;
    p2_.y = pos_.y + (p2_.y - pos_.y) * factor;
    p3_.x = pos_.x + (p3_.x - pos_.x) * factor;
    p3_.y = pos_.y + (p3_.y - pos_.y) * factor;
    p4_.x = pos_.x + (p4_.x - pos_.x) * factor;
    p4_.y = pos_.y + (p4_.y - pos_.y) * factor;
  }

  rectangle_t Complexquad::getFrameRect() const
  {
    rectangle_t frame_rect;

    double x_max = std::max({p1_.x, p2_.x, p3_.x, p4_.x});
    double y_max = std::max({p1_.y, p2_.y, p3_.y, p4_.y});
    double x_min = std::min({p1_.x, p2_.x, p3_.x, p4_.x});
    double y_min = std::min({p1_.y, p2_.y, p3_.y, p4_.y});

    frame_rect.height = y_max - y_min;
    frame_rect.width = x_max - x_min;
    frame_rect.pos = {(x_max + x_min) / 2.0, (y_max + y_min) / 2.0};

    return frame_rect;
  }
} 
