/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/uart.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <string.h>


#include "zephyr/uart_zephyr.h"
#include "protocol-v1/ProtocolStateMachine.h"
#include "protocol-v1/HandleUartMsg.h"

#include "robot.h"


#include <memory>

/* size of stack area used by each thread */
#define STACKSIZE 4096

/* scheduling priority used by each thread */
#define PRIORITY 7



/* UART device name */
#define UART_DEV_NAME usart3

/* UART buffer */
#define UART_BUF_SIZE 64
//static uint8_t uart_buffer[UART_BUF_SIZE];

/* UART device structure */
static const struct  device *uart_dev;

/* UART ISR callback */
static void uart_isr(const struct device *dev, void *user_data)
{
	// ARG_UNUSED(user_data);
	uint8_t recv_data;
	int rx_err;

	while (uart_irq_update(dev) && uart_irq_is_pending(dev)) {
		if (uart_irq_rx_ready(dev)) {
			rx_err = uart_fifo_read(dev, &recv_data, 1);
			if (rx_err == 0) {
				// Process received data
				// ...
			}
		}
	}
}



#define UART_DEVICE_NODE DT_CHOSEN(zephyr_shell_uart)
#define UART_NODE2 DT_ALIAS(single_line_uart2)
#define UART_NODE2a DT_CHOSEN(zephyr_console)

//const struct device *const sl_uart1 ;//= DEVICE_DT_GET(UART_NODE2);
const struct device *const sl_uart2 = DEVICE_DT_GET(UART_NODE2a);



// static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

#if 0
/* Initialize and configure UART */
static int uart_init(void)
{
	uart_dev = DEVICE_DT_GET(UART_NODE2a);

	//   uart_dev = device_get_binding("usart3");
	if (!uart_dev) {
		printk("Failed to get UART device\n");
		return -ENODEV;
	}

	/* Configure UART */
	const struct uart_config uart_cfg = {
		.baudrate = 115200,
		.parity = UART_CFG_PARITY_NONE,
		.stop_bits = UART_CFG_STOP_BITS_1,
		.data_bits = UART_CFG_DATA_BITS_8,
		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE
	};

	int ret = uart_configure(uart_dev, &uart_cfg);
	if (ret != 0) {
		printk("Failed to configure UART: %d\n", ret);
		return ret;
	}

	/* Register UART ISR callback */
	uart_irq_callback_set(uart_dev, uart_isr);

	/* Enable UART interrupt */
	uart_irq_rx_enable(uart_dev);

	printk("UART initialized\n");
	return 0;
}
#endif

int main(void)
{
	int ret;

	printk("Zephyr USART Example\n");
#if 0

	/* Initialize UART */
	ret = uart_init();
	if (ret != 0) {
		printk("UART initialization failed\n");
		return 0;
	}

	//unsigned char recv;
	if (/*!device_is_ready(sl_uart1) || */!device_is_ready(sl_uart2)) {
		printk("uart devices not ready\n");
		return 0;
	}
	//char c='a';
	while (true) {
		//uart_poll_out(sl_uart2, c);
		//c++;
		//if (c=='z')
		//	 c='a';
		/* give the uarts some time to get the data through */
		//k_sleep(K_MSEC(50));

		int ret = uart_poll_in(sl_uart2, &c);

		if (ret < 0) {
			//printk("Receiving failed. Error: %d", ret);
		} else {
			uart_poll_out(sl_uart2, c);	
			//	k_sleep(K_MSEC(50));

			//		printk("Received %c\n", recv);
		}
		k_sleep(K_MSEC(2000));

	}
#endif
	while (1) {
		k_sleep(K_MSEC(2000));		
	}
	return 0;

}
#if 1
void uart_init(void);
void message_in_listenr(void)
{
	//unsigned char c;
	printk("message_in_listenr\n");
	/* Initialize UART */
	// uart_init();
#if 0
	if (ret != 0) {
		printk("UART initialization failed\n");
		return;
	}
	if (ret != 0) {
		printk("UART initialization failed\n");
		return ;
	}

	//unsigned char recv;
	if (/*!device_is_ready(sl_uart1) || */!device_is_ready(sl_uart2)) {
		printk("uart devices not ready\n");
		return ;
	}
#endif
	
	auto uart = Hal::GetUartZephyr(sl_uart2);
	uart->Open();
	auto p  =  std::shared_ptr<Simple::HandleUartMsg>(new Simple::HandleUartMsg(uart) );
	std::shared_ptr<IProtocolParser> parser = std::shared_ptr<Simple::ProtocolStateMachine> ( new Simple::ProtocolStateMachine  (uart, p));
		
	std::cout << "begin c++ app"<<std::endl;	

#if 0
 	auto login =  [] () ->void{
   
           };	
	login();
#endif

	while (1) {
		parser->Parse();
	
		//k_sleep(K_MSEC(1));

#if 0
		unsigned char c;
		int ret = uart_poll_in(sl_uart2, &c);

		if (ret < 0) {
			//printk("Receiving failed. Error: %d", ret);
		} else {
			uart_poll_out(sl_uart2, c);	
			//	k_sleep(K_MSEC(50));

			//		printk("Received %c\n", recv);
		}
#endif


	}

}

K_THREAD_DEFINE(message_in_listenr_id, STACKSIZE, message_in_listenr, NULL, NULL, NULL, PRIORITY, 0, 0);
#endif

/**
 * Created  06/22/2023
 * @brief   
 * @param   
 * @return  
 */
