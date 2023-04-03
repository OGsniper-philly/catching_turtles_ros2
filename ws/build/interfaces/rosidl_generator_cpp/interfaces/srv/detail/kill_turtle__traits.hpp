// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interfaces:srv/KillTurtle.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__KILL_TURTLE__TRAITS_HPP_
#define INTERFACES__SRV__DETAIL__KILL_TURTLE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "interfaces/srv/detail/kill_turtle__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const KillTurtle_Request & msg,
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
  const KillTurtle_Request & msg,
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

inline std::string to_yaml(const KillTurtle_Request & msg, bool use_flow_style = false)
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
  const interfaces::srv::KillTurtle_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::srv::KillTurtle_Request & msg)
{
  return interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::srv::KillTurtle_Request>()
{
  return "interfaces::srv::KillTurtle_Request";
}

template<>
inline const char * name<interfaces::srv::KillTurtle_Request>()
{
  return "interfaces/srv/KillTurtle_Request";
}

template<>
struct has_fixed_size<interfaces::srv::KillTurtle_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<interfaces::srv::KillTurtle_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<interfaces::srv::KillTurtle_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const KillTurtle_Response & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const KillTurtle_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const KillTurtle_Response & msg, bool use_flow_style = false)
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
  const interfaces::srv::KillTurtle_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const interfaces::srv::KillTurtle_Response & msg)
{
  return interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<interfaces::srv::KillTurtle_Response>()
{
  return "interfaces::srv::KillTurtle_Response";
}

template<>
inline const char * name<interfaces::srv::KillTurtle_Response>()
{
  return "interfaces/srv/KillTurtle_Response";
}

template<>
struct has_fixed_size<interfaces::srv::KillTurtle_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<interfaces::srv::KillTurtle_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<interfaces::srv::KillTurtle_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<interfaces::srv::KillTurtle>()
{
  return "interfaces::srv::KillTurtle";
}

template<>
inline const char * name<interfaces::srv::KillTurtle>()
{
  return "interfaces/srv/KillTurtle";
}

template<>
struct has_fixed_size<interfaces::srv::KillTurtle>
  : std::integral_constant<
    bool,
    has_fixed_size<interfaces::srv::KillTurtle_Request>::value &&
    has_fixed_size<interfaces::srv::KillTurtle_Response>::value
  >
{
};

template<>
struct has_bounded_size<interfaces::srv::KillTurtle>
  : std::integral_constant<
    bool,
    has_bounded_size<interfaces::srv::KillTurtle_Request>::value &&
    has_bounded_size<interfaces::srv::KillTurtle_Response>::value
  >
{
};

template<>
struct is_service<interfaces::srv::KillTurtle>
  : std::true_type
{
};

template<>
struct is_service_request<interfaces::srv::KillTurtle_Request>
  : std::true_type
{
};

template<>
struct is_service_response<interfaces::srv::KillTurtle_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // INTERFACES__SRV__DETAIL__KILL_TURTLE__TRAITS_HPP_
