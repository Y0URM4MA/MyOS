#include "screen.h"
#include "system.h"

void init_cursor(void){
	// set maximum scan line register to 15
	port_byte_out(REG_SCREEN_CTRL, 0x09);
	port_byte_out(REG_SCREEN_DATA, 0x0F);
	// requesting register index 10 to write the cursor start line
	port_byte_out(REG_SCREEN_CTRL,0x0a);
	port_byte_out(REG_SCREEN_DATA,0x0e);
	// requesting register index 11 to write the cursor end line
	port_byte_out(REG_SCREEN_CTRL,0x0b);
	port_byte_out(REG_SCREEN_DATA,0x0f);
	set_cursor(0);
}

int get_cursor(void){
	unsigned int position;
	// requesting high byte of cursor position
	port_byte_out(REG_SCREEN_CTRL,0x0e);
	position=port_byte_in(REG_SCREEN_DATA);
	position = position << 8;
	// requesting low byte of cursor position
	port_byte_out(REG_SCREEN_CTRL,0x0f);
	position += port_byte_in(REG_SCREEN_DATA);
	return position*2;
}

void set_cursor(int offset){
	// like get cursor but instead of reading the data I am writing it
	offset /= 2;
	port_byte_out(REG_SCREEN_CTRL,0x0e);
	port_byte_out(REG_SCREEN_DATA,(unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL,0x0f);
	port_byte_out(REG_SCREEN_DATA,(unsigned char)(offset & 0xff));
}


int get_screen_offset(int cols,int rows){
	return (160*rows)+(cols*2);
}


int handle_scrolling(int cursor_offset){
	// if the cursor is within the screen, just return it without scrolling
	if(cursor_offset < MAX_ROWS*MAX_COLS*2){return cursor_offset;}
	// moving every row one row back
	for(int i = 1; i<MAX_ROWS;i++){
	memcpy((unsigned char*)(get_screen_offset(0,i-1) + VIDEO_ADDRESS), (unsigned char*)(get_screen_offset(0,i) + VIDEO_ADDRESS), MAX_COLS*2);
	}
	// setting last row to be empty
	memsetw((unsigned short*)(get_screen_offset(0,MAX_ROWS-1) + VIDEO_ADDRESS), 0, 80);
	// moving the cursor back by one row
	cursor_offset -= 2*MAX_COLS;
	// return cursor offset after scrolling
	return cursor_offset;
}

void clear_screen(void){
	memsetw((unsigned short*)(VIDEO_ADDRESS),0x0f20,MAX_ROWS*MAX_COLS);
}

void print_char(char character, int col, int row, char attribute_byte)
{	
	// Creating a byte pointer to the start of video memory
	unsigned char *vidmem = (unsigned char*)VIDEO_ADDRESS;
	
	// If attribute byte is zero, make it the default style
	if(!attribute_byte){
		attribute_byte = WHITE_ON_BLACK;
	}
	
	// Get the video memory offset for the screen location
	int offset;
	// If col and row are non-negative, use them for offset
	if(col >= 0 && row >= 0){
		offset = get_screen_offset(col,row);
	// Otherwise, use the current cursor position
	} else {
		offset = get_cursor();
	}
	
	// If it's a  newline character, set offset to the end of current row
	// so it will be advanced to the first col of the next row
	if(character == '\n'){
		int rows = offset / (2*MAX_COLS);
		offset = get_screen_offset(79,rows);
	// Otherwise, write the character and its attribute byte to video memoey
	// at the calculated offset
	} else {
		vidmem[offset] = character;
		vidmem[offset+1] = attribute_byte;
	}
	// Update the offset to the next character  cell (two bytes ahead)
	offset += 2;
	// Make scrolling adjustment if it reaches the bottom of the screen
	offset = handle_scrolling(offset);
	// Update the cursor position ont the screen
	set_cursor(offset);
}

void  print_at(char* message , int col , int  row) {
	//  Update  the  cursor  if col  and  row  not  negative.
	if (col  >= 0 && row  >= 0){
		set_cursor(get_screen_offset(col , row));
	}
	// Loop  through  each  char of the  message  and  print  it.
	int i = 0;
	while(message[i] != 0){
		print_char(message[i], col , row , WHITE_ON_BLACK);
		i++;
		}
}

// wrapper from print_at to print with the current cursor location without specifying negative parameters
void kprint(char* message){
print_at(message ,  -1,  -1);
}		
		
		
		
		
		
		
		
		
		



