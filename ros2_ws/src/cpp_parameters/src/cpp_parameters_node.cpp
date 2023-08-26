/**
 * @file cpp_parameters_node.cpp
 * @author Bilal Kahraman (kahramannbilal@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "rclcpp/rclcpp.hpp"

#include <chrono>
#include <functional>
#include <string>

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node {
public:
  MinimalParam() : Node("minimal_param_node") {
    auto param_desc = rcl_interfaces::msg::ParameterDescriptor();
    param_desc.description = "A parameter that stores a string.";

    this->declare_parameter("my_parameter", "world", param_desc);
    timer_ = this->create_wall_timer(
        1000ms, std::bind(&MinimalParam::timer_callback, this));
  }

  void timer_callback() {
    std::string my_param = this->get_parameter("my_parameter").as_string();

    RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());
    std::vector<rclcpp::Parameter> all_new_parameters{
        rclcpp::Parameter("my_parameter", "world")};
    this->set_parameters(all_new_parameters);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalParam>());
  rclcpp::shutdown();
  return 0;
}