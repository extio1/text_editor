set(target gui) 
cmake_minimum_required(VERSION 3.14)

set(GUI_SOURCES
        main.cpp
        window.cpp
        menu.cpp
        window.h
        menu.h
        window.ui
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${target}
        MANUAL_FINALIZATION
        ${GUI_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${target} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${target} SHARED
            ${GUI_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${target}
            ${GUI_SOURCES}
        )
    endif()
endif()

target_link_libraries(${target} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${target} PRIVATE executor compositor document point)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${target})
endif()

target_include_directories(${target} PUBLIC ${include_dir})
