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

// Variáveis para a varredura do display

#define Barramento_Displays PORTD

#define Selecao_D1 LATEbits.LATE2
#define Selecao_D2 LATEbits.LATE0
#define Selecao_D3 LATAbits.LATA2
#define Selecao_D4 LATAbits.LATA5

// Variáveis para a varredura do teclado

#define LA PORTBbits.RB3
#define LB PORTBbits.RB4
#define LC PORTBbits.RB5
#define LD PORTBbits.RB6

#define C1 LATBbits.LATB0
#define C2 LATBbits.LATB1
#define C3 LATBbits.LATB2

//#define Coluna_4 PORTBbits.RB0

//declara as suas variaveis de software

char Milhar=11,Centena=11,Dezena=11,Unidade=11;
char Tecla;
char Converte_7seg []=
{
0b00111111,
0b00000110,
0b01011011,
0b01001111,
0b01100110,
0b01101101,
0b01111101,
0b00000111,
0b01111111,
0b01101111, // 9
0b00000000, // espaço (10)
0b00001000, // underline (11)
0b01000000, // traço (12)
0b01100011, // graus (13)
0b00111001, // Celcius (14)
0b01110111, // letra A (15)
};

void Delay_Cinema ()
{
long int i;
for (i=0;i<=200;i++) {} 
}

char Varre_Teclado ()

{
C1=1;		//SELECIONA COLUNA 1
C2=0;
C3=0;
if (LA==1) {return 1;};
if (LB==1) {return 4;};
if (LC==1) {return 7;};
if (LD==1) {return 10;};

C1=0;		//SELECIONA COLUNA 2
C2=1;
C3=0;
if (LA==1) {return 2;};
if (LB==1) {return 5;};
if (LC==1) {return 8;};
if (LD==1) {return 0;};

C1=0;		//SELECIONA COLUNA 3
C2=0;
C3=1;
if (LA==1) {return 3;};
if (LB==1) {return 6;};
if (LC==1) {return 9;};
if (LD==1) {return 11;};
return 12;
}

void Varre_Displays ()

{
Selecao_D1=0;
Selecao_D2=0;
Selecao_D3=0;
Selecao_D4=0; // apaga todos os displays

Barramento_Displays = Converte_7seg [Milhar];// manda para todos os displays
Selecao_D1=1;   //acende o primeiro display
Delay_Cinema (); // dá um tempo
Selecao_D1=0; //apaga o primeiro display

Barramento_Displays = Converte_7seg [Centena];// manda para todos os displays
Selecao_D2=1;   //acende o segundo display
Delay_Cinema (); // dá um tempo
Selecao_D2=0; //apaga o segundo display

Barramento_Displays = Converte_7seg [Dezena];// manda para todos os displays
Selecao_D3=1;   //acende o terceiro display
Delay_Cinema (); // dá um tempo
Selecao_D3=0; //apaga o terceiro display

Barramento_Displays = Converte_7seg [Unidade];// manda para todos os displays
Selecao_D4=1;   //acende o quarto display
Delay_Cinema (); // dá um tempo
Selecao_D4=0; //apaga o quarto display

}


void Contador ()
{
Unidade++;
if (Unidade==10) 
	{
	Unidade=0;
	Dezena++;
	if (Dezena==10)
		{
		Dezena=0;
		}
}
}

void main()
{
ADCON1=0x0F;
 
TRISD=0b00000000;  
TRISE=0b11111010;
TRISA=0b11011011;
TRISB=0b11111000;

while (1)
	{
	if (Varre_Teclado ()<=9)
	{
	Centena=Varre_Teclado ();
	}
	Varre_Displays ();
	}
}
