#include "Validation.h"

void instanceErrorCheck(VkResult res)
{
	if (res != VK_SUCCESS)
	{
		std::cout << "Error!\n";
		assert(0 && "There was an error");
	}
}
