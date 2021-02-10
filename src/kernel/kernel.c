#include "system.h"
#include "screen.h"
#include <idt.h>

void main(){
make_idt();
clear_screen();
init_cursor();
asm volatile("int $0x0");
for(;;);


}
