#include <vector>
#include <string_view>
#include <string>
#include <stdio.h>
#include <memory>

namespace easy_log {
    class Logger
    {
    public:
        virtual bool Log(std::string_view str) = 0;
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
            fp( fopen(log_path.data(),"a+"),&ValidLogger::closeFile )
        {
        }

        virtual bool Log(std::string_view data) override {
            printf("log data %s\n", data.data());
            return (0 < fwrite(data.data(), data.size(), 1, fp.get()));
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

        virtual bool Log(std::string_view data) override {
            if(logger_) {
                return logger_->Log(data);
            }
            return false;
        }

        ~LineLogger() {
            if(logger_) {
                logger_->Log("\n");
            }
        }

        private:
            ValidLogger* logger_;
    };

}