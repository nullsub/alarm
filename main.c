#include "board.h"
#include "uart.h"
#include "pio/pio.h"

#define Buffer_size 10
#define DISPLAY_NR_PINS 14

/// LED #0 pin definition (PA0).
#define DISPLAY_PIN_0   {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_1   {1 << 1, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_2   {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_3   {1 << 3, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_4   {1 << 4, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_5   {1 << 5, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_6   {1 << 6, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_7   {1 << 7, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_8   {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_9   {1 << 9, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_10   {1 << 10, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_11   {1 << 11, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_12   {1 << 12, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PIN_13   {1 << 13, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define DISPLAY_PINS    DISPLAY_PIN_0, DISPLAY_PIN_1, DISPLAY_PIN_2, DISPLAY_PIN_3, DISPLAY_PIN_4, DISPLAY_PIN_5, DISPLAY_PIN_6, DISPLAY_PIN_7, DISPLAY_PIN_8, DISPLAY_PIN_9, DISPLAY_PIN_10, DISPLAY_PIN_11,  DISPLAY_PIN_12, DISPLAY_PIN_13 

static const Pin display_pins[] = {DISPLAY_PINS};

void init_display()
{
	PIO_Configure(display_pins, DISPLAY_NR_PINS);
}

void device_init()
{
	//USART0Setup();

	// First, enable the clock of the PIO
	//AT91F_PMC_EnablePeriphClock ( AT91C_BASE_PMC, 1 << AT91C_ID_PIOA );
	// then, we configure the PIO Lines corresponding to LED1 to LED4
	// to be outputs. No need to set these pins to be driven by the PIO because it is GPIO pins only.
	//AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, LED_MASK );
	//USART_puts("Device init\n");
}

#define AI_STEP 5
#define PONG_STEP 5

int main(void) {
	device_init();
	init_display();

	PIO_Set(&display_pins[0]);
	PIO_Clear(&display_pins[1]);
	PIO_Clear(&display_pins[2]);
	PIO_Set(&display_pins[3]);
	while(1){

	}
}

