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
 
 
#ifndef ANDROID_LEDCTRL_INTERFACE_H
#define ANDROID_LEDCTRL_INTERFACE_H

#include <hardware/hardware.h>

__BEGIN_DECLS


/* 定义模块ID */
#define LEDCTRL_HARDWARE_MODULE_ID	"ledctrl"

/* 硬件模块结构体 */
struct ledctrl_module_t {
	struct hw_module_t common;
};

/* 硬件接口结构体 */
struct ledctrl_device_t {
	struct hw_device_t common;
	
	int fd;
	int (*set_state)(struct ledctrl_device_t *dev, const char *state);
	int (*get_state)(struct ledctrl_device_t *dev, char **state);
};


__END_DECLS

#endif