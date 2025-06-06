#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include <iostream>
#include <string>
#include <string.h>

class TimeStamp
{
private:
    time_t m_tim;  // 整数表示的时间（从1970到现在所过去的秒数）
public:
    TimeStamp():m_tim(time(0)) {}
    TimeStamp(int64_t tim): m_tim(tim) {}
    ~TimeStamp() {}

    static TimeStamp Now(); // 返回当前时间的TimeStamp对象

    time_t GetTimeInt() const;  // 返回整数表示的时间
    std::string GetTimeStr() const; // 返回字符串表示的时间
};

#endif // _TIMESTAMP_H_