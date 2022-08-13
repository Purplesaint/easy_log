#include <string>
#include <stdio.h>
#include <memory>

namespace easy_log {
    class Logger {
      public:
          virtual bool Log(const std::string & str) = 0;
          Logger & operator<<(const std::string & str)
          {
              Log(str);
              return (*this);
          }
    };

    class InvalidLogger:public Logger
    {
        public:
            virtual bool Log(const std::string & str) override {
                (void)str;
                return false;
            }
    };

    class ValidLogger: public Logger
    {
    public:
        explicit ValidLogger(const std::string & log_path)
            :
            fp( fopen(log_path.c_str(),"a+"),&ValidLogger::closeFile )
        {
        }

        bool Log(const std::string & data) {
            return (0 < fwrite(data.c_str(),data.size() , 1, fp.get() ));
        }

    private:
        static void closeFile(FILE * f) {
            fclose(f);
        }
        std::unique_ptr<std::FILE, decltype(&ValidLogger::closeFile)> fp;
    };
}