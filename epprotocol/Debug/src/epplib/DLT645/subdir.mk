################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/epplib/DLT645/app645.c \
../src/epplib/DLT645/main645.c 

OBJS += \
./src/epplib/DLT645/app645.o \
./src/epplib/DLT645/main645.o 

C_DEPS += \
./src/epplib/DLT645/app645.d \
./src/epplib/DLT645/main645.d 


# Each subdirectory must supply rules for building sources it contributes
src/epplib/DLT645/%.o: ../src/epplib/DLT645/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


