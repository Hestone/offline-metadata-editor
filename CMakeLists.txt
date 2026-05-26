cmake_minimum_required(VERSION 3.16)

project(offlinemusiceditor VERSION 0.1 LANGUAGES CXX OBJC OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(offlinemusiceditor
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# TagLib
find_library(TAGLIB tag PATHS ${CMAKE_SOURCE_DIR}/taglib-install/lib NO_DEFAULT_PATH)
include_directories(${CMAKE_SOURCE_DIR}/taglib-install/include)


add_subdirectory(nfd)

target_link_libraries(offlinemusiceditor PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets 
    nfd
    ${TAGLIB}
    z
    "-framework AppKit"
    "-framework UniformTypeIdentifiers"
)

set_target_properties(offlinemusiceditor PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS offlinemusiceditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
