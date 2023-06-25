
if (${TARGET} STREQUAL "LINUX_PC")
	file (GLOB_RECURSE SRC pc/*.cpp
			pc/*.c)
	
elseif(${TARGET} STREQUAL "LINUX_IMX")
	file (GLOB_RECURSE SRC imx/*.cpp
			imx/*.c)
			
endif()

add_library (${PROJECT_NAME} STATIC
	${SRC}
	./uart_linux.cpp

)


if(${TARGET} STREQUAL "LINUX_IMX")
	target_link_libraries (${PROJECT_NAME} PRIVATE pxp)
	target_include_directories(${PROJECT_NAME} PUBLIC .. . ../.. imx)		
elseif (${TARGET} STREQUAL "LINUX_PC")
	target_include_directories(${PROJECT_NAME} PUBLIC .. . ../.. pc)		
endif()


