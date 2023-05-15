set ( robot_SRC 
	./matrix.c
	./optim.c
	../../generated/jacobian.c
)


add_library(robot_static STATIC
	${robot_SRC}
)




target_include_directories(robot_static PUBLIC 
	./	
)


target_link_libraries(robot_static PUBLIC
	lapack
)



