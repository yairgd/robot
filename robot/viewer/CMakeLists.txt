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



