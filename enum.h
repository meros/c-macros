#pragma once

// ENUM is an extension to a basic enum
//
// To define an enum, first define an X-macro on this format:
//
// #define CONNECTION_STATUS_ENUM_FOREACH(X, ...)   \
//   X(CONNECTION_STATUS_DISCONNECTED, __VA_ARGS__) \
//   X(CONNECTION_STATUS_CONNECTING, __VA_ARGS__)   \
//   X(CONNECTION_STATUS_CONNECTED, __VA_ARGS__)
//
// ENUM_DECLARE(CONNECTION_STATUS_ENUM_FOREACH, connection_status_t)

// Each line in the X macro takes
//  * enum value name
//  * __VA_ARGS__ - used internally
//
// The ENUM_DECLARE macro takes
//  * a foreach x-macro
//  * an enum type name
//
// To get the string name of an enum value, use
// connection_status_t_get_str(value) where the function name is on the format:
// * <enum name>_get_str(...)

#define ENUM_DECLARE(FOREACH, ENUM_NAME)                               \
  typedef enum { FOREACH(_ENUM_FE_ENUM_VALUES, ENUM_NAME) } ENUM_NAME; \
  static inline const char *ENUM_NAME##_get_str(ENUM_NAME value) {     \
    switch (value) {                                                   \
      FOREACH(_ENUM_FE_SWITCH_CASES_RETURN_NAME_STR, ENUM_NAME)        \
      default:                                                         \
        return "";                                                     \
    }                                                                  \
  }

// Various internal macros
#define _ENUM_NAME_TO_ENUM(NAME, ENUM_NAME) NAME

// _ENUM_FE_ macros are all macros that can be passed to FOREACH as an
// argument, the need to have signature:
// (NAME, ENUM_NAME)
#define _ENUM_FE_ENUM_VALUES(NAME, ENUM_NAME) \
  _ENUM_NAME_TO_ENUM(NAME, ENUM_NAME),

#define _ENUM_FE_SWITCH_CASES_RETURN_NAME_STR(NAME, ENUM_NAME) \
  case NAME:                                                   \
    return #NAME;
