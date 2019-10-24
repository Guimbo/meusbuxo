#include <p18f4550.h>
#include <string.h>
#include <stdio.h>

// Configura��o do microcontrolador para execu��o de instru��es

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
//#define Start_Bit 0
// Configura a USART para comunicação Serial
void configurarUSART(){
	OpenUSART(USART_TX_INT_OFF &  // Transmit Interrupt OFF OBS: Tem no datasheet -> mudei para ON
            USART_RX_INT_ON & // Receive Interrupt ON OBS: Tem no datasheet -> mudei para ON
            USART_ASYNCH_MODE & // Asynchronous Mode OBS: Tem no datasheet
            USART_EIGHT_BIT & // 8-bit Transmit/Receive OBS: Tem no datasheet
            USART_CONT_RX & // Continuous Reception OBS: Pesquisar para qu? serve. Deve ter no datasheet
			  		USART_SYNC_SLAVE &
            USART_BRGH_HIGH, // High Baud Rate
    		  	51); // Baud Rate 9600 OBS: Formula no livro
						baudUSART(BAUD_8_BIT_RATE &
			  		BAUD_AUTO_OFF &
		      	BAUD_WAKEUP_OFF);
	
	BAUDCONbits.RXDTP = 0; //Inversao
	BAUDCONbits.TXCKP = 0; //Inversao
}




//declara as suas variaveis de software

char mens []= "U";
int k;

void Delay_1200bps () // tempo = 833us -> 1200bps
{
int j;
for (j=0;j<43;j++) {}   //43 -> 1200bps
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
TxD=dado;      // 01000001
dado=dado>>1;  // 00100000
Delay_1200bps ();
}
TxD=1;	//Stop_Bit;
Delay_1200bps ();
}

void Envia_Frase_Serial (char *mensagem)
{
char temp[1] = {1};
while(temp[0]!=0)
{
memcpypgm2ram (temp,mensagem,1);
Envia_Byte_Serial (temp[0]); 
*mensagem++;
}
}




void main()
{
 
TRISC=0b10111110;  // TxD -> saida = 0

TxD=1; //coloca a linha de transmiss�o em repouso
Delay_1200bps ();
configurarUSART();
while (1)
	{
	Envia_Byte_Serial ('A');
	for (k=0;k<1000;k++) {Delay_1200bps ();};
//	Envia_Frase_Serial ("As mensagens estao inseridas direto no codigo\r");
//	Envia_Frase_Serial ("e podem ter qualquer tamanho\r");
//	Envia_Frase_Serial ("OBS: nao gastamos RAM para alocar as mensagens\r");
//	while (1) {}; // parada for�ada
	}
}
