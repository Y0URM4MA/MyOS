#include "system.h"
#include "screen.h"
#include <idt.h>
#include <isr.h>
#include <pit.h>
#include <keyboard.h>

void main(){

clear_screen();
init_cursor();
kprint("cleared screen\n");

pic_init();
kprint("PIC INIT\n");
irq_install_handler(0, &timer_handler);
PIT_init(100);
kprint("PIT INIT\n");
irq_install_handler(1, &keyboard_handler);
make_idt();

kprint("hello there\n");
kybrd_init();
kprint("keyboard init\n");
kprint("\\");



for(;;);

}
