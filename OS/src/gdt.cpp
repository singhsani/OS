//globla descriptor table cpp file
#include <gdt.h>
#include<common/types.h>//header file 
using namespace OS;
using namespace OS::common;

GlobalDescripterTable::GlobalDescripterTable()
:nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,64*1024*1024,0x9A),
dataSegmentSelector(0,64*1024*1024,0x92){
    uint32_t i[2];
    i[0]=(uint32_t)this;
    i[1]=sizeof(GlobalDescripterTable)<<16;
    asm volatile("lgdt (%0)": :"p" (((uint8_t *)i)+2));
}

GlobalDescripterTable::~GlobalDescripterTable(){
}
uint16_t GlobalDescripterTable::DataSegmentSelector(){
    return (uint8_t *)&dataSegmentSelector - (uint8_t *)this;
}
uint16_t GlobalDescripterTable::CodeSegmentSelector(){
    return (uint8_t *)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescripterTable::SegmentDescripter::SegmentDescripter(uint32_t base,uint32_t limit,uint8_t flags){
    uint8_t* target=(uint8_t*)this;
    if(limit<=65536){
        target[6]=0x40;
    }else{
        if((limit & 0xFFF)!=0xFFF)//0xFFF=1000000000000 & 65539=010000000000000011=3
        {
            limit=(limit>>12)-1;
        }else{
            limit=limit>>12;
        target[6]=0xC0;//0xc0=192
        }
    }
    target[0]=limit & 0xFF;//limit is 65539 & 0xFF=255 =3 
    target[1]=(limit>>8) & 0xFF;//128
    target[6] |=(limit>>16) & 0xF;// 1
    //set base part of RAM
    target[2]=base & 0xFF;
    target[3]=(base>>8) & 0xFF;
    target[4]=(base>>16) & 0xFF;
    target[7]=(base >> 24) & 0xFF;
    
    //set flags in RAM
    target[5]=flags;
}
uint32_t GlobalDescripterTable::SegmentDescripter::Base(){
    uint8_t* target=(uint8_t *)this;
    uint32_t result=target[7];
    result=(result<<8)+target[4];
    result=(result<<8)+target[3];
    result=(result<<8)+target[2];
    return result;
}
uint32_t GlobalDescripterTable::SegmentDescripter::Limit(){
    uint8_t* target=(uint8_t *)this;
    uint32_t result=target[6] & 0xF;
    result=(result<<8)+target[1] ;
    result=(result<<8) + target[0];
    
    if((target[6] & 0xC0)==0xC0)
        result=(result<<12) | 0xFFF;
    return result;
}
    
