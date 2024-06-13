#include "log.h"

log_config_t glog_config;

log_config_t log_config_default() {
    log_config_t cfg = {
        .level = LOG_LEVEL_INFO,
        .subsystems_enabled = { true, true, true, true, true }
    };
    return cfg;
}

void log_open(log_config_t c) {
    glog_config = c;
}

void log_close() {
    glog_config.subsystems_enabled = { false, false, false, false, false };
}

const char *log_level_str[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL",
};

void log_backend(const char *fmt, ...) { };

void log_msg(enum log_subsystem ls, enum log_level level, const char *msg) {
    if (glog_config.level <= level && glog_config.subsystems_enabled[ls]) {
        log_backend("%s: %s\n", log_level_str[level], msg);
    }
}
