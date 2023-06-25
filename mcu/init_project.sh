#!/bin/bash
export ZEPHYR_BASE=/mnt/sdb1/yair/stm32/zephyrproject/zephyr
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr
cd hello_world
west build -b nucleo_h745zi_q_m7  --  -G"Unix Makefiles"
