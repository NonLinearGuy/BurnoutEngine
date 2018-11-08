cmake_minimum_required(VERSION 3.4.1)


# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

# Import the CMakeLists.txt for the glm library
add_subdirectory(src/main/cpp/glm)

add_library( burnout_engine
             SHARED
             src/main/cpp/Main.cpp
             src/main/cpp/BurnoutApp.cpp
             src/main/cpp/IProcess.cpp
             src/main/cpp/ProcessHandler.cpp
             src/main/cpp/Delay.cpp
             src/main/cpp/GLESRenderer
             src/main/cpp/Triangle
             src/main/cpp/ShaderProgram
             src/main/cpp/FileReader
             src/main/cpp/TexturedPlane
             src/main/cpp/android_fopen.c
             src/main/cpp/SpriteRenderer.cpp
             src/main/cpp/Texture2D.cpp
               src/main/cpp/Camera.cpp
               src/main/cpp/Cubemap.cpp
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
     glm
     native_app_glue
     EGL
     GLESv3
     log)