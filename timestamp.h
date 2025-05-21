#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <ctime>

// Hàm lấy timestamp hiện tại
inline time_t getCurrentTimestamp() {
    return std::time(nullptr);
}

#endif 