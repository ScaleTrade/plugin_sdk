//
// Created by  ScaleTrade on 11.03.2025.
//
#pragma once
#include <ctime>
#include <rapidjson/document.h>
#include <string>
#include <vector>

#include "Structures.h"
#include "sdk_contract/plugin/PluginAccount.hpp"
#include "sdk_contract/plugin/PluginAccountInput.hpp"
#include "sdk_contract/plugin/PluginCandle.hpp"
#include "sdk_contract/plugin/PluginGroup.hpp"
#include "sdk_contract/plugin/PluginLog.hpp"
#include "sdk_contract/plugin/PluginSymbol.hpp"
#include "sdk_contract/plugin/PluginTrade.hpp"
#include "sdk_contract/plugin/PluginTradeInput.hpp"

class Core;

inline int PLUGIN_SERVER_API = 105;

class PluginServerInterface {
public:
    virtual ~PluginServerInterface() = default;

    virtual int TickSet(TickInfo& tick) = 0; //set quotes tick
    virtual int LogsOut(const std::string& type, const std::string& message) = 0;  //send logs to console
    virtual int GetLogs(time_t from, time_t to, const std::string &type, const std::string &filter, std::vector<PluginServerLog>* logs) = 0;  //get logs
    static int GetApiVersion() { return PLUGIN_SERVER_API; }

    //+------------------------------------------------------------------+
    // Accounts
    //+------------------------------------------------------------------+
    virtual int GetAccountsByGroup(const std::string& group, std::vector<PluginAccountRecord>* accounts) = 0; //Get acccounts by group
    virtual int GetAccountByLogin(int login, PluginAccountRecord* account) = 0;                               //Get acccount by login
    virtual int GetAccountBalanceByLogin(int login, PluginMarginLevel* margin) = 0;                           //Get acccount by login
    virtual int AddAccount(const PluginAccountRequestRecord& account) = 0;                                    //Add acccount
    virtual int UpdateAccount(const PluginAccountRequestRecord& account) = 0;                                 //Upd acccount
    virtual int DeleteAccount(int login) = 0;                                                           //Del acccount by login
    virtual int GetMarginLevelByGroup(const std::string& group, std::vector<PluginMarginLevel>* margins) = 0; //Get marginLevels by group
    virtual int GetAccountsEquitiesByGroup(time_t from, time_t to, const std::string& group_filter, std::vector<PluginEquityRecord>* equities) = 0; //Get equities by group
    virtual int GetAccountsEquitiesByLogin(time_t from, time_t to, int login, std::vector<PluginEquityRecord>* equities) = 0; //Get equities by group

    //+------------------------------------------------------------------+
    // Trades
    //+------------------------------------------------------------------+
    virtual int OpenTrade(const PluginTradeRequestRecord& trade) = 0;
    virtual int CloseTrade(const PluginTradeRequestRecord& trade) = 0;
    virtual int UpdateOpenTrade(const PluginTradeRequestRecord& trade) = 0;
    virtual int UpdateCloseTrade(const PluginTradeRequestRecord& trade) = 0;
    virtual int CheckOpenTrade(const PluginTradeRequestRecord& trade) = 0;
    virtual int CheckCloseTrade(const PluginTradeRequestRecord& trade) = 0;
    virtual int GetOpenTradesByLogin(int login, std::vector<PluginTradeRecord>* trades) = 0;
    virtual int GetPendingTradesByLogin(int login, std::vector<PluginTradeRecord>* trades) = 0;
    virtual int GetOpenTradesByMagic(int magic, std::vector<PluginTradeRecord>* trades) = 0;
    virtual int GetOpenTradeByOrder(int order, PluginTradeRecord* trade) = 0;
    virtual int GetOpenTradeByGwUUID(const std::string& gw_uuid, PluginTradeRecord* trade) = 0;
    virtual int GetCloseTradeByGwUUID(const std::string& gw_uuid, PluginTradeRecord* trade) = 0;
    virtual int GetOpenTradeByGwOrder(int gw_order, PluginTradeRecord* trade) = 0;
    virtual int GetCloseTradeByGwOrder(int gw_order, PluginTradeRecord* trade) = 0;
    virtual int GetOpenTradesByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<PluginTradeRecord>* trades) = 0;
    virtual int GetCloseTradesByLogin(int login, std::vector<PluginTradeRecord>* trades) = 0;
    virtual int GetCloseTradesByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<PluginTradeRecord>* trades) = 0;
    virtual int GetPendingTradesByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<PluginTradeRecord>* trades) = 0;
    virtual int GetAllOpenTrades(std::vector<PluginTradeRecord>* trades) = 0;

    //+------------------------------------------------------------------+
    // Finance
    //+------------------------------------------------------------------+
    virtual int BalanceIn(int login, double amount, const std::string& comment) = 0;
    virtual int BalanceOut(int login, double amount, const std::string& comment) = 0;
    virtual int CreditIn(int login, double amount, const std::string& comment) = 0;
    virtual int CreditOut(int login, double amount, const std::string& comment) = 0;
    virtual int GetTransactionsByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<PluginTradeRecord>* trades) = 0;
    virtual int GetTransactionsByLogin(int login, time_t from, time_t to, std::vector<PluginTradeRecord>* trades) = 0;

    //+------------------------------------------------------------------+
    // Symbols
    //+------------------------------------------------------------------+
    virtual int GetSymbol(const std::string& symbol, PluginSymbolRecord *cs) = 0;

    //+------------------------------------------------------------------+
    // Groups
    //+------------------------------------------------------------------+
    virtual int GetGroup(const std::string& group_name, PluginGroupRecord* group) = 0;
    virtual int GetAllGroups(std::vector<PluginGroupRecord>* groups) = 0;

    //+------------------------------------------------------------------+
    // System
    //+------------------------------------------------------------------+
    virtual int CalculateCommission(const PluginTradeRecord& trade, double *calculated_commission) = 0;
    virtual int CalculateSwap(const PluginTradeRecord& trade, double *calculated_swap) = 0;
    virtual int CalculateProfit(const PluginTradeRecord& trade, double *calculated_profit) = 0;
    virtual int CalculateMargin(const PluginTradeRecord& trade, double *calculated_margin) = 0;
    virtual int CalculateConvertRateByCurrency(const std::string& from_cur, const std::string& to_cur, int cmd, double *multiplier) = 0;

    //+------------------------------------------------------------------+
    // Chart
    //+------------------------------------------------------------------+
    virtual int GetCandles(const std::string& symbol, const std::string& frame, time_t from, time_t to, std::vector<PluginCandleRecord>* candles) = 0;
    virtual int SetCandles(const std::string& symbol, const std::vector<PluginCandleRecord>& candles) = 0;
    virtual int DeleteCandlesAll(const std::string& symbol) = 0;
    virtual int DeleteCandlesPeriod(const std::string& symbol, time_t from, time_t to) = 0;
    virtual int ImportCandleStores(const std::vector<PluginCandleRecord>& candles, int flush_data,const std::string& symbol) = 0;


    //+------------------------------------------------------------------+
    // Stream
    //+------------------------------------------------------------------+
    virtual int SendToManager(int manager_id, const rapidjson::Value& data) = 0; //send data to some Manager
    virtual int BroadcastToManagers(const rapidjson::Value& data) = 0; //send data to all Managers
    virtual int SendToAccount(int account_id, const rapidjson::Value& data) = 0; //send data to some Account
    virtual int BroadcastToAccounts(const rapidjson::Value& data) = 0; //send data to all Accounts
    virtual int SendState(const rapidjson::Value& data) = 0; //send update data to Plugin State
};
