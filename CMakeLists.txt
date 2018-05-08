#must existence
cmake_minimum_required(VERSION 3.5)
#####################################################################################################################################
#project_name
project(STM32CMAKE)
enable_language(ASM)
#####################################################################################################################################
set(CMAKE_SYSTEM_NAME Generic)          
set(CMAKE_SYSTEM_PROCESSOR arm)     
set(CMAKE_CROSSCOMPILING TRUE)          
#####################################################################################################################################
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-c++")
set(CMAKE_STRIP "arm-none-eabi-strip")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
#####################################################################################################################################
#抑制_CMake_用动态链接来编译、链接
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
#####################################################################################################################################
set(START_NAME_PATH User/Dep/startup_stm32f769xx.s)
message(START_NAME_PATH=${START_NAME_PATH})
set(LINK_NAME_PATH /home/zxzhang/CPP/User/Dep/STM32F769NIHx_FLASH.ld)
message(LINK_NAME_PATH=${LINK_NAME_PATH})
set(CDEFINE -DUSE_USB_FS)
set(BUILD_PATH Build/)
message(BUILD_PATH=${BUILD_PATH})
#####################################################################################################################################
set(ARCH_OPTION "-mthumb -mcpu=cortex-m7")
set(CODE_OPTION "-Os -ffunction-sections -fdata-sections -g")
#####################################################################################################################################
#set(S_OBJECT_OPTION ${ARCH_OPTION})
#message(S_OBJECT_OPTION=${S_OBJECT_OPTION})
set(C_OBJECT_OPTION "${ARCH_OPTION} ${CODE_OPTION}")
message(C_OBJECT_OPTION=${C_OBJECT_OPTION})
set(LINK_OPTION "${ARCH_OPTION} ${CODE_OPTION} -Wl,--gc-sections --specs=nosys.specs -Wl,-Map=map.map")
message(LINK_OPTION=${LINK_OPTION})
#####################################################################################################################################
#c/c++编译选项_设置-----------编译
set(CMAKE_C_FLAGS ${C_OBJECT_OPTION}) #${CDEFINE})
#c/c++链接选项_设置-----------链接
set(CMAKE_EXE_LINKER_FLAGS "${LINK_OPTION} -T${LINK_NAME_PATH}") #${CDEFINE} -T${LINK_NAME_PATH})
#####################################################################################################################################
#header_files
include_directories(User/Inc
                    STM32F7xx_HAL_Driver/Inc
                    CMSIS/Device/ST/STM32F7xx/Include
                    CMSIS/Include
                    STM32_USB_Device_Library/Core/Inc
                    STM32_USB_Device_Library/Class/CDC/Inc
)
#####################################################################################################################################
#source_files
aux_source_directory(STM32F7xx_HAL_Driver/Src STM32F7xx_HAL_Driver_src)
aux_source_directory(STM32_USB_Device_Library/Core/Src STM32_USB_Device_Library_Core_src)
aux_source_directory(STM32_USB_Device_Library/Class/CDC/Src STM32_USB_Device_Library_Class_CDC_src)
aux_source_directory(User/Src User_src)

#merge_all_source_files
set(USER    ${STM32F7xx_HAL_Driver_src}
            ${STM32_USB_Device_Library_Core_src}
            ${STM32_USB_Device_Library_Class_CDC_src}
            ${User_src}
        )
#####################################################################################################################################
#exe_lists
#add_executable(STM32CMAKE   ${User_src}
#                            ${STM32F7xx_HAL_Driver_src} 
#                            ${STM32_USB_Device_Library_Core_src} 
#                            ${STM32_USB_Device_Library_Class_CDC_src} 
#                            ${START_NAME_PATH}
#                            )
#merge_all_files
add_executable(STM32CMAKE ${USER} ${START_NAME_PATH} ${LINK_NAME_PATH}) 
##################################################################################################################################### 
#cmake _shell 
execute_process(COMMAND  arm-none-eabi-objcopy -O binary STM32CMAKE cccc.bin)   
#####################################################################################################################################
#set(CMAKE_ASM_FLAGS  ${S_OBJECT_OPTION} ${START_NAME_PATH} -o Startup.o)
#set(CMAKE_C_FLAGS ${C_OBJECT_OPTION} ${STM32F7xx_HAL_Driver_src} ${STM32_USB_Device_Library_Core_src} ${STM32_USB_Device_Library_Class_CDC_src} ${User_src} ${CDEFINE})
#set(CMAKE_C_FLAGS ${LINK_OPTION} ${CDEFINE} -T${LINK_NAME_PATH} ${BUILD_PATH}*.o -o ${TARGET_NAME}.elf)
#####################################################################################################################################
                
#all:$(TARGET_NAME).elf $(TARGET_NAME).hex $(TARGET_NAME).bin
#	mkdir -p Obj
#	mv $(BUILD_PATH)$(TARGET_NAME).elf $(OBJECT_PATH)
#	mv $(BUILD_PATH)$(TARGET_NAME).hex $(OBJECT_PATH)
#	mv $(BUILD_PATH)$(TARGET_NAME).bin $(OBJECT_PATH)
#	mv $(BUILD_PATH)*.o $(OBJECT_PATH)
#	mv map.map $(OBJECT_PATH)

#$(TARGET_NAME).elf: $(START_NAME_PATH) $(SOURCE_NAME_PATH)
#	$(AS) $(S_OBJECT_OPTION) $(START_NAME_PATH) -o Startup.o
#	$(CC) $(C_OBJECT_OPTION) $(HEAD_PATH) $(SOURCE_NAME_PATH) $(CDEFINE)
#	$(CC) $(LINK_OPTION) $(CDEFINE) -T$(LINK_NAME_PATH) $(BUILD_PATH)*.o -o $(TARGET_NAME).elf

#$(TARGET_NAME).hex: $(TARGET_NAME).elf
#	$(OBJCOPY) $(HEX_OPTION) $(TARGET_NAME).elf $(TARGET_NAME).hex

#$(TARGET_NAME).bin: $(TARGET_NAME).elf
#	$(OBJCOPY) $(BIN_OPTION) $(TARGET_NAME).elf $(TARGET_NAME).bin
#clean: 
#	rm -rf Obj
#	rm -rf *.o
#	rm -rf *.map
#####################################################################################################################################
#set(linkFlags "-mcpu=cortex-m7 -mthumb -Os -ffunction-sections -fdata-sections -g -Wl,--gc-sections --specs=nosys.specs -Wl,-Map=map.map")
#set(CMAKE_C_FLAGS "-mthumb -mcpu=cortex-m0  -Wall -fsigned-char -fno-builtin  -ffunction-sections -O0 -g")    #设置编译选项
#set(CMAKE_EXE_LINKER_FLAGS "-static -Wl,-T -Xlinker ${PROJECT_SOURCE_DIR}/src/gnu.ld -u Default_Handler -nostartfiles -Wl,-Map -Xlinker -Wl,--gc-sections")        #设置链接选项
#set(CMAKE_ASM_FLAGS "-v")
#set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")
#set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")
#####################################################################################################################################
#set(CMAKE_C_FLAGS "-mthumb -mcpu=cortex-m7 -Os -ffunction-sections -fdata-sections -g -c -DUSE_USB_FS")
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-Map,map.map -Wl,--gc-sections")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-T${LINK_SCRIPT}")
#set(CMAKE_EXE_LINKER_FLAGS "-DUSE_USB_FS ${linkFlags} " " -TUser/Dep/STM32F769NIHx_FLASH.ld")
#####################################################################################################################################
