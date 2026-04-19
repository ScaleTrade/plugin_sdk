#pragma once

#include <ctime>
#include <string>

#include "PluginTradeEnums.hpp"

struct PluginTradeDiffRecord {
    int volume = 0;
    time_t open_time = 0;
    PluginTradeState state = PluginTradeState::NoChange;
    double open_price = 0.0;
    double sl = 0.0;
    double tp = 0.0;
    time_t close_time = 0;
    time_t expiration = 0;
    PluginTradeReason reason = PluginTradeReason::Client;
    double commission = 0.0;
    double storage = 0.0;
    double profit = 0.0;
    double close_price = 0.0;
    double taxes = 0.0;
    int magic = 0;
    std::string comment;
    int gw_order = 0;
    PluginTradeActivation activation = PluginTradeActivation::None;
    double gw_open_price = 0.0;
    double gw_close_price = 0.0;
    time_t last_swap_time = 0;
};
