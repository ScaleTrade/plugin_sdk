#pragma once

#include <ctime>

struct CandleRecord {
    double open = 0;
    double high = 0;
    double low = 0;
    double close = 0;
    time_t time = 0;
    double volume = 0;
};
