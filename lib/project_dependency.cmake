#------------------------------------------------------------------------------
#                       General Projects Settings
#------------------------------------------------------------------------------
#include(${CMAKE_SOURCE_DIR}/cmake/StandardProjectSettings.cmake)
# General dependency target
add_library(project_dependency ${CMAKE_SOURCE_DIR}/lib/empty.cpp)

#------------------------------------------------------------------------------
#                         CMake modules and options
#------------------------------------------------------------------------------

#include(ExternalProject)

# enable cache system
include(${CMAKE_SOURCE_DIR}/cmake/Cache.cmake)

# sanitizer options if supported by compiler
#include(${CMAKE_SOURCE_DIR}/cmake/Sanitizers.cmake)
#enable_sanitizers(project_options)

# enable doxygen
#include(${CMAKE_SOURCE_DIR}/cmake/Doxygen.cmake)
#enable_doxygen()

# allow for static analysis options
#include(${CMAKE_SOURCE_DIR}/cmake/StaticAnalyzers.cmake)

#TODO change target to project files
# Add as many warning as possible:
#add_library(project_warning INTERFACE)
#target_compile_features(project_warning INTERFACE cxx_std_17)
#target_compile_options(project_warning INTERFACE -Wall)
#include(${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)
#set_project_warnings(project_warning)
#target_link_libraries(project_warning INTERFACE ${PROJECT_NAME})

# Very basic PCH example
#option(ENABLE_PCH "Enable Precompiled Headers" OFF)
#if (ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which
    # is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
#    target_precompile_headers(${PROJECT_NAME} PRIVATE <vector> <array> <string> <map> <utility> <memory> <algorithm> <bitset>)
#endif ()

#------------------------------------------------------------------------------
#                        ImGui, included for debugging only
#------------------------------------------------------------------------------
if (${DEBUG})
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/lib/imgui/CMakeLists.txt)
        message(FATAL_ERROR "ImGui not found, download lib/imgui or use 'git submodules update'.")
    endif ()
    SET(imgui_lib_path  "${CMAKE_SOURCE_DIR}/lib/imgui" CACHE INTERNAL "imgui_lib_path")
    include(${CMAKE_SOURCE_DIR}/lib/imgui/CMakeLists.txt)
    add_definitions(-DIMGUI_ENABLED) # <- new cast definition
    target_link_libraries(project_dependency INTERFACE cc_imgui)
endif ()

#------------------------------------------------------------------------------
#                               deprecated: Rapidjson
#------------------------------------------------------------------------------
#if (NOT EXISTS ${CMAKE_SOURCE_DIR}/lib/rapidjson/include)
#    message(FATAL_ERROR "Rapidjson not found, download lib/rapidjson or use 'git submodules update'.")
#endif()
#add_library(rapidjson_target INTERFACE)
#target_include_directories(rapidjson_target INTERFACE
#        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/rapidjson/include>
#        )
#target_link_libraries(project_dependency INTERFACE rapidjson_target)

#------------------------------------------------------------------------------
#                               DragonBones
#------------------------------------------------------------------------------
if (NOT EXISTS ${CMAKE_SOURCE_DIR}/lib/dragonBones/DragonBonesHeaders.h)
    message(FATAL_ERROR "DragonBones not found, check folder lib/dragonBones.")
endif()
include(${CMAKE_SOURCE_DIR}/cmake/DragonBones.cmake)

#target_include_directories(dragonbones_target INTERFACE
#        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/dragonBones/>
#        )
target_link_libraries(dragonbones_target PRIVATE cocos2d)
target_link_libraries(project_dependency INTERFACE dragonbones_target)

#------------------------------------------------------------------------------
#                               Build Interface for all dependency
#------------------------------------------------------------------------------
target_include_directories(project_dependency INTERFACE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/>
        )