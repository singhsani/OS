#ifndef __OS_HARDWARECOMMUNICATION__INTERRUPTMANAGER_H
#define __OS_HARDWARECOMMUNICATION__INTERRUPTMANAGER_H

#include <common/types.h>
#include <hardwareCommunication/interrupts.h>
#include <hardwareCommunication/port.h>
#include <gdt.h>

namespace OS
{
    namespace hardwareCommunication
    {
        class InterruptManager;
        class InterruptHandler{
        protected:
            OS::common::uint8_t interruptNumber;
            InterruptManager* interruptManager;
            InterruptHandler(InterruptManager* interruptManager,OS::common::uint8_t interruptNumber);
            ~InterruptHandler();
        public:
        virtual OS::common::uint32_t handleInterrupt(OS::common::uint32_t esp);
        //uint32_t HandlerInterrupt(uint32_t esp);
        };
            

        class InterruptManager
        {
            friend class InterruptHandler;
        protected:
            static InterruptManager* ActiveInterruptManager;
            InterruptHandler* handler[256];
            struct GateDescriptor{
                OS::common::uint16_t handlerAddressLowBits;
                OS::common::uint16_t gdt_codeSegmentSelector;
                OS::common::uint8_t reserved;
                OS::common::uint8_t access;
                OS::common::uint16_t handlerAddressHighBits;
            }__attribute__((packed));
            struct interruptDescriptorTablePointer{
                OS::common::uint16_t size;
                OS::common::uint32_t base;
            }__attribute__((packed));
            static GateDescriptor interruptDescriptorTable[256];
            OS::common::uint16_t hardwareInterruptOffset;
            static void SetInterruptDescriptorTableEntry(
                OS::common::uint8_t interruptNumber,
                OS::common::uint16_t codeSegmentSelectorOffset,
                void (*handler)(),
                OS::common::uint8_t DescriptorPrivilegeLevel,
                OS::common::uint8_t DescriptorType
            );
        public:
             static OS::common::uint32_t HandleInterrupt(OS::common::uint8_t interruptNumber,OS::common::uint32_t esp);
        
            OS::common::uint32_t DoHandleInterrupt(OS::common::uint8_t interruptNumber,OS::common::uint32_t esp);
            
            
            OS::hardwareCommunication::Port8BitLow picMasterCommand;
            OS::hardwareCommunication::Port8BitLow picMasterData;
            OS::hardwareCommunication::Port8BitLow picSlaveCommand;
            OS::hardwareCommunication::Port8BitLow picSlaveData;
        
            InterruptManager(OS::common::uint16_t hardwareInterruptOffset,OS::GlobalDescripterTable* gdt);
            ~InterruptManager();
            OS::common::uint32_t HardwareInterruptOffset();
            void Activate();
            void DiActive(); 
            
            static void IgnoreInterruptRequest();
            
//             static void HandleException0x00();
//             static void HandleException0x01();
//             static void HandleException0x02();
//             static void HandleException0x03();
//             static void HandleException0x04();
//             static void HandleException0x05();
//             static void HandleException0x06();
//             static void HandleException0x07();
//             static void HandleException0x08();
//             static void HandleException0x09();
//             static void HandleException0x0A();
//             static void HandleException0x0B();
//             static void HandleException0x0C();
//             static void HandleException0x0D();
//             static void HandleException0x0E();
//             static void HandleException0x0F();
//             static void HandleException0x10();
//             static void HandleException0x11();
//             static void HandleException0x12();
//             static void HandleException0x13();
//             
            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
            static void HandleInterruptRequest0x02();
            static void HandleInterruptRequest0x03();
            static void HandleInterruptRequest0x04();
            static void HandleInterruptRequest0x05();
            static void HandleInterruptRequest0x06();
            static void HandleInterruptRequest0x07();
            static void HandleInterruptRequest0x08();
            static void HandleInterruptRequest0x09();
            static void HandleInterruptRequest0x0A();
            static void HandleInterruptRequest0x0B();
            static void HandleInterruptRequest0x0C();
            static void HandleInterruptRequest0x0D();
            static void HandleInterruptRequest0x0E();
            static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x31();
            
           
        };
    }
}

#endif
