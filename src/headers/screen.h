#ifndef _SCREEN_H
#define _SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80


// Attribute byte for color of character

#define WHITE_ON_BLACK 0x0f


// Screen device I/O ports

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

// Functions

int get_cursor();
void set_cursor(int offset);
int get_screen_offset(int cols,int rows);
int handle_scrolling(int cursor_offset);
void clear_screen();
void print_char(char character, int col, int row, char attribute_byte);
void init_cursor();
void print_at(char* message , int col , int  row);
void kprint(char* message);

#endif
