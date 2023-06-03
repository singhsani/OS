#ifndef __OS__GUI__DESKTOP_H
#define __OS__GUI__DESKTOP_H

#include<GUI/widget.h>
#include<drivers/mouse.h>
#include<common/types.h>

namespace OS{
    namespace GUI{
        class Desktop:public CompositeWidget,public OS::drivers::MouseEventHandlers{
        private:
            OS::common::uint32_t MouseX;
            OS::common::uint32_t MouseY;
        public:
            Desktop(OS::common::uint32_t w,OS::common::uint32_t h,OS::common::uint8_t r,OS::common::uint8_t g,OS::common::uint8_t b);
            
            void Draw(OS::common::GraphicsContext* gc);
            void OnMouseUp(OS::common::uint8_t button);
            void OnMouseDown(OS::common::uint8_t button);
            void OnMove(int x,int y);
        };
    }
}
#endif
