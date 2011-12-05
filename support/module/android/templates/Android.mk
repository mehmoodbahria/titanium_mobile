# Android.mk for @MODULE_ID@
LOCAL_PATH := $(call my-dir)
THIS_DIR := $(LOCAL_PATH)

include $(CLEAR_VARS)

THIS_DIR = $(LOCAL_PATH)
LOCAL_MODULE := @MODULE_ID@
LOCAL_CFLAGS := -g -I$(TI_MOBILE_SDK)/android/native/include -I$(SYSROOT)/usr/include
LOCAL_LDLIBS :=  -L$(SYSROOT)/usr/lib -ldl -llog -L$(TARGET_OUT) -L$(TI_MOBILE_SDK)/android/native/libs/$(TARGET_ARCH_ABI) -lkroll-v8

ABS_SRC_FILES := $(wildcard $(LOCAL_PATH)/*.cpp)
LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%,%,$(ABS_SRC_FILES))

GEN_DIR := $(realpath .)
GEN_JNI_DIR := $(GEN_DIR)/jni

$(LOCAL_PATH)/@CLASS_NAME@Bootstrap.cpp: $(GEN_DIR)/KrollGeneratedBindings.cpp $(GEN_DIR)/BootstrapJS.cpp

$(GEN_DIR)/KrollGeneratedBindings.cpp:
	gperf -L C++ -E -t $(GEN_DIR)/KrollGeneratedBindings.gperf > $(GEN_DIR)/KrollGeneratedBindings.cpp

$(GEN_DIR)/BootstrapJS.cpp:
	$(TI_MOBILE_SDK)/module/android/js2c.py $(GEN_DIR)/BootstrapJS.cpp $(GEN_DIR)/bootstrap.js

include $(BUILD_SHARED_LIBRARY)