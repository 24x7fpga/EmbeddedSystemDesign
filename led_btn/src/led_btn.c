/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpiops.h"

XGpioPs_Config *gpio_config;
XGpioPs my_gpio;

void init(){
	int status;
	gpio_config = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	status = XGpioPs_CfgInitialize(&my_gpio, gpio_config, gpio_config->BaseAddr);
	if(status==XST_SUCCESS)
		xil_printf("Device Initialization is Successful\n");
	else
		xil_printf("Device Initialization is Failed\n");
}

int main()
{
    init_platform();
    init(); // initialize device

    int p1, p2, p3 ,p4;

    xil_printf("Hello World\n\r");
    xil_printf("Successfully ran Hello World application\n");

    // make the btns as the input pin
    XGpioPs_SetDirectionPin(&my_gpio, 54, 0);
    XGpioPs_SetDirectionPin(&my_gpio, 55, 0);
    XGpioPs_SetDirectionPin(&my_gpio, 56, 0);
    XGpioPs_SetDirectionPin(&my_gpio, 57, 0);

    // make leds as output
    XGpioPs_SetDirectionPin(&my_gpio, 58, 1);
    XGpioPs_SetDirectionPin(&my_gpio, 59, 1);
    XGpioPs_SetDirectionPin(&my_gpio, 60, 1);
    XGpioPs_SetDirectionPin(&my_gpio, 61, 1);

    // enable the leds as output
    XGpioPs_SetOutputEnablePin(&my_gpio, 58, 1);
    XGpioPs_SetOutputEnablePin(&my_gpio, 59, 1);
    XGpioPs_SetOutputEnablePin(&my_gpio, 60, 1);
    XGpioPs_SetOutputEnablePin(&my_gpio, 61, 1);


    // forever loop
    while(1){
    	// read the btns
    	p1=XGpioPs_ReadPin(&my_gpio, 54);
    	p2=XGpioPs_ReadPin(&my_gpio, 55);
    	p3=XGpioPs_ReadPin(&my_gpio, 56);
    	p4=XGpioPs_ReadPin(&my_gpio, 57);
    	// set the leds
    	XGpioPs_WritePin(&my_gpio, 58, p1);
    	XGpioPs_WritePin(&my_gpio, 59, p2);
    	XGpioPs_WritePin(&my_gpio, 60, p3);
    	XGpioPs_WritePin(&my_gpio, 61, p4);

    }

    cleanup_platform();
    return 0;
}
