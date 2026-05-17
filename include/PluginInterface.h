//
// Created by  ScaleTrade on 14.04.2025.
//
#pragma once
#include <rapidjson/document.h>
#include "Structures.h"
#include "model/PluginAccount.hpp"
#include "model/PluginAccountEnums.hpp"
#include "model/PluginAccountOutput.hpp"
#include "model/PluginGroup.hpp"
#include "model/PluginSymbol.hpp"
#include "model/PluginTrade.hpp"
#include "model/PluginTradeOutput.hpp"

// подключение модулей

inline int PLUGIN_VERSION_API = 149;

//+------------------------------------------------------------------+
// Hooks Trades
//+------------------------------------------------------------------+
class HookTrade {
public:
    virtual ~HookTrade() = default;
    virtual int HookTradeRequestOpen(
        const PluginTradeRecord&,const PluginGroupRecord&,const PluginSymbolRecord&,const PluginAccountRecord&,const PluginMarginLevel&,PluginTradeDiffRecord&
    ){ return RET_OK; }
    virtual int HookTradeProcessOpen(
        const PluginTradeRecord&,const PluginGroupRecord&,const PluginSymbolRecord&,const PluginAccountRecord&,const PluginMarginLevel&,PluginTradeDiffRecord&
    ) { return RET_OK; }
    virtual int HookTradeRequestClose(
        const PluginTradeRecord&,const PluginGroupRecord&,const PluginSymbolRecord&,const PluginAccountRecord&,const PluginMarginLevel&,PluginTradeDiffRecord&
     ){ return RET_OK; }
    virtual int HookTradeProcessClose(
        const PluginTradeRecord&,const PluginGroupRecord&,const PluginSymbolRecord&,const PluginAccountRecord&,const PluginMarginLevel&,PluginTradeDiffRecord&
    ) { return RET_OK; }
    virtual int HookTradeProcessCommision(
        const PluginTradeRecord&,const PluginGroupRecord&,const PluginSymbolRecord&,const PluginAccountRecord&,const PluginMarginLevel&,PluginTradeDiffRecord&
    ) { return RET_OK; }
};

//+------------------------------------------------------------------+
// Hooks Accounts
//+------------------------------------------------------------------+
class HookAccount {
public:
    virtual ~HookAccount() = default;
    virtual int HookAccountAdd(const PluginAccountRecord&, const PluginMarginLevel&, PluginAccountDiffRecord&){ return RET_OK; }
    virtual int HookAccountUpdate(const PluginAccountRecord&, const PluginMarginLevel&, PluginAccountDiffRecord&) { return RET_OK; }
    virtual int HookAccountDelete(const PluginAccountRecord&, const PluginMarginLevel&, PluginAccountDiffRecord&){ return RET_OK; }
    virtual int HookAccountLogin(const PluginAccountRecord&) { return RET_OK; }
    virtual int HookAccountLogout(const PluginAccountRecord&) { return RET_OK; }
};

//+------------------------------------------------------------------+
// Events Trades
//+------------------------------------------------------------------+
class EventTrade {
public:
    virtual ~EventTrade() = default;
    virtual void OnTradeRequestOpen(const PluginTradeRecord&) {}
    virtual void OnTradeAddDB(const PluginTradeRecord&) {}
    virtual void OnTradeRequestClose(const PluginTradeRecord&) {}
    virtual void OnTradeRequestUpdate(const PluginTradeRecord&) {}
    virtual void OnTradeUpdateDB(const PluginTradeRecord&) {}
    virtual void OnTradeRequestDelete(const PluginTradeRecord&) {}
    virtual void OnTradeDeleteDB(const PluginTradeRecord&) {}
    virtual void OnTradeExecuteOpen(const PluginTradeRecord&) {}
    virtual void OnTradeExecuteClose(const PluginTradeRecord&) {}
};

//+------------------------------------------------------------------+
// Events Symbols
//+------------------------------------------------------------------+
class EventSymbol {
public:
    virtual ~EventSymbol() = default;
};

//+------------------------------------------------------------------+
// Events Accounts
//+------------------------------------------------------------------+
class EventAccount {
public:
    virtual ~EventAccount() = default;
    virtual void OnAccountAdd(const PluginAccountRecord& account) {}
    virtual void OnAccountUpdate(const PluginAccountRecord& account) {}
    virtual void OnAccountDelete(const PluginAccountRecord& account) {}
    virtual void OnAccountLogin(const std::string& ip, PluginConnectionType type, const PluginAccountRecord& account) {}
    virtual void OnAccountLogout(const std::string& ip, PluginConnectionType type, const PluginAccountRecord& account) {}
    virtual void OnAccountPasswordChange(const std::string& password, const PluginAccountRecord& account) {}
    virtual void OnAccountSync() {}
};

//+------------------------------------------------------------------+
// Events Group
//+------------------------------------------------------------------+
class EventGroup {
public:
    virtual ~EventGroup() = default;
};

class PluginInterface {
public:
    virtual ~PluginInterface() = default;
    virtual int getApiVersion() const { return PLUGIN_VERSION_API; }
    virtual std::string plugin_name() const { return "Demo plugin"; };
    virtual std::string plugin_description() const { return "Demo plugin"; }
    virtual int CustomAction(rapidjson::Value& req, rapidjson::Value& res, rapidjson::Document::AllocatorType& allocator) { return RET_OK_NONE; }
};
