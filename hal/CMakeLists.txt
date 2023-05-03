project ("ScanerHal")


if (${TARGET} STREQUAL "LINUX_PC" OR ${TARGET} STREQUAL "LINUX_IMX")
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/linux)
elseif(${TARGET} STREQUAL "WINDOWS")
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/windows)
endif()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/emul)	

