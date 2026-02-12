#pragma once

#include "enum.h"

// VARIANT is a tagged union type (similar to Rust's enum with data)
//
// To define a variant, first define format helper macros:
//
// #define ARGS_IDENT(x) x
// #define FMT_BOOL "%s"
// #define ARGS_BOOL(x) x ? "true" : "false"
//
// Then define an X-macro:
//
// #define MY_VARIANT_FOREACH(X, ...)                                \
//   X(int, count, "%d", ARGS_IDENT, __VA_ARGS__)                   \
//   X(bool, enabled, FMT_BOOL, ARGS_BOOL, __VA_ARGS__)             \
//   X(const char*, name, "%s", ARGS_IDENT, __VA_ARGS__)
//
// Each X entry takes:
//  * type          - the C type for this variant member
//  * name          - identifier for this variant member
//  * fmt           - printf format string for logging
//  * args          - macro to transform the value for printf
//  * __VA_ARGS__   - used internally
//
// VARIANT_DECLARE(MY_VARIANT_FOREACH, my_variant_t, MY_LOG_FN)
//
// The VARIANT_DECLARE macro takes:
//  * a foreach x-macro
//  * a variant type name
//  * a log function macro with signature LOG_FN(fmt, ...)
//
// This generates:
//  * my_variant_t_tag_t         - enum for the tag
//  * my_variant_t               - struct with tag + anonymous union
//  * my_variant_t_<name>(value) - constructor for each member
//  * my_variant_t_log(variant)  - logs the active member

#define VARIANT_DECLARE(FOREACH, VARIANT_NAME, LOG_FN)                  \
  typedef enum {                                                        \
    FOREACH(_VARIANT_FE_TAG_VALUES, VARIANT_NAME)                       \
  } VARIANT_NAME##_tag_t;                                               \
  typedef struct {                                                      \
    VARIANT_NAME##_tag_t tag;                                           \
    union {                                                             \
      FOREACH(_VARIANT_FE_UNION_MEMBERS, VARIANT_NAME)                  \
    };                                                                  \
  } VARIANT_NAME;                                                       \
  FOREACH(_VARIANT_FE_CONSTRUCTORS, VARIANT_NAME)                       \
  static inline void VARIANT_NAME##_log(VARIANT_NAME variant) {         \
    switch (variant.tag) {                                              \
      FOREACH(_VARIANT_FE_LOG_CASES, VARIANT_NAME, LOG_FN)              \
      default:                                                          \
        break;                                                          \
    }                                                                   \
  }

// Various internal macros
// _VARIANT_FE_ macros are all macros that can be passed to FOREACH.
// They use ... to accept extra trailing arguments from VARIANT_DECLARE.

#define _VARIANT_FE_TAG_VALUES(TYPE, NAME, FMT, ARGS, VARIANT_NAME, ...) \
  VARIANT_NAME##_TAG_##NAME,

#define _VARIANT_FE_UNION_MEMBERS(TYPE, NAME, FMT, ARGS, ...) \
  TYPE NAME;

#define _VARIANT_FE_CONSTRUCTORS(TYPE, NAME, FMT, ARGS, VARIANT_NAME, ...) \
  static inline VARIANT_NAME VARIANT_NAME##_##NAME(TYPE value) {           \
    return (VARIANT_NAME){                                                 \
        .tag = VARIANT_NAME##_TAG_##NAME,                                  \
        .NAME = value,                                                     \
    };                                                                     \
  }

#define _VARIANT_FE_LOG_CASES(TYPE, NAME, FMT, ARGS, VARIANT_NAME, LOG_FN) \
  case VARIANT_NAME##_TAG_##NAME:                                           \
    LOG_FN(#NAME "=" FMT, ARGS(variant.NAME));                              \
    break;
