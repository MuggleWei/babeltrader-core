@echo off

setlocal ENABLEDELAYEDEXPANSION

set origin_path=%~dp0
cd %origin_path%
set pkg_dir=%origin_path%build\pkg

md build
cd build
cmake .. ^
	-G "Visual Studio 14 2015 Win64" ^
	-DBABELTRADER_BUILD_SHARED_LIB=ON ^
	-DBABELTRADER_BUILD_TESTING=ON ^
	-DBABELTRADER_BUILD_EXAMPLE=ON ^
	-DMUGGLE_BUILD_SHARED_LIB=ON ^
	-DMUGGLE_CPP_BUILD_SHARED_LIB=ON ^
	-Dgtest_force_shared_crt=ON ^
	-DCMAKE_PREFIX_PATH=f:/c_pkg ^
	-DCMAKE_INSTALL_PREFIX=%origin_path%build

endlocal
