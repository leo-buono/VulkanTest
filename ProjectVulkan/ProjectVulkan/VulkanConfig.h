#pragma once
#include "BUILD_ORDER.h"

struct VulkanConfig 
{
	const char* applicationName = "";
	uint32_t applicationVersion = VK_MAKE_VERSION(0,0,0);
	const char* engine_name = "YesENG";
	const uint32_t engineVersion = VK_MAKE_VERSION(0, 0, 0);
	const uint32_t apiVersion = VK_MAKE_VERSION(1,2,141);

};