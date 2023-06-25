cmake_minimum_required(VERSION 3.10)


##https://stackoverflow.com/questions/39807664/how-to-best-tell-cmake-where-to-find-dll
##https://discourse.cmake.org/t/copying-config-specific-paths-at-build-time/4776
project(lvgl)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

include (${CMAKE_SOURCE_DIR}/cmake/functions.cmake)
set(PRE_CONFIGURE_FILE "${CMAKE_SOURCE_DIR}/cmake/git.h.in")
set(POST_CONFIGURE_FILE "${CMAKE_BINARY_DIR}/git.h")
include (${CMAKE_SOURCE_DIR}/cmake/git_watcher.cmake)
#include(ExternalProject)
set (CMAKE_CXX_STANDARD 17)


#https://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_definitions(-DSLEEP=sleep)
	set (CMAKE_C_FLAGS  " -g -O0 ${CMAKE_C_FLAGS_DEBUG_INIT}  ${CMAKE_C_FLAGS_DEBUG}    " )
	set (CMAKE_CXX_FLAGS  " -g -O0  ${CMAKE_CXX_FLAGS_DEBUG_INIT}  ${CMAKE_CXX_FLAGS_DEBUG}    " )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_definitions(-DSLEEP=Sleep) 
	add_definitions("-D_CRT_SECURE_NO_WARNINGS -DWIN32")
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")  
	set(CMAKE_CXX_FLAGS_DEBUG_INIT " /Zi ")
	set (CMAKE_CXX_FLAGS  " ${CMAKE_CXX_FLAGS_DEBUG_INIT}  ${CMAKE_CXX_FLAGS_DEBUG}  /MDd" )

	set(CMAKE_C_FLAGS_DEBUG_INIT "  /Zi")
	set (CMAKE_C_FLAGS  " ${CMAKE_C_FLAGS_DEBUG_INIT}  ${CMAKE_C_FLAGS_DEBUG}   /MDd " )

	link_directories(
		${CMAKE_SOURCE_DIR}/x64-windows/debug/lib
	)
	include_directories(
		${CMAKE_SOURCE_DIR}/x64-windows/include/
	)
endif()




if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
	if (NOT ${PC_SDL})
		set (TARGET "LINUX_IMX")

	else() 
		set (TARGET "LINUX_PC")	
		add_definitions(-DLINUX_PC)
	endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set (UART_FILE uart_win.cpp)
	set (TARGET "WINDOWS")	
endif()



add_subdirectory (comm_protocol)
add_subdirectory(Lapack)
add_subdirectory(hal)
add_subdirectory(robot)



if (FALSE)
	add_executable(scanner 
		main.cpp
	)

	target_include_directories(scanner PRIVATE 
		${PROJECT_BINARY_DIR}/	
		${CMAKE_SOURCE_DIR}	
	)







	set (libs streaming gui curl jsoncpp )
	if (UNIX)
		list(APPEND libs pthread)
		set (libs  -Wl,--start-group ${libs} -Wl,--end-group)

	else()
		add_custom_command(TARGET scanner  POST_BUILD
			#	COMMAND ${CMAKE_COMMAND} -E copy_directory   ${CMAKE_SOURCE_DIR}/x64-windows/debug/bin/  ${CMAKE_BINARY_DIR}/bin/debug
			COMMAND ${CMAKE_COMMAND} -E copy_directory   ${CMAKE_SOURCE_DIR}/x64-windows/debug/bin/  ${CMAKE_BINARY_DIR}/bin
		)
	endif()

	target_link_libraries(scanner PRIVATE
		${libs}
		ScanerHal
		#"$<LINK_GROUP:RESCAN, streaming, gui, curl, jsoncpp>"
	)



	if (YOCTO)
		install(TARGETS scanner DESTINATION /usr/bin)
	else()
		#add_subdirectory(testing)
	endif()
endif()


