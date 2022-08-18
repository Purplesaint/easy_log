#include <vector>
#include <string_view>
#include <string>
#include <string.h>
#include <stdio.h>
#include <memory>

namespace easy_log {
    class Logger
    {
    public:
        virtual bool Log(std::string_view str,bool log_sep = false) = 0;
        Logger &operator<<(const std::string &str)
        {
            Log(str);
            return (*this);
        }
        Logger &operator<<(const char *data)
        {
            Log(data);
            return (*this);
        }

        Logger &operator<<(std::string_view data)
        {
            Log(data);
            return (*this);
        }

        Logger &operator<<(bool n)
        {
            Log(std::to_string(n));
            return (*this);
        }

        Logger &operator<<(char n)
        {
            Log(std::to_string(n));
            return (*this);
        }

        Logger &operator<<(short n)
        {
            Log(std::to_string(n));
            return (*this);
        }

        Logger &operator<<(int n)
        {
            Log(std::to_string(n));
            return (*this);
        }

        Logger &operator<<(long n)
        {
            Log(std::to_string(n));
            return (*this);
        }

        Logger &operator<<(unsigned char n)
        {
            Log(std::to_string(n));
            return (*this);
        }

        Logger &operator<<(unsigned short n)
        {
            Log(std::to_string(n));
            return (*this);
        }

        Logger &operator<<(unsigned int n)
        {
            Log(std::to_string(n));
            return (*this);
        }

        Logger &operator<<(unsigned long n)
        {
            Log(std::to_string(n));
            return (*this);
        }
    };

    template<typename DataType>
    Logger & operator<<(Logger & logger,DataType data)
    {
        logger << data;
        return logger;
    }

    class ValidLogger: public Logger
    {
    public:
        explicit ValidLogger(std::string_view log_path)
            :
            fp( fopen(log_path.data(),"a+"),&ValidLogger::closeFile ) {}

        virtual bool Log(std::string_view data,bool log_sep = false) override {
            if(data.empty()) {
                return false;
            }

            static const char * seperator = " ";
            if(log_sep) {
                fwrite(seperator,strlen(seperator),1,fp.get());
            }

            if( 0 >= fwrite(data.data(), data.size(), 1, fp.get())) {
                return false;
            }
            
            return true;
        }

    private:
        static void closeFile(FILE * f) {
            fclose(f);
        }
        std::unique_ptr<std::FILE, decltype(&ValidLogger::closeFile)> fp;
    };
    
    class LineLogger:public Logger{
        public:
        explicit LineLogger(ValidLogger * logger,const char * file_str
        ,const char * function_str,int line_n)
        :logger_(logger) {
            if (logger_)
            {
                (*logger_) << file_str << ":" << line_n << "-" << function_str << " ";
            }
        }

        virtual bool Log(std::string_view data,bool log_sep = false) override {
            if(logger_) {
                logger_->Log(data,log_before_);
                log_before_ = true;
            }
            return true;
        }

        ~LineLogger() {
            if(logger_) {
                logger_->Log("\n");
            }
        }

        private:
            ValidLogger* logger_;
            bool log_before_ = false;
    };
}