

#find_program(PYTHON "python")	

set (PYTHON "/usr/bin/python3")


#if ( DEFINED PYTHON)

	# the sources and headers are here since we want then to show on a visual
	# studio project
	set (python_SRC
		${CMAKE_SOURCE_DIR}/robot/python/src/robot.c	
		)

	





	set (PACKAGE_VERSION "1.0")
	set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
	set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
	set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build/")
	set(DEPS        
		robot_static	
		${python_H}
		${python_SRC}
		${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
		${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in
		${CMAKE_CURRENT_SOURCE_DIR}/robot/__init__.py
		)
	configure_file(${SETUP_PY_IN} ${SETUP_PY})




	if (UNIX)
		add_custom_command(OUTPUT ${OUTPUT}
			COMMAND ${PYTHON} ${SETUP_PY}  clean build --force install  --user 
			COMMAND ${PYTHON} ${SETUP_PY}  bdist_wheel 
			COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
			DEPENDS ${DEPS}
			POST_BUILD
			COMMAND ${PYTHON} ${SETUP_PY}  build  install --user
			)

	else()
		add_custom_command(OUTPUT ${OUTPUT}
			COMMAND ${PYTHON} ${SETUP_PY}  build --plat-name=win-amd64   install --user #--force  bdist bdist_wininst	
			COMMAND ${PYTHON} ${SETUP_PY}   bdist_wininst bdist_wheel			
			COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
			DEPENDS ${DEPS}
			POST_BUILD
			COMMAND ${PYTHON} ${SETUP_PY}  build  install --user

			#COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
			)

	endif(UNIX)

	add_custom_target(demo_package  ALL 
		DEPENDS ${OUTPUT}
		)


	install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} build install --user --force)")




	#	if (UNIX)
	#		install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} build                         install --user --force bdist)")
	#else()
	#	install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} build   --plat-name=win-amd64  install --user --force  bdist)")
	#endif()
	#
	#  --plat-name=win-amd64
#else()
#	message (WARNING "Cannot find python")
#ndif()







