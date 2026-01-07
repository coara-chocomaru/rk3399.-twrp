LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := wipe_helper
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := wipe.c

LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_STATIC_LIBRARIES := \
    libc \
    liblog

LOCAL_CFLAGS := -Wall -Werror -Wno-unused-parameter
include $(BUILD_EXECUTABLE)
