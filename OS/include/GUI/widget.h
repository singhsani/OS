#ifndef __OS__GUI__WIDGET_H
#define __OS__GUI__WIDGET_H
#include <common/types.h>
#include<drivers/keyboard.h>
#include<common/GraphicsContext.h>
namespace OS{
    namespace GUI{
        class Widget:public OS::drivers::KeyBoardEventHandler
        {
        protected:
            Widget* parent;
            OS::common::uint32_t x;
            OS::common::uint32_t y;
            OS::common::uint32_t w;
            OS::common::uint32_t h;
            
            OS::common::uint8_t r;
            OS::common::uint8_t g;
            OS::common::uint8_t b;
            bool focusable;
        public :
            Widget(Widget* parent,OS::common::uint32_t x,OS::common::uint32_t y,OS::common::uint32_t w,OS::common::uint32_t h,OS::common::uint8_t r,OS::common::uint8_t g,OS::common::uint8_t b);
            
            ~Widget();
            
            virtual void GetFocuse(Widget* widget);
            virtual void ModelToScreen(OS::common::int32_t &x,OS::common::int32_t &y);
            virtual bool ContainsCoordinate(OS::common::uint32_t x,OS::common::uint32_t y);
            virtual void Draw(OS::common::GraphicsContext* gc);
            virtual void OnMouseDown(OS::common::uint32_t x,OS::common::uint32_t y,OS::common::uint32_t button);
            virtual void OnMouseUp(OS::common::uint32_t x,OS::common::uint32_t y,OS::common::uint32_t button);
            virtual void OnMouseMove(OS::common::uint32_t oldx,OS::common::uint32_t oldy,OS::common::uint32_t newx,OS::common::uint32_t newy);
            
            //virtual void OnKeyDown(OS::common::uint32_t x,OS::common::uint32_t y);
            //virtual void OnKeyUp(OS::common::uint32_t x,OS::common::uint32_t y);
            
        };
        class CompositeWidget:public Widget{
        private:
            Widget* childeWidget[100];
            int numChildren;
            Widget* focussedChild;
        public:
            CompositeWidget(Widget* parent,OS::common::uint32_t x,OS::common::uint32_t y,OS::common::uint32_t w,OS::common::uint32_t h,OS::common::uint8_t r,OS::common::uint8_t g,OS::common::uint8_t b);
            
            ~CompositeWidget();
            
            virtual void GetFocuse(Widget* widget);
            virtual void Draw(OS::common::GraphicsContext* gc);
            virtual void OnMouseDown(OS::common::uint32_t x,OS::common::uint32_t y,OS::common::uint32_t button);
            virtual void OnMouseUp(OS::common::uint32_t x,OS::common::uint32_t y,OS::common::uint32_t button);
            virtual void OnMouseMove(OS::common::uint32_t oldx,OS::common::uint32_t oldy,OS::common::uint32_t newx,OS::common::uint32_t newy);
            
            virtual bool AddChild(Widget* child);
            
             virtual void OnkeyDown(char str);
             virtual void OnkeyUp(char str);
        };
    }
}
#endif
