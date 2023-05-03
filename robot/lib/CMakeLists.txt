set ( robot_SRC 
	./matrix.c
)


add_library(robot STATIC
	${robot_SRC}
)




target_include_directories(robot PUBLIC 
	./	
)


target_link_libraries(robot PUBLIC
	lapack
)



