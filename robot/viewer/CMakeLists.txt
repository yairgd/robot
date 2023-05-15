
set (viewer_SRC 
	./screen.cpp
	./ShapeObject.cpp	
	./robot.cpp
	./cube.cpp
	./CoordinateSystem.cpp
)
add_library(viewer STATIC
	${viewer_SRC}
)

target_link_libraries(viewer PUBLIC
	SDL2	
	robot_static	
)
target_include_directories(viewer PUBLIC
	./	
)




