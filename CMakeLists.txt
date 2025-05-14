cmake_minimum_required(VERSION 3.10)
project(SoftRenderAdv)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_CXX_STANDARD 17)

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
    "src/base/MathInc.h"
    "src/base/Logger.h"
    "src/base/Logger.cpp"
    "src/base/FileUtils.h"
    "src/base/MemoryUtils.h"
    "src/base/Buffer.h"
    "src/base/UUID.h"
    "src/base/ImageUtils.h"
    "src/base/ImageUtils.cpp"
)
source_group("base" FILES ${__base})

set(__math
    "src/math/compiler.h"
    "src/math/fast.h"
    "src/math/half.h"
    "src/math/mat2.h"
    "src/math/mat3.h"
    "src/math/mat4.h"
    "src/math/mathfwd.h"
    "src/math/norm.h"
    "src/math/quat.h"
    "src/math/scalar.h"
    "src/math/TMatHelpers.h"
    "src/math/TQuatHelpers.h"
    "src/math/TVecHelpers.h"
    "src/math/vec2.h"
    "src/math/vec3.h"
    "src/math/vec4.h"
)
source_group("math" FILES ${__math})

set(__render
    "src/render/Renderer.h"
    "src/render/Texture.h"
    "src/render/Framebuffer.h"
    "src/render/PipelineStates.h"
    "src/render/RenderStates.h"
    "src/render/ShaderProgram.h"
    "src/render/Uniform.h"
    "src/render/Vertex.h"
)
source_group("render" FILES ${__render})

set(__render__opengl
    "src/render/opengl/OpenGLUtils.h"
    "src/render/opengl/GLSLUtils.h"
    "src/render/opengl/GLSLUtils.cpp"
    "src/render/opengl/EnumsOpenGL.h"
    "src/render/opengl/FramebufferOpenGL.h"
    "src/render/opengl/RendererOpenGL.h"
    "src/render/opengl/RendererOpenGL.cpp"
    "src/render/opengl/ShaderProgramOpenGL.h"
    "src/render/opengl/TextureOpenGL.h"
    "src/render/opengl/UniformOpenGL.h"
    "src/render/opengl/VertexOpenGL.h"
)
source_group("render/opengl" FILES ${__render__opengl})

set(Source
    "src/Main.cpp"
    "src/Config.h"
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
