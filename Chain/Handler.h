#pragma once
#ifndef HANDLER_H
#define HANDLER_H

#include "LogMessage.h"
#include <memory>

class Handler {
public:
    virtual ~Handler() = default;
    virtual void handle(const LogMessage& message) = 0;
    void setNext(std::shared_ptr<Handler> next) {
        next_ = next;
    }

protected:
    std::shared_ptr<Handler> next_;
};

class FatalErrorHandler : public Handler {
public:
    void handle(const LogMessage& message) override {
        if (message.type() == Type::FATAL_ERROR) {
            throw std::runtime_error("Fatal Error: " + message.message());
        }
        else if (next_) {
            next_->handle(message);
        }
    }
};

class ErrorHandler : public Handler {
public:
    explicit ErrorHandler(const std::string& filePath) : filePath_(filePath) {}

    void handle(const LogMessage& message) override {
        if (message.type() == Type::ERROR) {
            std::ofstream file(filePath_, std::ios::app);
            if (file.is_open()) {
                file << "Error: " << message.message() << std::endl;
                file.close();
            }
            else {
                std::cerr << "Failed to open file: " << filePath_ << std::endl;
            }
        }
        else if (next_) {
            next_->handle(message);
        }
    }

private:
    std::string filePath_;
};

class WarningHandler : public Handler {
public:
    void handle(const LogMessage& message) override {
        if (message.type() == Type::WARNING) {
            std::cout << "Warning: " << message.message() << std::endl;
        }
        else if (next_) {
            next_->handle(message);
        }
    }
};

class UnknownHandler : public Handler {
public:
    void handle(const LogMessage& message) override {
        if (message.type() == Type::UNKNOWN) {
            throw std::runtime_error("Unknown message: " + message.message());
        }
        else if (next_) {
            next_->handle(message);
        }
    }
};

#endif // HANDLER_H
