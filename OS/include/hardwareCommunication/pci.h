#ifndef __OS__HARDWARECOMMUNICATION__PCI_H
#define __OS__HARDWARECOMMUNICATION__PCI_H

#include<hardwareCommunication/port.h>
#include<hardwareCommunication/interrupts.h>
#include<common/types.h>
#include<drivers/driver.h>

namespace OS{
  namespace hardwareCommunication{
    enum BaseAddressRegisterType{
      MemoryMapping =0,
      InputOutput=1
    };
    
    class BaseAddressRegister{
    public:
      bool perfectchable;
      OS::common::uint8_t* address;
      OS::common::uint32_t size;
      BaseAddressRegisterType type;
    };
    class peripheralComponentInterConnectControllarDeviceDescriptor{
        public:
            OS::common::uint16_t bus;
            OS::common::uint16_t device;
            OS::common::uint16_t functions;
            OS::common::uint32_t portBase;
            OS::common::uint32_t interrupts;
            OS::common::uint16_t vendor_id;
            OS::common::uint16_t device_id;
            OS::common::uint8_t class_id;
            OS::common::uint8_t subclass_id;
            OS::common::uint8_t interface_id;
            OS::common::uint8_t revision;
                        
          peripheralComponentInterConnectControllarDeviceDescriptor();
          ~peripheralComponentInterConnectControllarDeviceDescriptor();
    };

                  class peripheralComponentInterConnectControllar
                  {
                      OS::hardwareCommunication::Port32Bit dataPort;
                      OS::hardwareCommunication::Port32Bit commondPort;
                  public:
                    peripheralComponentInterConnectControllar();
                    ~peripheralComponentInterConnectControllar();
                    
                    OS::common::uint32_t Read(OS::common::uint16_t bus,OS::common::uint16_t device,OS::common::uint16_t functions,OS::common::uint32_t registerOffset); 
                    
                    void Write(OS::common::uint16_t bus,OS::common::uint16_t device,OS::common::uint16_t functions,OS::common::uint32_t registerOffset,OS::common::uint32_t value); 
                    
                    bool DeviceHasFunctions(common::uint16_t bus,OS::common::uint16_t device);
                    
                    OS::drivers::Driver* GetDriver(peripheralComponentInterConnectControllarDeviceDescriptor dev,OS::hardwareCommunication::InterruptManager* InterruptManager);
                    
                    void selectDriver(OS::drivers::DriverManager* driver,OS::hardwareCommunication::InterruptManager* interruptsManager);
                    
                    
                    peripheralComponentInterConnectControllarDeviceDescriptor GetDeviceDescriptor(OS::common::uint16_t bus,OS::common::uint16_t device,OS::common::uint16_t functions);
                     
                    BaseAddressRegister GetBaseAddressRegister(OS::common::uint16_t  bus,OS::common::uint16_t device,OS::common::uint16_t functions,OS::common::uint16_t bar);
                  };
  }
}
#endif
