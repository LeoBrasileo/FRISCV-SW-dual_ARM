# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\Leo\Desktop\FRISCV\FRISCV-system-SW\dual_arm_0_system\_ide\scripts\systemdebugger_dual_arm_0_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\Leo\Desktop\FRISCV\FRISCV-system-SW\dual_arm_0_system\_ide\scripts\systemdebugger_dual_arm_0_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Xilinx HW-FTDI-TEST FT2232H 1234-tulA" && level==0 && jtag_device_ctx=="jsn-HW-FTDI-TEST FT2232H-1234-tulA-23727093-0"}
fpga -file C:/Users/Leo/Desktop/FRISCV/FRISCV-system-SW/dual_arm_0/_ide/bitstream/friscv_system_fpga_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/Leo/Desktop/FRISCV/FRISCV-system-SW/friscv_platform/export/friscv_platform/hw/friscv_system_fpga_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/Leo/Desktop/FRISCV/FRISCV-system-SW/dual_arm_0/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/Leo/Desktop/FRISCV/FRISCV-system-SW/dual_arm_0/Debug/dual_arm_0.elf
targets -set -nocase -filter {name =~ "*A9*#1"}
dow C:/Users/Leo/Desktop/FRISCV/FRISCV-system-SW/dual_arm_1/Debug/dual_arm_1.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
targets -set -nocase -filter {name =~ "*A9*#1"}
con
