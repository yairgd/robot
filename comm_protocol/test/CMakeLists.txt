

add_executable(test1 
	${CMAKE_CURRENT_SOURCE_DIR}/test1.cpp
	${CMAKE_SOURCE_DIR}/common/ThreadPool.cpp
	${CMAKE_SOURCE_DIR}/common/logger.c

)

target_include_directories(test1 PRIVATE 
	${PROJECT_BINARY_DIR}/	
	${CMAKE_CURRENT_SOURCE_DIR}	
)

target_link_libraries(test1 PRIVATE
	ScanerHal
	protocol_static
	#"$<LINK_GROUP:RESCAN, streaming, gui, curl, jsoncpp>"
)
