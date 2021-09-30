cmake_minimum_required(VERSION 3.0.2)
project(BabelTraderCore)

# set compile parameter
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra")
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra -Wno-missing-field-initializers")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_UNICODE -DUNICODE)
endif()

# set standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# for vim plugin - YCM
if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# set use folder in vs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################ version ################

file(STRINGS "version.txt" babeltrader_version)

string(REPLACE "-" ";" babeltrader_semver_ext ${babeltrader_version})
list(GET babeltrader_semver_ext 0 babeltrader_semver)
string(REPLACE "." ";" babeltrader_semver_list ${babeltrader_semver})

list(GET babeltrader_semver_list 0 BABELTRADER_VER_MAJOR)
list(GET babeltrader_semver_list 1 BABELTRADER_VER_MINOR)
list(GET babeltrader_semver_list 2 BABELTRADER_VER_PATCH)

set(BABELTRADER_VERSION "${babeltrader_version}")
set(BABELTRADER_SOVERSION "${BABELTRADER_VER_MAJOR}")

################ options ################

set(BABELTRADER_BUILD_SHARED_LIB OFF CACHE BOOL "babeltrader base build shared library")
set(BABELTRADER_BUILD_TESTING ON CACHE BOOL "babeltrader build testing")
set(BABELTRADER_BUILD_EXAMPLE ON CACHE BOOL "babeltrader build example")

if (BABELTRADER_BUILD_SHARED_LIB)
	set(BABELTRADER_LIB_TYPE SHARED)
else()
	set(BABELTRADER_LIB_TYPE STATIC)
endif()

# output options
message("-- babeltrader version ${BABELTRADER_VERSION}")
message("-- option BABELTRADER_BUILD_SHARED_LIB ${BABELTRADER_BUILD_SHARED_LIB}")
message("-- option BABELTRADER_LIB_TYPE ${BABELTRADER_LIB_TYPE}")
message("-- option BABELTRADER_BUILD_TESTING ${BABELTRADER_BUILD_TESTING}")
message("-- option BABELTRADER_BUILD_EXAMPLE ${BABELTRADER_BUILD_EXAMPLE}")

################ import dependencies ################
include(${CMAKE_CURRENT_LIST_DIR}/cmake/dep.cmake.in)

set(MUGGLECPP_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/mugglecpp-src)
set(MUGGLEC_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/mugglecpp-build/mugglec-src)
set(RAPIDJSON_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/rapidjson-src)


################ base set ################

set(babeltrader_api babeltrader_cpp_api)
set(babeltrader_base babeltrader_cpp_base)
set(babeltrader_test_utils babeltrader_test_utils)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}
)

################ babeltrader_cpp_api ################
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/babeltrader/api/cpp)

################ babeltrader_cpp_base ################
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/babeltrader/base)

################ test_utils ################
if (BABELTRADER_BUILD_TESTING)
	enable_testing()
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test_utils)
endif()

############### functions ################
function(add_gtest name folder)
	message("add test ${name} ${folder}")
	
	set(name test_${name})

	file(GLOB tmp_h ${folder}/*.h)
	file(GLOB tmp_c ${folder}/*.c)
	file(GLOB tmp_cpp ${folder}/*.cpp)
	file(GLOB tmp_cc ${folder}/*.cc)

	if (WIN32)
		add_executable(${name} ${tmp_h} ${tmp_c} ${tmp_cpp} ${tmp_cc})
		set_target_properties(${name}
			PROPERTIES
			FOLDER "test"
			VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
		)
	else()
		add_executable(${name} ${tmp_c} ${tmp_cpp} ${tmp_cc})
	endif(WIN32)

	target_include_directories(${name} PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
		${GTEST_INCLUDE_DIRS}
	)
	if (NOT FOUND_GTEST_FROM_SEARCH)
		add_dependencies(${name}
			${babeltrader_test_utils}
			${GTEST_BOTH_LIBRARIES}
		)
	endif()
	target_link_libraries(${name}
		${babeltrader_test_utils}
		${GTEST_BOTH_LIBRARIES}
	)

	add_test(NAME ${name} COMMAND ${name})
endfunction()

################ c++ api & base test ################
if (BABELTRADER_BUILD_TESTING)
	message("---------------------- test api & base ----------------------")
	SUBDIRLIST(test_root_dir ${CMAKE_CURRENT_LIST_DIR}/test)
	FOREACH(subdir ${test_root_dir})
		add_gtest(${subdir} ${CMAKE_CURRENT_LIST_DIR}/test/${subdir})
	ENDFOREACH()
endif()
