//
// Created by loxam on 7/20/2022.
//
#ifndef UNTITLED26_CMAKE_BUILD_DEBUG_VECTOR2D_H_
#define UNTITLED26_CMAKE_BUILD_DEBUG_VECTOR2D_H_

#include <cmath>

template<typename Vector>
class Vector2D {
 public:
  static Vector GetRotatedCoordinates(Vector &vector_, float angle) {
      return Vector(vector_.x * cosf(angle) + vector_.y * sinf(angle),
                    vector_.y * cosf(angle) - vector_.x * sinf(angle));
  }
  //Returns angle between -PI and PI.
  static float GetAngleBetweenPi(float angle) {
      while (std::abs(angle) > M_PI) {
          if (angle > 0)
              angle -= 2 * M_PI;
          else
              angle += 2 * M_PI;
      }
      return angle;
  }
  //Returns normalized vector.
  static Vector Normalize(Vector vector_) {
      float length = Length(vector_);
      return Vector(vector_.x / length, vector_.y / length);
  }
  //Returns Angle between two vectors.
  template<typename Vector1>
  static float GetAngleAbsolute(const Vector &vector_1, const Vector1 &vector_2, float vector_2_rotation) {
      Vector shape_pos(vector_1.x - vector_2.x,
                       vector_1.y - vector_2.y);
      float angle = std::atan2(shape_pos.y, shape_pos.x) - vector_2_rotation * M_PI / 180;
      return angle;
  }
  static float GetAngleRegarding(const Vector &vector_1, const Vector &vector_2) {
      float dot = vector_1.x * vector_2.x + vector_1.y * vector_2.y;
      float det = vector_1.x * vector_2.x - vector_1.y * vector_2.y;
      float angle = atan2f(det, dot);
      return angle;
  }
  //Returns length of vector.
  static float Length(Vector vector_) {
      return sqrtf((vector_.x * vector_.x) + (vector_.y * vector_.y));
  }
  //Returns sign of the difference of x-projections.
  static int DirectionOfVectorRegardingXAxis(Vector vector_angle_1, Vector vector_angle_2, Vector vector_direction) {
      float angle = (M_PI / 2 - atan2f(vector_angle_2.y, vector_angle_2.x));
      if ((GetRotatedCoordinates(vector_angle_1, -angle)).x > 0) {
          return 1;
      }
      return -1;
  }
};


#endif //UNTITLED26_CMAKE_BUILD_DEBUG_VECTOR2D_H_
