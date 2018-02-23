################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/epplib/PubFunctions.c \
../src/epplib/debug.c \
../src/epplib/pstring.c \
../src/epplib/safe.c 

OBJS += \
./src/epplib/PubFunctions.o \
./src/epplib/debug.o \
./src/epplib/pstring.o \
./src/epplib/safe.o 

C_DEPS += \
./src/epplib/PubFunctions.d \
./src/epplib/debug.d \
./src/epplib/pstring.d \
./src/epplib/safe.d 


# Each subdirectory must supply rules for building sources it contributes
src/epplib/%.o: ../src/epplib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


