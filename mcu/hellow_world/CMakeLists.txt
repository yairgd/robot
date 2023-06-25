# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)


include (${CMAKE_SOURCE_DIR}/cmake/functions.cmake)
set(PRE_CONFIGURE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/git.h.in")
set(POST_CONFIGURE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/git.h")
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/git_watcher.cmake)
set (CMAKE_CXX_STANDARD 17)


set (PROJ_TOP ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_sources(app PRIVATE 
	src/uart.c	
	src/main.cpp
	${PROJ_TOP}/comm_protocol/protocol-v1/ProtocolStateMachine.cpp
	${PROJ_TOP}/hal/zephyr/uart_zephyr.cpp
)


target_include_directories(app PRIVATE
	${PROJ_TOP}/comm_protocol/
	${PROJ_TOP}/hal
	${PROJ_TOP}/
	${PROJECT_BINARY_DIR}
	)

