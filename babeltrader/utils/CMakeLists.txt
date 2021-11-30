################ babeltrader utils ################

# cmake
include(${MUGGLEC_SRC_DIR}/cmake/muggle_utils.cmake)

# include
include_directories(
	${RAPIDJSON_SRC_DIR}/include
)

# babeltrader_cpp_utils
muggle_add_project(${babeltrader_utils}
	${CMAKE_CURRENT_LIST_DIR} ${BABELTRADER_LIB_TYPE}
)

set_target_properties(${babeltrader_utils}
	PROPERTIES
	VERSION ${BABELTRADER_VERSION}
	SOVERSION ${BABELTRADER_SOVERSION}
	DEBUG_POSTFIX d
)

if (BABELTRADER_BUILD_SHARED_LIB)
	target_compile_definitions(${babeltrader_utils}
		PUBLIC BABELTRADER_UTILS_USE_DLL
		PRIVATE BABELTRADER_UTILS_EXPORTS
	)
endif()
target_compile_definitions(${babeltrader_utils} PRIVATE
	BABELTRADER_VER=${babeltrader_version}
	BABELTRADER_USE_LOG_MACRO=1
)

target_link_libraries(${babeltrader_utils}
	${babeltrader_base}
	${babeltrader_api}
)
add_dependencies(${babeltrader_utils}
	${babeltrader_base}
	${babeltrader_api}
)

install(TARGETS ${babeltrader_utils}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)
muggle_install_headers(${CMAKE_CURRENT_LIST_DIR} include/babeltrader/utils)
