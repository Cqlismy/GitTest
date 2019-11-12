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

typedef struct led_device {
	struct hw_device_t common;
	int (*get_led_state)(struct led_device *dev, char **state);
	int (*set_led_state)(struct led_device *dev, char *state);
	...
	...
} led_device_t;

static int led_device_open(const struct hw_module_t *module, 
						   const char *id, struct hw_device_t **device)
{
	struct led_device *dev;
	
	dev = malloc(sizeof(struct led_device));
	if (!dev) {
		ALOGE("Failed to malloc memory");
		return -ENOMEM;
	}
	memset(dev, 0, sizeof(led_device));
	
	dev->common.tag = HARDWARE_DEVICE_TAG;
	dev->common.version = MODULE_API_VERSION_1_0;
	dev->common.module = (struct hw_module_t *)module;
	
	dev->get_led_state = get_led_state;
	dev->set_led_state = set_led_state;
	...
	...
	...
	
	*device = (struct hw_device_t *)dev;
	return 0;
}

gpio_keys {
	status = "okay";
	compatible = "gpio-keys";
	#address-cells = <1>;
	#size-cells = <0>;
	input-name = "test-keys";
	pinctrl-names = "tlmm_gpio_key_active","tlmm_gpio_key_suspend";
	pinctrl-0 = <&gpio_key_active>;
	pinctrl-1 = <&gpio_key_suspend>;
	
	key1@1 {
		label = "key1";
		gpios = <&msm_gpio 96 1>;
		linux,code = <116>;
		linux,input-type = <1>;
	};
	
	key2@2 {
		label = "key2";
		gpios = <&msm_gpio 98 0>;
		linux,code = <102>;
		linux,input-type = <1>;
	};
};

