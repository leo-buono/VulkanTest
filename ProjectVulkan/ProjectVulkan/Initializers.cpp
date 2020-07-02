#include "Initializers.h"

VkApplicationInfo Initializers::ApplicationInfo(VulkanConfig& config)
{
	VkApplicationInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationName = config.applicationName;
	info.pEngineName = config.engine_name;
	info.engineVersion = config.engineVersion;
	info.applicationVersion = config.applicationVersion;
	info.apiVersion = config.apiVersion;
	return info;
}

VkInstanceCreateInfo Initializers::instanceCreateInfo(VkApplicationInfo& app_info, std::vector<const char*> &layers, std::vector<const char*> &extensions)
{
	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pApplicationInfo = &app_info;
	info.enabledExtensionCount = extensions.size();
	info.enabledLayerCount = layers.size();
	info.ppEnabledExtensionNames = extensions.data();
	info.ppEnabledLayerNames = layers.data();

	return info;
}
