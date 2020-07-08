#include "BUILD_ORDER.h"

VulkanInstance* instance;
VulkanPhysicalDevice* physicalDevice;

int main() 
{
	VulkanConfig vulkan_config;
	vulkan_config.applicationName = "Bruh've";
	vulkan_config.applicationVersion = VK_MAKE_VERSION(0,0,1);

	instance = new VulkanInstance(vulkan_config);
	physicalDevice = VulkanPhysicalDevice::GetPhysicalDevice(instance);


	delete physicalDevice;
	delete instance;
	return 0;
}