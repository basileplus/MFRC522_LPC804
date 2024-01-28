################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MCUXpresso_Retarget.c \
../src/MCUXpresso_cr_startup.c \
../src/MCUXpresso_crp.c \
../src/MCUXpresso_mtb.c \
../src/MFRC522Debug.c \
../src/MFRC522DriverSPI.c \
../src/MFRC522v2.c \
../src/Serial.c \
../src/lib_ENS_II1_lcd_v2.c \
../src/main.c \
../src/spi.c \
../src/system.c 

C_DEPS += \
./src/MCUXpresso_Retarget.d \
./src/MCUXpresso_cr_startup.d \
./src/MCUXpresso_crp.d \
./src/MCUXpresso_mtb.d \
./src/MFRC522Debug.d \
./src/MFRC522DriverSPI.d \
./src/MFRC522v2.d \
./src/Serial.d \
./src/lib_ENS_II1_lcd_v2.d \
./src/main.d \
./src/spi.d \
./src/system.d 

OBJS += \
./src/MCUXpresso_Retarget.o \
./src/MCUXpresso_cr_startup.o \
./src/MCUXpresso_crp.o \
./src/MCUXpresso_mtb.o \
./src/MFRC522Debug.o \
./src/MFRC522DriverSPI.o \
./src/MFRC522v2.o \
./src/Serial.o \
./src/lib_ENS_II1_lcd_v2.o \
./src/main.o \
./src/spi.o \
./src/system.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -DCR_INTEGER_PRINTF -D__USE_CMSIS -D__CODE_RED -DCORE_M0PLUS -D__MTB_DISABLE -D__MTB_BUFFER_SIZE=256 -D__REDLIB__ -DSDK_DEBUGCONSOLE=0 -I"C:\NXP\MCUXpressoIDE_11.8.0_1165\workspace\SPI_ProjetC_from_lib\inc" -I"C:\NXP\MCUXpressoIDE_11.8.0_1165\workspace\peripherals_lib\inc" -I"C:\NXP\MCUXpressoIDE_11.8.0_1165\workspace\utilities_lib\inc" -I"C:\NXP\MCUXpressoIDE_11.8.0_1165\workspace\common\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/MCUXpresso_Retarget.d ./src/MCUXpresso_Retarget.o ./src/MCUXpresso_cr_startup.d ./src/MCUXpresso_cr_startup.o ./src/MCUXpresso_crp.d ./src/MCUXpresso_crp.o ./src/MCUXpresso_mtb.d ./src/MCUXpresso_mtb.o ./src/MFRC522Debug.d ./src/MFRC522Debug.o ./src/MFRC522DriverSPI.d ./src/MFRC522DriverSPI.o ./src/MFRC522v2.d ./src/MFRC522v2.o ./src/Serial.d ./src/Serial.o ./src/lib_ENS_II1_lcd_v2.d ./src/lib_ENS_II1_lcd_v2.o ./src/main.d ./src/main.o ./src/spi.d ./src/spi.o ./src/system.d ./src/system.o

.PHONY: clean-src

