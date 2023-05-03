
file(GLOB_RECURSE lapack_SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/Blas/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/Scr/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/F2c/*.c"	
	"${CMAKE_CURRENT_SOURCE_DIR}/Install/*.c"
)


add_library(lapack STATIC
	${lapack_SRC}
)



target_include_directories(lapack PUBLIC 
	./Include	
)


target_link_libraries(lapack PUBLIC
	m
)

