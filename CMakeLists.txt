cmake_minimum_required(VERSION 3.6)

set(APP_NAME swipe-rpg)

project(${APP_NAME})

if (ANDROID OR IOS)
    add_definitions(-DRELEASE=1)
else ()
    if (${DEBUG})
        add_definitions(-DDEBUG=1)
    else ()
        add_definitions(-DRELEASE=1)
    endif ()
endif ()

if (XCODE)
    SET(CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 11.0)
endif ()

if (NOT DEFINED BUILD_ENGINE_DONE) # to test cocos-db into root project
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif ()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        )
if (APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif ()

# add cross-platforms source files and header files
file(GLOB_RECURSE GAME_HEADER src/*.h include/*.hpp)
file(GLOB_RECURSE GAME_SOURCE src/*.cpp)

if (ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME SwipeRpg)
    list(APPEND GAME_SOURCE
            proj.android/app/jni/hellocpp/main.cpp
            )
elseif (LINUX)
    list(APPEND GAME_SOURCE
            proj.linux/main.cpp
            )
elseif (WINDOWS)
    list(APPEND GAME_HEADER
            proj.win32/main.h
            proj.win32/resource.h
            )
    list(APPEND GAME_SOURCE
            proj.win32/main.cpp
            proj.win32/game.rc
            ${common_res_files}
            )
elseif (APPLE)
    if (IOS)
        list(APPEND GAME_HEADER
                proj.ios_mac/ios/AppController.h
                proj.ios_mac/ios/RootViewController.h
                )
        set(APP_UI_RES
                proj.ios_mac/ios/LaunchScreen.storyboard
                proj.ios_mac/ios/LaunchScreenBackground.png
                proj.ios_mac/ios/Images.xcassets
                )
        list(APPEND GAME_SOURCE
                proj.ios_mac/ios/main.m
                proj.ios_mac/ios/AppController.mm
                proj.ios_mac/ios/RootViewController.mm
                proj.ios_mac/ios/Prefix.pch
                ${APP_UI_RES}
                )
    elseif (MACOSX)
        set(APP_UI_RES
                proj.ios_mac/mac/Icon.icns
                proj.ios_mac/mac/Info.plist
                )
        list(APPEND GAME_SOURCE
                proj.ios_mac/mac/main.cpp
                proj.ios_mac/mac/Prefix.pch
                ${APP_UI_RES}
                )
    endif ()
    list(APPEND GAME_SOURCE ${common_res_files})
endif ()

# mark app complie info and libs info
set(all_code_files
        ${GAME_HEADER}
        ${GAME_SOURCE}
        )
if (NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else ()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif ()
#include(${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)
include(${CMAKE_SOURCE_DIR}/lib/project_dependency.cmake)
target_link_libraries(${APP_NAME} cocos2d project_dependency)
target_include_directories(${APP_NAME}
        PRIVATE src
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
        )
#set_project_warnings(cocos2d warning)
target_compile_features(${APP_NAME} PRIVATE cxx_std_17)
target_compile_options(${APP_NAME} PRIVATE -Wall)
#set_project_warnings(${APP_NAME} error)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if (APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")

    if (MACOSX)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist")
    elseif (IOS)
        include(${CMAKE_SOURCE_DIR}/cmake/IOSHelper.cmake)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
        #Deployment
        set_attr_to_all_target(INSTALL_PATH "/" "all")
        set_attr_to_all_target(SKIP_INSTALL "YES" "not_project")
        set_attr_to_all_target(SKIP_INSTALL "NO" "project")
    endif ()
elseif (WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif ()

if (LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif ()

target_include_directories(${APP_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )

#------------------------------------------------------------------------------
#                               Tests section
#------------------------------------------------------------------------------
#if (DEBUG)
#    enable_testing()
#    add_subdirectory(tests)
#endif ()
