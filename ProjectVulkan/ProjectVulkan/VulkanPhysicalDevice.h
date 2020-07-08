#pragma once
#include "BUILD_ORDER.h"

class VulkanInstance;

class VulkanPhysicalDevice
{
public:
	~VulkanPhysicalDevice();
	VkPhysicalDevice& GetPhysicalDevice();
	QueueFamilyIndices& GetQueueFamilyIndices();
	VkPhysicalDeviceProperties& GetPhysicalDeviceProperties();
	VkPhysicalDeviceFeatures& GetPhysicalDeviceFeatures();
	VkPhysicalDeviceMemoryProperties& GetPhysicalDeviceMemoryProperties();
	static VulkanPhysicalDevice* GetPhysicalDevice(VulkanInstance* instance);

private:
	VulkanPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice device, QueueFamilyIndices indices);
	static std::vector<VkPhysicalDevice> GetAvailablePhysicalDevices(VulkanInstance* instance);
	static bool PhysicalDeviceSupported(VulkanInstance* instance, VkPhysicalDevice& device, QueueFamilyIndices& familyIndices);
	static bool SupportsQueueFamily(VkPhysicalDevice& device, QueueFamilyIndices& familyIndices);
	VulkanInstance* m_instance;
	VkPhysicalDevice m_device;
	QueueFamilyIndices m_familyIndices;
	VkPhysicalDeviceProperties m_physicalDeviceProperties;
	VkPhysicalDeviceFeatures  m_physicalDeviceFeatures;
	VkPhysicalDeviceMemoryProperties  m_physicalDeviceMemoryProperties;
};

