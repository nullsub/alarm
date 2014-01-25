#include "board.h"
#include "pio/pio.h"
#include "uart.h"
#include "display.h"

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
	display_init();
	unsigned int   loop_count ;
	AT91PS_AIC     pAic;
	//* Load System pAic Base address
	pAic = AT91C_BASE_AIC;

	//* Enable User Reset and set its minimal assertion to 960 us
	AT91C_BASE_RSTC->RSTC_RMR = AT91C_RSTC_URSTEN | (0x4<<8) | (unsigned int)(0xA5<<24);

	//* Init
	loop_count = 0 ;
	// First, enable the clock of the PIOB
	AT91F_PMC_EnablePeriphClock ( AT91C_BASE_PMC, 1 << AT91C_ID_PIOA ) ;

	// mt: added reset enable to make the board reset-button "useful"
	AT91F_RSTSetMode( AT91C_BASE_RSTC , AT91C_RSTC_URSTEN );


	while(1){
		__asm("nop");
	}
}

