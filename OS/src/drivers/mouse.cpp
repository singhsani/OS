#include <drivers/mouse.h>
#include <hardwareCommunication/interrupts.h>
using namespace OS::common;
using namespace OS::drivers;
using namespace OS::hardwareCommunication;

MouseEventHandlers::MouseEventHandlers(){
}
void MouseEventHandlers::OnMove(uint8_t x,uint8_t y){
}
void MouseEventHandlers:: OnMouseUp(uint8_t button){
}
void MouseEventHandlers:: OnMouseDown(uint8_t button){
}
void MouseEventHandlers::OnActivate(){
}

MouseDriver::MouseDriver(InterruptManager* manager,MouseEventHandlers* handler):InterruptHandler(manager,0x2C),
dataport(0x60),commandport(0x64){
    this->handler=handler;
}
MouseDriver::~MouseDriver(){
}
void MouseDriver::Activate(){
    
    offset=0;
    buttons=0;
    commandport.Write(0xAB);
    commandport.Write(0x20);
    uint8_t status=dataport.Read()|2;
    commandport.Write(0x60);
    dataport.Write(status);
    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
}
uint32_t MouseDriver::HandlerInterrupt(uint32_t esp){
    uint8_t status=commandport.Read();
    if(!(status & 0x20))
     return esp;
    buffer[offset]=dataport.Read();
    if(handler==0)
        return esp;
    offset=(offset+1)%3;
    if(offset==0){
        if(buffer[1]!=0 || buffer[2]!=0){
         handler->OnMove((int)buffer[1],-((int)buffer[2]));
        }
         for(uint8_t i=0;i<3;i++){
             if((buffer[0] & (0x01<<i))!=(buttons & (0x01<<i)))
             {
                 if(buttons & (0x1>>1))
                     handler->OnMouseUp(i+1);
                 else
                     handler->OnMouseDown(i+1);
             }
         }
        buttons=buffer[0];
    }
    return esp;
}
