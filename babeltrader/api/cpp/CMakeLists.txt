################ babeltrader api ################

# cmake
include(${MUGGLEC_SRC_DIR}/cmake/muggle_utils.cmake)

# babeltrader_cpp_api
muggle_add_project(${babeltrader_api}
	${CMAKE_CURRENT_LIST_DIR} ${BABELTRADER_LIB_TYPE}
)

set_target_properties(${babeltrader_api}
	PROPERTIES
	VERSION ${BABELTRADER_VERSION}
	SOVERSION ${BABELTRADER_SOVERSION}
	DEBUG_POSTFIX d
)

if (BABELTRADER_BUILD_SHARED_LIB)
	target_compile_definitions(${babeltrader_api}
		PUBLIC BABELTRADER_API_USE_DLL
		PRIVATE BABELTRADER_API_EXPORTS
	)
endif()
target_compile_definitions(${babeltrader_api} PRIVATE
	BABELTRADER_VER=${babeltrader_version}
)

install(TARGETS ${babeltrader_api}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)
muggle_install_headers(${CMAKE_CURRENT_LIST_DIR} include/babeltrader/api/cpp)
