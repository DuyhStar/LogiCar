################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
timer/systemtick.obj: ../timer/systemtick.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/timer" --include_path="D:/CCS/TivaWare_C_Series-2.1.4.178" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/CarCtl" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/delay" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/ExternSensor" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/GPIO" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/I2C" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/MPU6050" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/PWM" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/ServoCtl" --include_path="D:/CCS/WorkSpace_CCS_Code/LogisticsCar/UART" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="timer/systemtick.d" --obj_directory="timer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


