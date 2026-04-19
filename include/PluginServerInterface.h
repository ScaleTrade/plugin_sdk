//
// Created by  ScaleTrade on 11.03.2025.
//
#pragma once
#include <ctime>
#include <rapidjson/document.h>
#include <string>
#include <vector>

#include "Structures.h"
#include "structures/AccountStructures.hpp"
#include "structures/CandleStructures.hpp"
#include "structures/GroupStructures.hpp"
#include "structures/LogStructures.hpp"
#include "structures/SymbolStructures.hpp"
#include "structures/TradeStructures.hpp"

class Core;

inline int PLUGIN_SERVER_API = 105;

class PluginServerInterface {

public:
    PluginServerInterface(Core* st, const std::string name);
    ~PluginServerInterface();

    virtual int TickSet(TickInfo& tick); //set quotes tick
    virtual int LogsOut(const std::string& type, const std::string& message);  //send logs to console
    virtual int GetLogs(time_t from, time_t to, const std::string &type, const std::string &filter, std::vector<ServerLog>* logs);  //get logs
    static int GetApiVersion() { return PLUGIN_SERVER_API; }

    //+------------------------------------------------------------------+
    // Accounts
    //+------------------------------------------------------------------+
    virtual int GetAccountsByGroup(const std::string& group, std::vector<AccountRecord>* accounts); //Get acccounts by group
    virtual int GetAccountByLogin(int login, AccountRecord* account);                               //Get acccount by login
    virtual int GetAccountBalanceByLogin(int login, MarginLevel* margin);                           //Get acccount by login
    virtual int AddAccount(const AccountRecord& account);                                           //Add acccount
    virtual int UpdateAccount(const AccountRecord& account);                                        //Upd acccount
    virtual int DeleteAccount(int login);                                                           //Del acccount by login
    virtual int GetMarginLevelByGroup(const std::string& group, std::vector<MarginLevel>* margins); //Get marginLevels by group
    virtual int GetAccountsEquitiesByGroup(time_t from, time_t to, const std::string& group_filter, std::vector<EquityRecord>* equities); //Get equities by group
    virtual int GetAccountsEquitiesByLogin(time_t from, time_t to, int login, std::vector<EquityRecord>* equities); //Get equities by group

    //+------------------------------------------------------------------+
    // Trades
    //+------------------------------------------------------------------+
    virtual int OpenTrade(const TradeRecord& trade);
    virtual int CloseTrade(const TradeRecord& trade);
    virtual int UpdateOpenTrade(const TradeRecord& trade);
    virtual int UpdateCloseTrade(const TradeRecord& trade);
    virtual int CheckOpenTrade(const TradeRecord& trade);
    virtual int CheckCloseTrade(const TradeRecord& trade);
    virtual int GetOpenTradesByLogin(int login, std::vector<TradeRecord>* trades);
    virtual int GetPendingTradesByLogin(int login, std::vector<TradeRecord>* trades);
    virtual int GetOpenTradesByMagic(int magic, std::vector<TradeRecord>* trades);
    virtual int GetOpenTradeByOrder(int order, TradeRecord* trade);
    virtual int GetOpenTradeByGwUUID(const std::string& gw_uuid, TradeRecord* trade);
    virtual int GetCloseTradeByGwUUID(const std::string& gw_uuid, TradeRecord* trade);
    virtual int GetOpenTradeByGwOrder(int gw_order, TradeRecord* trade);
    virtual int GetCloseTradeByGwOrder(int gw_order, TradeRecord* trade);
    virtual int GetOpenTradesByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<TradeRecord>* trades);
    virtual int GetCloseTradesByLogin(int login, std::vector<TradeRecord>* trades);
    virtual int GetCloseTradesByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<TradeRecord>* trades);
    virtual int GetPendingTradesByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<TradeRecord>* trades);
    virtual int GetAllOpenTrades(std::vector<TradeRecord>* trades);

    //+------------------------------------------------------------------+
    // Finance
    //+------------------------------------------------------------------+
    virtual int BalanceIn(int login, double amount, const std::string& comment);
    virtual int BalanceOut(int login, double amount, const std::string& comment);
    virtual int CreditIn(int login, double amount, const std::string& comment);
    virtual int CreditOut(int login, double amount, const std::string& comment);
    virtual int GetTransactionsByGroup(const std::string& filter_group, time_t from, time_t to, std::vector<TradeRecord>* trades);
    virtual int GetTransactionsByLogin(int login, time_t from, time_t to, std::vector<TradeRecord>* trades);

    //+------------------------------------------------------------------+
    // Symbols
    //+------------------------------------------------------------------+
    virtual int GetSymbol(const std::string& symbol, SymbolRecord *cs);

    //+------------------------------------------------------------------+
    // Groups
    //+------------------------------------------------------------------+
    virtual int GetGroup(const std::string& group_name, GroupRecord* group);
    virtual int GetAllGroups(std::vector<GroupRecord>* groups);

    //+------------------------------------------------------------------+
    // System
    //+------------------------------------------------------------------+
    virtual int CalculateCommission(const TradeRecord& trade, double *calculated_commission);
    virtual int CalculateSwap(const TradeRecord& trade, double *calculated_swap);
    virtual int CalculateProfit(const TradeRecord& trade, double *calculated_profit);
    virtual int CalculateMargin(const TradeRecord& trade, double *calculated_margin);
    virtual int CalculateConvertRateByCurrency(const std::string& from_cur, const std::string& to_cur, int cmd, double *multiplier);

    //+------------------------------------------------------------------+
    // Chart
    //+------------------------------------------------------------------+
    virtual int GetCandles(const std::string& symbol, const std::string& frame, time_t from, time_t to, std::vector<CandleRecord>* candles);
    virtual int SetCandles(const std::string& symbol, const std::vector<CandleRecord>& candles);
    virtual int DeleteCandlesAll(const std::string& symbol);
    virtual int DeleteCandlesPeriod(const std::string& symbol, time_t from, time_t to);
    virtual int ImportCandleStores(const std::vector<CandleRecord>& candles, int flush_data,const std::string& symbol);


    //+------------------------------------------------------------------+
    // Stream
    //+------------------------------------------------------------------+
    virtual int SendToManager(int manager_id, const rapidjson::Value& data); //send data to some Manager
    virtual int BroadcastToManagers(const rapidjson::Value& data); //send data to all Managers
    virtual int SendToAccount(int account_id, const rapidjson::Value& data); //send data to some Account
    virtual int BroadcastToAccounts(const rapidjson::Value& data); //send data to all Accounts
    virtual int SendState(const rapidjson::Value& data); //send update data to Plugin State

private:
    Core* St;
    std::string plugin_name;
};
