if (BABELTRADER_BUILD_TESTING)
	enable_testing()

	muggle_add_project(${babeltrader_test_utils}
		${CMAKE_CURRENT_LIST_DIR} SHARED
	)
	add_dependencies(${babeltrader_test_utils} ${babeltrader_base})
	target_link_libraries(${babeltrader_test_utils} ${babeltrader_base})
	target_compile_definitions(${babeltrader_test_utils}
		PUBLIC TESTUTILS_USE_DLL BABELTRADER_USE_LOG_MACRO=1
		PRIVATE TESTUTILS_EXPORTS
	)
endif()
