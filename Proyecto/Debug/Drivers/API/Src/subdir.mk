################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_ALARMA.c \
../Drivers/API/Src/API_BUZZER.c \
../Drivers/API/Src/API_Debounce.c \
../Drivers/API/Src/API_Delay.c \
../Drivers/API/Src/API_GPIO.c \
../Drivers/API/Src/API_LEDS.c \
../Drivers/API/Src/API_MOTOR.c \
../Drivers/API/Src/API_SM.c \
../Drivers/API/Src/API_US.c \
../Drivers/API/Src/ULTRASONICO.c 

OBJS += \
./Drivers/API/Src/API_ALARMA.o \
./Drivers/API/Src/API_BUZZER.o \
./Drivers/API/Src/API_Debounce.o \
./Drivers/API/Src/API_Delay.o \
./Drivers/API/Src/API_GPIO.o \
./Drivers/API/Src/API_LEDS.o \
./Drivers/API/Src/API_MOTOR.o \
./Drivers/API/Src/API_SM.o \
./Drivers/API/Src/API_US.o \
./Drivers/API/Src/ULTRASONICO.o 

C_DEPS += \
./Drivers/API/Src/API_ALARMA.d \
./Drivers/API/Src/API_BUZZER.d \
./Drivers/API/Src/API_Debounce.d \
./Drivers/API/Src/API_Delay.d \
./Drivers/API/Src/API_GPIO.d \
./Drivers/API/Src/API_LEDS.d \
./Drivers/API/Src/API_MOTOR.d \
./Drivers/API/Src/API_SM.d \
./Drivers/API/Src/API_US.d \
./Drivers/API/Src/ULTRASONICO.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Fabrizzio/STM32CubeIDE/workspace_1.16.1/Proyecto/Drivers/API/Src" -I"C:/Users/Fabrizzio/STM32CubeIDE/workspace_1.16.1/Proyecto/Drivers/API/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_ALARMA.cyclo ./Drivers/API/Src/API_ALARMA.d ./Drivers/API/Src/API_ALARMA.o ./Drivers/API/Src/API_ALARMA.su ./Drivers/API/Src/API_BUZZER.cyclo ./Drivers/API/Src/API_BUZZER.d ./Drivers/API/Src/API_BUZZER.o ./Drivers/API/Src/API_BUZZER.su ./Drivers/API/Src/API_Debounce.cyclo ./Drivers/API/Src/API_Debounce.d ./Drivers/API/Src/API_Debounce.o ./Drivers/API/Src/API_Debounce.su ./Drivers/API/Src/API_Delay.cyclo ./Drivers/API/Src/API_Delay.d ./Drivers/API/Src/API_Delay.o ./Drivers/API/Src/API_Delay.su ./Drivers/API/Src/API_GPIO.cyclo ./Drivers/API/Src/API_GPIO.d ./Drivers/API/Src/API_GPIO.o ./Drivers/API/Src/API_GPIO.su ./Drivers/API/Src/API_LEDS.cyclo ./Drivers/API/Src/API_LEDS.d ./Drivers/API/Src/API_LEDS.o ./Drivers/API/Src/API_LEDS.su ./Drivers/API/Src/API_MOTOR.cyclo ./Drivers/API/Src/API_MOTOR.d ./Drivers/API/Src/API_MOTOR.o ./Drivers/API/Src/API_MOTOR.su ./Drivers/API/Src/API_SM.cyclo ./Drivers/API/Src/API_SM.d ./Drivers/API/Src/API_SM.o ./Drivers/API/Src/API_SM.su ./Drivers/API/Src/API_US.cyclo ./Drivers/API/Src/API_US.d ./Drivers/API/Src/API_US.o ./Drivers/API/Src/API_US.su ./Drivers/API/Src/ULTRASONICO.cyclo ./Drivers/API/Src/ULTRASONICO.d ./Drivers/API/Src/ULTRASONICO.o ./Drivers/API/Src/ULTRASONICO.su

.PHONY: clean-Drivers-2f-API-2f-Src

