#pragma once

#include <stdbool.h>
#define LOG_NUM_SUBSYSTEMS 5

typedef struct {
    bool level;
    bool subsystems_enabled[LOG_NUM_SUBSYSTEMS];
} log_config_t;

enum log_subsystem {
    LOG_SUBSYSTEM_MAIN,
    LOG_SUBSYSTEM_CONTROL,
    LOG_SUBSYSTEM_SENSOR,
    LOG_SUBSYSTEM_CONFIG,
    LOG_SUBSYSTEM_DISPLAY,
};

enum log_level {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
};

log_config_t log_config_default();
void log_open(log_config_t cfg);
void log_close();

void log_msg(enum log_subsystem ls, enum log_level level, const char *msg);

#define LOG_DEBUG(ls, msg) log_msg(ls, LOG_LEVEL_DEBUG, msg)
#define LOG_INFO(ls, msg) log_msg(ls, LOG_LEVEL_INFO, msg)
#define LOG_WARN(ls, msg) log_msg(ls, LOG_LEVEL_WARN, msg)
#define LOG_ERROR(ls, msg) log_msg(ls, LOG_LEVEL_ERROR, msg)
#define LOG_FATAL(ls, msg) log_msg(ls, LOG_LEVEL_FATAL, msg)
