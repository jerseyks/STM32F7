#include "led.h"

const uint32_t STM32_GPIO_PIN[ledn] = {STM32_LED1_PIN,STM32_LED2_PIN,STM32_LED3_PIN};

class Led
{
    public:
        void STM32_LED_Init(STM32_LED_TypeDef led)
        {
            GPIO_InitTypeDef  gpio_init_structure;
            GPIO_TypeDef*     gpio_led;

            if ((led == STM32_LED1) || (led == STM32_LED2) || (led == STM32_LED3))
            {
                if (led == STM32_LED1)
                {
                    gpio_led = STM32_LED1_GPIO_PORT;
                    STM32_LED1_GPIO_CLK_ENABLE();
                }
                else 
                    if(led == STM32_LED2)
                    {
                        gpio_led = STM32_LED2_GPIO_PORT;
                        STM32_LED2_GPIO_CLK_ENABLE();
                    }
                    else
                    {
                        gpio_led = STM32_LED3_GPIO_PORT;
                        STM32_LED3_GPIO_CLK_ENABLE();    
                    }

                gpio_init_structure.Pin = STM32_GPIO_PIN[led];
                gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
                gpio_init_structure.Pull = GPIO_PULLUP;
                gpio_init_structure.Speed = GPIO_SPEED_HIGH;
            
                HAL_GPIO_Init(gpio_led, &gpio_init_structure);
                
                HAL_GPIO_WritePin(gpio_led, STM32_GPIO_PIN[led], GPIO_PIN_SET);
            }
        };
        void STM32_LED_On(STM32_LED_TypeDef led)
        {
            GPIO_TypeDef*     gpio_led;

            if ((led == STM32_LED1) || (led == STM32_LED2) || (led == STM32_LED3))
            {
                if (led == STM32_LED1)
                {
                    gpio_led = STM32_LED1_GPIO_PORT;
                }
               else 
                    if(led == STM32_LED2)
                    {
                        gpio_led = STM32_LED2_GPIO_PORT;
                    }
                    else
                    {
                        gpio_led = STM32_LED3_GPIO_PORT;   
                    }
                HAL_GPIO_WritePin(gpio_led, STM32_GPIO_PIN[led], GPIO_PIN_RESET);
            }

        };
        void STM32_LED_Off(STM32_LED_TypeDef led)
        {
            GPIO_TypeDef*     gpio_led;

            if ((led == STM32_LED1) || (led == STM32_LED2) || (led == STM32_LED3))
            {
                if (led == STM32_LED1)
                {
                    gpio_led = STM32_LED1_GPIO_PORT;
                }
               else 
                    if(led == STM32_LED2)
                    {
                        gpio_led = STM32_LED2_GPIO_PORT;
                    }
                    else
                    {
                        gpio_led = STM32_LED3_GPIO_PORT;   
                    }
                HAL_GPIO_WritePin(gpio_led, STM32_GPIO_PIN[led], GPIO_PIN_SET);
            }

        };
        void STM32_LED_Toggle(void)
        {
            GPIO_TypeDef*     gpio_led;

            if ((led == STM32_LED1) || (led == STM32_LED2) || (led == STM32_LED3))
            {
                if (led == STM32_LED1)
                {
                    gpio_led = STM32_LED1_GPIO_PORT;
                }
                else 
                    if(led == STM32_LED2)
                    {
                        gpio_led = STM32_LED2_GPIO_PORT;
                    }
                    else
                    {
                        gpio_led = STM32_LED3_GPIO_PORT;   
                    }       
                HAL_GPIO_TogglePin(gpio_led, STM32_GPIO_PIN[led]);
            }
        };
};

Led deng;



