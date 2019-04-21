/*
 * Copyright (C) 2018 Björn Schmidt <bschmidt@panvision.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define MORSE_TIME_1 50
#define MORSE_TIME_2 50
#define MORSE_TIME_3 50
#define MORSE_TOLERANCE 50

uint16_t ui16;
uint8_t ui8;
uint8_t ui8b;
uint8_t ui8a;
uint8_t ui8X;

void main() {
	
		ui8a = 1 + 238 + 128 -127 + 48;
		ui8b = 46 + 238 + 128 -127 + 1;
		ui8 = ui8b - ui8a;
		ui8X =224;
		
		printf("%d %d %d \r\n", (uint8_t)(ui8b-ui8a), (ui8b-ui8a), ui8);
		
		if (((uint8_t)(ui8b-ui8a))<224){
			printf("good\r\n");
		}else{
			printf("bad\r\n");
		}
		
		if (((ui8b-ui8a))<224){
			printf("good\r\n");
		}else{
			printf("bad\r\n");
		}
		
		if (((ui8b-ui8a))<ui8X){
			printf("good\r\n");
		}else{
			printf("bad\r\n");
		}
		
		printf("deltatest\r\n");
		printf("%d %d %d\r\n", ui8a, ui8b,ui8);
	
		ui8 = -1;
		ui16 = (1 << 8) / 200;
		printf("divtest\r\n");
		printf("%d %d\r\n", ui16, ui8);

		
		ui8 = -1;
		ui16 = -1;
		printf("underflowtest\r\n");
		printf("%d %d\r\n", ui16, ui8);

		
		ui8++;
		ui16++;
		
		printf("\r\n%d %d\r\n", ui16, ui8);

}



