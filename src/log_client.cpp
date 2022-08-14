#include "log_client.h"
namespace easy_log {
LogClient LogClient::instance_;
LogLevel LogClient::current_level_ = LogLevel::kDebug;
}