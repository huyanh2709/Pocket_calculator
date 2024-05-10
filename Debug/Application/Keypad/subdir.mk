################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Keypad/keypad.c 

OBJS += \
./Application/Keypad/keypad.o 

C_DEPS += \
./Application/Keypad/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Keypad/%.o Application/Keypad/%.su Application/Keypad/%.cyclo: ../Application/Keypad/%.c Application/Keypad/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32 cube/stm32f1_register/Keypad_calculator/Application/LCD" -I"D:/STM32 cube/stm32f1_register/Keypad_calculator/Application/Keypad" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-Keypad

clean-Application-2f-Keypad:
	-$(RM) ./Application/Keypad/keypad.cyclo ./Application/Keypad/keypad.d ./Application/Keypad/keypad.o ./Application/Keypad/keypad.su

.PHONY: clean-Application-2f-Keypad

