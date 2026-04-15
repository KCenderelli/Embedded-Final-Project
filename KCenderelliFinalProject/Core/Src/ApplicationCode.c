/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */

extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#if TOUCH_INTERRUPT_ENABLED == 1
static EXTI_HandleTypeDef LCDTouchIRQ;
void LCDTouchScreenInterruptGPIOInit(void);
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

RNG_HandleTypeDef hrng;
TIM_HandleTypeDef Timer7_handle;
GPIO_InitTypeDef Button;

volatile uint8_t resetRequested = 0;

static uint32_t buttonPressStart = 0;
static uint8_t buttonActive = 0;

void ApplicationInit(void)
{
	__HAL_RCC_TIM7_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef ButtonConfig = {0};
	ButtonConfig.Pin = GPIO_PIN_0;
	ButtonConfig.Mode = GPIO_MODE_IT_RISING_FALLING;
	ButtonConfig.Pull = GPIO_PULLDOWN;
	ButtonConfig.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &ButtonConfig);

	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#if TOUCH_INTERRUPT_ENABLED == 1
	LCDTouchScreenInterruptGPIOInit();
	#endif // TOUCH_INTERRUPT_ENABLED

	#endif // COMPILE_TOUCH_FUNCTIONS
	__HAL_RCC_RNG_CLK_ENABLE();
	hrng.Instance = RNG;
	HAL_RNG_Init(&hrng);
}


void processTouchIfPending(void)
{
    if(touchPending == 1)
    {
        touchPending = 0;
        HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);

        uint8_t fifoSize = 0;
        while(fifoSize == 0)
        {
            fifoSize = ReadRegisterFromTouchModule(STMPE811_FIFO_SIZE);
        }

        uint16_t x = 0;
        uint16_t y = 0;

        for(int i = 0; i < fifoSize; i++)
        {
            DetermineTouchPosition(&StaticTouchData);
            if(StaticTouchData.y != 0 && StaticTouchData.x < 230)
            {
                x = StaticTouchData.x;
                y = StaticTouchData.y;
            }
        }

        WriteDataToTouchModule(STMPE811_FIFO_STA, 0x01);
        WriteDataToTouchModule(STMPE811_FIFO_STA, 0x00);

        HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

        if(y == 0 || x == 0) return;

        static uint32_t lastTouchTime = 0;
        uint32_t now = HAL_GetTick();
        if(now - lastTouchTime < 300) return;
        lastTouchTime = now;

        static uint16_t lastX = 0;
        static uint16_t lastY = 0;
        int16_t dx = (int16_t)x - (int16_t)lastX;
        int16_t dy = (int16_t)y - (int16_t)lastY;
        if(dx < 0) dx = -dx;
        if(dy < 0) dy = -dy;
        if(dx < 10 && dy < 10)
        {
            lastTouchTime = now;
            return;
        }
        lastX = x;
        lastY = y;

        printf("\nX: %03d\nY: %03d\n", x, y);
        TouchLogic(x, y);
    }
}


void LCD_Visual_Demo(void)
{
	visualDemo();
}


void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	printf("EXTI triggered\n");
    if(GPIO_Pin != GPIO_PIN_0)
        return;
    uint8_t pressed = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    if(pressed == 0)  // <-- pressed (ACTIVE LOW)
    {
        buttonPressStart = HAL_GetTick();
        buttonActive = 1;
    }
    else  // released
    {
        if(buttonActive)
        {
            uint32_t elapsed = HAL_GetTick() - buttonPressStart;

            if(elapsed >= 1000)
            {
            	resetRequested = 1;
            }
        }

        buttonActive = 0;
    }
}


#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(LCD_COLOR_GREEN);
	while (1) {
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(LCD_COLOR_RED);
		} else {
			printf("Not Pressed\n\n");
			LCD_Clear(LCD_COLOR_GREEN);
		}
	}
}


// TouchScreen Interrupt
#if TOUCH_INTERRUPT_ENABLED == 1

void LCDTouchScreenInterruptGPIOInit(void)
{
	GPIO_InitTypeDef LCDConfig = {0};
    LCDConfig.Pin = GPIO_PIN_15;
    LCDConfig.Mode = GPIO_MODE_IT_FALLING;
    LCDConfig.Pull = GPIO_NOPULL;
    LCDConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    
    // Clock enable
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // GPIO Init      
    HAL_GPIO_Init(GPIOA, &LCDConfig);

    // Interrupt Configuration
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	LCDTouchIRQ.Line = EXTI_LINE_15;

}

#define TOUCH_DETECTED_IRQ_STATUS_BIT   (1 << 0)  // Touchscreen detected bitmask

static uint8_t statusFlag;

void EXTI15_10_IRQHandler()
{
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // May consider making this a universial interrupt guard
	bool isTouchDetected = false;

	// Disable touch interrupt bit on the STMPE811
	uint8_t currentIRQEnables = ReadRegisterFromTouchModule(STMPE811_INT_EN);
	WriteDataToTouchModule(STMPE811_INT_EN, 0x00);

	// Clear the interrupt bit in the STMPE811
	statusFlag = ReadRegisterFromTouchModule(STMPE811_INT_STA);
	uint8_t clearIRQData = (statusFlag | TOUCH_DETECTED_IRQ_STATUS_BIT); // Write one to clear bit
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);
	
	uint8_t ctrlReg = ReadRegisterFromTouchModule(STMPE811_TSC_CTRL);
//	if (ctrlReg & 0x80)
//	{
//		isTouchDetected = true;
//	}
	uint8_t fifoSize = ReadRegisterFromTouchModule(STMPE811_FIFO_SIZE);
	if((ctrlReg & 0x80) && fifoSize > 0)
	{
	    isTouchDetected = true;
	}


	// Determine if it is pressed or unpressed
	if(isTouchDetected) // Touch has been detected
	{
		touchPending = 1;
//		printf("\nPressed");

	}
	else{
		/* Touch not pressed */
//		printf("\nNot pressed \n");
	}

	// Re-enable IRQs
    WriteDataToTouchModule(STMPE811_INT_EN, currentIRQEnables);
	HAL_EXTI_ClearPending(&LCDTouchIRQ, EXTI_TRIGGER_FALLING);

	HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	//Potential ERRATA? Clearing IRQ bit again due to an IRQ being triggered DURING the handling of this IRQ..
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);

}
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

