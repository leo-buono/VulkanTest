#include "VulkanInstance.h"

VulkanInstance::VulkanInstance(VulkanConfig& vulkan_config)
{
	VkApplicationInfo appInfo = Initializers::ApplicationInfo(vulkan_config);
	VkInstanceCreateInfo instance_Info = Initializers::instanceCreateInfo(appInfo, layers, extensions);
	instanceErrorCheck(vkCreateInstance(&instance_Info, NULL, &instance));
}

VulkanInstance::~VulkanInstance()
{
	vkDestroyInstance(instance, NULL);
}

VkInstance VulkanInstance::GetInstance()
{
	return instance;
}
