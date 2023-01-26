/******************************************************************
Universidad del Valle de Guatemala
IE2023 Programación de Microcontroladores
Autor: Fernando Donis
Compilador: PIC-AS (v2.36), MPLAB X IDE (v6.00)
Proyecto: Laboratorio 1
Hardware: PIC16F887
Creado: 24/08/2022
Última Modificación: 17/09/2022
******************************************************************/

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f887.h>
#include "ADC.h"
#include "Timer0.h"
#define _XTAL_FREQ 4000000
/**************************************************
 Variables
 ***************************************************/
unsigned char a;
unsigned char displayAC[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned d1, d2; 
int ADC;
char cont =0x00;
/**************************************************
 Prototipos de funciones
 ***************************************************/
void setup (void);
void setupADC (void);
void setupTimer0 (void);
/**************************************************
 Código Principal
 ***************************************************/

void main(void) {
    setup();
    setupADC();
    setupTimer0();
    //Loop Principal
    while(1){
    /**************************************************
     Displays Potenciómetro
    ***************************************************/    
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO == 1){;}
        ADIF = 0;
        ADC = ADRESH;
        
        d1 = ((ADC/10)%10);
        d2 = (ADC%10);
        
        if(TMR0IF){
            TMR0 = 6;
            cont = !cont;
            
            if (cont == 0x01){
                RC3 = 0;
                RC4 = 0;
                PORTD = displayAC[d2];
                RC3 = 0;
                RC4 = 1;
            }
            
            if (cont == 0x00){
                RC3 = 0;
                RC4 = 0;
                PORTD = displayAC[d1];
                RC3 = 1;
                RC4 = 0;
            }
        }
    /**************************************************
     Contador
    ***************************************************/    
        if(PORTCbits.RC0==1){
            __delay_ms(100);
            a++;
        }else{
            a = a;
        }
        if(PORTCbits.RC1==1){
            __delay_ms(100);
            a--;
        }else{
            a = a;
        }
        __delay_ms(100);
        PORTB=a;
    /**************************************************
     Alarma
    ***************************************************/            
        if (ADRESH >= PORTB){
            RA2 = 1;
        }else{
            RA2 = 0;
        }
    }
    return;
}
/**************************************************
 Funcion para configurar GPIOs
 ***************************************************/
void setup (void) {
    ANSELH = 0;
    
    TRISB = 0;
    PORTB = 0;
    
    TRISD = 0;
    PORTD = 0;
    
    TRISAbits.TRISA2 = 0;
    PORTAbits.RA2 = 0;
    
    
    TRISCbits.TRISC0=1;
    TRISCbits.TRISC1=1;
    TRISCbits.TRISC3=0;
    TRISCbits.TRISC4=0;
    OSCCONbits.IRCF = 0b110;
    OSCCONbits.SCS = 1;
    __delay_us(100);
}
