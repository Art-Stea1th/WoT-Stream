cmake_minimum_required(VERSION 3.9)

project(wot_stream)

set(WS_DEPS "${CMAKE_SOURCE_DIR}/../deps/core")

set(OBS_INC "${WS_DEPS}/includes/libobs")
set(OBS_LIB "${WS_DEPS}/libraries_x86")

set(WS_ROOT "${CMAKE_SOURCE_DIR}/core")

set(WS_INCLUDE_DIRS

    "${OBS_INC}"

    "${WS_ROOT}"
    "${WS_ROOT}/helpers"

	"${WS_ROOT}/obs_management/sources"
	"${WS_ROOT}/obs_management/services"
	"${WS_ROOT}/obs_management/encoders"
	"${WS_ROOT}/obs_management/outputs"
)

include_directories(WS_INCLUDE_DIRS)

file(GLOB_RECURSE SOURCES
    "${WS_ROOT}/*.h"
	"${WS_ROOT}/*.c"
	"${WS_ROOT}/*.cpp"
)

# add_library(wot_stream SHARED "${SOURCES}")
add_executable(wot_stream "${SOURCES}")

set_property(TARGET wot_stream PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET wot_stream PROPERTY CXX_STANDARD 17)

# hardcode
find_library(LIB_OBS NAMES "obs" PATHS "${OBS_LIB}")
target_link_libraries(wot_stream "${LIB_OBS}")

# hardcode
# set_property(TARGET wot_stream PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${OBS_SLN}/rundir/Debug/bin/32bit") #?