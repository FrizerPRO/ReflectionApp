//
// Created by loxam on 7/20/2022.
//

#ifndef UNTITLED26__TRACE_H_
#define UNTITLED26__TRACE_H_
#include "../Vector2D/Vector2D.h"
#include <SFML/System/Vector3.hpp>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include <SFML/Window/Mouse.hpp>

class Trace {
 private:
  //Difference between two neighboring lines.
  const float width_delta = 1.0f;
  //Temporary array for testing.
  std::vector<sf::RectangleShape> temporary_array;
  //Array of traces.
  std::vector<sf::RectangleShape> line_array;
  //Window for render.
  sf::RenderWindow &window_;
  //Width of the trace.
  int width_;
  const float color_reflection_factor = 0.5f;
  //Returns the distance from the point with the guide vector to the circle.
  float GetCircleDistance(sf::CircleShape *circle_, int number) const;
  //Creates new rectangle(the ray).
  sf::RectangleShape CreateNewLine(const sf::RectangleShape &rec);
//Returns reflection angle(reflects in point A).
  float GetReflectionAngle(const sf::Vector2f &a_point, const sf::Vector2f &b_point, const sf::Vector2f &c_point);
  //Returns the distance from the point with the guide vector to the rectangle.
  sf::Vector3<float> GetColorInRGB(int32_t color_);
  //Creating next trace for circle.
  void CreateTraceForCircle(sf::CircleShape *circle_, int position_);
  //Making Retracing for every trace.
  void Retrace(std::vector<sf::Shape *> &shapes_array);
 public:
  //Creates trace.
  Trace(sf::RenderWindow &window, int width = 3);
  //Sets position of initial trace.
  void setPosition(sf::Vector2f pos);
  //Draws all the traces.
  void Draw(std::vector<sf::Shape *> &shapes_array);
  //Ray points the mouse.
  void TrackMouse();
};

#endif //UNTITLED26__TRACE_H_
