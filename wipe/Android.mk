LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := wipe_helper
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_SRC_FILES := wipe_helper.cpp

LOCAL_C_INCLUDES += \
    system/core/include \
    system/core/base/include \
    system/core/libutils/include \
    external/zlib

LOCAL_STATIC_LIBRARIES := \
    libbase \
    liblog \
    libcutils \
    libutils \
    libz

LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_SHARED_LIBRARIES :=
LOCAL_CFLAGS := -Wall -Werror -Wno-unused-parameter -std=c++17
LOCAL_MODULE_PATH := $(TARGET_RECOVERY_ROOT_OUT)/sbin

include $(BUILD_EXECUTABLE)
