/*
"helloworld.c" template is used as a startign point to toggle led on the ZYBO Z7-20 board. 
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

    print("Hello World\n\r");
    print("Successfully ran Hello World application\n");

    // make the pin as the output pin
    XGpioPs_SetDirectionPin(&my_gpio, 7, 1);

    // enable the output
    XGpioPs_SetOutputEnablePin(&my_gpio, 7, 1);

    // forever loop
    while(1){
    	// turn on the led
    	XGpioPs_WritePin(&my_gpio, 7, 1);
    	sleep(1);
    	// turn off the led
    	XGpioPs_WritePin(&my_gpio, 7, 0);
    	sleep(1);
    }

    cleanup_platform();
    return 0;
}

