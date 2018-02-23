################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/645/app645.c \
../src/645/main645.c 

OBJS += \
./src/645/app645.o \
./src/645/main645.o 

C_DEPS += \
./src/645/app645.d \
./src/645/main645.d 


# Each subdirectory must supply rules for building sources it contributes
src/645/%.o: ../src/645/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


