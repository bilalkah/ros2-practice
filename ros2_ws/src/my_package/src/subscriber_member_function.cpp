/**
 * @file subscriber_member_function.cpp
 * @author Bilal Kahraman (kahramannbilal@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalSubcsriber : public rclcpp::Node {
public:
  MinimalSubcsriber() : Node("minimal_subscriber") {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
        "topic", 10, std::bind(&MinimalSubcsriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::String &msg) const {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubcsriber>());
  rclcpp::shutdown();
  return 0;
}