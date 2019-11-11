# Android.mk for ledctrl hal module

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_SRC_FILES := ledctrl.c
LOCAL_MODULE := ledctrl.default
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)
