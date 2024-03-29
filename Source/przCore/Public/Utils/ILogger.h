#pragma once

#include <functional>

namespace prz {
namespace utl {

enum class ELogPriority {
	Debug,
	Error
};
	
class ILogger {
public:
    virtual ~ILogger() = default;

    typedef std::function<void(ELogPriority priority, const char* fileName, int lineNum, const char* message)> ZLogCallback;

    virtual void Log(ELogPriority priority, const char* fileName, int lineNum, const char* format, ...) const = 0;
    virtual void SetLogCallback(ZLogCallback callback) = 0;
};

}
}
