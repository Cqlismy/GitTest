#include <hardware/hardware.h>

typedef struct led_module {
	struct hw_module_t common;
	...
	...
} led_module_t;

struct led_module HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.module_api_version = LED_MODULE_API_VERSION_1_0,
		.hal_api_version = HARDWARE_HAL_API_VERSION,
		.id = LED_HARDWARE_MODULE_ID,
		.name = "Defaule Led HAL",
		.author = "hly",
		.methods = &led_module_methods,
	},
	...
	...
};
