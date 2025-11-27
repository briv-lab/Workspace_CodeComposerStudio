################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
driverlib/MSP430FR5xx_6xx/%.obj: ../driverlib/MSP430FR5xx_6xx/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccs1210/ccs/ccs_base/msp430/include" --include_path="U:/Workspace_CodeComposerStudio/OutOfBox_MSP430FR6989/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power=all --advice:hw_config=all -g --define=__MSP430FR6989__ --display_error_number --diag_warning=225 --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="driverlib/MSP430FR5xx_6xx/$(basename $(<F)).d_raw" --obj_directory="driverlib/MSP430FR5xx_6xx" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


