#include <PluginInterface.h>
#include <PluginServerInterface.h>

class MinimalPlugin final : public PluginInterface {
public:
    std::string plugin_name() const override { return "minimal-plugin"; }
};

extern "C" int GetPluginApiVersion() {
    return PLUGIN_VERSION_API;
}

extern "C" int GetPluginServerApiVersion() {
    return PluginServerInterface::GetApiVersion();
}

int main() {
    MinimalPlugin plugin;
    return plugin.getApiVersion() > 0 ? 0 : 1;
}
