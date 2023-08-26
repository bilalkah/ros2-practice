/**
 * @file test_sub.cpp
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

#include <functional>
#include <memory>

using std::placeholders::_1;

class MinimalSubcsriber : public rclcpp::Node {
public:
  MinimalSubcsriber() : Node("minimal_subscriber") {
    subscription_ = this->create_subscription<my_package::msg::Num>(
        "topic", 10, std::bind(&MinimalSubcsriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const my_package::msg::Num::SharedPtr msg) const {
    RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->num);
  }
  rclcpp::Subscription<my_package::msg::Num>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubcsriber>());
  rclcpp::shutdown();
  return 0;
}