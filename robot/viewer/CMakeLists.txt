set ( cube_SRC 
	./cube.cpp
	./screen.cpp
	./cube_demo.cpp
)
add_executable(cube 
	${cube_SRC}
)


target_include_directories(cube PRIVATE
	./	
)

target_link_libraries(cube PRIVATE
	SDL2	
	robot
	
)





set ( robot_demo_SRC 
	./robot.cpp
	./screen.cpp
	./robot_demo.cpp
	./CoordinateSystem.cpp


)

add_executable(robot_demo
	${robot_demo_SRC}
)




target_include_directories(robot_demo PUBLIC 
	./	
)


target_link_libraries(robot_demo PUBLIC
	-Wl,--start-group  		
	SDL2
	robot
	-Wl,--end-group
	
)



