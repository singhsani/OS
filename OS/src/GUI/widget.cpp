#include<GUI/widget.h>
using namespace OS::common;
using namespace OS::GUI;

Widget::Widget(Widget* parent,uint32_t x,uint32_t y,uint32_t w,uint32_t h,uint8_t r,uint8_t g,uint8_t b):KeyBoardEventHandler(){
    this->parent=parent;
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
    this->r=r;
    this->g=g;
    this->b=b;
    this->focusable=true;
}
            
Widget::~Widget(){
}

bool Widget::ContainsCoordinate(uint32_t x,uint32_t y){
    return this->x <= x && x < this->x + this->w
    && this->y <= y && y< this->y + this->h;
}
            
void Widget::GetFocuse(Widget* widget){
    if(parent!=0)
        parent->GetFocuse(widget);
    
}
void Widget::ModelToScreen(int32_t &x,int32_t &y){
    if(parent!=0)
        parent->ModelToScreen(x,y);
    x+=this->x;
    y+=this->y;
}
void Widget::Draw(GraphicsContext* gc){
    int X=0;
    int Y=0;
    ModelToScreen(X,Y);
    gc->FillRectangle(X,Y,w,h,r,g,b);
    
}
void Widget::OnMouseDown(uint32_t x,uint32_t y,uint32_t button){
    if(focusable)
        GetFocuse(this);
}
void Widget::OnMouseUp(uint32_t x,uint32_t y,uint32_t button){
    
}
void Widget::OnMouseMove(uint32_t oldx,uint32_t oldy,uint32_t newx,uint32_t newy){
    
}

CompositeWidget::CompositeWidget(Widget* parent,uint32_t x,uint32_t y,uint32_t w,uint32_t h,uint8_t r,uint8_t g,uint8_t b):Widget(parent,x,y,w,h,r,g,b){
    this->focussedChild=0;
    numChildren=0;
}
            
CompositeWidget::~CompositeWidget(){
}
            
void CompositeWidget::GetFocuse(Widget* widget){
    this->focussedChild=widget;
    if(parent!=0)
        parent->GetFocuse(this);
}
void CompositeWidget::Draw(GraphicsContext* gc){
    Widget::Draw(gc);
    for(int i=numChildren-1;i>=0;--i)
        childeWidget[i]->Draw(gc);
}
void CompositeWidget::OnMouseDown(uint32_t x,uint32_t y,uint32_t button){
    for(int i=0;i<numChildren;++i){
        if(childeWidget[i]->ContainsCoordinate(x-this->x,y-this->y)){
            childeWidget[i]->OnMouseDown(x-this->x,y-this->y,button);
            break;
        }
    }
}
void CompositeWidget::OnMouseUp(uint32_t x,uint32_t y,uint32_t button){
    for(int i=0;i<numChildren;++i){
        if(childeWidget[i]->ContainsCoordinate(x-this->x,y-this->y)){
            childeWidget[i]->OnMouseUp(x-this->x,y-this->y,button);
            break;
        }
    }
}
void CompositeWidget::OnMouseMove(uint32_t oldx,uint32_t oldy,uint32_t newx,uint32_t newy){
    int firstChild=-1;
    for(int i=0;i<numChildren;++i){
        if(childeWidget[i]->ContainsCoordinate(oldx-this->x,oldy-this->y)){
        childeWidget[i]->OnMouseMove(oldx-this->x,oldy-this->y,newx-this->x,newy-this->y);
        firstChild=i;
            break;
        }
    }
    for(int i=0;i<numChildren;++i){
        if(childeWidget[i]->ContainsCoordinate(newx-this->x,newy-this->y)){
            if(firstChild!=i)
                childeWidget[i]->OnMouseMove(oldx-this->x,oldy-this->y,newx-this->x,newy-this->y);
            break;
        }
    }
}

bool CompositeWidget::AddChild(Widget* child){
    if(numChildren >= 100)
        return false;
    childeWidget[numChildren++]=child;
    return true;
}

void CompositeWidget::OnkeyDown(char str){
    if(focussedChild!=0)
        focussedChild->OnkeyDown(str);
}
void CompositeWidget::OnkeyUp(char str){
    if(focussedChild!=0)
        focussedChild->OnkeyUp(str);
}
