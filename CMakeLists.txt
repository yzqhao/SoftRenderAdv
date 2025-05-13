cmake_minimum_required(VERSION 3.10)
project(SoftRenderAdv)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_CXX_STANDARD 11)

set(TARGET_NAME SoftRenderAdv)
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

# enable SIMD
add_definitions("-DSOFTGL_SIMD_OPT")

# debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions("-DDEBUG")
endif ()


include_directories(
        "${THIRD_PARTY_DIR}/glfw/include"
        "${THIRD_PARTY_DIR}/glad/include"
        "${THIRD_PARTY_DIR}/imgui"
        "${THIRD_PARTY_DIR}/json11"
        "${THIRD_PARTY_DIR}/md5"
        "${THIRD_PARTY_DIR}/stb/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

set(__base
    "src/base/Logger.h"
    "src/base/Logger.cpp"
)
source_group("base" FILES ${__base})

set(__render
    "src/render/Renderer.h"
)
source_group("render" FILES ${__render})

set(__render__opengl
    "src/render/opengl/OpenGLUtils.h"
    "src/render/opengl/GLSLUtils.h"
    "src/render/opengl/GLSLUtils.cpp"
)
source_group("render/opengl" FILES ${__render__opengl})

set(Source
    "src/Main.cpp"
    "src/Viewer.h"
    "src/Viewer.cpp"
    "src/Viewer.h"
    "src/ViewerOpenGL.h"
    "src/ViewerVulkan.h"
    "src/ViewerManager.h"
)
source_group("Source" FILES ${Source})

set(ALL_FILES
    ${__base}
    ${__render}
    ${__render__opengl}
    ${Source}
)

add_executable(${TARGET_NAME}
        "${ALL_FILES}"
        "${IMGUI_SRC}"
        "${THIRD_PARTY_DIR}/glad/src/glad.c"
        "${THIRD_PARTY_DIR}/json11/json11.cpp"
        "${THIRD_PARTY_DIR}/md5/md5.c"
        )

if (WIN32)
    if (MSVC)
        set(LINK_LIBS ${LINK_LIBS}
                "${THIRD_PARTY_DIR}/glfw/lib-vc2022/glfw3.lib"
                "${THIRD_PARTY_DIR}/glfw/lib-vc2022/glfw3dll.lib"
                )
    else ()
        set(LINK_LIBS ${LINK_LIBS}
                "${THIRD_PARTY_DIR}/glfw/lib-mingw-w64/libglfw3.a"
                "${THIRD_PARTY_DIR}/glfw/lib-mingw-w64/libglfw3dll.a"
                )
    endif ()
endif ()

if (MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE $<$<BOOL:${MSVC}>:/arch:AVX2 /std:c++11>)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -mfma -O3")
endif ()

target_link_libraries(${TARGET_NAME} ${LINK_LIBS})

# output dir
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
