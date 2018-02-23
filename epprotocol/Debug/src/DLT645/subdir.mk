################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DLT645/app645.c \
../src/DLT645/main645.c 

O_SRCS += \
../src/DLT645/app645.o \
../src/DLT645/main645.o 

OBJS += \
./src/DLT645/app645.o \
./src/DLT645/main645.o 

C_DEPS += \
./src/DLT645/app645.d \
./src/DLT645/main645.d 


# Each subdirectory must supply rules for building sources it contributes
src/DLT645/%.o: ../src/DLT645/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


