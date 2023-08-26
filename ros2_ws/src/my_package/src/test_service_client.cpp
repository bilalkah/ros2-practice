/**
 * @file test_service_client.cpp
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
#include <chrono>
#include <cstdlib>

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared(
      "add_three_ints_client"); // node name must be unique

  rclcpp::Client<my_package::srv::AddThreeInts>::SharedPtr client =
      node->create_client<my_package::srv::AddThreeInts>("add_three_ints");

  auto request = std::make_shared<my_package::srv::AddThreeInts::Request>();
  request->a = atoll(argv[1]);
  request->b = atoll(argv[2]);
  request->c = atoll(argv[3]);

  while (!client->wait_for_service(std::chrono::seconds(1))) {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Waiting for service to appear...");
  }

  auto result = client->async_send_request(request);

  if (rclcpp::spin_until_future_complete(node, result) ==
      rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service");
  }

  rclcpp::shutdown();
  return 0;
}