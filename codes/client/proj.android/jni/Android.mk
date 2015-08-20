LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := main/main.cpp \
                   ../../../common/platform/source/VSystem.cpp \
                   ../../../common/platform/source/adapter/android/VAdapterFactory.cpp \
#				   ../../../common/platform/source/adapter/android/QGAndroidApnManager.cpp \
#				   ../../../common/platform/source/adapter/android/QGAndroidJNIHelper.cpp \
#				   ../../../common/platform/source/adapter/android/QGApnAdapter.cpp \
#				   ../../../common/platform/source/adapter/android/QGConsoleAdapter.cpp \
#				   ../../../common/platform/source/adapter/android/QGDirAdapter.cpp \
#				   ../../../common/platform/source/adapter/android/QGTimerAdapter.cpp \
				   ../../../common/platform/source/adapter/unix/VDirAdapter_Unix.cpp \
				   ../../../common/platform/source/apn/VApnManager.cpp \
				   ../../../common/platform/source/codec/VTextCodec.cpp \
				   ../../../common/platform/source/console/VConsole.cpp \
				   ../../../common/platform/source/device/VDeviceInfo.cpp \
				   ../../../common/platform/source/io/VDataStream.cpp \
				   ../../../common/platform/source/io/VDir.cpp \
				   ../../../common/platform/source/io/VFileDataStream.cpp \
				   ../../../common/platform/source/io/VMemoryDataStream.cpp \
				   ../../../common/platform/source/memory/VObjectList.cpp \
				   ../../../common/platform/source/memory/VObjectPool.cpp \
				   ../../../common/platform/source/memory/VPoolObject.cpp \
				   ../../../common/platform/source/network/VBufQueue.cpp \
				   ../../../common/platform/source/network/VSocket.cpp \
				   ../../../common/platform/source/time/VDateTime.cpp \
				   ../../../common/platform/source/time/VRunLoop.cpp \
				   ../../../common/platform/source/time/VTimer.cpp \
				   ../../../common/platform/source/time/VTimerManager.cpp \
				   ../../../common/framework/source/base_param/VEventParamBuffer.cpp \
				   ../../../common/framework/source/core/VEventHandler.cpp \
				   ../../../common/framework/source/core/VEventManager.cpp \
				   ../../../common/framework/source/core/VInstance.cpp \
                   ../../Classes/app/AppDelegate.cpp \
				   ../../Classes/TGFrameDispatcher.cpp \
				   ../../Classes/scenemgr/TGSceneManager.cpp \
				   ../../Classes/scene/menu/TGSceneMainMenu.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../common/platform/include \
					$(LOCAL_PATH)/../../../common/platform/include/adapter \
					$(LOCAL_PATH)/../../../common/platform/include/adapter/android \
					$(LOCAL_PATH)/../../../common/platform/include/adapter/unix \
					$(LOCAL_PATH)/../../../common/platform/include/apn \
					$(LOCAL_PATH)/../../../common/platform/include/codec \
					$(LOCAL_PATH)/../../../common/platform/include/console \
					$(LOCAL_PATH)/../../../common/platform/include/device \
					$(LOCAL_PATH)/../../../common/platform/include/io \
					$(LOCAL_PATH)/../../../common/platform/include/memory \
					$(LOCAL_PATH)/../../../common/platform/include/network \
					$(LOCAL_PATH)/../../../common/platform/include/time \
					$(LOCAL_PATH)/../../../common/framework/include \
					$(LOCAL_PATH)/../../../common/framework/include/base_param \
					$(LOCAL_PATH)/../../../common/framework/include/core \
					$(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/app \
					$(LOCAL_PATH)/../../Classes/scenemgr \
					$(LOCAL_PATH)/../../Classes/scene \
					$(LOCAL_PATH)/../../Classes/scene/menu

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
