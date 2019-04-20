################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./src/boot/tm4c1294ncpdt_startup_ccs.obj" \
"./src/fake_code.obj" \
"./src/main.obj" \
"./src/signal/FFT.obj" \
"./src/utils/uartstdio.obj" \
"../src/boot/tm4c1294ncpdt.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"D:/Desktop/TI/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include src/boot/subdir_vars.mk
-include src/subdir_vars.mk
-include src/signal/subdir_vars.mk
-include src/utils/subdir_vars.mk
-include src/boot/subdir_rules.mk
-include src/subdir_rules.mk
-include src/signal/subdir_rules.mk
-include src/utils/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
piano.out \

EXE_OUTPUTS__QUOTED += \
"piano.out" \

BIN_OUTPUTS += \
piano.hex \

BIN_OUTPUTS__QUOTED += \
"piano.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "piano.out"

# Tool invocations
piano.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"D:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=TARGET_IS_TM4C129_RA0 --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"piano.map" --heap_size=0 --stack_size=512 -i"D:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/lib" -i"D:/Desktop/TI/inc" -i"D:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" -i"D:/Desktop/TI/driverlib" -i"D:/Desktop/TI" -i"D:/Desktop/TI/utils" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="piano_linkInfo.xml" --rom_model -o "piano.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

piano.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"D:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armhex"  -o "piano.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "src\boot\tm4c1294ncpdt_startup_ccs.obj" "src\fake_code.obj" "src\main.obj" "src\signal\FFT.obj" "src\utils\uartstdio.obj" 
	-$(RM) "src\boot\tm4c1294ncpdt_startup_ccs.d" "src\fake_code.d" "src\main.d" "src\signal\FFT.d" "src\utils\uartstdio.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

