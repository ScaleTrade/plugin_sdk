#pragma once

#include <ctime>
#include <string>

struct PluginAccountDiffRecord {
    int login = 0;
    std::string group;
    int enable = 1;
    int enable_change_password = 0;
    int enable_read_only = 0;
    int enable_otp = 0;
    std::string name;
    std::string country;
    std::string city;
    std::string state;
    std::string zipcode;
    std::string address;
    std::string lead_source;
    std::string phone;
    std::string email;
    std::string comment;
    std::string id;
    std::string status;
    time_t regdate = 0;
    time_t lastdate = 0;
    int leverage = 0;
    int agent_account = 0;
    double balance = 0.0;
    double prevmonthbalance = 0.0;
    double prevbalance = 0.0;
    double credit = 0.0;
    double interestrate = 0.0;
    double taxes = 0.0;
    double prevmonthequity = 0.0;
    double prevequity = 0.0;
    std::string otp_secret;
    std::string secure_reserved;
    int send_reports = 0;
    std::string user_color = "#ffffff";
};
