#include<GUI/desktop.h>
#include<drivers/mouse.h>
using namespace OS;
using namespace OS::common;
using namespace OS::GUI;
using namespace OS::drivers;

Desktop::Desktop(uint32_t w,uint32_t h,uint8_t r,uint8_t g,uint8_t b):                        CompositeWidget(0,0,0,w,h,r,g,b),
 MouseEventHandlers()
{
    MouseX=w/2;
    MouseY=h/2;
}

void Desktop::Draw(GraphicsContext* gc){
    CompositeWidget::Draw(gc);
    for(int i=0;i<4;i++){
        gc->putPexil(MouseX+i,MouseY,0xFF,0xFF,0xFF);
        gc->putPexil(MouseX+i,MouseY,0xFF,0xFF,0xFF);
        gc->putPexil(MouseX,MouseY+i,0xFF,0xFF,0xFF);
        gc->putPexil(MouseX,MouseY+i,0xFF,0xFF,0xFF);
    }
}
void Desktop::OnMouseUp(uint8_t button){
    CompositeWidget::OnMouseUp(MouseX,MouseY,button);
}
void Desktop::OnMouseDown(uint8_t button){
      CompositeWidget::OnMouseDown(MouseX,MouseY,button);  
}
void Desktop::OnMove(int x,int y){
    x/=4;
    y/=4;
    int32_t newMouseX=MouseX +x;
    if(newMouseX<0)
        newMouseX=0;
    if(newMouseX>w)
        newMouseX=w-1;
    int32_t newMouseY=MouseY +y;
    if(newMouseY <0)
        newMouseY=0;
    if(newMouseY>h)
        newMouseY=h-1;
    CompositeWidget::OnMouseMove(MouseX,MouseY,newMouseX,newMouseY);
    
    MouseX=newMouseX;
    MouseY=newMouseY;
}
