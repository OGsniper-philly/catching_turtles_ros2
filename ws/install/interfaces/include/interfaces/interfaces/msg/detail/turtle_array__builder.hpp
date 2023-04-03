// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/TurtleArray.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__TURTLE_ARRAY__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__TURTLE_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/turtle_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_TurtleArray_alive_turtles
{
public:
  Init_TurtleArray_alive_turtles()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::msg::TurtleArray alive_turtles(::interfaces::msg::TurtleArray::_alive_turtles_type arg)
  {
    msg_.alive_turtles = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::TurtleArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::TurtleArray>()
{
  return interfaces::msg::builder::Init_TurtleArray_alive_turtles();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__TURTLE_ARRAY__BUILDER_HPP_
