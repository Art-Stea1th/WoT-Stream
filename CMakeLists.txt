cmake_minimum_required(VERSION 3.9)

project(wot_stream)

set(WS_DEPS "${CMAKE_SOURCE_DIR}/dependencies")

set(OBS_SRC "${WS_DEPS}/obs_src")
set(OBS_SLN "${WS_DEPS}/obs_sln")

set(WS_ROOT "${CMAKE_SOURCE_DIR}/extension")

set(WS_INCLUDE_DIRS
    "${OBS_SRC}/libobs"
    "${WS_ROOT}"
    "${WS_ROOT}/helpers"
	"${WS_ROOT}/utilities"
	"${WS_ROOT}/obs_management"
)

include_directories(WS_INCLUDE_DIRS)

file(GLOB_RECURSE SOURCES
    "${WS_ROOT}/*.h"
	"${WS_ROOT}/*.cpp"
)

add_executable(wot_stream "${SOURCES}")

set_property(TARGET wot_stream PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET wot_stream PROPERTY CXX_STANDARD 17)


# hardcode
find_library(LIB_OBS NAMES "obs" PATHS "${OBS_SLN}/libobs/Debug/")
target_link_libraries(wot_stream "${LIB_OBS}")

# hardcode
set_property(TARGET wot_stream PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${OBS_SLN}/rundir/Debug/bin/32bit") # ??