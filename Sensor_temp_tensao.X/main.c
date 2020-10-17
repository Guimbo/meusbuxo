#include <p18f4550.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
//incluindo a biblioteca de delay
#include <delays.h>
//#define _XTAL_FREQ 4000000  //Define cock interno com 4MHz

// Configura��o do microcontrolador para execu��o de instru��es
#pragma config FOSC = INTOSC_EC

//#pragma config FOSC     = HS    /// EXTERN CLOCK 8MHZ
#pragma config IESO     = OFF   /// INTERNAL/EXTERNAL OSCILATOR DISABLE
#pragma config PWRT     = OFF   /// DISABLE POWER-UP TIMER
#pragma config BORV     = 3     /// BROWN-OUT RESET MINIMUM
#pragma config WDT      = OFF   /// DISABLE WATCHDOG TIMER
#pragma config WDTPS    = 32768 /// WATCHDOG TIMER 32768s
#pragma config MCLRE    = OFF   /// MASTER CLEAR PIN (RE3) DISBALE
#pragma config LPT1OSC  = OFF   /// TIMER1 LOW POWER OPERATION
#pragma config PBADEN   = OFF   /// PORTB.RB0,1,2,3,4 AS I/O DIGITAL
#pragma config STVREN   = ON    /// STACK FULL/UNDERFLOW CAUSE RESET
#pragma config LVP      = OFF   /// DISABLE LOW VOLTAGE PROGRAM (ICSP DISABLE)


//  Fun��o para envio de dado serial
void tx_data(char data){
    TXREG = data;
//  Wait for the Tx flag bit to be high
    while(TXIF == 0);
}

// tempo = 415us -> 600bps
void Delay (){
int j;
for (j=0;j<200;j++) {}   //21 -> 600bps
j=0;
j=0;
}

//  Fun��o para configurar o m�dulo ADC
void adc_setup(){
//  Seleccionar o resultado ajustado direito , tempo 4TAD Aquisi��o , FOSC / 16
    ADCON2 = 0x95;
//  Seleccionar VDD e VSS como fonte de tens�o de refer�ncia , Pin0 ( AN0 ) como entrada anal�gica
    ADCON1 = 0b1101;
//  Selecionando AN0 como canal de entrada anal�gica para a convers�o , permitindo m�dulo A / D
    ADCON0 = 0b001;
}

//  Fun��o para converter valores analogicos em digitais
void adc_output(){
//  Store the result in 16-bit variable

    if (ADCON0 == 0b001){
        char va3[5],va4[5];
        int valor = (ADRES * 5)/10.24;
        int ponto = fmod((ADRES * 5), 10.24);
        if(ponto>3){ponto =5;}
        else{ponto = 0;}
         
        sprintf(va3, "%d", valor);
        sprintf(va4, "%d", ponto);
        tx_data(' ');
        tx_data(' ');
        tx_data('T');
        tx_data('=');
        tx_data(va3[0]);
        tx_data(va3[1]);
        tx_data(va3[2]);
        tx_data(va3[3]);
        tx_data('.');
        tx_data(va4[0]);
        tx_data(va4[1]);
        tx_data(va4[2]);
        tx_data(va4[3]);
        tx_data(' ');
        Delay ();
        //pode usar a lib de delay
        Delay1KTCYx(200);
    }
    else{
        int tensao = (1480 * ADRES)/1023;  
        char va3[5];
        sprintf(va3, "%d", tensao);
        tx_data('V');
        tx_data('=');
        tx_data(va3[0]);
        tx_data(va3[1]);
        tx_data(va3[2]);
        tx_data(va3[3]);
        tx_data('.');
        Delay1KTCYx(200);
        Delay ();
    } 
}

// Fun��o para trocar o canal de leitura analogica
void swap_channel(){
    
    if (ADCON0 == 0b001){
            ADCON0 = 0b101;
    }
    else{
        ADCON0 = 0b001;
    }
}

// Configura��o Serial
void serial_setup(){
//  Fazer o pino 6 (Tx) de PORTC como pino de sa�da
    TRISCbits.TRISC6 = 0;
//  Fazer o pino 7 (Rx) de PORTC como pino de entrada
    TRISCbits.TRISC7 = 1;
//  Ativando transmissor, modo ass�ncrono, tamanho caracteres de 8-bit, taxa alta de transmiss�o
    TXSTA = 0x24;
//  Ativando porta serial, receptor, tamanho caracter 8-bit
    RCSTA = 0x90;
//  selecionando 16-bit Baud Rate Generator
    BRG16 = 1;
//  FOSC value 16000000 MHz, SPBRG value 103, 38400 baud rate generated
    SPBRG = 0x67;
//  Enabling Priority Interrupts
    IPEN = 1;
//  Enabling High Priority Interrupts
    GIEH = 1;
//  Enabling Receive Interrupt
    RCIE = 1;
//  Assigning high priority to receiver
    RCIP = 1;
}

void main(){

    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    IRCF2 = 1; IRCF1 = 1; IRCF0 = 0;

    GO_DONE = 0;
    serial_setup();
    adc_setup();

    while(1){
    //  inicia a convers�o A/D
        GO_DONE = 1;
        GO_DONE = 1;
    //  Espera a convers�o ser concluida
        while (GO_DONE) {};
        adc_output();
        swap_channel();
    }      
}