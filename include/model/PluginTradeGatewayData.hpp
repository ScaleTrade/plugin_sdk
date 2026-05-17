#pragma once

#include <string>

struct PluginTradeGatewayDataUpdateRecord {
    int order = 0;

    bool has_gw_volume = false;
    int gw_volume = 0;

    bool has_gw_order = false;
    std::string gw_order;

    bool has_gw_source = false;
    std::string gw_source;

    bool has_gw_uuid = false;
    std::string gw_uuid;

    bool has_gw_open_price = false;
    double gw_open_price = 0.0;

    bool has_gw_close_price = false;
    double gw_close_price = 0.0;
};
