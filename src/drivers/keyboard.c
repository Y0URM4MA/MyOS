#include <keyboard.h>
#include <system.h>
#include <screen.h>




#define KYBRD_ENC_PORT 0x60
#define KYBRD_CTRL_PORT 0x64

char DO_NOTHING = 0;
char KYBRD_LSHIFT = 0;
char KYBRD_RSHIFT = 0;
char KYBRD_CPSLCK = 0;
char KYBRD_NMLCK = 0;
char KYBRD_SCRLLLCK = 0;
char INPUT_BUFFER[256] = {0};
int POSITION = 0;

// used to convert the scan code to the appropriate string to print
static char const *const SCAN_TO_ASCII[0x54] =  {"E","","1","2","3","4","5","6","7","8","9","0","-","=","","","q","w","e","r","t","y","u","i","o","p","[","]","\n","","a","s","d","f","g","h","j","k","l",";","\'","`","","\\","z","x","c","v","b","n","m",",",".","/","","*",""," ","","","","","","","","","","","","","","7","8","9","-","4","5","6","+","1","2","3","0","."};

// used to convert the scan code to the appropriate char to put in the input buffer
static char const SCAN_TO_ASCII_CHAR[0x54] =
{'E', 0,'1','2','3','4','5','6','7','8','9','0','-','=',0,0,'q','w','e','r','t','y','u','i','o','p','[',']',10,0,'a','s','d','f','g','h','j','k','l',';',39,'`',0,92,'z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,'7','8','9','-','4','5','6','+','1','2','3','0','.'};


unsigned char kybrd_enc_value(void){	// getting the value sent by the keyboard encoder from the output buffer
	unsigned char status_reg = port_byte_in(KYBRD_CTRL_PORT);
	while(status_reg & 0x01 != 0x01){ // first bit of status register tells about the output buffer, 0: output buffer empty, 1: output buffer full (able to read).
		status_reg = port_byte_in(KYBRD_CTRL_PORT); // wating for output buffer to be full
	}
	return port_byte_in(KYBRD_CTRL_PORT); // reading the output buffer with assembly "in" command from port 0x60
}

void kybrd_enc_cmd(unsigned char cmd){ // sending the command cmd to the keyboard encoder.
	unsigned char status_reg = port_byte_in(KYBRD_CTRL_PORT);
	while(status_reg & 0x02 != 0x00){ // second bit of status register tells about the input buffer, 0: input buffer empty (can be written), 1: input buffer full.
		status_reg = port_byte_in(KYBRD_CTRL_PORT); // wating for input buffer to be empty
	}
	
	port_byte_out(KYBRD_ENC_PORT,cmd); // sending the command with assembly "out" command to port 0x60
}

void kybrd_ctrl_cmd(unsigned char cmd){ // sending the command cmd to the keyboard controller.
	unsigned char status_reg = port_byte_in(KYBRD_CTRL_PORT);
	while(status_reg & 0x02 != 0x00){ // second bit of status register tells about the input buffer, 0: intput buffer empty (can be written), 1: intput buffer full.
		status_reg = port_byte_in(KYBRD_CTRL_PORT); // wating for input buffer to be empty
	}
	
	port_byte_out(KYBRD_CTRL_PORT,cmd); // sending the command with assembly "out" command to port 0x64
}

void keyboard_handler(registers_t* r){ // this function 
	
	if(POSITION == 256)
		POSITION = 0;
		
	unsigned char scan = port_byte_in(KYBRD_ENC_PORT);
	if (scan == 0xe0){
		DO_NOTHING = 1;
	}else if(DO_NOTHING == 0){
		if(scan == 0x0e){
			backspace();
			if(POSITION != 0){
				POSITION--;
				INPUT_BUFFER[POSITION] = 0;
				}
		}else if(scan>= 0x00 && scan <= 0x53){
			kprint(SCAN_TO_ASCII[scan]);
			INPUT_BUFFER[POSITION] = SCAN_TO_ASCII_CHAR[scan];
			POSITION++;
			}
	}else{
		DO_NOTHING = 0;
		}
		
}

char get_last_char(void){
	if(POSITION == 0)
		return INPUT_BUFFER[POSITION];
		
	return INPUT_BUFFER[POSITION-1];		
}

void buffer_clear(void){
	memsetw((short*)INPUT_BUFFER,0,128);
	POSITION = 0;
}

void kybrd_init(void){
	kybrd_enc_cmd(0xf0);
	unsigned char ack = kybrd_enc_value();
	kybrd_enc_cmd(0x00);
	ack = kybrd_enc_value();
	unsigned char set = kybrd_enc_value();
	

}

	









