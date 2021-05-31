#include <screen.h>
#include <system.h>
#include <shell.h>


char const* const commands[] = {"echo ", "color "}; 		// iterating through this array to determine which command has been typed
extern char INPUT_BUFFER[];					// input buffer contains the keys that the user pressed
void const* const shell_cmd[] = {&echo, &change_color};	// contains the function pointers that handles each command for generic use 
extern char ATTRIBUTE;						// attribute byte for the screen contains text color and background color

int get_command(void)	// returns the position of the matched function in the "shell_cmd" array according to the command the user typed,
{			// if a non command has been entered, the function returns -1
	int i = 0;
	for(;i < 256; i++){
		if(INPUT_BUFFER[i] == ' ')
			break;
	}
	
	char cmd[i+2];
	for(int j = 0; j < (i+1); j++){
		cmd[j] =  INPUT_BUFFER[j];
	}
	cmd[i+1] = 0;
	
	for(int j = 0; j < 2; j++){
		if(strcmp(cmd,commands[j]))
			return j;
	}
	
	return -1;	
}

void echo(void)
{
	char* parameter = INPUT_BUFFER+5;
	kprint(parameter);
}

void change_color(void)
{
	char attr;
	char arr[3] = {INPUT_BUFFER[6], INPUT_BUFFER[7], INPUT_BUFFER[8]};
	if(arr[2] != '\n')
		kprint("invalid parameter\n");
	else if(((arr[0] >= '0' && arr[0] <= '9') || (arr[0] >= 'a' && arr[0] <= 'f')) && ((arr[1] >= '0' && arr[1] <= '9') || (arr[1] >= 'a' && arr[1] <= 'f')))
	{
		ATTRIBUTE = atoh(arr);
		change_attribute();
	}		

}
