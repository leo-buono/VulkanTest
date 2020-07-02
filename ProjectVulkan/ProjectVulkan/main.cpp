#include "BUILD_ORDER.h"

VkInstance instance;

std::vector<const char*> layers;
std::vector<const char*> extensions;


int main() 
{
	VulkanConfig vulkan_config;
	vulkan_config.applicationName = "Bruh've";
	vulkan_config.applicationVersion = VK_MAKE_VERSION(0,0,1);

	VkApplicationInfo appInfo = Initializers::ApplicationInfo(vulkan_config);

	VkInstanceCreateInfo instance_Info = Initializers::instanceCreateInfo(appInfo, layers, extensions);

	instanceErrorCheck(vkCreateInstance(&instance_Info, NULL, &instance));

	vkDestroyInstance(instance, NULL);
	return 0;
}