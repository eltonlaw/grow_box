#include "log.h"

log_config_t log_cfg;

log_config_t log_config_default() {
    log_config_t cfg = {
        .level = LOG_LEVEL_INFO,
        .subsystems_enabled = { true, true, true, true, true }
    };
    return cfg;
}

void log_open(log_config_t c) {
    log_cfg = c;
}

void log_close() {
	for (int i = 0; i < LOG_NUM_SUBSYSTEMS; i++) {
		log_cfg.subsystems_enabled[i] = false;
	}
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
    if (log_cfg.level <= level && log_cfg.subsystems_enabled[ls]) {
        log_backend("%s: %s\n", log_level_str[level], msg);
    }
}
