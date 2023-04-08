// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:srv/CatchTurtle.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__CATCH_TURTLE__BUILDER_HPP_
#define INTERFACES__SRV__DETAIL__CATCH_TURTLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/srv/detail/catch_turtle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace srv
{

namespace builder
{

class Init_CatchTurtle_Request_name
{
public:
  Init_CatchTurtle_Request_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::srv::CatchTurtle_Request name(::interfaces::srv::CatchTurtle_Request::_name_type arg)
  {
    msg_.name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::srv::CatchTurtle_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::CatchTurtle_Request>()
{
  return interfaces::srv::builder::Init_CatchTurtle_Request_name();
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
auto build<::interfaces::srv::CatchTurtle_Response>()
{
  return ::interfaces::srv::CatchTurtle_Response(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace interfaces

#endif  // INTERFACES__SRV__DETAIL__CATCH_TURTLE__BUILDER_HPP_
