#include "VulkanPhysicalDevice.h"

//This sets up the graphics card, by finding which one to use, as well as different features, and VRAM the card has

VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice device, QueueFamilyIndices indices)
{
	m_instance = instance;
	m_device = device;
	m_familyIndices = indices;

	vkGetPhysicalDeviceProperties(m_device, &m_physicalDeviceProperties);
	vkGetPhysicalDeviceFeatures(m_device, &m_physicalDeviceFeatures);
	vkGetPhysicalDeviceMemoryProperties(m_device, &m_physicalDeviceMemoryProperties);
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

VkPhysicalDevice& VulkanPhysicalDevice::GetPhysicalDevice()
{
	return m_device;
}

QueueFamilyIndices& VulkanPhysicalDevice::GetQueueFamilyIndices()
{
	return m_familyIndices;
}

VkPhysicalDeviceProperties& VulkanPhysicalDevice::GetPhysicalDeviceProperties()
{
	return m_physicalDeviceProperties;
}

VkPhysicalDeviceFeatures& VulkanPhysicalDevice::GetPhysicalDeviceFeatures()
{
	return m_physicalDeviceFeatures;
}

VkPhysicalDeviceMemoryProperties& VulkanPhysicalDevice::GetPhysicalDeviceMemoryProperties()
{
	return m_physicalDeviceMemoryProperties;
}

VulkanPhysicalDevice* VulkanPhysicalDevice::GetPhysicalDevice(VulkanInstance* instance)
{
	std::vector<VkPhysicalDevice> devices = GetAvailablePhysicalDevices(instance);

	VkPhysicalDevice secondaryDevice = VK_NULL_HANDLE;
	QueueFamilyIndices secondaryQueue;

	for (auto& device : devices)
	{
		QueueFamilyIndices queueFamily;
		if (PhysicalDeviceSupported(instance, device, queueFamily))
		{
			VkPhysicalDeviceProperties physicalDeviceProperties;
			vkGetPhysicalDeviceProperties(device, &physicalDeviceProperties);

			if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				return new VulkanPhysicalDevice(instance, device, queueFamily);
			}
			else 
			{
				secondaryDevice = device;
				secondaryQueue = queueFamily;
			}
		}
	}

	if (secondaryDevice == VK_NULL_HANDLE)
	{
		return nullptr;
	}

	return new VulkanPhysicalDevice(instance, secondaryDevice, secondaryQueue);
}



std::vector<VkPhysicalDevice> VulkanPhysicalDevice::GetAvailablePhysicalDevices(VulkanInstance* instance)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance->GetInstance(), &deviceCount, nullptr);

	std::vector<VkPhysicalDevice> devices(deviceCount);

	vkEnumeratePhysicalDevices(instance->GetInstance(), &deviceCount, devices.data());

	return devices;
}

bool VulkanPhysicalDevice::PhysicalDeviceSupported(VulkanInstance* instance, VkPhysicalDevice& device, QueueFamilyIndices& familyIndices)
{
	bool supportsQueueFamily = SupportsQueueFamily(device, familyIndices);
	return supportsQueueFamily;
}

bool VulkanPhysicalDevice::SupportsQueueFamily(VkPhysicalDevice& device, QueueFamilyIndices& familyIndices)
{
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);

	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	uint32_t i = 0;
	for (auto& queueFamily : queueFamilies) 
	{
		if (queueFamily.queueCount > 0)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				familyIndices.graphicsIndices = i;
			}
			
			if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				familyIndices.computeIndices = i;
			}
		}
		if (familyIndices.graphicsIndices < UINT32_MAX && familyIndices.computeIndices < UINT32_MAX)
		{
			return true;
		}
		i++;
	}
	return false;
}
