
file (GLOB_RECURSE SRC *.cpp
	*.c)



add_library (${PROJECT_NAME} STATIC
	${SRC}
	./../qrdecode.c

)

target_include_directories(${PROJECT_NAME} PUBLIC .. . ../..)		


