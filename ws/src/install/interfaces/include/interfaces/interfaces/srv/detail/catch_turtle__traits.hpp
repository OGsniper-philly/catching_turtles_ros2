// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interfaces:srv/CatchTurtle.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__CATCH_TURTLE__TRAITS_HPP_
#define INTERFACES__SRV__DETAIL__CATCH_TURTLE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "interfaces/srv/detail/catch_turtle__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const CatchTurtle_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CatchTurtle_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CatchTurtle_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace interfaces

namespace rosidl_generator_traits
{

[[deprecated("use interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const interfaces::srv::CatchTurtle_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::srv::CatchTurtle_Request & msg)
{
  return interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::srv::CatchTurtle_Request>()
{
  return "interfaces::srv::CatchTurtle_Request";
}

template<>
inline const char * name<interfaces::srv::CatchTurtle_Request>()
{
  return "interfaces/srv/CatchTurtle_Request";
}

template<>
struct has_fixed_size<interfaces::srv::CatchTurtle_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<interfaces::srv::CatchTurtle_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<interfaces::srv::CatchTurtle_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const CatchTurtle_Response & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CatchTurtle_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CatchTurtle_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace interfaces

namespace rosidl_generator_traits
{

[[deprecated("use interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const interfaces::srv::CatchTurtle_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::srv::CatchTurtle_Response & msg)
{
  return interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::srv::CatchTurtle_Response>()
{
  return "interfaces::srv::CatchTurtle_Response";
}

template<>
inline const char * name<interfaces::srv::CatchTurtle_Response>()
{
  return "interfaces/srv/CatchTurtle_Response";
}

template<>
struct has_fixed_size<interfaces::srv::CatchTurtle_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<interfaces::srv::CatchTurtle_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<interfaces::srv::CatchTurtle_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<interfaces::srv::CatchTurtle>()
{
  return "interfaces::srv::CatchTurtle";
}

template<>
inline const char * name<interfaces::srv::CatchTurtle>()
{
  return "interfaces/srv/CatchTurtle";
}

template<>
struct has_fixed_size<interfaces::srv::CatchTurtle>
  : std::integral_constant<
    bool,
    has_fixed_size<interfaces::srv::CatchTurtle_Request>::value &&
    has_fixed_size<interfaces::srv::CatchTurtle_Response>::value
  >
{
};

template<>
struct has_bounded_size<interfaces::srv::CatchTurtle>
  : std::integral_constant<
    bool,
    has_bounded_size<interfaces::srv::CatchTurtle_Request>::value &&
    has_bounded_size<interfaces::srv::CatchTurtle_Response>::value
  >
{
};

template<>
struct is_service<interfaces::srv::CatchTurtle>
  : std::true_type
{
};

template<>
struct is_service_request<interfaces::srv::CatchTurtle_Request>
  : std::true_type
{
};

template<>
struct is_service_response<interfaces::srv::CatchTurtle_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // INTERFACES__SRV__DETAIL__CATCH_TURTLE__TRAITS_HPP_
