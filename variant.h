#pragma once

#include "./windows/windows.h"
#include "logging/logging.h"
#include "lvgl/lvgl.h"
#include "net/prov.h"
#include "protocol/devproto.pb-c.h"
#include "utils/variant.h"

// Actions
#define ARGS_IDENT(x) x
#define FMT_BOOL "%s"
#define ARGS_BOOL(x) x ? "true" : "false"

#define ACTION_EVENT_ENUM_FOREACH(X, ...)            \
  X(ACTION_DISMISS_LOCK_SCREEN, __VA_ARGS__)         \
  X(ACTION_DISMISS_LOCK_SCREEN_TIMEOUT, __VA_ARGS__) \
  X(ACTION_EVENT_TOGGLE_FOCUS_MODE, __VA_ARGS__)     \
  X(ACTION_EVENT_EXTEND_BOOKING, __VA_ARGS__)        \
  X(ACTION_EVENT_OPEN_MENU, __VA_ARGS__)             \
  X(ACTION_EVENT_CLOSE_MENU, __VA_ARGS__)

ENUM_DECLARE(ACTION_EVENT_ENUM_FOREACH, action_event_t);

// Create app_action_t, a variant type that contains all actions possible to
// undertake using dispatch
#define APP_ACTION_VARIANT_FOREACH(X, ...)                                    \
  X(provisioning_status_t, net_prov_status, "%u", ARGS_IDENT, __VA_ARGS__)    \
  X(bool, net_wifi_has_ip, FMT_BOOL, ARGS_BOOL, __VA_ARGS__)                  \
  X(bool, net_connected, FMT_BOOL, ARGS_BOOL, __VA_ARGS__)                    \
  X(action_event_t, event, "%s", action_event_t_get_str, __VA_ARGS__)         \
  X(Devproto__DeviceState*, device_state_updated, "%p", ARGS_IDENT,           \
    __VA_ARGS__)                                                              \
  X(bool, human_present, FMT_BOOL, ARGS_BOOL, __VA_ARGS__)                    \
  X(temporary_modal_t, show_temporary_modal, "%s", temporary_modal_t_get_str, \
    __VA_ARGS__)

#define LOG_ACTION(FMT, ...) LOG_TAG_INFO(FMT, "action", __VA_ARGS__)

VARIANT_DECLARE(APP_ACTION_VARIANT_FOREACH, app_action_t, LOG_ACTION)
