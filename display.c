#include "display.h"
#include "board.h"
#include "pio/pio.h"
#include "pit/pit.h"

//* Global variable
volatile int count_timer1_interrupt;

#define TIMER0_INTERRUPT_LEVEL		1
#define TIMER1_INTERRUPT_LEVEL		4

/*-----------------*/
/* Clock Selection */
/*-----------------*/
#define TC_CLKS                  0x7
#define TC_CLKS_MCK2             0x0
#define TC_CLKS_MCK8             0x1
#define TC_CLKS_MCK32            0x2
#define TC_CLKS_MCK128           0x3
#define TC_CLKS_MCK1024          0x4

#define DISPLAY_NR_PINS 14
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

void display_int_handler() __attribute__((interrupt(irq)));
__ramfunc void display_int_handler()
{
	unsigned int dummy = AT91C_BASE_TC1->TC_SR;
	dummy = dummy;

	count_timer1_interrupt++;

	static volatile int tick = 0;
	if(tick) {
		PIO_Set(&display_pins[0]);
		PIO_Clear(&display_pins[1]);
		PIO_Clear(&display_pins[2]);
		PIO_Set(&display_pins[3]);
		tick = 0;
	} 
	else {
		PIO_Clear(&display_pins[0]);
		PIO_Set(&display_pins[1]);
		PIO_Set(&display_pins[2]);
		PIO_Clear(&display_pins[3]);

		tick = 1;
	}
}


void display_set(int nr1, int nr2)
{
	//PIO_Clear(&display_pins[1]);
}

void display_cursor(int on)
{

}



//*------------------------- Internal Function --------------------------------
//*----------------------------------------------------------------------------
//* Function Name       : AT91F_TC_Open
//* Object              : Initialize Timer Counter Channel and enable is clock
//* Input Parameters    : <tc_pt> = TC Channel Descriptor Pointer
//*                       <mode> = Timer Counter Mode
//*                     : <TimerId> = Timer peripheral ID definitions
//* Output Parameters   : None
//*----------------------------------------------------------------------------
void AT91F_TC_Open ( AT91PS_TC TC_pt, unsigned int Mode, unsigned int TimerId)
//* Begin
{
    unsigned int dummy;

    //* First, enable the clock of the TIMER
    	PMC_EnablePeripheral ( AT91C_BASE_PMC, 1<< TimerId);

    //* Disable the clock and the interrupts
	TC_pt->TC_CCR = AT91C_TC_CLKDIS ;
	TC_pt->TC_IDR = 0xFFFFFFFF ;

    //* Clear status bit
        dummy = TC_pt->TC_SR;
    //* Suppress warning variable "dummy" was set but never used
        dummy = dummy;
    //* Set the Mode of the Timer Counter
	TC_pt->TC_CMR = Mode ;

    //* Enable the clock
	TC_pt->TC_CCR = AT91C_TC_CLKEN ;
//* End
}


//*-------------------------- External Function -------------------------------

//*----------------------------------------------------------------------------
//* Function Name       : timer_init
//* Object              : Init timer counter
//* Input Parameters    : none
//* Output Parameters   : TRUE
//*----------------------------------------------------------------------------
void timer_init ( void )
//* Begin
{
    //init the timer interrupt counter
    count_timer1_interrupt=0;

    //* Open timer1
	AT91F_TC_Open(AT91C_BASE_TC1,TC_CLKS_MCK1024,AT91C_ID_TC1);

    //* Open Timer 1 interrupt
	AIC_ConfigureIT ( AT91C_BASE_AIC, AT91C_ID_TC1, TIMER1_INTERRUPT_LEVEL,AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL, display_int_handler);
	AT91C_BASE_TC1->TC_IER  = AT91C_TC_CPCS;  //  IRQ enable CPC
	AIC_EnableIT (AT91C_BASE_AIC, AT91C_ID_TC1);

    //* Start timer1
        AT91C_BASE_TC1->TC_CCR = AT91C_TC_SWTRG ;

//* End
}

void display_init()
{

	PIO_Configure(display_pins, DISPLAY_NR_PINS);

	//display_cursor(false);
	//display_set(DISPLAY_OFF, DISPLAY_OFF);

  	PMC_EnablePeripheral (AT91C_BASE_PMC, 1<< AT91C_ID_TC1);
	
	AT91C_BASE_TC1->TC_CCR = AT91C_TC_CLKDIS;
	AT91C_BASE_TC1->TC_IDR = 0xFFFFFFFF;
	unsigned int dummy = AT91C_BASE_TC1->TC_SR;

	AT91C_BASE_TC1->TC_CMR = 0x4; //MCK1024 |  TCPCTRG
	AT91C_BASE_TC1->TC_CCR = AT91C_TC_CLKEN;
	AT91C_BASE_TC1->TC_IER = AT91C_TC_CPCS;

	AT91C_BASE_AIC->AIC_IDCR = (1<<AT91C_ID_TC1);
	AT91C_BASE_AIC->AIC_SVR[AT91C_ID_TC1] = (unsigned int) display_int_handler;
	AT91C_BASE_AIC->AIC_SMR[AT91C_ID_TC1] = (0x00 | 0x4);
	AT91C_BASE_AIC->AIC_ICCR = (1<<AT91C_ID_TC1);
	AT91C_BASE_AIC->AIC_IECR = (1<<AT91C_ID_TC1);

	AT91C_BASE_TC1->TC_RC = 0xFBC5;
	AT91C_BASE_TC1->TC_CCR = AT91C_TC_SWTRG;
	AT91C_BASE_TC1->TC_CCR = AT91C_TC_CLKEN;

//	timer_init();
}
