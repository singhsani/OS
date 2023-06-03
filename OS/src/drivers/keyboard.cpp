#include <drivers/keyboard.h>
#include <common/types.h>
#include <hardwareCommunication/interrupts.h>
using namespace OS::common;
using namespace OS::drivers;
using namespace OS::hardwareCommunication;

KeyBoardEventHandler::KeyBoardEventHandler()
{
}

void KeyBoardEventHandler::OnkeyDown(char)
{
}
void KeyBoardEventHandler:: OnkeyUp(char)
{
}

KeyboardDriver::KeyboardDriver(InterruptManager* manager,KeyBoardEventHandler *eventHandler):InterruptHandler(manager,0x21),
dataport(0x60),
commandport(0x64){
    this->eventHandler=eventHandler;
}
KeyboardDriver::~KeyboardDriver(){
}
void KeyboardDriver::Activate(){
    while(commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xAE);//activate state
    commandport.Write(0x20);
    uint8_t status=(dataport.Read()| 1) & ~0x10;//current state
    commandport.Write(0x60);//set state
    dataport.Write(status);
    dataport.Write(0xF4);
}
    
void output(char*);
void outputHex(uint8_t);

 uint32_t KeyboardDriver:: HandleInterrupt(uint32_t esp){
     uint8_t key=dataport.Read();
     if(eventHandler==0)
         return esp;
     if(key<0x80){
     switch(key){
         case 0x01:eventHandler->OnkeyDown('!');  break;
         case 0x02:eventHandler->OnkeyDown('@');  break;
         case 0x03:eventHandler->OnkeyDown('#');  break;
         case 0x04:eventHandler->OnkeyDown('$');  break;
         case 0x05:eventHandler->OnkeyDown('%');  break;
         case 0x06:eventHandler->OnkeyDown('^');  break;
         case 0x07:eventHandler->OnkeyDown('&');  break;
         case 0x08:eventHandler->OnkeyDown('*');  break;
         case 0x09:eventHandler->OnkeyDown('(');  break;
         case 0x0A:eventHandler->OnkeyDown(')');  break;
         case 0x0B:eventHandler->OnkeyDown('_');  break;
         case 0x0C:eventHandler->OnkeyDown('+');  break;
         
         case 0x10:eventHandler->OnkeyDown('Q');  break;
         case 0x11:eventHandler->OnkeyDown('W');  break;
         case 0x12:eventHandler->OnkeyDown('E');  break;
         case 0x13:eventHandler->OnkeyDown('R');  break;
         case 0x14:eventHandler->OnkeyDown('T');  break;
         case 0x15:eventHandler->OnkeyDown('Y');  break;
         case 0x16:eventHandler->OnkeyDown('U');  break;
         case 0x17:eventHandler->OnkeyDown('I');  break;
         case 0x18:eventHandler->OnkeyDown('O');  break;
         case 0x19:eventHandler->OnkeyDown('P');  break;
         case 0x20:eventHandler->OnkeyDown('{');  break;
         case 0x21:eventHandler->OnkeyDown('}');  break;
         case 0x22:eventHandler->OnkeyDown('|');  break;  
         case 0x1E:eventHandler->OnkeyDown('A');  break;
         case 0x1F:eventHandler->OnkeyDown('S');  break; 
         case 0x23:eventHandler->OnkeyDown('D');  break;
         case 0x24:eventHandler->OnkeyDown('F');  break;
         case 0x25:eventHandler->OnkeyDown('G');  break;
         case 0x26:eventHandler->OnkeyDown('H');  break;
         case 0x27:eventHandler->OnkeyDown('J');  break;
         case 0x28:eventHandler->OnkeyDown('K');  break;
         case 0x29:eventHandler->OnkeyDown('L');  break;
         case 0x30:eventHandler->OnkeyDown(':');  break;
         case 0x31:eventHandler->OnkeyDown('\''); break; 
         case 0x2C:eventHandler->OnkeyDown('Z'); break;
         case 0x2D:eventHandler->OnkeyDown('X');  break; 
         case 0x2E:eventHandler->OnkeyDown('C');  break;
         case 0x2F:eventHandler->OnkeyDown('V');  break;
         case 0x32:eventHandler->OnkeyDown('B');  break;
         case 0x33:eventHandler->OnkeyDown('N');  break;
         case 0x34:eventHandler->OnkeyDown('Z');  break;
         case 0x35:eventHandler->OnkeyDown('M');  break;
         case 0x36:eventHandler->OnkeyDown('<');  break;
         case 0x37:eventHandler->OnkeyDown('>');  break;
         case 0x38:eventHandler->OnkeyDown('?');  break;
         case 0x41: eventHandler->OnkeyUp('-');   break;
         case 0x42: eventHandler->OnkeyDown('+'); break;
         
         case 0x1C:eventHandler->OnkeyDown('\n');break;
         case 0x39:eventHandler->OnkeyDown(' ');break;
         
         default:
         {
             output("Keyboard 0x");
             outputHex(key);
             break;
         }
       }
    }
    return esp;
}
