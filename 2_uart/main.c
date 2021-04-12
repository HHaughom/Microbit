#include <stdint.h>
#include "gpio.h"
#include "uart.h"
//#include <stdio.h>




int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	uart_init();

	//iprintf("The average grade in TTK%d was in %d and %d: %c\n\r",4235,2019,2018,'C');

	char result;
	int sleep = 0;
	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if(!(GPIO->IN & (1 << 26))) {
			//GPIO->OUTSET = 00000000 << 4;
			//GPIO->OUTSET = 111 << 13;

			uart_send('B');
		}

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if(!(GPIO->IN & (1 << 17))) {
			//GPIO->OUTCLR = 00000000 << 4;
			//GPIO->OUTCLR = 111 << 13;

			uart_send('A');
		}

		result = uart_read();
		if(result != '\0') {
			if(GPIO->OUT & (1 << 13)) {
				//GPIO->OUTCLR = 00000000 << 4;
				GPIO->OUTCLR = 111 << 13;
				while(!(GPIO->IN & (1 << 26)) || !(GPIO->IN & (1 << 17)));
			}
			else {
				//GPIO->OUTSET = 00000000 << 4;
				GPIO->OUTSET = 111 << 13;
				while(!(GPIO->IN & (1 << 26)) || !(GPIO->IN & (1 << 17)));
			}
			
		}
		result = '\0';

		

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}

/*
ssize_t _read(int fd, void *buf, size_t count){
	char *str = (char *)(buf);
	char letter;
	do {
	letter = uart_read();
	} while(letter == '\0');
	*str = letter;
	return 1;
}
*/