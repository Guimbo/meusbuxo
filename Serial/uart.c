#include <p18f4550.h>
#include <string.h>
#include <stdio.h>

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

//declarar as suas variaveis de hardware

#define TxD PORTCbits.RC6
#define RxD PORTCbits.RC7

#define Start_Bit 0

//declara as suas variaveis de software

unsigned char Caractere;
int k;

void Delay_1200bps () // tempo = 833us -> 1200bps
{
int j;
for (j=0;j<43;j++) {}   //43 -> 1200bps
j=0;
j=0;
}

void Delay_600bps () // tempo = 415us -> 600bps
{
int j;
for (j=0;j<21;j++) {}   //21 -> 600bps
j=0;
j=0;
}

void Envia_Byte_Serial (unsigned char dado)
{
int i;

TxD=0;	//Start_Bit;
Delay_1200bps ();

for (i=0;i<8;i++)
{
TxD=dado;      // 01000001 = 'A'
dado=dado>>1;  // 00100000
Delay_1200bps ();
}
TxD=1;	//Stop_Bit;
Delay_1200bps ();
}

unsigned char Recebe_Byte_Serial ()

{
int i;
unsigned char dado,aux;

while (RxD==1) {};

Delay_600bps (); //defasa a recepcao de meio bit

if (RxD==0) 

{
Delay_1200bps ();

for (i=0;i<7;i++)
	{
		aux=RxD;
		aux=aux<<7;
		dado=dado|aux;
		dado=dado>>1;
		Delay_1200bps ();
	}
	Delay_1200bps ();
	return dado;
}
}

void main()
{
 
TRISC=0b10111110;  // TxD -> saida = 0

TxD=1; //coloca a linha de transmissão em repouso
Delay_1200bps ();

while (1)
	{
//	TxD=RxD;
	Caractere = Recebe_Byte_Serial ();
	Envia_Byte_Serial (Caractere);
	}
}

/*

for i= 0 a 7
1 0 0 0  0 1  0
1+2+4+8+16+64+128

caractere = caractere + 2^i

for i=0 a 7

Caractere = Caractere>>1

0b01000001
0b00100000
0b00010000
ob00001000
0b00000100
0b00000010
0b00000001
0b00000000


*/