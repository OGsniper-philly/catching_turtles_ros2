// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from interfaces:msg/Turtle.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__TURTLE__STRUCT_HPP_
#define INTERFACES__MSG__DETAIL__TURTLE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__interfaces__msg__Turtle __attribute__((deprecated))
#else
# define DEPRECATED__interfaces__msg__Turtle __declspec(deprecated)
#endif

namespace interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Turtle_
{
  using Type = Turtle_<ContainerAllocator>;

  explicit Turtle_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      std::fill<typename std::array<float, 3>::iterator, float>(this->pose.begin(), this->pose.end(), 0.0f);
    }
  }

  explicit Turtle_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc),
    pose(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      std::fill<typename std::array<float, 3>::iterator, float>(this->pose.begin(), this->pose.end(), 0.0f);
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _pose_type =
    std::array<float, 3>;
  _pose_type pose;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__pose(
    const std::array<float, 3> & _arg)
  {
    this->pose = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    interfaces::msg::Turtle_<ContainerAllocator> *;
  using ConstRawPtr =
    const interfaces::msg::Turtle_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<interfaces::msg::Turtle_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<interfaces::msg::Turtle_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::Turtle_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::Turtle_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::Turtle_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::Turtle_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<interfaces::msg::Turtle_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<interfaces::msg::Turtle_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__interfaces__msg__Turtle
    std::shared_ptr<interfaces::msg::Turtle_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__interfaces__msg__Turtle
    std::shared_ptr<interfaces::msg::Turtle_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Turtle_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const Turtle_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Turtle_

// alias to use template instance with default allocator
using Turtle =
  interfaces::msg::Turtle_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__TURTLE__STRUCT_HPP_
