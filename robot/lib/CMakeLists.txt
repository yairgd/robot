set ( robot_SRC 
	./matrix.c
	./model.c
	./optimization.c
	#	../../generated/jacobian.c
	../../generated/output.c
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



