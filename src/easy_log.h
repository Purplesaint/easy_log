#include "log_client.h"
#define LOG_INFO easy_log::LogClient::getInstance().LOG(easy_log::LogLevel::kInfo,__FILE__,__FUNCTION__,__LINE__)
#define LOG_ERROR easy_log::LogClient::getInstance().LOG(easy_log::LogLevel::kError,__FILE__,__FUNCTION__,__LINE__)
#define LOG_DEBUG easy_log::LogClient::getInstance().LOG(easy_log::LogLevel::kDebug,__FILE__,__FUNCTION__,__LINE__)
