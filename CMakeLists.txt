#must existence
cmake_minimum_required(VERSION 3.5)
#####################################################################################################################################
#project_name
project(STM32CMAKE)
message(${CMAKE_PROJECT_NAME})
message(PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR})
enable_language(ASM)
set(CMAKE_SYSTEM_NAME Generic)          
set(CMAKE_SYSTEM_PROCESSOR arm)     
set(CMAKE_CROSSCOMPILING TRUE) 
#####################################################################################################################################       
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_STRIP "arm-none-eabi-strip")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
#####################################################################################################################################
#Suppress _CMake_ to compile and link with dynamic link
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
#####################################################################################################################################
#macro_definition
add_definitions(-DUSE_USB_FS)
#####################################################################################################################################
set(START_NAME_PATH User/Dep/startup_stm32f769xx.s)
message(START_NAME_PATH=${START_NAME_PATH})
set(LINK_NAME_PATH ${PROJECT_SOURCE_DIR}/User/Dep/STM32F769NIHx_FLASH.ld)
message(LINK_NAME_PATH=${LINK_NAME_PATH})
#####################################################################################################################################
set(ARCH_OPTION "-mthumb -mcpu=cortex-m7")
set(CODE_OPTION "-Os -ffunction-sections -fdata-sections -g")
#####################################################################################################################################
#set(S_OBJECT_OPTION ${ARCH_OPTION})
#message(S_OBJECT_OPTION=${S_OBJECT_OPTION})
set(C_OBJECT_OPTION "${ARCH_OPTION} ${CODE_OPTION}")
message(C_OBJECT_OPTION=${C_OBJECT_OPTION})
set(LINK_OPTION "${ARCH_OPTION} ${CODE_OPTION} -Wl,--gc-sections --specs=nosys.specs -Wl,-Map=${CMAKE_PROJECT_NAME}.map")
message(LINK_OPTION=${LINK_OPTION})
#####################################################################################################################################
#c/c++Compilation Options_Settings ----- Compile
set(CMAKE_C_FLAGS "${C_OBJECT_OPTION}") 
set(CMAKE_CXX_FLAGS "${C_OBJECT_OPTION}")
#####################################################################################################################################
#c/c++Link Options _ Settings ----------- Links
set(CMAKE_EXE_LINKER_FLAGS "${LINK_OPTION} -T${LINK_NAME_PATH}") 
#####################################################################################################################################
#header_files
include_directories(User/Inc
                    User/Src/device/Inc
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
aux_source_directory(User/Src/device/Src User_Src_device_Src)
#####################################################################################################################################
#add_static_library
add_library(HAL_static STATIC ${STM32F7xx_HAL_Driver_src})
add_library(USB_Core STATIC ${STM32_USB_Device_Library_Core_src})
add_library(USB_Class_CDC STATIC ${STM32_USB_Device_Library_Class_CDC_src})
#####################################################################################################################################
#merge_all_source_files
set(USER    ${STM32F7xx_HAL_Driver_src}
            ${STM32_USB_Device_Library_Core_src}
            ${STM32_USB_Device_Library_Class_CDC_src}
            ${User_src}
            ${User_Src_device_Src}
        )
#####################################################################################################################################
#exe_lists
add_executable(STM32CMAKE ${USER} ${START_NAME_PATH}) 
##################################################################################################################################### 
#link_static_library_to_target
target_link_libraries(STM32CMAKE HAL_static 
                                USB_Core
                                USB_Class_CDC
)
             
