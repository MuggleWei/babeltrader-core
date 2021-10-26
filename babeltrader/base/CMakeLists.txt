################ babeltrader base ################

# cmake
include(${MUGGLEC_SRC_DIR}/cmake/muggle_utils.cmake)

# babeltrader_cpp_base
muggle_add_project(${babeltrader_base}
	${CMAKE_CURRENT_LIST_DIR} ${BABELTRADER_LIB_TYPE}
)
target_include_directories(${babeltrader_base} PUBLIC
	${MUGGLECPP_SRC_DIR}
	${MUGGLEC_SRC_DIR}
	${RAPIDJSON_SRC_DIR}/include
)
add_dependencies(${babeltrader_base}
	mugglecpp
	mugglec
)
target_link_libraries(${babeltrader_base} mugglecpp mugglec)
set_target_properties(${babeltrader_base}
	PROPERTIES
	VERSION ${BABELTRADER_VERSION}
	SOVERSION ${BABELTRADER_SOVERSION}
	DEBUG_POSTFIX d
)

if (BABELTRADER_BUILD_SHARED_LIB)
	target_compile_definitions(${babeltrader_base}
		PUBLIC BABELTRADER_USE_DLL
		PRIVATE BABELTRADER_EXPORTS
	)
endif()
target_compile_definitions(${babeltrader_base} PRIVATE
	BABELTRADER_VER=${babeltrader_version}
	BABELTRADER_USE_LOG_MACRO=1
)

install(TARGETS ${babeltrader_base}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)
muggle_install_headers(${CMAKE_CURRENT_LIST_DIR} include/babeltrader/base)
muggle_install_headers(${CMAKE_CURRENT_LIST_DIR}/../include include/babeltrader/include)
