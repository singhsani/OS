#include<hardwareCommunication/pci.h>
#include<drivers/driver.h>
#include<common/types.h>
#include<hardwareCommunication/interrupts.h>

using namespace OS::common;
using namespace OS::hardwareCommunication; 
using namespace OS::drivers;

peripheralComponentInterConnectControllar::peripheralComponentInterConnectControllar():dataPort(0xCFC),commondPort(0xCF8){
    
}
peripheralComponentInterConnectControllar::~peripheralComponentInterConnectControllar(){
}

peripheralComponentInterConnectControllarDeviceDescriptor::peripheralComponentInterConnectControllarDeviceDescriptor(){
}
peripheralComponentInterConnectControllarDeviceDescriptor::~peripheralComponentInterConnectControllarDeviceDescriptor(){
}

uint32_t peripheralComponentInterConnectControllar::Read(uint16_t bus,uint16_t device,uint16_t functions,uint32_t registerOffset){
    uint32_t id=
    0x1 << 31 
    | ((bus & 0xFF) << 16)
    | ((device & 0x1F ) << 11)
    | ((functions & 0x07) << 8)
    | (registerOffset & 0xFC);
    commondPort.Write(id);
    uint32_t result=dataPort.Read();
    return result >> (8*(registerOffset%4));
}

void peripheralComponentInterConnectControllar::Write(uint16_t bus,uint16_t device,uint16_t functions,uint32_t registerOffset,uint32_t value){
    uint32_t id=
    0x1 << 31
    | ((bus & 0xFF) << 16)
    | ((device & 0x1F) <<11)
    | ((functions & 0x07) << 8)
    | (registerOffset & 0xFC);
    commondPort.Write(id);
    dataPort.Write(value);
}

bool peripheralComponentInterConnectControllar::DeviceHasFunctions(uint16_t bus,uint16_t device){
    return Read(bus,device,0,0xE) & (1<<7);
}

void output(char*);
void outputHex(uint8_t);

void peripheralComponentInterConnectControllar::selectDriver(DriverManager* driver,InterruptManager* interruptsManager){
    for(int bus=0;bus<8;bus++){
        for(int device=0;device<32;device++){
            int numFunction=DeviceHasFunctions(bus,device) ? 8:1;
            for(int function=0;function<numFunction;function++){
               peripheralComponentInterConnectControllarDeviceDescriptor dev=GetDeviceDescriptor(bus,device,function);
               
               if(dev.vendor_id==0x0000 || dev.vendor_id==0xFFFF)
                   continue;
                
               for(int barNum=0;barNum<6;barNum++){
                   BaseAddressRegister bar=GetBaseAddressRegister(bus,device,function,barNum);
                   if(bar.address && (bar.type==InputOutput))
                       dev.portBase=(uint32_t)bar.address;
                   Driver* drivers=GetDriver(dev,interruptsManager);
                   if(drivers!=0)
                       driver->addDriver(drivers);
                   
               }
               output("Bus  ");
               outputHex(bus & 0xFF);
               output("\n");
               
               output(" Device ");
               outputHex(device & 0xFF);
               output("\n");
               
               output(" function ");
               outputHex(function & 0xFF);
               output("\n");
               
               output(" VENDOR ");
               outputHex((dev.vendor_id & 0xFF00) >>8);
               outputHex(dev.vendor_id & 0xFF);
               output("\n");
               
               output(" Device ");
               outputHex((dev.device_id & 0xFF00)>>8);
               outputHex(dev.device_id & 0xFF00);
               
            }
        }
    }
}

peripheralComponentInterConnectControllarDeviceDescriptor peripheralComponentInterConnectControllar::GetDeviceDescriptor(uint16_t bus,uint16_t device,uint16_t functions){
 peripheralComponentInterConnectControllarDeviceDescriptor result;
 result.bus=bus;
 result.device=device;
 result.functions=functions;
 
 result.vendor_id=Read(bus,device,functions,0x00);
 result.device_id=Read(bus,device,functions,0x02);
 
 result.class_id=Read(bus,device,functions,0x0b);
 result.subclass_id=Read(bus,device,functions,0x0a);
 result.interface_id=Read(bus,device,functions,0x09);
 
  result.interrupts=Read(bus,device,functions,0x3c);
  result.revision=Read(bus,device,functions,0x08);
  
  return result;
}

 BaseAddressRegister peripheralComponentInterConnectControllar:: GetBaseAddressRegister(uint16_t bus,uint16_t device,uint16_t functions,uint16_t bar){
     BaseAddressRegister result;
     uint32_t addressType=Read(bus,device,functions,0x0E) & 0x7F;
     int maxBarNum=6-(4*addressType);
     if(bar>=maxBarNum)
         return result;
     
     uint32_t bar_value=Read(bus,device,functions,0x10 + 4*bar);
     result.type=(bar_value & 0x1)?InputOutput:MemoryMapping;
     
     uint32_t temp;
     if(result.type == MemoryMapping)
     {
         switch((bar_value >> 1) & 0x3)
         {
             case 0://32 Bit
             case 1: //20 Bit
             case 2://64 Bit
                 break;
         }
     }
     else{
         result.address=(uint8_t*)(bar_value & ~0x3);
         result.perfectchable=false;
     }
     return result;
 }
 Driver* peripheralComponentInterConnectControllar:: GetDriver(peripheralComponentInterConnectControllarDeviceDescriptor dev,InterruptManager* InterruptManager){
     switch(dev.vendor_id){
         case 0x1022://AMD
             switch(dev.device_id){
                 case 0x2000:
                     break;
             }
             break;
        case 0x8086://Intel
            break;
     }
     switch(dev.class_id){   // Graphics
         case 0x01:
             switch(dev.subclass_id){
                 case 0x00://VGA
                     break;
             }
             break;
     }
     return 0;
 }
                    
 
