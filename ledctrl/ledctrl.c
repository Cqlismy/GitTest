/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "ledctrl_hw_default"

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cutils/log.h>

#include <hardware/hardware.h>
#include <hardware/ledctrl.h>

#define DEVICE_NAME "/sys/class/leds/led-red/brightness"
#define MODULE_NAME "ledctrl"
#define MODULE_AUTHOR "HLY"


/* 设备访问接口 */
static int ledctrl_set_state(struct ledctrl_device_t *dev, const char *state)
{
	int ret = -EINVAL;
	
	if (0 == strcmp(state, "enable")) {
		ret = write(dev->fd, "1", 1);
		if (ret != 1) {
			ALOGE("ledctrl: failed to enable led device");
			goto exit;
		}
		ALOGI("ledctrl: successed to enable led device");
		ret = 0;
	} else if (0 == strcmp(state, "disable")) {
		ret = write(dev->fd, "0", 1);
		if (ret != 1) {
			ALOGE("ledctrl: failed to close led device");
			goto exit;
		}
		ALOGI("ledctrl: successed to disable led device");
		ret = 0;
	} else
		ALOGE("ledctrl: not define the led device state");
	
exit:
	return ret;	
}

static int ledctrl_get_state(struct ledctrl_device_t *dev, char **state)
{
	int ret,value;
	char *buf = malloc(sizeof(char) * 5);
	
	memset(buf, 0, sizeof(char) * 5);
	ret = read(dev->fd, buf, sizeof(int));
	if (ret < 0) {
		ALOGE("ledctrl: failed to read led device");
		goto exit;
	}
	
	value = atoi(buf);
	if (value == 0)
		*state = "disable";
	else
		*state = "enable";
	ALOGD("value = %d, led_state = %s", value, *state);

exit:
	free(buf);
	return ret;
}

/* 设备的打开和关闭接口 */
static int ledctrl_device_close(struct hw_device_t *device)
{
	struct ledctrl_device_t *dev = (struct ledctrl_device_t *)device;
	
	if (dev) {
		close(dev->fd);
		free(dev);
	}
	
	return 0;
}

static int ledctrl_device_open(const struct hw_module_t *module,
			const char *id, struct hw_device_t **device)
{
	int fd;
	struct ledctrl_device_t *dev;
	
	dev = malloc(sizeof(struct ledctrl_device_t));
	if (!dev) {
		ALOGE("ledctrl: failed to malloc memory");
		return -ENOMEM;
	}
	memset(dev, 0, sizeof(struct ledctrl_device_t));
	
	dev->common.tag = HARDWARE_DEVICE_TAG;
	dev->common.version = 0;
	dev->common.module = (struct hw_module_t *)module;
	dev->common.close = ledctrl_device_close;
	
	fd = open(DEVICE_NAME, O_RDWR);
	if (fd == -1) {
		ALOGE("ledctrl: failed to open device file");
		free(dev);
		return fd;
	}
	dev->fd = fd;
	dev->set_state = ledctrl_set_state;
	dev->get_state = ledctrl_get_state;
	
	*device = &dev->common;
	
	return 0;
}

/* 模块方法表 */
static struct hw_module_methods_t ledctrl_module_methods = {
	.open = ledctrl_device_open,
};

/* 模块实例变量 */
struct ledctrl_module_t HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.version_major = 1,
		.version_minor = 0,
		.id = LEDCTRL_HARDWARE_MODULE_ID,
		.name = MODULE_NAME,
		.author = MODULE_AUTHOR,
		.methods = &ledctrl_module_methods,
	},
};
