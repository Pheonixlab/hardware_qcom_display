LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/../../../common.mk
include $(CLEAR_VARS)

ifeq ($(use_hwc2),true)

LOCAL_MODULE                  := hwcomposer.$(TARGET_BOARD_PLATFORM)
LOCAL_VENDOR_MODULE           := true
LOCAL_MODULE_TAGS             := optional
LOCAL_C_INCLUDES              := $(common_includes)
LOCAL_C_INCLUDES              += $(kernel_includes)
LOCAL_ADDITIONAL_DEPENDENCIES := $(common_deps)
LOCAL_HEADER_LIBRARIES        := display_headers

LOCAL_CFLAGS                  := -Wno-missing-field-initializers -Wno-unused-parameter \
                                 -fcolor-diagnostics\
                                 -DLOG_TAG=\"SDM\" $(common_flags)
LOCAL_CLANG                   := true

LOCAL_SHARED_LIBRARIES        := libsdmcore libqservice libbinder libhardware libhardware_legacy \
                                 libutils libcutils libsync libqdutils libqdMetaData \
                                 libdisplaydebug libsdmutils libc++ liblog libgrallocutils libui \
                                 libgpu_tonemapper libhidlbase libhidltransport libdisplayconfig.qti \
                                 android.hardware.graphics.mapper@2.0 \
                                 android.hardware.graphics.mapper@2.1 \
                                 android.hardware.graphics.mapper@3.0 \
                                 android.hardware.graphics.allocator@2.0 \
                                 android.hardware.graphics.allocator@3.0 \
                                 android.hardware.graphics.composer@2.2 \
                                 android.hardware.graphics.composer@2.3 \
                                 android.hardware.graphics.composer@2.4 \
                                 vendor.display.config@1.0 \
                                 vendor.display.config@1.1 \
                                 vendor.display.config@1.2 \
                                 vendor.display.config@1.3 \
                                 vendor.display.config@1.4 \
                                 vendor.display.config@1.5 \
                                 vendor.display.config@1.6 \
                                 vendor.display.config@1.7 \
                                 vendor.display.config@1.8 \
                                 vendor.display.config@1.9 \
                                 vendor.display.config@1.10 \
                                 vendor.display.config@1.11 \
                                 vendor.display.config@2.0

ifeq ($(TARGET_BOARD_AUTO), true)
LOCAL_CFLAGS                  += -DCONFIG_BASEID_FROM_PROP
endif

ifeq ($(TARGET_USES_FOD_ZPOS), true)
LOCAL_CFLAGS                  += -DFOD_ZPOS
endif

LOCAL_SRC_FILES               := hwc_session.cpp \
                                 hwc_session_services.cpp \
                                 hwc_display.cpp \
                                 hwc_display_builtin.cpp \
                                 hwc_display_pluggable.cpp \
                                 hwc_display_dummy.cpp \
                                 hwc_display_pluggable_test.cpp \
                                 hwc_display_virtual.cpp \
                                 hwc_debugger.cpp \
                                 hwc_buffer_sync_handler.cpp \
                                 hwc_color_manager.cpp \
                                 hwc_layers.cpp \
                                 hwc_callbacks.cpp \
                                 cpuhint.cpp \
                                 hwc_tonemapper.cpp \
                                 display_null.cpp \
                                 hwc_socket_handler.cpp \
                                 hwc_buffer_allocator.cpp
LOCAL_VINTF_FRAGMENTS         := android.hardware.graphics.composer-qti-display.xml

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE                  := vendor.qti.hardware.display.composer-service
LOCAL_MODULE_NAME	      := dolby_vision
LOCAL_MODULE_TYPE 	      := cc_defaults
LOCAL_CONFIG_NAMESPACE        := dolby_vision
LOCAL_MODULE_VARIABLES        := enabled
LOCAL_MODULE_PROPERTIES       := cflags
LOCAL_VENDOR_MODULE           := true
LOCAL_MODULE_RELATIVE_PATH    := hw
LOCAL_MODULE_TAGS             := optional
LOCAL_C_INCLUDES              := $(common_includes)
LOCAL_HEADER_LIBRARIES        := display_headers

LOCAL_CFLAGS                  := -Wno-missing-field-initializers -Wno-unused-parameter \
                                 -std=c++11 -fcolor-diagnostics \
                                 -DTARGET_SUPPORTS_DOLBY_VISION \
                                 -DLOG_TAG=\"QtiComposer\" $(common_flags)
LOCAL_CLANG                   := true

LOCAL_SHARED_LIBRARIES        := libbinder libhardware libutils libcutils libsync \
                                 libc++ liblog libhidlbase libhidltransport \
                                 hwcomposer.$(TARGET_BOARD_PLATFORM) \
                                 vendor.display.config@1.0 liblog libfmq \
                                 vendor.qti.hardware.display.composer@1.0 \
                                 vendor.qti.hardware.display.composer@2.0 \
                                 android.hardware.graphics.composer@2.1 \
                                 android.hardware.graphics.composer@2.2 \
                                 android.hardware.graphics.composer@2.3 \
                                 android.hardware.graphics.mapper@2.0 \
                                 android.hardware.graphics.mapper@2.1 \
                                 android.hardware.graphics.mapper@3.0 \
                                 android.hardware.graphics.allocator@2.0 \
                                 android.hardware.graphics.allocator@3.0

$(info IDisplayConfig version: $(display_config_version))
ifeq ($(display_config_version), DISPLAY_CONFIG_1_1)
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.1
endif
ifeq ($(display_config_version), DISPLAY_CONFIG_1_2)
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.2 vendor.display.config@1.1
endif
ifeq ($(display_config_version), DISPLAY_CONFIG_1_3)
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.1
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.2
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.3
endif
ifeq ($(display_config_version), DISPLAY_CONFIG_1_4)
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.1
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.2
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.3
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.4
endif
ifeq ($(display_config_version), DISPLAY_CONFIG_1_5)
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.1
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.2
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.3
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.4
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.5
endif
ifeq ($(display_config_version), DISPLAY_CONFIG_1_6)
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.1
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.2
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.3
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.4
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.5
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.6
endif
ifeq ($(display_config_version), DISPLAY_CONFIG_1_7)
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.1
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.2
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.3
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.4
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.5
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.6
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.7
endif
ifeq ($(display_config_version), DISPLAY_CONFIG_1_8)
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.1
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.2
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.3
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.4
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.5
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.6
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.7
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.8
endif
ifeq ($(display_config_version), DISPLAY_CONFIG_1_9)
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.1
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.2
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.3
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.4
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.5
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.6
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.7
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.8
LOCAL_SHARED_LIBRARIES        += vendor.display.config@1.9
endif

LOCAL_SRC_FILES               := QtiComposer.cpp QtiComposerClient.cpp service.cpp \
                                 QtiComposerHandleImporter.cpp
LOCAL_INIT_RC                 := vendor.qti.hardware.display.composer-service.rc
include $(BUILD_EXECUTABLE)

endif
