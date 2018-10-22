#include <p18f4550.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// Não cara não é mentira vim do futuro para dizer que funciona no hooldor o codigo o hooldor não!!!!!

// Configuração do microcontrolador para execução de instruções

#pragma config FOSC     = HS    /// EXTERN CLOCK 8MHZ
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


//  Função para envio de dado serial
void tx_data(char data){

    TXREG = data;
//  Wait for the Tx flag bit to be high
    while(TXIF == 0);
}

void Delay () // tempo = 415us -> 600bps
{
int j;
for (j=0;j<200;j++) {}   //21 -> 600bps
j=0;
j=0;
}

//  Função para configurar o módulo ADC
void adc_setup(){
//  Seleccionar o resultado ajustado direito , tempo 4TAD Aquisição , FOSC / 16
    ADCON2 = 0x95;
//  Seleccionar VDD e VSS como fonte de tensão de referência , Pin0 ( AN0 ) como entrada analógica
    ADCON1 = 0b1101;
//  Selecionando AN0 como canal de entrada analógica para a conversão , permitindo módulo A / D
    ADCON0 = 0b001;
}

//  Função para converter valores analogicos em digitais
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
        Delay ();
    }
    else{
        char va3[5];
        sprintf(va3, "%d", ADRES);
        tx_data('V');
        tx_data('=');
        tx_data(va3[0]);
        tx_data(va3[1]);
        tx_data(va3[2]);
        tx_data(va3[3]);
        tx_data('.');
        Delay ();*/ 
    } 
}

// Função para trocar o canal de leitura analogica
void swap_channel(){
    
    if (ADCON0 == 0b001){
            ADCON0 = 0b101;
        }
    else{
        ADCON0 = 0b001;
    }
}

// Configuração Serial
void serial_setup(){
//  Fazer o pino 6 (Tx) de PORTC como pino de saída
    TRISCbits.TRISC6 = 0;
//  Fazer o pino 7 (Rx) de PORTC como pino de entrada
    TRISCbits.TRISC7 = 1;
//  Ativando transmissor, modo assíncrono, tamanho caracteres de 8-bit, taxa alta de transmissão
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
    GO_DONE = 0;
    serial_setup();
    adc_setup();

    while(1){
    //  inicia a conversão A/D
        GO_DONE = 1;
        GO_DONE = 1;
    //  Espera a conversão ser concluida
        while (GO_DONE) {};
        adc_output();
        swap_channel();
    }      
}