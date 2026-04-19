#pragma once

#include <array>
#include <string>
#include <ctime>

//todo Все манипуляции с кешем должно происходить через этого менеджера так как нужен mutex


//--- Торговые команды cmd (тип ордера)
enum {
    OP_NOTHING = -1,
    OP_BUY = 0,                     // Покупка (Buy)
    OP_SELL = 1,                    // Продажа (Sell)
    OP_BUY_LIMIT = 2,               // Лимитный ордер на покупку (Buy Limit)
    OP_SELL_LIMIT = 3,              // Лимитный ордер на продажу (Sell Limit)
    OP_BUY_STOP = 4,                // Стоп-ордер на покупку (Buy Stop)
    OP_SELL_STOP =  5,              // Стоп-ордер на продажу (Sell Stop)
    OP_BALANCE_IN = 6,              // Балансовая операция пополнение (Balance)
    OP_CREDIT_IN = 7,               // Кредитная операция пополнение (Credit)
    OP_BALANCE_OUT = 8,             // Балансовая операция списание (Balance)
    OP_CREDIT_OUT = 9,              // Кредитная операция списание (Credit)
    OP_BUY_STOP_LIMIT = 10,         // Лимитный стоп ордер на покупку (Buy Limit)
    OP_SELL_STOP_LIMIT = 11,        // Лимитный стоп ордер на продажу (Sell Limit)
    OP_CHARGE = 12,                 // Additional charges/withdrawals.
    OP_CORRECTION = 13,             // Correcting operation
    OP_BONUS,
    OP_COMMISSION,
    OP_COMMISSION_DAYLY = 16,
    OP_COMMISSION_MONTHLY,
    OP_INTERESTRATE,                // Accrual of annual interest.
    OP_DIVIDEND,
    OP_DIVIDEND_FRANKED = 20,
    OP_TAX,
    OP_SO_COMPENSATION
};

//--- Состояния торговой записи state
enum {
    TS_ROLLOVER = -2,                   // Открытые позиции которые необходимо засинкать в базу
    TS_NO_CHANGE = -1,                  // Открыта в обычном режиме
    TS_OPEN_NORMAL,                     // Открыта в обычном режиме
    TS_OPEN_REQUEST,                    // Запрос на открытие Ожидание подтверждения
    TS_OPEN_RESTORED,                   // Восстановлена
    TS_CLOSED_NORMAL,                   // Закрыта
    TS_CLOSED_PART,                     // Частично закрыта
    TS_CLOSED_BY,                       // Закрыта встречным ордером
    TS_DELETED = 6,                     // Удалена
    TS_CLOSE_REQUEST = 7,               // Запрос на закрытие ордера
    TS_DELETE_REQUEST = 8,              // Запрос на удаление закрытой позиции
    TS_CANCEL_REQUEST,                  // Запрос на удаление открытой/pending позиции
    TS_FINANCE_OPEN_REQUEST,            // Запрос на добавление операции финансов
    TS_FINANCE_UPDATE_REQUEST,          // Запрос на добавление операции финансов
    TS_FINANCE_DELETE_REQUEST = 12,     // Запрос на удаление финансовой операции
    TS_RESTORE_REQUEST,                 // Запрос на перелткрытие позиции
    TS_OPEN_UPDATE_REQUEST,             // Запрос на обновление открытой позиции
    TS_CLOSED_UPDATE_REQUEST,           // Запрос на обновление закрытой позиции
    TS_PENDING_UPDATE_REQUEST,           // Запрос на обновление отложенной позиции
};

//--- базовые типы трейдов tradeType
enum {
    TRD_ALL_TRADES = 0,     // все трейды
    TRD_OPEN_TRADES,        // все открытые трейды
    TRD_CLOSE_TRADES,       // все закрытые трейды
    TRD_PENDING_TRADES,     // все пендинг трейды
    TRD_FINANCE_TRADES      // все финансовые трейды
};

//--- Причины открытия ордера
enum {
    TR_REASON_CLIENT = 0, // Клиентский терминал
    TR_REASON_EXPERT = 1, // Советник (Expert Advisor)
    TR_REASON_DEALER = 2, // Дилер
    TR_REASON_SIGNAL = 3, // Торговый сигнал
    TR_REASON_GATEWAY = 4,// Внешний шлюз
    TR_REASON_MOBILE = 5, // Мобильное приложение
    TR_REASON_WEB = 6,    // Веб-терминал
    TR_REASON_API = 7     // API-запрос
};

//--- Типы активации (используются в MT Manager)
enum {
    ACTIVATION_NONE = 0,                                // Без активации
    ACTIVATION_SL, ACTIVATION_TP,                       // Стоп-лосс, Тейк-профит
    ACTIVATION_PENDING,                                 // Ожидание исполнения ордера
    ACTIVATION_STOPOUT,                                 // Принудительное закрытие по маржин-коллу
    ACTIVATION_CANCEL,                                  // Отмена ордера из-за невозможности активации
    ACTIVATION_SL_ROLLBACK = -ACTIVATION_SL,            // Откат по стоп-лоссу
    ACTIVATION_TP_ROLLBACK = -ACTIVATION_TP,            // Откат по тейк-профиту
    ACTIVATION_PENDING_ROLLBACK = -ACTIVATION_PENDING,  // Откат по лимитному/стоп-ордеру
    ACTIVATION_STOPOUT_ROLLBACK = -ACTIVATION_STOPOUT,  // Откат по маржин-коллу
    ACTIVATION_CANCEL_ROLLBACK = -ACTIVATION_CANCEL     // Откат отмены активации
};

//+------------------------------------------------------------------+
//| Структура записи трейда используется по проекту
//+------------------------------------------------------------------+
struct TradeRecord {
    int         order = 0;             // Уникальный идентификатор ордера (ticket)
    int         login;                 // Идентификатор владельца счета
    std::string symbol;                // Символ торгового инструмента (например, "EURUSD")
    int         digits = 2;            // Количество знаков после запятой в котировке
    int         cmd;                   // Тип ордера (см. `enum OP_*`)
    int         volume;                // Объем ордера (лотность) Оно приводится в int min лотность / 100

    //--- Время и состояние ордера
    time_t      open_time = 0;         // Время открытия ордера (UNIX timestamp)
    int         state;                 // Текущее состояние ордера (см. `enum TS_*`)
    double      open_price;            // Цена открытия ордера
    double      sl = 0.0, tp = 0.0;    // Уровни Stop Loss и Take Profit
    double      margin_initial;        // Маржа инициализации ордера
    time_t      close_time = 0;        // Время закрытия ордера (если закрыт)

    //int trailing_stop = 0; Stop Loss to follow the current price if the profit from a position increases.

    //--- Данные для шлюзов и исполнения
    int         gw_volume;             // Объем, исполненный через внешний шлюз
    time_t      expiration;            // Время истечения ордера (для отложенных ордеров)
    int         reason;                // Причина создания ордера (см. `enum TR_REASON_*`)

    //--- Конверсионные коэффициенты
    std::array<double, 2> conv_rates; // Курсы конвертации валюты прибыли в валюту депозита:
                                      // conv_rates[0] - на момент открытия
                                      // conv_rates[1] - на момент закрытия
    //--- Финансовые показатели
    double      commission;            // Комиссия за сделку
    double      prev_commission = 0.0; // Предыдущая комиссия за сделку
    double      commission_agent;      // Комиссия агента (IB)
    double      storage;               // Своп (overnight fee)
    double      prev_storage = 0.0;    // Предыдущий своп (overnight fee)
    double      profit;                // Итоговая прибыль/убыток
    double      prev_profit = 0.0;     // предыдущая итоговая прибыль/убыток

    //--- Функции для начисления свопа
    //time_t last_accrual_time;         // предыдущие начисление свопа
    //time_t next_rollover_time;        // следующие начисление свопа

    double      close_price;           // Цена закрытия ордера
    double      taxes;                 // Налоги

    //--- LP параметры
    int         magic;                 // Магический номер (идентификатор советника)
    std::string comment;               // Комментарий к ордеру
    int         gw_order;              // Номер ордера во внешнем шлюзе
    std::string gw_source;             // Источник/провайдер внешнего шлюза
    std::string gw_uuid;               // Внешний UUID/идентификатор сделки в шлюзе
    int         activation;            // Тип активации ордера (см. `enum ACTIVATION_*`)
    double      gw_open_price;         // Цена открытия во внешнем шлюзе
    double      gw_close_price;        // Цена закрытия во внешнем шлюзе
    double      margin_rate;           // Коэффициент маржи (конвертация валюты маржи в валюту депозита)
    std::string api_data;
    time_t      last_swap_time;             // Временная метка последнего изменения

    //--- Sysstem параметры
    int db_state = 0;
};

//+------------------------------------------------------------------+
//| Структура изменений записи (ордер) используется в плагине
//+------------------------------------------------------------------+
struct TradeDiffRecord {
    int         volume;                // Объем ордера (лотность) Оно приводится в int min лотность / 100
    time_t      open_time;             // Время открытия ордера (UNIX timestamp)
    int         state;                 // Текущее состояние ордера (см. `enum TS_*`)
    double      open_price;            // Цена открытия ордера
    double      sl, tp;                // Уровни Stop Loss и Take Profit
    time_t      close_time;            // Время закрытия ордера (если закрыт)
    time_t      expiration;            // Время истечения ордера (для отложенных ордеров)
    int         reason;                // Причина создания ордера (см. `enum TR_REASON_*`)
    double      commission;            // Комиссия за сделку
    double      storage;               // Своп (overnight fee)
    double      profit;                // Своп (overnight fee)
    double      close_price;           // Цена закрытия ордера
    double      taxes;                 // Налоги
    int         magic;                 // Магический номер (идентификатор советника)
    std::string comment;               // Комментарий к ордеру
    int         gw_order;              // Номер ордера во внешнем шлюзе
    int         activation;            // Тип активации ордера (см. `enum ACTIVATION_*`)
    double      gw_open_price;         // Цена открытия во внешнем шлюзе
    double      gw_close_price;        // Цена закрытия во внешнем шлюзе
    time_t      last_swap_time;        // Временная метка последнего изменения
};

//+------------------------------------------------------------------+
//| Структура для калькулирования
//+------------------------------------------------------------------+
struct TradeCalcRecord {
    int         order;                 // Уникальный идентификатор
    std::string symbol;                 // Уникальный идентификатор
    int         login;                 // Уникальный идентификатор
    int         volume;                // Объем ордера (лотность) Оно приводится в int min лотность / 100
    int         state;                 // Текущее состояние ордера (см. `enum TS_*`)
    int         cmd;                   // Текущее состояние ордера (см. `enum TS_*`)
    double      open_price;            // Цена открытия ордера
    double      sl, tp;                // Уровни Stop Loss и Take Profit
    time_t      open_time;             // Время закрытия ордера (если закрыт)
    time_t      close_time;            // Время закрытия ордера (если закрыт)
    double      commission;            // Комиссия за сделку
    double      storage;               // Своп (overnight fee)
    double      profit;                // Своп (overnight fee)
    double      prev_commission;       // Предыдущая Комиссия за сделку
    double      prev_storage;          // Предыдущая Своп (overnight fee)
    double      prev_profit;           // Предыдущая Своп (overnight fee)
    double      close_price;           // Цена закрытия ордера
    int         activation;            // Тип активации ордера (см. `enum ACTIVATION_*`)
    double      margin_rate;           //
    double      margin_initial;        //
    time_t      last_swap_time = 0;    //
    int         update_state = 0;      //
};

//+------------------------------------------------------------------+
//| Trade summary                                                   |
//+------------------------------------------------------------------+
struct TradeSummaryRecord {
    std::string       symbol;                  // symbol
    int               digits = 0;              // floating point digits
    int               type = 0;                // symbol type (0 - symbol group index)

    //--- clients summary
    int               orders = 0;              // count number of client orders
    int               buylots = 0;             // buy volume
    int               selllots = 0;            // sell volume
    double            buyprice = 0.0;          // average buy price
    double            sellprice = 0.0;         // average sell price
    double            profit = 0.0;            // clients profit

    //--- coverage summary by LP
    int               covorders = 0;           // number of coverage orders
    int               covbuylots = 0;          // buy volume
    int               covselllots = 0;         // sell volume
    double            covbuyprice = 0.0;       // average buy price
    double            covsellprice = 0.0;      // average sell price
    double            covprofit = 0.0;         // coverage profit
};

struct TradeStatRecord {
    int total_trades = 0;
    int total_profitable_trades = 0;
    double total_pnl = 0.0;
    double total_commission = 0.0;
    double total_swap = 0.0;
};
