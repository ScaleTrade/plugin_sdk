#pragma once
#include <string>
#include <ctime>


//--- типы подключчения
enum {
    SESSION_TYPE_TCP = 0,        // Покупка (Buy)
    SESSION_TYPE_FIX,           // Продажа (Sell)
};

//--- Режим расчета маржи
enum { MARGIN_MODE_DONT_USE, MARGIN_MODE_USE_ALL, MARGIN_MODE_USE_PROFIT, MARGIN_MODE_USE_LOSS };
//--- Тип контроля маржи
enum { MARGIN_TYPE_PERCENT, MARGIN_TYPE_CURRENCY };
//--- margin level type
enum { MARGINLEVEL_OK=0, MARGINLEVEL_MARGINCALL, MARGINLEVEL_STOPOUT };

struct AccountOnlineRecord {
    int login = 0;
    int state = 0;
};

//+------------------------------------------------------------------+
//| Margin level of the user                                         |
//+------------------------------------------------------------------+
// memory data
struct MarginLevel {
    int               login;                                // user login // эх надо было бы переделать на ID
    std::string       group;                                // user group
    int               leverage;                             // user leverage
    double            balance = 0.0;                        // balance для рассчетов добавляем credit
    double            credit = 0.0;                         // credit кредит может только гасится
    double            equity = 0.0;                         // equity
    double            profit = 0.0;                         // profit
    double            storage = 0.0;                        // profit
    double            commission = 0.0;                     // profit
    double            margin = 0.0;                         // margin requirements
    double            margin_free = 0.0;                    // free margin
    double            margin_level = 0.0;                   // margin level
    int               margin_type = MARGIN_TYPE_PERCENT;    // margin controlling type (percent/currency)
    int               level_type = MARGINLEVEL_OK;          // level type(ok/margincall/stopout)
};

//+------------------------------------------------------------------+
//| Equity snapshot data the user                                         |
//+------------------------------------------------------------------+
struct EquityRecord {
    int               login;                                // user login // эх надо было бы переделать на ID
    time_t            create_time;                          // create Time
    std::string       group;                                // user group
    double            balance = 0.0;                        // balance для рассчетов добавляем credit
    double            prevbalance = 0.0;                    // prevent balance
    double            credit = 0.0;                         // credit кредит может только гасится
    double            equity = 0.0;                         // equity
    double            profit = 0.0;                         // profit
    double            storage = 0.0;                        // profit
    double            commission = 0.0;                     // profit
    double            margin = 0.0;                         // margin requirements
    double            margin_free = 0.0;                    // free margin
    double            margin_level = 0.0;                   // margin level
    std::string       currency;                             // user group
};
//+------------------------------------------------------+
//| Структура данных пользователя/account                       |
//+------------------------------------------------------+
struct AccountRecord {
    // --- Учетные данные пользователя ---
    int login = 0;                     // Логин пользователя (уникальный идентификатор)
    std::string group;                 // Группа пользователя (например, "Admin", "Trader")
    std::string password;              // Пароль (обычно в зашифрованном виде)

    // --- Параметры доступа ---
    int enable = 1;                     // Статус учетной записи (1 - активна, 0 - заблокирована)
    int enable_change_password;         // Разрешено ли менять пароль (1 - да, 0 - нет)
    int enable_read_only;               // Режим "Только просмотр" (1 - нельзя торговать)
    int enable_otp;                     // Включена ли двухфакторная аутентификация (OTP)
    int enable_reserved[2];             // Зарезервированные параметры

    // --- Альтернативные пароли ---
    std::string password_investor;      // Пароль инвестора (режим "Только просмотр")

    // --- Личная информация ---
    std::string avatar;                 // Аватар аккаунта
    std::string name;                   // Полное имя пользователя
    std::string country;                // Страна проживания
    std::string city;                   // Город проживания
    std::string state;                  // Область/штат
    std::string zipcode;                // Почтовый индекс
    std::string address;                // Адрес проживания
    std::string lead_source;            // Источник привлечения клиента (например, "Реклама", "Партнер")
    std::string phone;                  // Контактный телефон
    std::string email;                  // Электронная почта
    std::string comment;                // Дополнительный комментарий к пользователю
    std::string id;                     // Идентификационный номер (паспорт, ИНН)
    std::string status;                 // Статус клиента (например, "Active", "VIP", "Blocked")

    // --- Временные метки ---
    time_t regdate;                     // Дата регистрации пользователя в системе
    time_t lastdate;                    // Дата последнего входа в систему

    // --- Финансовые параметры ---
    int leverage;                           // Кредитное плечо (например, 1:100, 1:500) // только для форекс
    int agent_account;                      // ID реферального агента (если есть)
    time_t timestamp;                       // Временная метка последнего обновления данных
    int last_ip;                            // Последний IP-адрес входа (в числовом формате)

    double balance;                         // Текущий баланс пользователя дублирующий он равен сумме позиций
    double prevmonthbalance;                // Баланс на конец предыдущего месяца
    double prevbalance;                     // Баланс на конец предыдущего дня

    double credit;                          // Кредитные средства (если были предоставлены)
    double interestrate;                    // Процентная ставка (например, по депозиту)
    double taxes;                           // Налоговые удержания
    double prevmonthequity;                 // Эквити (чистые средства) на конец предыдущего месяца
    double prevequity;                      // Эквити на конец предыдущего дня
    double reserved2[2];                    // Зарезервированные значения для будущего использования

    // --- Параметры безопасности ---
    std::string otp_secret;                 // Секретный ключ для генерации одноразовых паролей (OTP)
    std::string secure_reserved;            // Зарезервированные параметры безопасности
    int send_reports;                       // Флаг отправки отчетов на e-mail (1 - да, 0 - нет)
    int mqid;                               // Идентификатор в системе MQ

    std::string user_color = "#ffffff";        // Цветовая метка пользователя в системе (например, для VIP-клиентов)

    // --- Дополнительные зарезервированные данные ---
    std::string unused;                // Зарезервированные данные (на будущее расширение системы)
    std::string api_data;              // Данные для API-интеграции
    MarginLevel margin;                // todo как идея

    int db_state = 0;

    //Online stats
    int online = 0;
};


struct AccountDiffRecord {
 // --- Учетные данные пользователя ---
    int login = 0;                    // Логин пользователя (уникальный идентификатор)
    std::string group;                // Группа пользователя (например, "Admin", "Trader")

    // --- Параметры доступа ---
    int enable = 1;                   // Статус учетной записи (1 - активна, 0 - заблокирована)
    int enable_change_password;       // Разрешено ли менять пароль (1 - да, 0 - нет)
    int enable_read_only;             // Режим "Только просмотр" (1 - нельзя торговать)
    int enable_otp;                   // Включена ли двухфакторная аутентификация (OTP)

    // --- Личная информация ---
    std::string name;                  // Полное имя пользователя
    std::string country;               // Страна проживания
    std::string city;                  // Город проживания
    std::string state;                 // Область/штат
    std::string zipcode;               // Почтовый индекс
    std::string address;               // Адрес проживания
    std::string lead_source;           // Источник привлечения клиента (например, "Реклама", "Партнер")
    std::string phone;                 // Контактный телефон
    std::string email;                 // Электронная почта
    std::string comment;               // Дополнительный комментарий к пользователю
    std::string id;                    // Идентификационный номер UID
    std::string status;                // Статус клиента (например, "Active", "VIP", "Blocked")

    // --- Временные метки ---
    time_t regdate;                    // Дата регистрации пользователя в системе
    time_t lastdate;                   // Дата последнего входа в систему

    // --- Финансовые параметры ---
    int leverage;                           // Кредитное плечо (например, 1:100, 1:500) // только для форекс
    int agent_account;                      // ID реферального агента (если есть)

    double balance;                         // Текущий баланс пользователя дублирующий он равен сумме позиций
    double prevmonthbalance;                // Баланс на конец предыдущего месяца
    double prevbalance;                     // Баланс на конец предыдущего дня

    double credit;                          // Кредитные средства (если были предоставлены)
    double interestrate;                    // Процентная ставка (например, по депозиту)
    double taxes;                           // Налоговые удержания
    double prevmonthequity;                 // Эквити (чистые средства) на конец предыдущего месяца
    double prevequity;                      // Эквити на конец предыдущего дня

    // --- Параметры безопасности ---
    std::string otp_secret;                 // Секретный ключ для генерации одноразовых паролей (OTP)
    std::string secure_reserved;            // Зарезервированные параметры безопасности
    int send_reports;                       // Флаг отправки отчетов на e-mail (1 - да, 0 - нет)

    std::string user_color = "#ffffff";     // Цветовая метка пользователя в системе (например, для VIP-клиентов)

};

struct AccountStatRecord {
    int total_accounts = 0;
    int total_balance_accounts = 0;
    double total_balance = 0.0;
    double total_credit = 0.0;
    double total_margin = 0.0;
};
