# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/kiran/Projects/fpgaProjects/EmbeddedSystemDesign/mio_gpio/mio_gpio_vitis/mio_gpio_wrapper/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/kiran/Projects/fpgaProjects/EmbeddedSystemDesign/mio_gpio/mio_gpio_vitis/mio_gpio_wrapper/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {mio_gpio_wrapper}\
-hw {/home/kiran/Projects/fpgaProjects/EmbeddedSystemDesign/mio_gpio/mio_gpio_vitis/mio_gpio_wrapper.xsa}\
-out {/home/kiran/Projects/fpgaProjects/EmbeddedSystemDesign/mio_gpio/mio_gpio_vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {mio_gpio_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
platform generate
platform active {mio_gpio_wrapper}
bsp reload
domain active {zynq_fsbl}
bsp reload
platform generate -domains 
