/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_adc16.h"
#include "fsl_dac.h"

#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 4000000; ++i) // ~ 1 Hz
    {
        __asm("NOP"); /* delay */
    }
}


struct gpiotest {
	GPIO_Type *base;
	uint8_t pin_ix;
	PORT_Type *port;
	clock_ip_name_t clock;
};

void
toggle(struct gpiotest *g)
{
	GPIO_TogglePinsOutput(g->base, 1 << g->pin_ix);
}

static const gpio_pin_config_t gpio_output_config = {
	.pinDirection = kGPIO_DigitalOutput,
	.outputLogic = 0,
};
//static const port_pin_config_t pin_output_config = {
//	.mux = kPORT_MuxAsGpio;
//};
void
init_gpio(struct gpiotest *g)
{
	CLOCK_EnableClock(g->clock);
	PORT_SetPinMux(g->port, g->pin_ix, kPORT_MuxAsGpio);
	//PORT_SetPinConfig(g->port, g->pin_ix, &pin_output_config);
	GPIO_PinInit(g->base, g->pin_ix, &gpio_output_config);
}

#define GPIO_LINE(port, ix) {GPIO ## port , ix , PORT ## port, kCLOCK_Port ## port }

struct gpiotest gpios[] = {
	/** V2 Board **/
	/** J4 header **/
	GPIO_LINE(D, 4), // Pin 8, UART0_RTS_b, SPI1_PCS0
	GPIO_LINE(D, 5), // Pin 7, UART0_CTS_b / UART0_COL_b, SPI1_SCK, ADC0_SE6b
	GPIO_LINE(D, 6), // Pin 6, UART0_RX, SPI1_SOUT, ADC0_SE7b
	GPIO_LINE(D, 7), // Pin 5, UART0_TX, SPI1_SIN
	GPIO_LINE(A, 10), // Pin 4
	GPIO_LINE(A, 11), // Pin 3
	GPIO_LINE(E, 24), // Pin 2, CAN1_TX, UART4_TX, I2C0_SCL
	GPIO_LINE(E, 12), // Pin 1

	/** J6 header **/
	GPIO_LINE(A, 7), // Pin 8
	GPIO_LINE(C, 1), // Pin 7, ADC0_SE15, UART1_RTS_b
	GPIO_LINE(A, 8), // Pin 6, ADC0_SE11
	GPIO_LINE(C, 8), // Pin 5, ADC1_SE4b
	GPIO_LINE(A, 4), // Pin 4
	GPIO_LINE(A, 17), // Pin 3, ADC1_SE17, UART0_RTS_b
	GPIO_LINE(D, 11), // Pin 2
	GPIO_LINE(D, 12), // Pin 1

	/** Pressure Sensors **/
	/** U3 header **/
	GPIO_LINE(B, 5), // ADC1_SE11
	/** U4 header **/
	GPIO_LINE(B, 6), // ADC1_SE12
	/** U5 header **/
	GPIO_LINE(B, 7), // ADC1_SE13
	/** U6 header **/
	GPIO_LINE(B, 10), // ADC1_SE14
	/** U8 header **/
	GPIO_LINE(E, 25), // ADC0_SE18
	/** U9 header **/
	// No GPIO, ADC1_SE18
	/** U10 header **/
	// No GPIO, ADC1_DP0, ADC0_DP3
	/** U11 header **/
	// No GPIO, ADC0_DM0, ADC1_DM3

	/** J8 header **/
	GPIO_LINE(C, 11), // Pin 1, I2C1_SDA, ADC1_SE7b
	GPIO_LINE(C, 10), // Pin 4, I2C1_SCL, ACD1_SE6b
	GPIO_LINE(C, 9), // Pin 7, ADC1_SE5b / CMP0_IN3

	/** J15 header **/
	GPIO_LINE(A, 12), // Pin 2, CAN0_TX
	GPIO_LINE(A, 13), // Pin 3, CAN0_RX

	/** J14 header **/
	GPIO_LINE(E, 2), // Pin 1, SDHC0_DCLK, ADC1_SE6a
	GPIO_LINE(E, 1), // Pin 2, DSHC0_D0, ADC1_SE5a
	GPIO_LINE(E, 3), // Pin 3, SDHC0_CMD, ADC1_SE7a
	GPIO_LINE(E, 4), // Pin 4, DSHC0_D3

	/** J3 header **/
	GPIO_LINE(A, 15), // Pin 2
	GPIO_LINE(A, 14), // Pin 3

	/** J9 header **/
	GPIO_LINE(B, 18), // Pin 1, CAN0_TX
	GPIO_LINE(B, 19), // Pin 2, CAN0_RX
	GPIO_LINE(B, 20), // Pin 3, SPI2_PCS0
	GPIO_LINE(B, 21), // Pin 4, SPI2_SCK
	GPIO_LINE(B, 22), // Pin 5, SPI2_SOUT
	GPIO_LINE(B, 23), // Pin 6, SPI2_SIN
	GPIO_LINE(C, 0), // Pin 7, ADC0_SE14

	/** J22 header **/
	GPIO_LINE(B, 11), // Pin 2, ADC1_SE15
	// No GPIO on Pin 3, ADC1_SE16, ADC0_SE22

	/** J20 header **/
	/***** Power ****/

	/** J10 header **/
	/*** To motor ***/

	/** U7 header **/
	GPIO_LINE(B, 1), // Pin 22
	GPIO_LINE(B, 0), // Pin 21
	GPIO_LINE(B, 2), // Pin 20
	GPIO_LINE(B, 3), // Pin 19
	// No GPIO, ADC1_SE23
	GPIO_LINE(B, 4), // Pin 25

    // V1
    /*
	//+++ J16 header +++
	GPIO_LINE(D, 6), // 1
	//GND 2
	GPIO_LINE(D, 4), // 3
	GPIO_LINE(D, 5), // 4
	GPIO_LINE(C, 6), // 5
	GPIO_LINE(C, 9), // 6
	GPIO_LINE(A, 4), // 7
	GPIO_LINE(C, 0), // 8
	GPIO_LINE(B, 1), // 9
	GPIO_LINE(C, 1), //10
	//GND 11
	GPIO_LINE(A, 8), // 12
	GPIO_LINE(B, 4), // 13
	GPIO_LINE(B, 3), // 14
	GPIO_LINE(B, 11), // 15
	GPIO_LINE(B, 10), // 16
	GPIO_LINE(B, 6), // 17
	GPIO_LINE(B, 7), // 18
	GPIO_LINE(B, 2), // 19
	GPIO_LINE(B, 5), // 20
	GPIO_LINE(B, 0), // 21
	GPIO_LINE(A, 11), // 22
	GPIO_LINE(A, 13), // 23
	GPIO_LINE(A, 14), // 24
	GPIO_LINE(A, 17), // 25
	GPIO_LINE(A, 15), // 26
	GPIO_LINE(A, 10), // 27
	//GND 28
	GPIO_LINE(E, 25), // 29
	GPIO_LINE(A, 12), // 30
	//ADC1_SE18 31 does not have a GPIO TODO
	GPIO_LINE(A, 7), // 32
	//ADC1_SE16 33 does not have a GPIO TODO
	GPIO_LINE(E, 24), // 34
	//ADC1_DP0 35 does not have a GPIO TODO
	//ADC0_SE16 36 does not have a GPIO TODO
	//ADC0_DM0 37 does not have a GPIO TODO
	//ADC1_DM0 38 does not have a GPIO TODO
	//GND 39
	//RST_TGT_MCU 40
	
	//+++ J17 Header +++
	GPIO_LINE(D, 11), // PTD11 1			
	//GND 2			
	GPIO_LINE(D, 12), // PTD12 3			
	GPIO_LINE(C, 14), // PTC14 4			
	GPIO_LINE(D, 9), // I2C0_SDA		PTD9	PTD9
	GPIO_LINE(C, 4), // FTM0_CH3		PTC4	PTC4
	GPIO_LINE(D, 8), // I2C0_SCL		PTD8	PTD8
	GPIO_LINE(C, 11), // I2C1_SDA		PTC11	PTC11
	GPIO_LINE(D, 7), // PTD7			
	GPIO_LINE(C, 10), // I2C1_SCL		PTC10	PTC10
	GPIO_LINE(C, 15), // PTC15			
	GPIO_LINE(C, 3), // FTM0_CH2		PTC3	PTC3
	//GND 13
	GPIO_LINE(C, 2), // FTM0_CH1		PTC2	PTC2
	GPIO_LINE(B, 21), //PTB21			
	GPIO_LINE(B, 23), //PTB23			
	GPIO_LINE(B, 20), //PTB20			
	GPIO_LINE(B, 22), //PTB22			
	GPIO_LINE(B, 18), //PTB18			
	GPIO_LINE(B, 19), //PTB19			
	GPIO_LINE(E, 2), //SDHC0_DCLK		PTE2	PTE2
	GPIO_LINE(D, 10), //SD_CARD_DETECT		PTD10	PTD10
	GPIO_LINE(E, 0), //SDHC0_D1		PTE0	PTE0
	GPIO_LINE(E, 1), //SDHC0_D0		PTE1	PTE1
	GPIO_LINE(E, 4), //SDHC0_D3		PTE4	PTE4
	GPIO_LINE(E, 3), //SDHC0_CMD		PTE3	PTE3
	GPIO_LINE(E, 6), //PTE6			
	GPIO_LINE(E, 5), //SDHC0_D2		PTE5	PTE5
	GPIO_LINE(E, 8), //PTE8			
	GPIO_LINE(E, 7), //PTE7			
	GPIO_LINE(E, 11), //PTE11			
	GPIO_LINE(E, 12), //PTE12			
	GPIO_LINE(C, 17), //CAN0_H		PTC17	PTC17
	GPIO_LINE(C, 16), //CAN0_L		PTC16	PTC16
	//DAC0_OUT_RC 35 TODO no gpio line
	//DAC1_OUT_RC 36 TODO no gpio line
	GPIO_LINE(E, 26), //PTE26			
	GPIO_LINE(E, 28), //PTE28			
	//GND 39			
	GPIO_LINE(A, 4), // PA3 40 TODO is this PTA3 or PA3? no PA3 in datasheet
    */
};

#define GPIO_NUM (sizeof(gpios)/sizeof(gpios[0]))

void
gpio_init(void *pvParams)
{
	//initialize all the gpios
	//every so often blink them
	for (int i = 0; i < GPIO_NUM; i++) {
		init_gpio(&gpios[i]);
	}
}

void
gpio_step(void)
{
	for (int i = 0; i < GPIO_NUM; i++) {
		toggle(&gpios[i]);
	}
}

//TODO ADC and DAC

struct adctest {
	ADC_Type *base;
	uint8_t adcix;
	unsigned int channelgroup;
	unsigned int channelNumber;
	int16_t last_result;
	adc16_channel_config_t adc16ChannelConfigStruct;
	bool isDiff;
};
//TODO spit ADC over serial port
//adcs that do not have a GPIO TODO
/*	name	qmax pin #	adc	adc channel
	//ADC1_SE18 31	1	
	//ADC1_SE16 33	1	
	//ADC1_DP0 35	1	
	//ADC0_SE16 36	0	
	//ADC0_DM0 37	0	
	//ADC1_DM0 38	1	
*/

struct adctest adcs[] = {
	{ADC1, 1, 0, 18, 0, 0, 0},
	{ADC1, 1, 0, 16, 0, 0, 0},
	//{ADC1, 0, 0}, // TODO DP0
	{ADC0, 0, 0, 16, 0, 0, 0},
	//{ADC0, 0, 18}, // 1 DM0
	//{ADC1, 0, 18}, // 1 DM0
	//ADC!_CM0 and DP0 are channel 0 with diff enabled
	{ADC1, 1, 0, 0, 0, 0, 1},
};

adc16_config_t adc16ConfigStructs[2];

#define ADC_NUM (sizeof(adcs)/sizeof(adcs[0]))

void
adc_init(void)
{

	//TODO initialize all the ADCs
	//adc16_config_t adc16ConfigStructs[2];
	/*
	 * adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
	 * adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
	 * adc16ConfigStruct.enableAsynchronousClock = true;
	 * adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
	 * adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;
	 * adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
	 * adc16ConfigStruct.enableHighSpeed = false;
	 * adc16ConfigStruct.enableLowPower = false;
	 * adc16ConfigStruct.enableContinuousConversion = false;
	 */
	ADC16_GetDefaultConfig(&adc16ConfigStructs[0]);
	ADC16_GetDefaultConfig(&adc16ConfigStructs[1]);
#ifdef BOARD_ADC_USE_ALT_VREF
	adc16ConfigStruct[0].referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
	adc16ConfigStruct[1].referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif    
	ADC16_Init(ADC0, &adc16ConfigStructs[0]);
	ADC16_Init(ADC1, &adc16ConfigStructs[1]);
	ADC16_EnableHardwareTrigger(ADC0, false); /* Make sure the software trigger is used. */
	ADC16_EnableHardwareTrigger(ADC1, false); /* Make sure the software trigger is used. */
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
	if (kStatus_Success == ADC16_DoAutoCalibration(ADC0)) {
		//PRINTF("ADC16_DoAutoCalibration() 0 Done.\r\n");
	} else {
		//PRINTF("ADC16_DoAutoCalibration() 0 Failed.\r\n");
	}
	if (kStatus_Success == ADC16_DoAutoCalibration(ADC1)) {
		//PRINTF("ADC16_DoAutoCalibration() 1 Done.\r\n");
	} else {
		//PRINTF("ADC16_DoAutoCalibration() 1 Failed.\r\n");
	}
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
	
	
	for (int i = 0; i < ADC_NUM; i++) {
    //adcs[i].adc16_channel_config_t adc16ChannelConfigStruct;

    //PRINTF("\r\nADC16 polling Example.\r\n");

    

    adcs[i].adc16ChannelConfigStruct.channelNumber = adcs[i].channelNumber;
    adcs[i].adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adcs[i].adc16ChannelConfigStruct.enableDifferentialConversion = adcs[i].isDiff;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
	}
}
void
adc_step(void)
{
	//read one value from each ADC
	// foreach adc, also store last value
	for (int i = 0; i < ADC_NUM; i++) {
        /*
         When in software trigger mode, each conversion would be launched once calling the "ADC16_ChannelConfigure()"
         function, which works like writing a conversion command and executing it. For another channel's conversion,
         just to change the "channelNumber" field in channel's configuration structure, and call the
         "ADC16_ChannelConfigure() again.
        */
        ADC16_SetChannelConfig(adcs[i].base, adcs[i].channelgroup, &adcs[i].adc16ChannelConfigStruct);
        while (0U == (kADC16_ChannelConversionDoneFlag &
                      ADC16_GetChannelStatusFlags(adcs[i].base, adcs[i].channelgroup)))
        {
        }
		adcs[i].last_result = ADC16_GetChannelConversionValue(adcs[i].base, adcs[i].channelgroup);
        //PRINTF("ADC %02d Value: %d\r\n", i, adcs[i].last_result);
    }
}
//TODO control DAC based on ADC reading

struct dactest {
	DAC_Type *base;
	dac_config_t cfg;
	uint8_t source_adc;
};
//DACs
//DAC0_OUT
//DAC1_OUT

struct dactest dacs[2] = {
	{DAC0, {kDAC_ReferenceVoltageSourceVref1, 0}, 1},
	{DAC1, {kDAC_ReferenceVoltageSourceVref1, 0}, 1},
};

#define DAC_NUM (sizeof(dacs)/sizeof(dacs[0]))

void
dac_init(void)
{
	for (int i = 0; i < DAC_NUM; i++) {
    /* Configure the DAC. */
    /*
     * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
     * dacConfigStruct.enableLowPowerMode = false;
     */
    DAC_GetDefaultConfig(&dacs[i].cfg);
    DAC_Init(dacs[i].base, &dacs[i].cfg);
    DAC_Enable(dacs[i].base, true);             /* Enable output. */
    DAC_SetBufferReadPointer(dacs[i].base, 0U); /* Make sure the read pointer to the start. */
                                                     /*
                                                     * The buffer is not enabled, so the read pointer can not move automatically. However, the buffer's read pointer
                                                     * and itemss can be written manually by user.
                                                     */
	}
}

void
dac_step(void)
{
	for (int i = 0; i < DAC_NUM; i++) {
		//dacmax = 0xFFFU;
		DAC_SetBufferValue(dacs[i].base, 0U, adcs[dacs[i].source_adc].last_result);
	}
}

/*
struct pwmtest {
	
};

struct pwmtest pwms[] = {
	PTB1_RC		PTB1	PTB1	TPM1_CH1
	PTA8_RC		PTA8	PTA8	TPM1_CH0
	PTB0_RC		PTB0	PTB0	TPM1_CH0
	PTA11_RC	PTA11	PTA11	TPM2_CH1
	PTA13_RC	PTA13	PTA13	TPM1_CH1
	PTA10_RC	PTA10	PTA10	TPM2_CH0
	PTA12_RC	PTA12	PTA12	TPM1_CH0
}
#define PWM_NUM (sizeof(pwms)/sizeof(pwms[0]))
*/
/*!
 * @brief Main function
 */
int main(void)
{
	/* Board pin, clock, debug console init */
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	gpio_init(NULL);
	adc_init();
	dac_init();

	for (;;) {
		gpio_step();
		adc_step();
		dac_step();
		delay();
	}
}
