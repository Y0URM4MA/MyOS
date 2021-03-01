#include "system.h"
#include "screen.h"
#include <idt.h>
#include <isr.h>
#include <pit.h>

void main(){

clear_screen();
init_cursor();
irq_install_handler(0, &timer_handler);
pic_init();
PIT_init(100);
make_idt();


while(1){
}

}
