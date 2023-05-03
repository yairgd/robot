

#find_program(PYTHON "python")	

set (PYTHON "/usr/bin/python3")


#if ( DEFINED PYTHON)

	# the sources and headers are here since we want then to show on a visual
	# studio project
	set (python_SRC
		"${PROJECT_SOURCE_DIR}/algo/python/src/strategy.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/strategy_tester.c"		
		"${PROJECT_SOURCE_DIR}/algo/python/src/algo.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/tickdata.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/performance_manager.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/parameter.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/parameter.h"		
		"${PROJECT_SOURCE_DIR}/algo/python/src/output.c"		
		"${PROJECT_SOURCE_DIR}/algo/python/src/output.h"		
		"${PROJECT_SOURCE_DIR}/algo/python/src/tech_indicator.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/model.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/tag_indicator.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/strategy.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/kfpt.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/sma.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/rsi.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/atr.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/adx.c"

		#"${PROJECT_SOURCE_DIR}/algo/python/src/high.c"
		#		"${PROJECT_SOURCE_DIR}/algo/python/src/low.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/ema.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/macd.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/ohlc.c"
		"${PROJECT_SOURCE_DIR}/algo/python/src/ema_cross.c"


		)

	set (python_H

		"${CMAKE_BINARY_DIR}/git.h"

		)


	set(OUTPUT    "${CMAKE_CURRENT_SOURCE_DIR}/Algo/gui/dashboard.py")
	add_custom_command(OUTPUT ${OUTPUT}
		COMMAND  pyuic5 ${CMAKE_CURRENT_SOURCE_DIR}/Algo/gui/dashboard.ui -o ${OUTPUT}
		COMMAND ${CMAKE_COMMAND} -E touch  ${OUTPUT} 
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Algo/gui/dashboard.ui)
	add_custom_target(gui_py ALL
		DEPENDS  "" 
		${OUTPUT})



	set (PACKAGE_VERSION "1.0")
	set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
	set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
	set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build/")
	set(DEPS        
		algo_static	
		${python_H}
		${python_SRC}
		${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
		${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in
		${CMAKE_CURRENT_SOURCE_DIR}/Algo/utils.py
		${CMAKE_CURRENT_SOURCE_DIR}/Algo/models.py
		${CMAKE_CURRENT_SOURCE_DIR}/Algo/tests.py
		${CMAKE_CURRENT_SOURCE_DIR}/Algo/parameters.py
		${CMAKE_CURRENT_SOURCE_DIR}/Algo/demo/ma.py
		${CMAKE_CURRENT_SOURCE_DIR}/Algo/__init__.py
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







