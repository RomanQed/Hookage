//
// Created by Roman on 25.08.2023.
//
#include "logger/LogLevel.h"


string_view levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::FAIL:
            return "FAIL";
    }
    return {};
}
