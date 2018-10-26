cmake_minimum_required(VERSION 3.4.1)


# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")


add_library( burnout_engine
             SHARED
             src/main/cpp/Main.cpp
             src/main/cpp/BurnoutApp.cpp
             src/main/cpp/IProcess.cpp
             src/main/cpp/ProcessHandler.cpp
             src/main/cpp/Delay.cpp
             src/main/cpp/GLESRenderer
             )

add_library(native_app_glue STATIC
     ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

target_include_directories(burnout_engine
PRIVATE
src/main/cpp
${ANDROID_NDK}/sources/android/native_app_glue)

# add lib dependencies
target_link_libraries(burnout_engine
     android
     native_app_glue
     EGL
     GLESv2
     log)