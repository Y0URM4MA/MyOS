#include <pit.h>
#include <system.h>
#include <screen.h>



static unsigned volatile int timer_ticks = 0;

// initialazing the pit to start counting.
// takes a wanted frequency as a parameter
void PIT_init(unsigned int frequency){

	// getting the count out of this formula: count = input_freq / wanted_freq
	// Disclaimer: at the end, the real frequency will probably be very close but not exactly what I wanted
	unsigned short count = 1193181 / frequency;

	// control word register is maaped to port 0x43.
	// value is 0x34 which means:
	// bit 0 = 0b0: giving counter value in binary mode and not BCD (4 decimal digits).
	// bits 1-3 = 0b010: Mode bits - I chose simple rate generator.
	// bits 4-5 = 0b11: RW bits - I give the counter value with LSB first and then MSB.
	// bits 6-7 = 0b00: Select counter bits - Dealing with counter 0.
	port_byte_out(0x43,0x34);
	
	// LSB first to counter 0
	port_byte_out(0x40,(unsigned char)(count & 0xff));
	// MSB of count now	
	port_byte_out(0x40,(unsigned char)(count >> 8));

}

void timer_handler(registers_t *r){
	// incrementing tick count.
	timer_ticks++;
	//if(timer_ticks % 200 == 0)
		//kprint("2 sec passed\n");
}

// sleep function which stops the system from exectuing any further commands.
// takes number of ticks as the delay parameter, every tick takes 10 milliseconds.
void sleep(int ticks){
	unsigned int l_ticks = timer_ticks + ticks;
	while(l_ticks > timer_ticks);

}


