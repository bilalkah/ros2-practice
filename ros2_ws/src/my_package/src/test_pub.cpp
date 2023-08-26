/**
 * @file test_pub.cpp
 * @author Bilal Kahraman (kahramannbilal@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "my_package/msg/num.hpp"
#include "rclcpp/rclcpp.hpp"

#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node {
public:
  MinimalPublisher() : Node("minimal_publisher"), count_(0) {
    publisher_ = this->create_publisher<my_package::msg::Num>("topic", 10);
    timer_ = this->create_wall_timer(
        500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback() {
    auto message = my_package::msg::Num();
    message.num = count_++;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.num);
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<my_package::msg::Num>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}