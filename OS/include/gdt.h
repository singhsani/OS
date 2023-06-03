//header file for global descriptor table
#ifndef __OS__GDT_H
#define __OS__GDT_H
#include <common/types.h>
//start class for global descriptor table
namespace OS{
    
        class GlobalDescripterTable{
        public:
            class SegmentDescripter{
            private:
                OS::common::uint16_t limit_lo;
                OS::common::uint16_t base_lo;
                OS::common::uint8_t base_hi;
                OS::common::uint8_t type;
                OS::common::uint8_t flags_limit_hi;
                OS::common::uint8_t base_vhi;
            public:
                SegmentDescripter(OS::common::uint32_t base,OS::common::uint32_t limit,OS::common::uint8_t type);
                OS::common::uint32_t Base();
                OS::common::uint32_t Limit();
            }__attribute__((packed));
            //RAM partition into four part 
        private:
            SegmentDescripter nullSegmentSelector;
            SegmentDescripter unusedSegmentSelector;
            SegmentDescripter codeSegmentSelector;
            SegmentDescripter dataSegmentSelector; 
            
        public:
            //constructor call
            GlobalDescripterTable();
            //deconstructor call
            ~GlobalDescripterTable();
            //code and data part or RAM
            OS::common::uint16_t CodeSegmentSelector();
            OS::common::uint16_t DataSegmentSelector();
        };
}
#endif
