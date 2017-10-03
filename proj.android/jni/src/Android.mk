LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	../../../src/Bomb.cpp \
	../../../src/BombFragment.cpp \
	../../../src/BoxCollider.cpp \
	../../../src/Button.cpp \
	../../../src/CircleCollider.cpp \
	../../../src/Collider.cpp \
	../../../src/Color.cpp \
	../../../src/Dispatcher.cpp \
	../../../src/Door.cpp \
	../../../src/Enemy.cpp \
	../../../src/EnemyChasing.cpp \
	../../../src/EnemyWandering.cpp \
	../../../src/Game.cpp \
	../../../src/Joystick.cpp \
	../../../src/Key.cpp \
	../../../src/LevelMap.cpp \
	../../../src/LevelMapCollider.cpp \
	../../../src/PathFinder.cpp \
	../../../src/Player.cpp \
	../../../src/Rect.cpp \
	../../../src/ScalarMath.cpp \
	../../../src/Utils.cpp \
	../../../src/Vector2.cpp \
	../../../src/main.cpp

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
LOCAL_LDLIBS := -latomic

include $(BUILD_SHARED_LIBRARY)

