#pragma once

#include <string>
#include <unordered_map>

//--- Режимы обработки сделок
enum { EXECUTION_MANUAL, EXECUTION_AUTO, EXECUTION_ACTIVITY };
//--- Тип комиссии
enum { COMM_TYPE_MONEY, COMM_TYPE_PIPS, COMM_TYPE_PERCENT };
//--- Режим расчета комиссии
enum { COMMISSION_PER_LOT, COMMISSION_PER_DEAL };
//--- Ограничения торговых прав клиентов
enum { TRADE_DENY_NONE=0, TRADE_DENY_CLOSEBY=1, TRADE_DENY_MUCLOSEBY=2 };
//--- Режим автоматического закрытия позиций
enum { CLOSE_OUT_NONE, CLOSE_OUT_HIHI, CLOSE_OUT_LOLO, CLOSE_OUT_HILO, CLOSE_OUT_LOHI, CLOSE_OUT_FIFO, CLOSE_OUT_LIFO, CLOSE_OUT_INTRDAY_FIFO };

//--- Режим новостей
enum { NEWS_NO, NEWS_TOPICS, NEWS_FULL };
//--- Права группы
enum { ALLOW_FLAG_EMAIL=1, ALLOW_FLAG_TRAILING=2, ALLOW_FLAG_ADVISOR=4, ALLOW_FLAG_EXPIRATION=8, ALLOW_FLAG_SIGNALS_ALL=16, ALLOW_FLAG_SIGNALS_OWN=32, ALLOW_FLAG_RISK_WARNING=64, ALLOW_FLAG_FORCED_OTP_USAGE=128 };
//--- OTP режим группы
enum { OTP_MODE_DISABLED=0, OTP_MODE_TOTP_SHA256=1 };

#define MAX_SEC_GROUPS       (32)
#define MAX_SEC_GROPS_MARGIN (128)

//--- Конфигурация торговой группы
struct GroupRecordSec {
    int sec_index = 0;            // Идентификатор
    int show = 0;                 // Разрешено ли показывать инструменты
    int trade = 0;                // Разрешена ли торговля
    int execution = 0;            // Режим исполнения (EXECUTION_MANUAL, EXECUTION_AUTO, EXECUTION_ACTIVITY)
    double comm_base = 0.0;       // Базовая комиссия
    int comm_type = 0;            // Тип комиссии (COMM_TYPE_MONEY, COMM_TYPE_PIPS, COMM_TYPE_PERCENT)
    int comm_lots = 0;            // Режим расчета комиссии (COMMISSION_PER_LOT, COMMISSION_PER_DEAL)
    double comm_agent = 0.0;      // Комиссия агента
    int comm_agent_type = 0;      // Режим комиссии агента
    int spread_diff = 0;          // Разница в спреде
    int lot_min = 0, lot_max = 0; // Минимальный и максимальный объем сделки
    int lot_step = 0;             // Шаг изменения объема
    int ie_deviation = 0;         // Максимальное отклонение цены в режиме Instant Execution
    int confirmation = 0;         // Требуется ли подтверждение сделки
    int trade_rights = 0;         // Ограничения на торговлю
    int ie_quick_mode = 0;        // Разрешено ли быстрое исполнение Instant Execution
    int autocloseout_mode = 0;    // Авто-закрытие позиций
    double comm_tax = 0.0;        // Налог на комиссию
    int comm_agent_lots = 0;      // Режим комиссии агента
    int freemargin_mode = 0;      // Режим контроля маржи
    int reserved[3]{};            // Зарезервированные поля
};

//--- Конфигурация маржи для инструментов в группе
struct GroupRecordMargin {
    std::string symbol;           // Символ
    int swap_enable = 0;          // Включить кастомный спред
    double swap_long = 0.0;       // Своп для длинных позиций
    double swap_short = 0.0;      // Своп для коротких позиций

    double margin_divider = 0.0;  // Делитель маржи

    //--- Спред
    int spread_enable = 0;        // Включить кастомный спред
    int spread = 0;               // Спред
    int spread_balance = 0;       // Баланс спреда

    int reserved[7]{};            // Зарезервировано
};

//+------------------------------------------------------------------+
// Конфигурация торгового группы
//+------------------------------------------------------------------+
struct GroupRecord {
    int grp_index;                // Индекс группы
    std::string group;            // Имя группы
    int enable = 0;               // Включена ли группа
    int timeout = 0;              // Тайм-аут подтверждения сделок
    int otp_mode = 0;             // Режим одноразовых паролей

    std::string company;          // Название компании
    std::string signature;        // Подпись в отчетах
    std::string support_page;     // Страница поддержки
    std::string smtp_server;      // SMTP-сервер
    std::string smtp_login;       // Логин SMTP
    std::string smtp_password;    // Пароль SMTP
    std::string support_email;    // Почта поддержки
    std::string templates;        // Директория шаблонов отчетов

    int copies = 0;               // Число копий отчетов
    int reports = 0;              // Включены ли отчеты
    int default_leverage = 0;     // Значение плеча по умолчанию
    double default_deposit = 0.0; // Депозит по умолчанию
    int maxsecurities = 0;        // Максимальное число инструментов

    std::unordered_map<int, GroupRecordSec> secgroups;               // Групповые настройки торговли символов
    std::unordered_map<std::string, GroupRecordMargin> secmargins;   // Настройки маржи symbol

    int secmargins_total = 0;                                     // Количество специальных настроек маржи

    std::string currency;             // Валюта счета -> присваивается аккаунту
    double credit = 0.0;              // Виртуальный кредит
    int margin_call = 0;              // Уровень Margin Call
    int margin_mode = 1;              // Режим маржи default = MARGIN_MODE_USE_ALL
    int margin_stopout = 0;           // Уровень Stop Out
    double interestrate = 0.0;        // Процентная ставка

    int use_swap = 0;                 // Использование свопов
    int news = 0;                     // Разрешен ли доступ к новостям
    int rights = 0;                   // Права группы
    int check_ie_prices = 0;          // Проверять ли цены IE
    int maxpositions = 0;             // Максимальное количество позиций
    int close_reopen = 0;             // Переоткрытие позиций
    int hedge_prohibited = 0;         // Запрет хеджирования
    int close_fifo = 0;               // Принудительное закрытие FIFO
    int hedge_largeleg = 0;           // Использовать маржу на большую ногу

    std::string securities_hash;      // Хеш-код инструментов

    int margin_type = 0;              // Тип маржи
    int archive_period = 0;           // Срок архивирования (в днях)
    int archive_max_balance = 0;      // Максимальный баланс для архивирования
    int stopout_skip_hedged = 0;      // Исключать полностью хеджированные счета из Stop Out
    int archive_pending_period = 0;   // Период очистки отложенных ордеров

    unsigned int news_languages[8]{};     // Языки новостей
    unsigned int news_languages_total = 0;// Количество языков новостей

    int reserved[17]{};               // Зарезервированные поля
};
