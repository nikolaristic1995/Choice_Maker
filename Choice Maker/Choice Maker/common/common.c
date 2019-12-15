#include <avr/io.h>
#include "common.h"

unsigned char common_get_digit(unsigned char digit){
	
	unsigned char character = '0';
	
	switch(digit){
		
		case 1:{
			
			character = '1';
			break;
		}
		
		case 2:{
			
			character = '2';
			break;
		}
		
		case 3:{
			
			character = '3';
			break;
		}
		
		case 4:{
			
			character = '4';
			break;
		}
		
		case 5:{
			
			character = '5';
			break;
		}
		
		case 6:{
			
			character = '6';
			break;
		}
		
		case 7:{
			
			character = '7';
			break;
		}
		
		case 8:{
			
			character = '8';
			break;
		}
		
		case 9:{
			
			character = '9';
			break;
		}
	}
	
	return character;
}

unsigned char common_get_tenth_digit(uint32_t number){
	
	return common_get_digit(number / 1000000000);
}

unsigned char common_get_ninth_digit(uint32_t number){
	
	return common_get_digit((number % 1000000000) / 100000000);
}

unsigned char common_get_eighth_digit(uint32_t number){
	
	return common_get_digit((number % 100000000) / 10000000);
}

unsigned char common_get_seventh_digit(uint32_t number){
	
	return common_get_digit((number % 10000000) / 1000000);
}

unsigned char common_get_sixth_digit(uint32_t number){
	
	return common_get_digit((number % 1000000) / 100000);
}

unsigned char common_get_fifth_digit(uint32_t number){
	
	return common_get_digit((number % 100000) / 10000);
}

unsigned char common_get_fourth_digit(uint32_t number){
	
	return common_get_digit((number % 10000) / 1000);
}

unsigned char common_get_third_digit(uint32_t number){
	
	return common_get_digit((number % 1000) / 100);
}

unsigned char common_get_second_digit(uint32_t number){
	
	return common_get_digit((number % 100) / 10);
}

unsigned char common_get_first_digit(uint32_t number){
	
	return common_get_digit(number % 10);
}
