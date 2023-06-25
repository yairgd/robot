yair@yair ~/zephyr-sdk-0.16.1 $ ./sysroots/x86_64-pokysdk-linux/usr/bin/openocd  -f ./sysroots/x86_64-pokysdk-linux/usr/share/openocd/scripts/interface/stlink.cfg -f ./sysroots/x86_64-pokysdk-linux/usr/share/openocd/scripts/target/stm32h7x_dual_bank.cfg 

~/zephyr-sdk-0.16.1 $  sudo ./sysroots/x86_64-pokysdk-linux/usr/bin/openocd  -s /home/yair/zephyr-sdk-0.16.1/sysroots/x86_64-pokysdk-linux/usr/share/openocd/scripts  -f ./board/st_nucleo_h745zi.cfg
yair@yair ~/zephyr-sdk-0.16.1 $  sudo ./sysroots/x86_64-pokysdk-linux/usr/bin/openocd  -s /home/yair/zephyr-sdk-0.16.1/sysroots/x86_64-pokysdk-linux/usr/share/openocd/scripts  -f /mnt/sdb1/yair/stm32/zephyrproject/zephyr/boards/arm/nucleo_h745zi_q/support/openocd.cfg
/home/yair/zephyr-sdk-0.16.1/sysroots/x86_64-pokysdk-linux/usr/bin/openocd -s /mnt/sdb1/yair/stm32/zephyrproject/zephyr/boards/arm/nucleo_h745zi_q/support -s /home/yair/zephyr-sdk-0.16.1/sysroots/x86_64-pokysdk-linux/usr/share/openocd/scripts -f /mnt/sdb1/yair/stm32/zephyrproject/zephyr/boards/arm/nucleo_h745zi_q/support/openocd.cfg '-c init' '-c targets' -c 'reset init' -c 'flash write_image erase /home/yair/trees/project/mcu/hellow_world/build/zephyr/zephyr.hex' -c 'reset run' -c shutdown
/home/yair/zephyr-sdk-0.16.1/sysroots/x86_64-pokysdk-linux/usr/bin/openocd -s /mnt/sdb1/yair/stm32/zephyrproject/zephyr/boards/arm/nucleo_h745zi_q/support -s /home/yair/zephyr-sdk-0.16.1/sysroots/x86_64-pokysdk-linux/usr/share/openocd/scripts -f /mnt/sdb1/yair/stm32/zephyrproject/zephyr/boards/arm/nucleo_h745zi_q/support/openocd.cfg '-c init' '-c targets' -c 'reset init'



# cortex m7 openocd
/home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mcu.externaltools.openocd.linux64_2.0.0.202105311346/tools/bin/openocd "-f" "diso-test1_CM7 Debug.cfg" "-s" "/home/yair/STM32CubeIDE/workspace_1.7.0/diso-test1/CM7" "-s" "/home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mcu.debug.openocd_2.0.0.202106290712/resources/openocd/st_scripts" "-s" "/home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mpu.debug.openocd_2.0.0.202106231211/resources/openocd/st_scripts" "-c" "gdb_report_data_abort enable" "-c" "gdb_port 3333" "-c" "tcl_port 6666" "-c" "telnet_port 4444" "-c" "st-link serial 002F00323137511439383538"


# cortex m7 stlink
/home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.linux64_2.0.0.202105311346/tools/bin/ST-LINK_gdbserver -p 61234 -l 1 -d -t -s -cp /home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.linux64_2.0.0.202105311346/tools/bin -m 0 -k



# cortex M4 stlink 
/home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.linux64_2.0.0.202105311346/tools/bin/ST-LINK_gdbserver -p 61234 -l 1 -d -t -s -cp /home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.linux64_2.0.0.202105311346/tools/bin -m 3 -k

# cortex m4 openocd
/home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mcu.externaltools.openocd.linux64_2.0.0.202105311346/tools/bin/openocd "-f" "diso-test1_CM4 Debug.cfg" "-s" "/home/yair/STM32CubeIDE/workspace_1.7.0/diso-test1/CM4" "-s" "/home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mcu.debug.openocd_2.0.0.202106290712/resources/openocd/st_scripts" "-s" "/home/yair/st/stm32cubeide_1.7.0/plugins/com.st.stm32cube.ide.mpu.debug.openocd_2.0.0.202106231211/resources/openocd/st_scripts" "-c" "gdb_report_data_abort enable" "-c" "gdb_port 3333" "-c" "tcl_port 6666" "-c" "telnet_port 4444" "-c" "st-link serial 002F00323137511439383538"
