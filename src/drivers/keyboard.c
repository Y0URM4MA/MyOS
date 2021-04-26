#include <keyboard.h>
#include <system.h>
#include <screen.h>




#define KYBRD_ENC_PORT 0x60
#define KYBRD_CTRL_PORT 0x64

unsigned char DO_NOTHING = 0;
char KYBRD_LSHIFT = 0;
char KYBRD_RSHIFT = 0; 
char KYBRD_CPSLCK = 0;
char KYBRD_NMLCK = 0;
char KYBRD_SCRLLLCK = 0;

// used to convert the scan code to some ascii char
static char  *const SCAN_TO_ASCII[0x54] =  {"E","","1","2","3","4","5","6","7","8","9","0","-","=","","","q","w","e","r","t","y","u","i","o","p","[","]","\n","","a","s","d","f","g","h","j","k","l",";","\'","`","","\\","z","x","c","v","b","n","m",",",".","/","","*",""," ","","","","","","","","","","","","","","7","8","9","-","4","5","6","+","1","2","3","0","."};


unsigned char kybrd_enc_value(void){	// getting the value sent by the keyboard encoder from the output buffer
	unsigned char status_reg = port_byte_in(KYBRD_CTRL_PORT);
	while(status_reg & 0x01 != 0x01){ // first bit of status register tells about the output buffer, 0: output buffer empty, 1: output buffer full (able to read).
		status_reg = port_byte_in(KYBRD_CTRL_PORT); // wating for output buffer to be full
	}
	return port_byte_in(KYBRD_CTRL_PORT); // reading the output buffer with assembly "in" command from port 0x60
}

void kybrd_enc_cmd(unsigned char cmd){ // sending the command cmd to the keyboard encoder.
	unsigned char status_reg = port_byte_in(KYBRD_CTRL_PORT);
	while(status_reg & 0x02 != 0x00){ // second bit of status register tells about the input buffer, 0: output buffer empty (can be written), 1: output buffer full.
		status_reg = port_byte_in(KYBRD_CTRL_PORT); // wating for input buffer to be empty
	}
	
	port_byte_out(KYBRD_ENC_PORT,cmd); // sending the command with assembly "out" command to port 0x60
}

void kybrd_ctrl_cmd(unsigned char cmd){ // sending the command cmd to the keyboard controller.
	unsigned char status_reg = port_byte_in(KYBRD_CTRL_PORT);
	while(status_reg & 0x02 != 0x00){ // second bit of status register tells about the input buffer, 0: output buffer empty (can be written), 1: output buffer full.
		status_reg = port_byte_in(KYBRD_CTRL_PORT); // wating for input buffer to be empty
	}
	
	port_byte_out(KYBRD_CTRL_PORT,cmd); // sending the command with assembly "out" command to port 0x64
}

void keyboard_handler(registers_t* r){ // this function 
	
	char scan = port_byte_in(KYBRD_ENC_PORT);
	char arr[3];
	htoa(scan,arr);
	//kprint(arr);
	if (scan != 0xe0){
		if (!(DO_NOTHING == 1)){
		if(scan == 0x0e)
			backspace();
	
		else if(scan>= 0x00 && scan <= 0x53)
			kprint(SCAN_TO_ASCII[scan]);
		}else{DO_NOTHING = 0;}
	}else{
	DO_NOTHING = 1;
	}	
}

void kybrd_init(void){
	kybrd_enc_cmd(0xf0);
	unsigned char ack = kybrd_enc_value();
	kybrd_enc_cmd(0x00);
	ack = kybrd_enc_value();
	unsigned char set = kybrd_enc_value();
	

}	









