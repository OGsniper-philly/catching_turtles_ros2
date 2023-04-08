// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/Turtle.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__TURTLE__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__TURTLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/turtle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_Turtle_pose
{
public:
  explicit Init_Turtle_pose(::interfaces::msg::Turtle & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::Turtle pose(::interfaces::msg::Turtle::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::Turtle msg_;
};

class Init_Turtle_name
{
public:
  Init_Turtle_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Turtle_pose name(::interfaces::msg::Turtle::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Turtle_pose(msg_);
  }

private:
  ::interfaces::msg::Turtle msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::Turtle>()
{
  return interfaces::msg::builder::Init_Turtle_name();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__TURTLE__BUILDER_HPP_
