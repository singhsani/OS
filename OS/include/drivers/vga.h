#ifndef __OS_DRIVERS__VGA_H
#define __OS_DRIVERS__VGA_H

#include <common/types.h>
#include <hardwareCommunication/interrupts.h>
#include <hardwareCommunication/port.h>
#include <drivers/driver.h>

namespace OS{
    namespace drivers{
        class VedioGraphicArray{
        protected:
         OS::hardwareCommunication::Port8Bit micsPort;
         OS::hardwareCommunication::Port8Bit crtcIndexPort;
         OS::hardwareCommunication::Port8Bit crtcDataPort;
         OS::hardwareCommunication::Port8Bit sequencerIndexPort;
         OS::hardwareCommunication::Port8Bit sequencerDataPort;
         OS::hardwareCommunication::Port8Bit GraphicsControllerIndexPort;
         OS::hardwareCommunication::Port8Bit GraphicsControllerDataPort;
         OS::hardwareCommunication::Port8Bit attributeControllerIndexPort;
         OS::hardwareCommunication::Port8Bit attributeControllerReadPort;
         OS::hardwareCommunication::Port8Bit attributeControllerWritePort;
         OS::hardwareCommunication::Port8Bit attributeControllerResetPort;
         
         void WriteRegister(OS::common::uint8_t* registers);
         OS::common::uint8_t* GetFrameBufferSegment();
         
         
         OS::common::uint8_t getColorIndex(OS::common::uint8_t r,OS::common::uint8_t g,OS::common::uint8_t b);
         
        public :
            VedioGraphicArray();
            ~VedioGraphicArray();
            
            virtual bool supportsMode(OS::common::uint32_t width,OS::common::uint32_t height,OS::common::uint32_t depthColor);
            
            virtual bool setMode(OS::common::uint32_t width,OS::common::uint32_t height,OS::common::uint32_t depthColor);
            
            virtual void putPexil(OS::common::uint32_t x,OS::common::uint32_t y,OS::common::uint8_t r,OS::common::uint8_t g,OS::common::uint8_t b);
            
            virtual void putPexil(OS::common::uint32_t x,OS::common::uint32_t y,OS::common::uint8_t colorIndex);
            
            virtual void FillRectangle(OS::common::uint32_t x,OS::common::uint32_t y,OS::common::uint32_t w,OS::common::uint32_t h,OS::common::uint8_t r,OS::common::uint8_t g,OS::common::uint8_t b);

        };
    }
}

#endif
