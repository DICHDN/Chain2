#pragma once
#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <string>

enum class Type {
    WARNING,
    ERROR,
    FATAL_ERROR,
    UNKNOWN
};

class LogMessage {
public:
    LogMessage(Type type, const std::string& message) : type_(type), message_(message) {}

    Type type() const {
        return type_;
    }

    const std::string& message() const {
        return message_;
    }

private:
    Type type_;
    std::string message_;
};

#endif // LOGMESSAGE_H