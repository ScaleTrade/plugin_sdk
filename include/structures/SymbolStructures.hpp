#pragma once

#include <string>
#include <ctime>

// --- Логика исполнения блокировок -
// [Securities -> Symbol -> TradingGroup -> TradingGroupSecurities -> TradingGroupSymbol]

//--- Режим исполнения ордеров
enum { EXE_REQUEST, EXE_INSTANT, EXE_MARKET };
//--- Режим торговли
enum { TRADE_NO, TRADE_CLOSE, TRADE_FULL };
//--- Тип свопов
enum { SWAP_BY_POINTS, SWAP_BY_DOLLARS, SWAP_BY_INTEREST, SWAP_BY_MARGIN_CURRENCY, SWAP_BY_INTEREST_OPEN_PRICE, SWAP_BY_INTEREST_CURRENT_PRICE };
//--- Режим расчета прибыли
enum { PROFIT_CALC_FOREX, PROFIT_CALC_CFD, PROFIT_CALC_FUTURES };
//--- Режим расчета маржи
enum { MARGIN_CALC_FOREX, MARGIN_CALC_CFD, MARGIN_CALC_FUTURES, MARGIN_CALC_CFDINDEX, MARGIN_CALC_CFDLEVERAGE };
//--- Режим GTC (Good Till Canceled)
enum { ORDERS_DAILY, ORDERS_GTC, ORDERS_DAILY_NO_STOPS };
//--- Market state
enum { MARKET_IS_OPEN, MARKET_IS_CLOSE };

enum class SymbolMarketState : int {
    Closed = 0,
    Open = 1
};

enum class SymbolMarketStateReason : int {
    None = 0,
    Holiday = 1,
    WorkTimeClosed = 2,
    SymbolSessionClosed = 3,
    Disabled = 4
};

struct SymbolMarketStateSnapshot {
    SymbolMarketState state{SymbolMarketState::Closed};
    SymbolMarketStateReason reason{SymbolMarketStateReason::None};
    time_t calculated_at{0};
    time_t next_recalc_at{0};
};

struct MarketStateEvent {
    std::string symbol;
    int sym_index = 0;
    SymbolMarketState previous_state{SymbolMarketState::Closed};
    SymbolMarketStateReason previous_reason{SymbolMarketStateReason::None};
    SymbolMarketState state{SymbolMarketState::Closed};
    SymbolMarketStateReason reason{SymbolMarketStateReason::None};
    time_t calculated_at{0};
    time_t next_recalc_at{0};
};

//+------------------------------------------------------------------+
//| Symbol groups                                                    |
// Forex (1)
// └ ─ ─ Majors (2)
//       └ ─ ─ EURUSD (3)
//+------------------------------------------------------------------+
struct SymbolGroupRecord
{
    int sec_index = 0;                              // инкрементационый ID для символ группы
    int parent_sec_index = -1;                      // Родительская группа (или -1, если корень)
    std::string       name = "Reserve";             // Symbol group name
    std::string       description = "Reserve";      // Symbol group description
    int trade = 1;                                  // Разрешена ли торговля в этой группе символов (symbol_group)
    int show = 1;                                   // Глабальная настройка показа символов в (symbol_group)
    int sort_index = 0;                             // Сортировка ID для символ группы

};

//+------------------------------------------------------------------+
//| Конфигурация сессии символа                                      |
//+------------------------------------------------------------------+
struct ConSession {
    short open_hour, open_min;   // Время открытия сессии: часы и минуты
    short close_hour, close_min; // Время закрытия сессии: часы и минуты
    int open, close;             // Внутренние данные о сессии
    short align[7];              // Выравнивание (зарезервировано)
};

//+------------------------------------------------------------------+
//| Конфигурация сессий символа                                      |
//+------------------------------------------------------------------+
struct ConSessions {
    ConSession quote[3];         // Сессии котировок
    ConSession trade[3];         // Сессии торговли
    int quote_overnight;         // Перенос котировок на следующий день
    int trade_overnight;         // Перенос торговли на следующий день
    int reserved[2];             // Зарезервировано
};

//+------------------------------------------------------------------+
// Конфигурация торгового инструмента (символа)
//+------------------------------------------------------------------+
struct SymbolRecord {
    //--- Основные параметры
    std::string symbol;               // Название символа
    std::string description;          // Описание символа
    std::string source;               // Синоним символа
    int feeder = 0;                   // Индекс привязанного фидера
    std::string currency;             // Валюта расчетов baseCurrency релевантно только для FOREX
    int sec_index = 0;                // Группа символов
    int digits = 0;                   // Точность (число знаков после запятой)
    int trade = 0;                    // Режим торговли { TRADE_NO, TRADE_CLOSE, TRADE_FULL }
    int sym_index = 0;                // Индекс нужен для уникальности
    int sort_index = 0;               // Индекс нужен для сортировки

    //--- Внешние настройки
    std::string background_color = "#ffffff"; // Цвет фона
    int count = 0;                            // Индекс символа
    int count_original = 0;                   // Индекс в Market Watch

    //--- Сессии
    ConSessions sessions[7];                 // Конфигурация сессий

    //--- Профит и комиссия
    int profit_mode = 0;                     // Режим расчета прибыли
    int profit_reserved = 0;                 // Зарезервировано

    //--- Фильтрация котировок
    int filter = 0;                          // Значение фильтра
    int filter_counter = 1;                  // количество котировок вне условия в фильтрации после которой они считаются нормой
    double filter_limit = 0.0;               // Максимально допустимое отклонение от последней котировки
    int filter_smoothing = 0;                // Сглаживание фильтрации
    float filter_reserved = 0.0f;            // Зарезервировано
    int logging = 0;                         // Включить логирование котировок

    //--- Спред
    int spread = 0;                          // Спред
    int spread_balance = 0;                  // Баланс спреда

    //--- Свопы
    int exemode = 0;                         // Режим исполнения
    int swap_enable = 0;                     // Включение свопов
    int swap_type = 0;                       // Тип свопов
    double swap_long = 0.0, swap_short = 0.0; // Свопы для длинных и коротких позиций
    int swap_rollover3days = 0;              // Тройной своп (день недели)
    int swap_daily = 0;                      // Начислять своп каждый день без triple rollover

    double contract_size = 0.0;              // Размер контракта
    double tick_value = 0.0;                 // Стоимость одного тика
    double tick_size = 0.0;                  // Размер одного тика
    int stops_level = 0;                     // Минимальное отклонение от текущей цены
    int gtc_pendings = 0;                    // GTC режим

    //--- Маржинальные параметры
    int margin_mode = 0;                     // Режим расчета маржи
    double margin_initial = 0.0;             // Начальная маржа
    double margin_maintenance = 0.0;         // Поддерживающая маржа
    double margin_hedged = 0.0;              // Маржа для хеджированных позиций
    double margin_divider = 0.0;             // Делитель маржи

    //--- Внутренние параметры
    double point = 0.0;                      // Размер пункта
    double multiply = 0.0;                   // Коэффициент умножения
    double bid_tickvalue = 0.0;              // Стоимость тика по Bid
    double ask_tickvalue = 0.0;              // Стоимость тика по Ask

    //--- Реалтайм котировки
    time_t tick_time = 0;                    // Время последнего тика
    double bid = 0.0, ask = 0.0;             // bid, ask

    //--- Ограничения
    int long_only = 0;                       // Разрешены только длинные позиции
    int instant_max_volume = 0;             // Максимальный объем для Instant Execution

    //--- Сессии
    int           realtime = 1;                        // allow real time quotes
    time_t        starting = 0;                        // trades starting date (UNIX time)
    time_t        expiration = 0;                      // trades end date      (UNIX time)

    //--- Дополнительные параметры
    std::string quote_currency;             // Валюта расчетов quoteCurrency
    std::string margin_currency;            // Валюта маржи
    int freeze_level = 0;                   // Уровень заморозки
    int margin_hedged_strong = 0;           // Строгий режим маржи
    time_t value_date = 0;                  // Дата расчета стоимости
    int quotes_delay = 0;                   // Задержка котировок

    int swap_openprice = 0;                 // Использовать цену открытия при расчете свопов
    int swap_variation_margin = 0;          // Вариационная маржа на ролловер

    //--- Зарезервированные параметры
    int unused[21]{};                        // Зарезервировано

    //--- Sysstem параметры
    int db_state = 0;

    //--- Additionals

};

struct SymbolAdditionalRecord {
    std::string symbol;
    std::string clear_symbol;
    std::string full_symbol_name;
    std::string exchange;
    std::string description;
    std::string category;
    std::string market;
    std::string sector;
    std::string country;
    std::string industry;
    std::string icon;
    int shareholders = 0;
    double market_cap = 0.0;
    double analyst_rating = 0.0;
    double os_rating = 0.0;
    double ma_rating = 0.0;
    double tech_rating = 0.0;
};
