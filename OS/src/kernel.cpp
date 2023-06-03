#include <common/types.h>
#include <hardwareCommunication/interrupts.h>
#include <drivers/keyboard.h>
#include <drivers/driver.h>
#include <drivers/mouse.h>
#include <hardwareCommunication/pci.h>
#include <gdt.h>
#include <drivers/vga.h>
#include <GUI/widget.h>
#include <GUI/desktop.h>
using namespace OS;
using namespace OS::common;
using namespace OS::hardwareCommunication;
using namespace OS::drivers;
using namespace OS::GUI;

void output(char* str){
    uint16_t* VideoMemory=(uint16_t*)0xb8000;
    static int x=0,y=0;
    
    for(int i=0;str[i]!='\0';++i){
        switch(str[i]){
           case '\n':
                y++;
                x=0;
                break;
            default:
                  VideoMemory[80*y+x]=(VideoMemory[80*y+x] & 0xFF00)| str[i];
                  x++;
                  break;
        }
        if(x>=80){
            y++;
            x=0;
        }
        if(y>=25){
            for(y=0;y<=25;y++){
                for(x=0;x<80;x++){
                 VideoMemory[80*y+x]=(VideoMemory[80*y+x] & 0xFF00)| ' ';
                }
            }
            x=0;
            y=0;
        }
    }
}
void outputHex(uint8_t  key){
    char* foo="00";
    char* hex="0123456789ABCDEF";
    foo[0]=hex[(key >> 4) & 0xF];
    foo[1]=hex[key & 0xF];
    output(foo);
}
class PrintKeyOnPress:public KeyBoardEventHandler{
public:
//     virtual void OnkeyUp(char c){
//         char* foo=" ";
//         foo[0]=c;
//         output(foo);
//     }
   virtual void OnkeyDown(char c){
        char* foo=" ";
        foo[0]=c;
        output(foo);
    }
};
class MouseConsole:public MouseEventHandlers{
    uint8_t x,y;
public:
    MouseConsole(){
        x=40;
        y=12;
        static uint16_t* VideoMemory=(uint16_t*)0xb8000;
        VideoMemory[80*y+x]=((VideoMemory[80*y+x] & 0xF000)>>4)|
                            ((VideoMemory[80*y+x] & 0x0F00)<<4)
                            |((VideoMemory[80*y+x] & 0x00FF));
    }
//     virtual void OnActivate(){
//         uint16_t* VideoMemory=(uint16_t*)0xb8000;
//         x=40;
//         y=12;
//         VideoMemory[80*y+x]=((VideoMemory[80*y+x] & 0xF000)>>4)|
//                         ((VideoMemory[80*y+x] & 0x0F00)<<4)
//                         |((VideoMemory[80*y+x] & 0x00FF));
//     }
//     void OnMouseUp(uint8_t button){
//     }
//     void OnMouseDown(uint8_t button){
//     }
    virtual void OnMove(int xoffset,int yoffset){
        x=40;
        y=12;
        static uint16_t* VideoMemory=(uint16_t*)0xb8000;
        VideoMemory[80*y+x]=((VideoMemory[80*y+x] & 0xF000)>>4)|
                            ((VideoMemory[80*y+x] & 0x0F00)<<4)
                            |((VideoMemory[80*y+x] & 0x00FF));
        x+=xoffset;
        if(x<0) x=0;
        if(x>=80) x=79;
        y-=yoffset;
        if(y<0) y=0;
        if(y>=25) y=24;
        VideoMemory[80*y+x]=((VideoMemory[80*y+x] & 0xF000)>>4)|
                            ((VideoMemory[80*y+x] & 0x0F00)<<4)
                            |((VideoMemory[80*y+x] & 0x00FF));
        }
};
typedef void(*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructor(){
    for(constructor* i=&start_ctors;i!=&end_ctors;i++){
        (*i)();
    }
}



extern "C" void kernelMain(void *multiboot_structure,uint32_t magicnumber){
    output("Hello World ......Welcome.........\n");
    GlobalDescripterTable gdt;
    InterruptManager interrupts(0x20,&gdt);
    
    output("Active 1 \n");
    DriverManager drivers;
        peripheralComponentInterConnectControllar pcidriver; pcidriver.selectDriver(&drivers,&interrupts);
        PrintKeyOnPress press;
        KeyboardDriver keyboard(&interrupts,&press);
        drivers.addDriver(&keyboard);
        MouseConsole mouseHandler;
        MouseDriver mouse(&interrupts,&mouseHandler);
        drivers.addDriver(&mouse);
        VedioGraphicArray vga;
         output("Active 2 \n");
        drivers.ActivateAll();
        
     output("Active 3 \n");
    interrupts.Activate();
    vga.setMode(320,200,8);
    Desktop desktop(320,200,0x00,0x00,0xA8);
    desktop.Draw(&vga);
    while(1);
}
