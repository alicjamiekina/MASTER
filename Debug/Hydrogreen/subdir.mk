################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hydrogreen/horn.c \
../Hydrogreen/hydrogensensor.c \
../Hydrogreen/hydrogreen.c \
../Hydrogreen/interrupt.c \
../Hydrogreen/measurements.c \
../Hydrogreen/rs485EF.c \
../Hydrogreen/rs485SW.c \
../Hydrogreen/rxinterrupt.c \
../Hydrogreen/timers.c \
../Hydrogreen/watchdog.c 

OBJS += \
./Hydrogreen/horn.o \
./Hydrogreen/hydrogensensor.o \
./Hydrogreen/hydrogreen.o \
./Hydrogreen/interrupt.o \
./Hydrogreen/measurements.o \
./Hydrogreen/rs485EF.o \
./Hydrogreen/rs485SW.o \
./Hydrogreen/rxinterrupt.o \
./Hydrogreen/timers.o \
./Hydrogreen/watchdog.o 

C_DEPS += \
./Hydrogreen/horn.d \
./Hydrogreen/hydrogensensor.d \
./Hydrogreen/hydrogreen.d \
./Hydrogreen/interrupt.d \
./Hydrogreen/measurements.d \
./Hydrogreen/rs485EF.d \
./Hydrogreen/rs485SW.d \
./Hydrogreen/rxinterrupt.d \
./Hydrogreen/timers.d \
./Hydrogreen/watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
Hydrogreen/%.o: ../Hydrogreen/%.c Hydrogreen/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

