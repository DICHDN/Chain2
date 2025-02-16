#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <memory>
#include "LogMessage.h"
#include "Handler.h"

class Logger {
public:
    Logger() {
        // Создаем цепочку обработчиков
        fatalErrorHandler_ = std::make_shared<FatalErrorHandler>();
        errorHandler_ = std::make_shared<ErrorHandler>("error_log.txt");
        warningHandler_ = std::make_shared<WarningHandler>();
        unknownHandler_ = std::make_shared<UnknownHandler>();

        // Устанавливаем цепочку
        fatalErrorHandler_->setNext(errorHandler_);
        errorHandler_->setNext(warningHandler_);
        warningHandler_->setNext(unknownHandler_);
    }

    void log(const LogMessage& message) {
        fatalErrorHandler_->handle(message);
    }

private:
    std::shared_ptr<Handler> fatalErrorHandler_;
    std::shared_ptr<Handler> errorHandler_;
    std::shared_ptr<Handler> warningHandler_;
    std::shared_ptr<Handler> unknownHandler_;
};