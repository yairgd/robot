set (ik_SRC 
	./ik.c
)


add_executable(ik 
	${ik_SRC}
)




target_include_directories(ik PUBLIC 
	./	
)


target_link_libraries(ik PRIVATE
	robot
)



