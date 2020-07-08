#include "BUILD_ORDER.h"

VulkanInstance* instance;

int main() 
{
	VulkanConfig vulkan_config;
	vulkan_config.applicationName = "Bruh've";
	vulkan_config.applicationVersion = VK_MAKE_VERSION(0,0,1);
	instance = new VulkanInstance(vulkan_config);



	delete instance;
	return 0;
}