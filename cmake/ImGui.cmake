# Конфигурайия для подключения ImGui
# На выходе будет таргет project_dependency и флаг IMGUI_ENABLED для подклчюения зависимости

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(IMGUI_ENABLED 1 CACHE INTERNAL "")

    add_library(imgui_target STATIC
            ${CMAKE_SOURCE_DIR}/lib/imgui/imconfig.h
            ${CMAKE_SOURCE_DIR}/lib/imgui/imgui.h
            ${CMAKE_SOURCE_DIR}/lib/imgui/imgui.cpp
            ${CMAKE_SOURCE_DIR}/lib/imgui/imgui_draw.cpp
            ${CMAKE_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp
            ${CMAKE_SOURCE_DIR}/lib/imgui/imgui_internal.h
            ${CMAKE_SOURCE_DIR}/lib/imgui/imstb_rectpack.h
            ${CMAKE_SOURCE_DIR}/lib/imgui/imstb_textedit.h
            ${CMAKE_SOURCE_DIR}/lib/imgui/imstb_truetype.h
            )

    target_include_directories(imgui_target INTERFACE
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/imgui/>
            )
else()
    return()
endif()