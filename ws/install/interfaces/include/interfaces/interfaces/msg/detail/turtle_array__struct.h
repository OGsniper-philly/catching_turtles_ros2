// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/TurtleArray.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__TURTLE_ARRAY__STRUCT_H_
#define INTERFACES__MSG__DETAIL__TURTLE_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'alive_turtles'
#include "interfaces/msg/detail/turtle__struct.h"

/// Struct defined in msg/TurtleArray in the package interfaces.
typedef struct interfaces__msg__TurtleArray
{
  interfaces__msg__Turtle__Sequence alive_turtles;
} interfaces__msg__TurtleArray;

// Struct for a sequence of interfaces__msg__TurtleArray.
typedef struct interfaces__msg__TurtleArray__Sequence
{
  interfaces__msg__TurtleArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__TurtleArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__TURTLE_ARRAY__STRUCT_H_
