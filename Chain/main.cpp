#include "Logger.h"

int main() {
    Logger logger;

    try {
        logger.log(LogMessage(Type::WARNING, "This is a warning message."));
        logger.log(LogMessage(Type::ERROR, "This is an error message."));
        logger.log(LogMessage(Type::FATAL_ERROR, "This is a fatal error message."));
        logger.log(LogMessage(Type::UNKNOWN, "This is an unknown message."));
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}