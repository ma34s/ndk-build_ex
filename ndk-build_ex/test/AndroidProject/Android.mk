LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  test.c \

LOCAL_MODULE := test
LOCAL_MODULE_TAGS := optional
LOCAL_LDFLAGS += -static

include $(BUILD_EXECUTABLE)

include $(call all-makefiles-under,$(LOCAL_PATH))
