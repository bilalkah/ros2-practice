/**
 * @file test_service_server.cpp
 * @author Bilal Kahraman (kahramannbilal@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "my_package/srv/add_three_ints.hpp"
#include "rclcpp/rclcpp.hpp"

#include <memory>

void add(const std::shared_ptr<my_package::srv::AddThreeInts::Request> request,
         std::shared_ptr<my_package::srv::AddThreeInts::Response> response) {
  response->sum = request->a + request->b + request->c;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
              "Incoming request\na: %ld"
              "\nb: %ld"
              "\nc: %ld",
              request->a, request->b, request->c);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sending back response: [%ld]",
              (long int)response->sum);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared(
      "add_three_ints_server"); // node name must be unique

  rclcpp::Service<my_package::srv::AddThreeInts>::SharedPtr service =
      node->create_service<my_package::srv::AddThreeInts>("add_three_ints",
                                                          &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints.");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}