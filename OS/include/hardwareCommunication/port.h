#ifndef __OS_HARDWARECOMMUNICATION__PORT_H
#define __OS_HARDWARECOMMUNICATION__PORT_H
#include <common/types.h>

namespace OS{
    
    namespace hardwareCommunication{
        
            class Port{
            protected:
                OS::common::uint16_t portnumber;
                Port(OS::common::uint16_t portnumber);
                ~Port();
            };
            class Port8Bit:public Port{
            public:
                OS::common::uint16_t portnumber;
                Port8Bit(OS::common::uint16_t portnumber);
                ~Port8Bit();
                virtual void Write(OS::common::uint8_t data);
                virtual OS::common::uint8_t Read();
            };
            class Port8BitLow:public Port8Bit{
            public:
                OS::common::uint16_t portnumber;
                Port8BitLow(OS::common::uint16_t portnumber);
                ~Port8BitLow();
                virtual void Write(OS::common::uint8_t data);
            };
            class Port16Bit:public Port{
            public:
                OS::common::uint16_t portnumber;
                Port16Bit(OS::common::uint16_t portnumber);
                ~Port16Bit();
            virtual void Write(OS::common::uint16_t data);
            virtual OS::common::uint16_t Read();
            };
            class Port32Bit:public Port{
            public:
                OS::common::uint32_t portnumber;
                Port32Bit(OS::common::uint16_t portnumber);
                ~Port32Bit();
            virtual void Write(OS::common::uint32_t data);
            virtual OS::common::uint32_t Read();
            };
      }
}

#endif
