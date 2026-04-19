# Plugin SDK

This directory contains the exported public header set for server plugins.

Sync command:

```bash
./tools/sync_plugin_sdk.sh
```

The command rebuilds:

- `sdk/plugin/include/PluginInterface.h`
- `sdk/plugin/include/PluginServerInterface.h`
- `sdk/plugin/include/Structures.h`
- `sdk/plugin/include/structures/*`
- `sdk/plugin/include/rapidjson/*`

The SDK exposes the full plugin-facing server API and public data structures required to compile plugins outside the main repository tree.

Example:

- `sdk/plugin/examples/minimal_plugin.cpp`

Notes:

- Public headers are synced directly from the product tree. Do not edit `sdk/plugin/include/*` manually.
- RapidJSON is exported under `sdk/plugin/include/rapidjson`, and public headers use `#include <rapidjson/...>`.
- Consumer include path should point to `sdk/plugin/include`.

Smoke-check:

```bash
./tools/check_sdk_headers.sh
```

This script re-syncs the SDKs and runs a syntax-only compile check for the SDK example files.
