LOCAL_PATH := $(call my-dir)

CORE_DIR = $(LOCAL_PATH)/..

include $(CORE_DIR)/Makefile.common

COREFLAGS := -D__LIBRETRO__ -DANDROID $(FLAGS)

GIT_VERSION := " $(shell git rev-parse --short HEAD || echo unknown)"
ifneq ($(GIT_VERSION)," unknown")
  COREFLAGS += -DGIT_VERSION=\"$(GIT_VERSION)\"
endif

include $(CLEAR_VARS)
LOCAL_MODULE       := retro
LOCAL_SRC_FILES    := $(SOURCES_CXX) $(SOURCES_C) $(SOURCES_S)
LOCAL_CXXFLAGS     := $(COREFLAGS) -std=c++14
LOCAL_CFLAGS       := $(COREFLAGS)
LOCAL_LDFLAGS      := -Wl,-version-script=$(CORE_DIR)/link.T
LOCAL_CPP_FEATURES := exceptions rtti
include $(BUILD_SHARED_LIBRARY)
