################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/boot/%.obj: ../src/boot/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/Desktop/TI/piano" --include_path="D:/Desktop/TI/piano/src/drivers" --include_path="D:/Desktop/TI" --include_path="D:/Desktop/TI/inc" --include_path="D:/Desktop/TI/driverlib" --include_path="D:/Desktop/TI/drivers" --include_path="D:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="src/boot/$(basename $(<F)).d_raw" --obj_directory="src/boot" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


