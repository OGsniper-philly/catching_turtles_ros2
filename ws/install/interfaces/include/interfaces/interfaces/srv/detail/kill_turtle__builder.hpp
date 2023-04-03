// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:srv/KillTurtle.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__KILL_TURTLE__BUILDER_HPP_
#define INTERFACES__SRV__DETAIL__KILL_TURTLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/srv/detail/kill_turtle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace srv
{

namespace builder
{

class Init_KillTurtle_Request_name
{
public:
  Init_KillTurtle_Request_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::srv::KillTurtle_Request name(::interfaces::srv::KillTurtle_Request::_name_type arg)
  {
    msg_.name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::srv::KillTurtle_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::KillTurtle_Request>()
{
  return interfaces::srv::builder::Init_KillTurtle_Request_name();
}

}  // namespace interfaces


namespace interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::KillTurtle_Response>()
{
  return ::interfaces::srv::KillTurtle_Response(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace interfaces

#endif  // INTERFACES__SRV__DETAIL__KILL_TURTLE__BUILDER_HPP_
