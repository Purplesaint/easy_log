#include "logger/logger.h"
namespace easy_log {
    enum class
    {
        kNone,
        kInfo,
        kDebug,
        kWarning,
        kError,
        kFatal
    } LogLevel;

    class LogClient
    {
    public:
        LogClient()
        : valid_logger_("log.txt") {}
        ~LogClient() = default;
        
        LogClient & operator<<(const std::string & data) {
            logger_.Log(data);
            return (*this);
        }
        
        Logger & LOG(LogLevel level) {
            if (level >= current_level_) {
                return valid_logger_ << data;
            }
            return invalid_logger_ << data;
        }
        
        static LogClient & getInstance() {
            return instance_;
        }

    private:

        std::unique_ptr<ValidLogger> valid_logger_;
        std::unique_ptr<InvalidLogger> invalid_logger_;
        static LogClient instance_;
        static LogLevel current_level_;
    };
}