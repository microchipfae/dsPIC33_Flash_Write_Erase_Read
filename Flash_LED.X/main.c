// *****************************************************************************
// * 
// * Test Flash Erase/Writes/Reads 
// *
// *****************************************************************************
// * MPLABX v3.30
// * XC16   v1.26
// * MICROSTICK for dsPIC33FJ64MC802 
// ***************************************************************************** 


// =============================================================================
// INCLUDES
// =============================================================================
#include <xc.h> 
#include <libpic30.h> 


// =============================================================================
// DEFINES
// =============================================================================s
#define PERIOD  0xFFFF					// sets the default interval flash rate
#define FLASH_RATE 10					// smaller value yields faster rate (1-100)
#define FOREVER 1						// endless 


// =============================================================================
// GLOBALS (most put here because it's easier/better for debug)
// =============================================================================
unsigned int Counter = 0;
volatile unsigned int timer_expired;


unsigned int __attribute__( (space( prog ), aligned( _FLASH_PAGE * 2 )) )
dat[_FLASH_PAGE] ={
    0xDEAD, 0xBEEF, 0xAAAA, 0xBBBB, 0xCCCC, 0xDDDD
};

int src[_FLASH_ROW];
unsigned int dst[_FLASH_ROW];
_prog_addressT p;

unsigned int i, temp;

unsigned int prog_data[10] __attribute__( (space( prog )) ) = {
    0x0000, 0x1111, 0x2222, 0x3333,
    0x4444, 0x5555, 0x6666, 0x7777,
    0x8888, 0x9999
};

unsigned int tableOffset, loopCount;


// =============================================================================
// FUNCTION PROTOTYPES
// =============================================================================s
void InitTimer1( );



// /////////////////////////////////////////////////////////////////////////////
// PROGRAM ENTRY
// /////////////////////////////////////////////////////////////////////////////
int main( void )
{

    // -------------------------------------------------------------------------
    // Initialize ports
    // -------------------------------------------------------------------------
    LATA  = 0x0000; // set latch levels
    TRISA = 0x0000; // set IO as outputs
    LATB  = 0x0000; // set latch levels
    TRISB = 0x0000; // set IO as outputs

    InitTimer1();

    // -------------------------------------------------------------------------
    // Example 3: Write to Program Memory
    // -------------------------------------------------------------------------
    // initialize some data 
    for (i = 0; i < _FLASH_ROW; i++)
    {
        src[i] = i;
        dst[i] = 0;
    }

    // For Breakpoint
    Nop();
    Nop();
    Nop();

    _init_prog_address(p, dat); /* get address in program space */
    _erase_flash(p); /* erase a page */
    
    // -------------------------------------------------------------------------
    // Read/Confirm - Should be all 0xFFFF
    // -------------------------------------------------------------------------
    TBLPAG = __builtin_tblpage(dat);
    tableOffset = __builtin_tbloffset(dat);

    /* Read all 10 constants into the lowWord and highWord arrays */
    for (loopCount = 0; loopCount < _FLASH_ROW; loopCount++)
    {
        dst[loopCount] = __builtin_tblrdl(tableOffset);
        tableOffset += 2;
    }
    
    // For Breakpoint
    Nop();
    Nop();
    Nop();
    
    _write_flash16(p, src); /* write first row with 16-bit data */

    // -------------------------------------------------------------------------
    // Read/Confirm 
    // -------------------------------------------------------------------------
    TBLPAG = __builtin_tblpage(dat);
    tableOffset = __builtin_tbloffset(dat);

    /* Read all 10 constants into the lowWord and highWord arrays */
    for (loopCount = 0; loopCount < _FLASH_ROW; loopCount++)
    {
        dst[loopCount] = __builtin_tblrdl(tableOffset);
        tableOffset += 2;
    }


    // -------------------------------------------------------------------------
    // Spin
    // -------------------------------------------------------------------------   
    while(FOREVER)
    {

        if( timer_expired && Counter == FLASH_RATE )
        {
            LATA = ~LATA;
            LATB = ~LATB;
            Counter = 0;
            timer_expired = 0;
        }
        
    }   // END: while(FOREVER)
        
}   // END:  int main( void )


// =============================================================================
//  Function Name: InitTimer1
//  Description:   Initialize Timer1 for 1 second intervals
//  Inputs:        None
//  Returns:       None
// =============================================================================
void InitTimer1( void )
{


    T1CON = 0; /* ensure Timer 1 is in reset state */
   
    IFS0bits.T1IF = 0; /* reset Timer 1 interrupt flag */
    IPC0bits.T1IP = 4; /* set Timer1 interrupt priority level to 4 */
    IEC0bits.T1IE = 1; /* enable Timer 1 interrupt */
    PR1 = PERIOD; /* set Timer 1 period register */
    T1CONbits.TCKPS1 = 0; /* select Timer1 Input Clock Prescale */
    T1CONbits.TCS = 0; /* select external timer clock */
    T1CONbits.TON = 1; /* enable Timer 1 and start the count */

}


// =============================================================================
//  Function Name: _T1Interrupt
//  Description:   Timer1 Interrupt Handler
//  Inputs:        None
//  Returns:       None
// =============================================================================
void __attribute__( (interrupt, auto_psv) ) _T1Interrupt( void )
{


    timer_expired = 1; /* flag */
    Counter++; /* keep a running counter */
    IFS0bits.T1IF = 0; /* reset timer interrupt flag	*/

}

// =============================================================================
// 
// =============================================================================
void __attribute__( (interrupt, no_auto_psv) ) _DefaultInterrupt( void )
{
    while(1)
    {
        ClrWdt();
    }
}




