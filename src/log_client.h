#include <functional>
#include "logger/logger.h"
namespace easy_log {
    enum class LogLevel
    {
        kNone,
        kDebug,
        kInfo,
        kWarning,
        kError,
        kFatal
    };

    class LogClient
    {
    public:
        LogClient()
        : valid_logger_( new ValidLogger("log.txt") ) {}
        ~LogClient() = default;
        
        LineLogger LOG(LogLevel level,
        const char * file_str ,const char * function_str,int line_n) {
            if(level < current_level_) {
                // 传入空的valid_logger让LineLogger什么也不做
                return LineLogger(nullptr,file_str,function_str,line_n);
            }
            return LineLogger(valid_logger_.get(),file_str,function_str,line_n);
        }

        static LogClient & getInstance() {
            return instance_;
        }

    private:
        static std::string getUTC() {
            return "";
                }

        static std::string getThreadId() {
            return "";
        }

        std::unique_ptr<ValidLogger> valid_logger_;
        static LogClient instance_;
        static LogLevel current_level_;
    };
}