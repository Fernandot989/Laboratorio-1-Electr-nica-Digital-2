/*
 * File:   ADC.c
 * Author: Oscar Fernando Donis Martínez
 *
 * Created on 20 de enero de 2023, 12:11 PM
 */

#define _XTAL_FREQ 4000000
#include "ADC.h"
#include <xc.h>

/**************************************************
 Funcion para configurar ADC
 ***************************************************/
void setupADC(void){
    TRISA = TRISA | 0x01;
    ANSEL = ANSEL | 0x01;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADCS0 = 1;
    
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.VCFG0 = 0;
    
    ADCON1bits.ADFM = 0;
    
    ADCON0bits.CHS3 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0;
    
    ADCON0bits.ADON = 1;
    __delay_us(100);
}
