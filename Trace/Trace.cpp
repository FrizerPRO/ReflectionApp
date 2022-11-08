#include "Trace.h"

//Returns the distance from the point with the guide vector to the circle.
float Trace::GetCircleDistance(sf::CircleShape *circle_, int number) const {
    //Center of the circle position.
    sf::Vector2f center_position = circle_->getPosition() + sf::Vector2f(circle_->getRadius(), circle_->getRadius());
    //Angle between your_point-to-circle_center vector and your_vector.
    float angle = Vector2D<sf::Vector2f>::GetAngleAbsolute<sf::Vector2f>
        (center_position,
         line_array[number].getPosition(),
         line_array[number].getRotation());
    //Distance to center.
    float distance_to_center =
        Vector2D<sf::Vector2f>::Length(-line_array[number].getPosition() + center_position);
    //Checking if the vector intersects the circle.
    if (std::abs(std::sin(angle)) > (circle_->getRadius() / distance_to_center)) {
        return -1;
    }
    //Distance to the first point of intersection.
    float first_point = distance_to_center * std::cos(angle) + sqrtf(circle_->getRadius() * circle_->getRadius()
                                                                         - distance_to_center * distance_to_center
                                                                             * std::sin(angle) * std::sin(angle));
    //Distance to the second point of intersection.
    float second_point = distance_to_center * std::cos(angle) - sqrtf(circle_->getRadius() * circle_->getRadius()
                                                                          - distance_to_center * distance_to_center
                                                                              * std::sin(angle) * std::sin(angle));
    //Returning distance to the nearest point
    return std::min(first_point, second_point);
}
//Creates new rectangle(the ray).
sf::RectangleShape Trace::CreateNewLine(const sf::RectangleShape &rec) {
    sf::RectangleShape rectangle_(sf::Vector2f(
        window_.getSize().x,
        rec.getSize().y - width_delta));
    rectangle_.rotate(rec.getRotation() + 180);
    rectangle_.setPosition(rec.getPosition().x + rec.getSize().x * cosf(rec.getRotation() * M_PI / 180),
                           rec.getPosition().y + rec.getSize().x * sinf(rec.getRotation() * M_PI / 180));
    return rectangle_;
};
//Returns reflection angle(reflects in point A).
float Trace::GetReflectionAngle(const sf::Vector2f &a_point, const sf::Vector2f &b_point, const sf::Vector2f &c_point) {
    float a_side = Vector2D<sf::Vector2f>::Length(b_point - c_point);
    float b_side = Vector2D<sf::Vector2f>::Length(a_point - c_point);
    float c_side = Vector2D<sf::Vector2f>::Length(b_point - a_point);
    float angle = acosf((b_side * b_side + c_side * c_side - a_side * a_side) / (2 * b_side * c_side));
    float angle_with_sign =
        Vector2D<sf::Vector2f>::DirectionOfVectorRegardingXAxis(a_point - c_point,
                                                                b_point - c_point,
                                                                b_point - a_point) * angle;
    return angle_with_sign;
}
//Returns the distance from the point with the guide vector to the rectangle.
float GetRectangleDistance(sf::RectangleShape *rectangle_) {
    return 0;
}
sf::Vector3<float> Trace::GetColorInRGB(int32_t color_) {
    int red = (color_ & 0xFF000000) >> 24;
    int green = (color_ & 0x00FF0000) >> 16;
    int blue = (color_ & 0x0000FF00) >> 8;
    return sf::Vector3<float>(red, green, blue);
}
//Creating new trace for circle.
void Trace::CreateTraceForCircle(sf::CircleShape *circle_, int position_) {
    float reflection_angle = GetReflectionAngle(
        line_array[position_].getPosition() +
            sf::Vector2f(line_array[position_].getSize().x * cosf(line_array[position_].getRotation() * M_PI / 180),
                         line_array[position_].getSize().x * sinf(line_array[position_].getRotation() * M_PI / 180)),
        circle_->getPosition() + sf::Vector2f(circle_->getRadius(), circle_->getRadius()),
        line_array[position_].getPosition());
    sf::RectangleShape rectangle_ = CreateNewLine(line_array[position_]);
    rectangle_.rotate(-2 * (reflection_angle * 180 / M_PI));
    //Setting reflection color.
    rectangle_.setFillColor(sf::Color(
        (GetColorInRGB(circle_->getFillColor().toInteger()) * (1 - color_reflection_factor)
            + color_reflection_factor * GetColorInRGB(line_array[position_].getFillColor().toInteger())).x,
        (GetColorInRGB(circle_->getFillColor().toInteger()) * (1 - color_reflection_factor)
            + color_reflection_factor * GetColorInRGB(line_array[position_].getFillColor().toInteger())).y,
        (GetColorInRGB(circle_->getFillColor().toInteger()) * (1 - color_reflection_factor)
            + color_reflection_factor * GetColorInRGB(line_array[position_].getFillColor().toInteger())).z));
    line_array.push_back(rectangle_);
}
//Making Retracing for every trace.
void Trace::Retrace(std::vector<sf::Shape *> &shapes_array) {
    //Check every ray.
    for (unsigned int i = 0; i < line_array.size(); i++) {
        bool intersects_shape = false;
        //Check every shape.
        for (unsigned int j = 0; j < shapes_array.size(); j++) {
            float changed_length = 0.0f;
            //If the shape is Circle.
            if (sf::CircleShape *circle_ = dynamic_cast<sf::CircleShape *>(shapes_array[j])) {
                //Distance to circle(==-1 if doesn't intersect).
                float x_size = GetCircleDistance(circle_, i);
                if (intersects_shape)
                    continue;
                //If the ray intersects the circle.
                if (x_size > 0) {
                    intersects_shape = true;
                    line_array[i].setSize(sf::Vector2f(x_size, line_array[i].getSize().y));
                    CreateTraceForCircle(circle_, i);
                }
                    //If the ray doesn't intersect the circle.
                else {
                    line_array[i].setSize(sf::Vector2f(
                        sqrtf(window_.getSize().x * window_.getSize().x + window_.getSize().y * window_.getSize().y)
                            + width_, line_array[i].getSize().y));
                }
            }
        }
    }
}
//Creates trace.
Trace::Trace(sf::RenderWindow &window, int width) : window_(window), width_(width) {
    line_array = std::vector<sf::RectangleShape>();
    line_array.emplace_back(sf::Vector2f(
        sqrtf(window.getSize().x * window.getSize().x + window.getSize().y * window.getSize().y) + width,
        width));
    temporary_array = std::vector<sf::RectangleShape>();
}
//Sets position of initial trace.
void Trace::setPosition(sf::Vector2f pos) {
    line_array[0].setPosition(pos);
}
//Draws all the traces.
void Trace::Draw(std::vector<sf::Shape *> &shapes_array) {
    Retrace(shapes_array);
    for (const auto &line : line_array) {
        window_.draw(line);
    }
    //for temporary array.
    for (const auto &line : temporary_array) {
        window_.draw(line);
    }
}
//Ray points the mouse.
void Trace::TrackMouse() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        float angle = Vector2D<sf::Vector2i>::GetAngleAbsolute<sf::Vector2f>(sf::Mouse::getPosition(window_),
                                                                             line_array[0].getPosition(),
                                                                             line_array[0].getRotation()) * 180 / M_PI;
        line_array[0].rotate(angle);
    }
}
