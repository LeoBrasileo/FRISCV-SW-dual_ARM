# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\Leo\Desktop\FRISCV\FRISCV-system-SW\friscv_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\Leo\Desktop\FRISCV\FRISCV-system-SW\friscv_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {friscv_platform}\
-hw {C:\Users\Leo\Desktop\FRISCV\FRISCV-system-HW\friscv_system_fpga\friscv_system_fpga_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/Leo/Desktop/FRISCV/FRISCV-system-SW}

platform write
platform generate -domains 
domain create -name {ps7_cortexa9_1} -os {standalone} -proc {ps7_cortexa9_1} -arch {32-bit} -display-name {ps7_cortexa9_1} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
bsp reload
platform generate
domain active {standalone_domain}
bsp reload
bsp reload
platform active {friscv_platform}
bsp reload
bsp reload
domain create -name {ps7_cortexa9_1_freertos} -os {freertos} -proc {ps7_cortexa9_1} -arch {32-bit} -display-name {ps7_cortexa9_1_freertos} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
bsp reload
bsp reload
platform generate
domain remove ps7_cortexa9_1_freertos
platform generate -domains 
platform write
platform generate -domains 
domain active {zynq_fsbl}
bsp reload
domain remove ps7_cortexa9_1
platform generate -domains 
platform write
domain create -name {ps7_cortexa9_1} -os {freertos} -proc {ps7_cortexa9_0} -arch {32-bit} -display-name {ps7_cortexa9_1} -desc {} -runtime {cpp}
platform generate -domains 
domain -report -json
platform write
domain remove ps7_cortexa9_1
platform generate -domains 
platform write
domain create -name {ps7_cortexa9_1} -os {freertos} -proc {ps7_cortexa9_1} -arch {32-bit} -display-name {ps7_cortexa9_1} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
bsp reload
platform generate -domains ps7_cortexa9_1 
bsp reload
domain remove ps7_cortexa9_1
platform generate -domains 
platform write
domain create -name {ps7_cortexa9_1} -os {standalone} -proc {ps7_cortexa9_1} -arch {32-bit} -display-name {ps7_cortexa9_1} -desc {} -runtime {cpp}
platform generate -domains 
domain -report -json
platform write
platform generate -domains 
domain remove ps7_cortexa9_1
platform generate -domains 
platform write
domain create -name {ps7_cortexa9_1} -os {standalone} -proc {ps7_cortexa9_1} -arch {32-bit} -display-name {ps7_cortexa9_1} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns"
bsp reload
platform generate -domains 
platform active {friscv_platform}
platform generate -domains 
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns"
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -fno-tree-loop-distribute-patterns -DUSE_AMP=1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains ps7_cortexa9_1 
platform clean
platform generate
bsp reload
platform clean
platform generate
platform clean
platform generate
