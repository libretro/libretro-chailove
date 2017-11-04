HAVE_GRIFFIN    := 0

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

GIT_VERSION := " $(shell git rev-parse --short HEAD || echo unknown)"
ifneq ($(GIT_VERSION)," unknown")
	LOCAL_CXXFLAGS += -DGIT_VERSION=\"$(GIT_VERSION)\"
endif

CORE_DIR = ../..
JIT=
DESMUME_JIT=0

ifeq ($(TARGET_ARCH),arm)
LOCAL_CXXFLAGS := -DANDROID_ARM
LOCAL_ARM_MODE := arm

DESMUME_JIT_ARM = 1
JIT = -D__RETRO_ARM__ -DHAVE_JIT
endif

ifeq ($(TARGET_ARCH),x86)
LOCAL_CXXFLAGS :=  -DANDROID_X86
DESMUME_JIT = 1
JIT = -DHAVE_JIT
endif

ifeq ($(TARGET_ARCH),mips)
LOCAL_CXXFLAGS := -DANDROID_MIPS -D__mips__ -D__MIPSEL__
endif

ifeq ($(TARGET_ARCH),mips64)
LOCAL_CXXFLAGS := -DANDROID_MIPS -D__mips__ -D__MIPSEL__
endif

LOCAL_MODULE    := libretro

include ../../../Makefile.common

LOCAL_SRC_FILES := $(SOURCES_CXX) $(SOURCES_C)
GLOBAL_DEFINES :=  $(JIT) -fexceptions

LOCAL_CXXFLAGS += -O3 -D__LIBRETRO__ -Wno-write-strings -DANDROID -DFRONTEND_SUPPORTS_RGB565 $(GLOBAL_DEFINES) $(INCDIR)
LOCAL_CFLAGS = -O3 -D__LIBRETRO__ -Wno-psabi -Wno-write-strings -DANDROID -DFRONTEND_SUPPORTS_RGB565 $(GLOBAL_DEFINES) $(INCDIR)

LOCAL_C_INCLUDES = -I$(CORE_DIR)/libretro/zlib -iquote $(CORE_DIR) -iquote $(CORE_DIR)/libretro

LOCAL_LDLIBS += -lz

include $(BUILD_SHARED_LIBRARY)
