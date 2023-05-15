set (ik_SRC 
	./ik.c
	#../../Lapack/Scr/dgetri.c
	#../../Lapack/Scr/dtrtri.c
	#../../Lapack/Scr/dtrti2.c

)


add_executable(ik 
	${ik_SRC}
)




target_include_directories(ik PUBLIC 
	./	
)

target_link_libraries(ik PRIVATE
	robot_static
)

add_executable(robot_demo 
	./robot_demo.cpp)

target_link_libraries(robot_demo PRIVATE
	viewer
)

add_executable(cube_demo 
	./cube_demo.cpp)

target_link_libraries(cube_demo PRIVATE
	viewer
)


