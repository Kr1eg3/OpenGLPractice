# CMakeList.txt : CMake project for KlubnichniyEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# use custom file to find libraries
if(WIN32)
	list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
endif()

# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 3.3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
#find_package(ASSIMP REQUIRED)
#message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

if(APPLE)
  find_package(Freetype REQUIRED)
  message(STATUS "Found Freetype in ${FREETYPE_INCLUDE_DIRS}")
endif(APPLE)

#variable is set by FindGLFW3.cmake, reuse for Linux
if(UNIX)
	set(GLFW3_LIBRARY glfw)
endif()


if(WIN32)
  set(LIBS ${GLFW3_LIBRARY} opengl32) #assimp freetype irrKlang)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  find_package(OpenGL REQUIRED)
  add_definitions(${OPENGL_DEFINITIONS})
  find_package(X11 REQUIRED)
  # note that the order is important for setting the libs
  # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
  set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype ${ASSIMP_LIBRARY})
  set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
elseif(APPLE)
  INCLUDE_DIRECTORIES(/System/Library/Frameworks)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  FIND_LIBRARY(IOKit_LIBRARY IOKit)
  FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
  MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
  SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
  SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY} ${FREETYPE_LIBRARIES})
  set(LIBS ${LIBS} ${APPLE_LIBS})
else()
  set(LIBS )
endif(WIN32)

add_library(STB_IMAGE "${CMAKE_SOURCE_DIR}/third_party/src/stb/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

add_library(GLAD "third_party/src/glad/glad.c")
set(LIBS ${LIBS} GLAD)

add_library(IMGUI "third_party/src/imgui/imgui.cpp"
				  "third_party/src/imgui/imgui_demo.cpp"
				  "third_party/src/imgui/imgui_draw.cpp"
				  "third_party/src/imgui/imgui_impl_glfw.cpp"
				  "third_party/src/imgui/imgui_impl_opengl3.cpp"
				  "third_party/src/imgui/imgui_tables.cpp"
				  "third_party/src/imgui/imgui_widgets.cpp")
set(LIBS ${LIBS} IMGUI)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("KlubnichniyEngine")

# Add source to this project's executable.
add_executable (KlubnichniyEngine "main.cpp"  "Model/include/Model.h"
											  "Model/src/Model.cpp"
											  "Window/include/Window.h"
											  "Window/src/Window.cpp"
											  "Logger/include/Logger.h"
											  "Logger/src/Logger.cpp"
											  "Renderers/include/GLRender.h"
											  "Renderers/src/GLRender.cpp"
											  "Renderers/include/GLRenderData.h"
											  "Buffers/include/Framebuffer.h"
											  "Buffers/src/Framebuffer.cpp"
											  "Buffers/include/VertexBuffer.h"
											  "Buffers/src/VertexBuffer.cpp"
											  "Buffers/include/Texture.h"
											  "Buffers/src/Texture.cpp"
											  "Buffers/include/Shader.h"
											  "Buffers/src/Shader.cpp"
											  "Camera/include/Camera.h"
											  "Camera/src/Camera.cpp"
											  "UserInterface/include/UserInterface.h"
											  "UserInterface/src/UserInterface.cpp"
											  "Timer/include/Timer.h"
											  "Timer/src/Timer.cpp")
target_link_libraries(KlubnichniyEngine ${LIBS}) #${GLFW3_LIBRARY})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET KlubnichniyEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

include_directories(${GLFW3_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Timer/include/)
include_directories(${CMAKE_SOURCE_DIR}/UserInterface/include/)
include_directories(${CMAKE_SOURCE_DIR}/Camera/include/)
include_directories(${CMAKE_SOURCE_DIR}/Model/include/)
include_directories(${CMAKE_SOURCE_DIR}/Buffers/include/)
include_directories(${CMAKE_SOURCE_DIR}/Window/include/)
include_directories(${CMAKE_SOURCE_DIR}/Logger/include/)
include_directories(${CMAKE_SOURCE_DIR}/Renderers/include/)
include_directories(${CMAKE_SOURCE_DIR}/third_party/includes/)
include_directories(${CMAKE_SOURCE_DIR}/third_party/includes/imgui/)
