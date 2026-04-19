#include <PluginInterface.h>
#include <PluginServerInterface.h>

class MinimalPlugin final : public PluginInterface {
public:
    std::string plugin_name() const override { return "minimal-plugin"; }
};

int main() {
    MinimalPlugin plugin;
    return plugin.getApiVersion() > 0 ? 0 : 1;
}
