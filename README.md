# Plugin SDK

This directory contains the exported public header set for server plugins.

The command rebuilds:

- `sdk/plugin/include/PluginInterface.h`
- `sdk/plugin/include/PluginServerInterface.h`
- `sdk/plugin/include/Structures.h`
- `sdk/plugin/include/model/*`
- `sdk/plugin/include/rapidjson/*`

The SDK exposes the full plugin-facing server API and public data structures required to compile plugins outside the main repository tree.

Host interface contract:

- `PluginServerInterface` is an abstract host interface, not a concrete runtime class
- plugins must not construct or store `PluginServerInterface` by value
- the host creates the runtime implementation and passes it to plugin entry points as `PluginServerInterface*`
- plugins must export `extern "C" int GetPluginApiVersion()` returning
  `PLUGIN_VERSION_API`
- plugins must export `extern "C" int GetPluginServerApiVersion()` returning
  `PluginServerInterface::GetApiVersion()`
- both versions must match the server exactly; compatibility is checked before
  `CreatePlugin()` is called

Trade contract:

- stable plugin trade types are exported under `sdk/plugin/include/model/*`
- `PluginInterface.h` and `PluginServerInterface.h` now use `PluginTradeRecord`, `PluginTradeRequestRecord`, and `PluginTradeDiffRecord`
- `PluginServerInterface::SetTradeGatewayData()` uses `PluginTradeGatewayDataUpdateRecord` for partial gateway metadata updates by order without running the main trading flow
- internal `TradeRecord` is no longer the public plugin trade contract

Account contract:

- stable plugin account types are exported under `sdk/plugin/include/model/*`
- `PluginInterface.h` and `PluginServerInterface.h` use `PluginAccountRecord`, `PluginAccountRequestRecord`, `PluginAccountDiffRecord`, `PluginMarginLevel`, and `PluginEquityRecord`
- internal `AccountRecord`, `MarginLevel`, and `EquityRecord` are no longer the public plugin account contract

Symbol contract:

- stable plugin symbol types are exported under `sdk/plugin/include/model/*`
- `PluginInterface.h` trade hooks and `PluginServerInterface::GetSymbol()` use `PluginSymbolRecord`
- internal `SymbolRecord` is no longer the public plugin symbol contract

Group contract:

- stable plugin group types are exported under `sdk/plugin/include/model/*`
- `PluginInterface.h` trade hooks and `PluginServerInterface::GetGroup()` / `GetAllGroups()` use `PluginGroupRecord`
- internal `GroupRecord` is no longer the public plugin group contract
- `PluginGroupRecord::partial_close` mirrors the server group setting for partial-close permission; `0` means partial close is disabled for the group, non-zero means enabled
- `PluginGroupRecord::allow_sl_tp_slippage` mirrors the server group setting for SL/TP execution; `1` allows market-price slippage after SL/TP trigger, `0` closes exactly at the configured SL/TP level

Common models:

- `PluginServerInterface::GetLogs()` uses `PluginServerLog`
- chart methods use `PluginCandleRecord`
- internal `ServerLog` and `CandleRecord` are no longer part of the public plugin contract

Example:

- `sdk/plugin/examples/minimal_plugin.cpp`

Notes:

- Public headers are synced directly from the product tree. Do not edit `sdk/plugin/include/*` manually.
- RapidJSON is exported under `sdk/plugin/include/rapidjson`, and public headers use `#include <rapidjson/...>`.
- Consumer include path should point to `sdk/plugin/include`.
- `sdk_contract/plugin/*` is the canonical source for the exported plugin contracts; `sdk/plugin/include/model/*` is the synced snapshot.

Smoke-check:

```bash
./tools/check_sdk_headers.sh
```

This script re-syncs the SDKs and runs a syntax-only compile check for the SDK example files.

Sync command:

```bash
./tools/sync_plugin_sdk.sh
```

Publish command:

```bash
./tools/publish_sdk.sh plugin
```

This command runs sync, smoke-check, creates a commit for `sdk/plugin` if the snapshot changed, and then pushes the SDK to the `plugin_sdk` remote with `git subtree`.
