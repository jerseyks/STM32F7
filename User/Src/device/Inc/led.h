#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

typedef enum 
{

    STM32_LED1 = 0,
    STM32_LED1_RED = STM32_LED1,
    STM32_LED2 = 1,
    STM32_LED2_GREEN = STM32_LED2,
    STM32_LED3 = 2,
    STM32_LED3_BLUE = STM32_LED3

}STM32_LED_TypeDef;




#define STM32_LED1_GPIO_PORT                   GPIOB
#define STM32_LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define STM32_LED1_PIN                         GPIO_PIN_1

#define STM32_LED2_GPIO_PORT                   GPIOC
#define STM32_LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define STM32_LED2_PIN                         GPIO_PIN_6

#define STM32_LED3_GPIO_PORT                   GPIOC
#define STM32_LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define STM32_LED3_PIN                         GPIO_PIN_7


#ifdef __cplusplus
}
#endif

#endif/*__LED_H*/