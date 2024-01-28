################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SPI_ProjetC_from_lib
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: SPI_ProjetC_from_lib.axf

# Tool invocations
SPI_ProjetC_from_lib.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\NXP\MCUXpressoIDE_11.8.0_1165\workspace\peripherals_lib\flash" -L"C:\NXP\MCUXpressoIDE_11.8.0_1165\workspace\utilities_lib\flash" -Xlinker -Map="SPI_ProjetC_from_lib.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T SPI_ProjetC_from_lib_flash.ld -o "SPI_ProjetC_from_lib.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lperipherals_lib -lutilities_lib
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SPI_ProjetC_from_lib.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "SPI_ProjetC_from_lib.axf"; # arm-none-eabi-objcopy -v -O binary "SPI_ProjetC_from_lib.axf" "SPI_ProjetC_from_lib.bin" ; # checksum -p LPC804 -d "SPI_ProjetC_from_lib.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
