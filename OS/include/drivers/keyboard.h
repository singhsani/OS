#ifndef __OS_DRIVERS__KEYBOARD_H
#define __OS_DRIVERS__KEYBOARD_H
    #include <common/types.h>
    #include <hardwareCommunication/interrupts.h>
    #include <hardwareCommunication/port.h>
    #include <drivers/driver.h>
    
namespace OS{
    namespace drivers{
        class KeyBoardEventHandler{
        public:
            KeyBoardEventHandler();
            virtual void OnkeyDown(char);
            virtual void OnkeyUp(char);
        };

        class KeyboardDriver : public OS::hardwareCommunication::InterruptHandler,public Driver,public KeyBoardEventHandler{
        protected:
           OS::hardwareCommunication:: Port8Bit dataport;
           OS::hardwareCommunication:: Port8Bit commandport;
            KeyBoardEventHandler *eventHandler;
        public:
            KeyboardDriver(OS::hardwareCommunication::InterruptManager* manager,KeyBoardEventHandler *eventHandler);
            ~KeyboardDriver();
            virtual OS::common::uint32_t HandleInterrupt(OS::common::uint32_t esp);
            virtual void Activate();
        };
    }
}
#endif
