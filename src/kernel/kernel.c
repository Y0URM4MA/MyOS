#include "system.h"
#include "screen.h"
#include <idt.h>
#include <isr.h>
#include <pit.h>
#include <keyboard.h>
#include <shell.h>

extern char INPUT_BUFFER[256];
extern void* shell_cmd[];

void main(){

	clear_screen(); 
	init_cursor(); 				// initiating cursor appearence and position

	pic_init(); 					//initiating master and slave PICs
	irq_install_handler(0, &timer_handler); 	//irq 0 is for timer so timer_handler funtion pointer is assigned at the first place of handlers' table
	PIT_init(100); 				// initiating the timer
	irq_install_handler(1, &keyboard_handler); 	//irq 1 is for timer so keyboard_handler funtion pointer is assigned at the first place of handlers' table
	make_idt(); 					// initiating the IDT and enabling interrupts with assembly "sti"

	kybrd_init(); 					// useless function for future use maybe (educational purposes only)
	buffer_clear(); 				// clearing the input buffer to make sure it's set properly

	for(;;){ 					// shell loop
		kprint(">");
		while(get_last_char() != '\n'){}	// waits until user presses "enter"
		int cmd_num = get_command();		// getting the command number according to the keyword position in the "commands" array (see "shell.c")
		if(cmd_num != -1){			// if no command was typed then print corresponding message
			void (*cmd)(void) = shell_cmd[get_command()];		// getting the function pointer from "shell_cmd" (see "shell.c") and executing it
			cmd();				
		}else{
			kprint("no such command, try \"echo\" or \"color\"\n");
		}
		buffer_clear();			// clearing the INPUT_BUFFER
	}

}
