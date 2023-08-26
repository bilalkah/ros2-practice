/**
 * @file publish_address_book.cpp
 * @author Bilal Kahraman (kahramannbilal@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "my_package/msg/address_book.hpp"
#include "rclcpp/rclcpp.hpp"

#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node {
public:
  AddressBookPublisher() : Node("address_book_publisher") {
    address_book_publisher_ =
        this->create_publisher<my_package::msg::AddressBook>("address_book",
                                                             10);
    auto publish_msg = [this]() -> void {
      auto message = my_package::msg::AddressBook();
      message.first_name = "Bilal";
      message.last_name = "Kahraman";
      message.phone_number = "1234567890";
      message.phone_type = message.PHONE_TYPE_MOBILE;

      RCLCPP_INFO(this->get_logger(), "Publishing: '%s %s %s %d'",
                  message.first_name.c_str(), message.last_name.c_str(),
                  message.phone_number.c_str(), message.phone_type);

      address_book_publisher_->publish(message);
    };
    timer_ = this->create_wall_timer(1s, publish_msg);
  }

private:
  rclcpp::Publisher<my_package::msg::AddressBook>::SharedPtr
      address_book_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AddressBookPublisher>());
  rclcpp::shutdown();
  return 0;
}