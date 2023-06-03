#ifndef __OS_DRIVERS__MOUSE_H
#define __OS_DRIVERS__MOUSE_H
    #include <common/types.h>
    #include <hardwareCommunication/interrupts.h>
    #include <hardwareCommunication/port.h>
    #include <drivers/driver.h>
    
namespace OS{
    namespace drivers{
            class MouseEventHandlers{
            public:
                MouseEventHandlers();
                
                virtual void OnMouseUp(OS::common::uint8_t button);
                virtual void OnMouseDown(OS::common::uint8_t button);
                virtual void OnMove(OS::common::uint8_t x,OS::common::uint8_t y);
                virtual void OnActivate();
            };

            class MouseDriver : public OS::hardwareCommunication:: InterruptHandler,public Driver{
            protected:
                OS::hardwareCommunication::Port8Bit dataport;
                OS::hardwareCommunication::Port8Bit commandport;
                OS::common::uint8_t buffer[3];
                OS::common:: uint8_t offset;
                OS::common::uint8_t buttons;
                MouseEventHandlers* handler;
            public:
                MouseDriver(OS::hardwareCommunication::InterruptManager* manager,MouseEventHandlers* handler);
                ~MouseDriver();
                virtual OS::common::uint32_t HandlerInterrupt(OS::common::uint32_t esp);
                virtual void Activate();
            };
    }
}

#endif
