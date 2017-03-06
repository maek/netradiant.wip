cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
# Enable Debug by default, can be changed with -DCMAKE_BUILD_TYPE=Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

project(NetRadiant C CXX)
option(BUILD_RADIANT "Build the gui" ON)

#-----------------------------------------------------------------------
# Version
#-----------------------------------------------------------------------

# CMake 3.0+ would allow this in project()
set(NetRadiant_VERSION_MAJOR 5)
set(NetRadiant_VERSION_MINOR 0)
set(NetRadiant_VERSION "1.${NetRadiant_VERSION_MAJOR}.${NetRadiant_VERSION_MINOR}")

file(WRITE "${PROJECT_BINARY_DIR}/RADIANT_MAJOR" ${NetRadiant_VERSION_MAJOR})
file(WRITE "${PROJECT_BINARY_DIR}/RADIANT_MINOR" ${NetRadiant_VERSION_MINOR})

set(RADIANT_ABOUTMSG "Custom build" CACHE STRING "About message")

find_package(Git REQUIRED)
execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(RADIANT_VERSION_STRING "${NetRadiant_VERSION}n")
if (GIT_VERSION)
    set(RADIANT_VERSION_STRING "${RADIANT_VERSION_STRING}-git-${GIT_VERSION}")
endif ()

message(STATUS "Building ${PROJECT_NAME} ${RADIANT_VERSION_STRING} ${RADIANT_ABOUTMSG}")

#-----------------------------------------------------------------------
# Language standard
#-----------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#-----------------------------------------------------------------------
# Flags
#-----------------------------------------------------------------------

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -fno-exceptions -fno-rtti")
set(CMAKE_POSITION_INDEPENDENT_CODE 1)

#-----------------------------------------------------------------------
# Defs
#-----------------------------------------------------------------------

add_definitions(-DRADIANT_VERSION="${RADIANT_VERSION_STRING}")
add_definitions(-DRADIANT_MAJOR_VERSION="${NetRadiant_VERSION_MAJOR}")
add_definitions(-DRADIANT_MINOR_VERSION="${NetRadiant_VERSION_MINOR}")

add_definitions(-DRADIANT_ABOUTMSG="${NetRadiant_ABOUT}")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEBUG=1)
endif ()

if (APPLE)
    option(XWINDOWS "Build against X11" ON)
    add_definitions(
            -DPOSIX=1
    )
elseif (WIN32)
    add_definitions(
            -DWIN32=1
            -D_WIN32=1
    )
else ()
    set(XWINDOWS ON)
    add_definitions(
            -DPOSIX=1
    )
endif ()

if (XWINDOWS)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    add_definitions(-DXWINDOWS=1)
endif ()

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/libs")

#-----------------------------------------------------------------------
# Libraries
#-----------------------------------------------------------------------

add_subdirectory(libs)
add_subdirectory(include)

#-----------------------------------------------------------------------
# Plugins
#-----------------------------------------------------------------------

if (BUILD_RADIANT)
    add_subdirectory(contrib)
endif ()

#-----------------------------------------------------------------------
# Modules
#-----------------------------------------------------------------------

if (BUILD_RADIANT)
    add_subdirectory(plugins)
endif ()

#-----------------------------------------------------------------------
# Radiant
#-----------------------------------------------------------------------

if (BUILD_RADIANT)
    add_subdirectory(radiant build)
endif ()

if (WIN32)
    set(RADIANT_EXECUTABLE "exe")
else ()
    execute_process(
            COMMAND uname -m
            OUTPUT_VARIABLE RADIANT_EXECUTABLE
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif ()

if (BUILD_RADIANT)
    set_target_properties(radiant PROPERTIES
            COMPILE_DEFINITIONS RADIANT_EXECUTABLE="${RADIANT_EXECUTABLE}"
            )
endif ()

#-----------------------------------------------------------------------
# Tools
#-----------------------------------------------------------------------

add_subdirectory(tools)

if (NOT (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR))
    # Copy data files from sources to the build directory
    message(STATUS "Copying data files")
    file(GLOB DATA_FILES "${PROJECT_SOURCE_DIR}/setup/data/tools/*")
    file(COPY ${DATA_FILES} DESTINATION "${PROJECT_BINARY_DIR}")
    file(GLOB DATA_FILES "${PROJECT_SOURCE_DIR}/docs/*")
    file(COPY ${DATA_FILES} DESTINATION "${PROJECT_BINARY_DIR}/docs")
endif ()

#-----------------------------------------------------------------------
# Game packs
#-----------------------------------------------------------------------

option(DOWNLOAD_GAMEPACKS "Download game packs" ON)
add_custom_target(game_packs
        COMMAND ${CMAKE_COMMAND} -E make_directory games
        COMMAND DOWNLOAD_GAMEPACKS=yes SOURCE_DIR="${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/install-gamepacks.sh" "${PROJECT_BINARY_DIR}"
        COMMENT "Downloading game packs"
        )
if (DOWNLOAD_GAMEPACKS)
    add_custom_target(game_packs_all ALL DEPENDS game_packs)
endif ()

#-----------------------------------------------------------------------
# Install
#-----------------------------------------------------------------------

# Setup install
if(UNIX)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local/vendor/netradiant")
elseif(MINGW)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/Dropbox/Unreal Arena/Tools/netradiant")
endif()

install(
  DIRECTORY
  "${CMAKE_CURRENT_LIST_DIR}/games/UnrealArenaPack/games"
  "${CMAKE_CURRENT_LIST_DIR}/games/UnrealArenaPack/unrealarena.game"
  "${CMAKE_CURRENT_LIST_DIR}/games/UnvanquishedPack/games"
  "${CMAKE_CURRENT_LIST_DIR}/games/UnvanquishedPack/unvanquished.game"
  "${CMAKE_CURRENT_LIST_DIR}/games/XonoticPack/games"
  "${CMAKE_CURRENT_LIST_DIR}/games/XonoticPack/xonotic.game"
  "${CMAKE_CURRENT_LIST_DIR}/setup/data/tools/bitmaps"
  "${CMAKE_CURRENT_LIST_DIR}/setup/data/tools/gl"
  "${CMAKE_CURRENT_LIST_DIR}/setup/data/tools/plugins"
  "${CMAKE_CURRENT_LIST_DIR}/docs"
  DESTINATION .
)

install(
  FILES
  "${CMAKE_CURRENT_LIST_DIR}/setup/data/tools/global.xlink"
  "${CMAKE_CURRENT_LIST_DIR}/setup/data/tools/q3data.qdt"
  "${CMAKE_CURRENT_LIST_DIR}/RADIANT_MAJOR"
  "${CMAKE_CURRENT_LIST_DIR}/RADIANT_MINOR"
  DESTINATION .
)

if(MINGW)
install(
  FILES
  "${CMAKE_FIND_ROOT_PATH}/etc/fonts/fonts.conf"
  DESTINATION etc/fonts
)

install(
  DIRECTORY
  "${CMAKE_FIND_ROOT_PATH}/lib/gtk-2.0"
  DESTINATION lib
  USE_SOURCE_PERMISSIONS
)

install(
  DIRECTORY
  "${CMAKE_FIND_ROOT_PATH}/share/themes"
  DESTINATION share
)

install(
  PROGRAMS
  "${CMAKE_FIND_ROOT_PATH}/bin/libatk-1.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libbz2-1.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libcairo-2.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libexpat-1.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libffi-6.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libfontconfig-1.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libfreetype-6.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgcc_s_seh-1.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgdkglext-win32-1.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgdk_pixbuf-2.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgdk-win32-2.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgio-2.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libglib-2.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgmodule-2.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgobject-2.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgraphite2.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgtkglext-win32-1.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libgtk-win32-2.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libharfbuzz-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libiconv-2.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libintl-8.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libjasper-1.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libjpeg-8.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/liblzma-5.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libpango-1.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libpangocairo-1.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libpangoft2-1.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libpangowin32-1.0-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libpcre-1.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libpixman-1-0.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libpng16-16.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libstdc++-6.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libwebp-6.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libwinpthread-1.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/libxml2-2.dll"
  "${CMAKE_FIND_ROOT_PATH}/bin/zlib1.dll"
  DESTINATION .
)
endif()

# Setup CPack
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_VERSION "1.5.x")
include(CPack)
