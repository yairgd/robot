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
)





set ( viewer_SRC 
	./main.cpp

)

add_executable(viewer 
	${viewer_SRC}
)




target_include_directories(viewer PUBLIC 
	./	
)


target_link_libraries(viewer PUBLIC
	SDL2	
)



