cmake_minimum_required(VERSION 3.8)
project(my_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED) # Add package that above messages depend on, in this case geometry_msgs for Sphere.msg
find_package(rosidl_default_generators REQUIRED)
find_package(my_package REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

set(msg_files
  "msg/Num.msg"
  "msg/Sphere.msg"
  "msg/AddressBook.msg"
)

set(srv_files
  "srv/AddThreeInts.srv"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  DEPENDENCIES geometry_msgs # Add packages that above messages depend on, in this case geometry_msgs for Sphere.msg
)

ament_export_dependencies(rosidl_default_runtime)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_executable(server src/add_two_ints_server.cpp)
ament_target_dependencies(server rclcpp example_interfaces)

add_executable(client src/add_two_ints_client.cpp)
ament_target_dependencies(client rclcpp example_interfaces)

add_executable(test_pub src/test_pub.cpp)
ament_target_dependencies(test_pub rclcpp my_package)

add_executable(test_sub src/test_sub.cpp)
ament_target_dependencies(test_sub rclcpp my_package)

add_executable(test_server src/test_service_server.cpp)
ament_target_dependencies(test_server rclcpp my_package)

add_executable(test_client src/test_service_client.cpp)
ament_target_dependencies(test_client rclcpp my_package)

add_executable(publish_address_book src/publish_address_book.cpp)
ament_target_dependencies(publish_address_book rclcpp my_package)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp
)

target_link_libraries(publish_address_book
  "${cpp_typesupport_target}"
)

install(TARGETS
  talker
  listener  
  server
  client
  test_pub
  test_sub
  test_server
  test_client
  publish_address_book
  DESTINATION lib/${PROJECT_NAME})

ament_package()