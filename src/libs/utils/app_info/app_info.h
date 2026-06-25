#pragma once

#include <string_view>

namespace utils
{
class AppInfo
{
public:
    static std::string_view getVersion();
    // static std::string_view getDeviceName();
};
}  // namespace utils
