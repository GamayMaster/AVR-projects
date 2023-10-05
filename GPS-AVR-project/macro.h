#ifndef MACRO_H
#define MACRO_H


typedef unsigned char       byte;
typedef unsigned short      word;
typedef unsigned long       dword;
typedef unsigned long long  qword;


#ifndef REGISTER_SIZE
#define REGISTER_SIZE   8
#endif

#ifndef SHL
#define SHL(bit)            (1<<bit)
#endif

#ifndef SHR
#define SHR(bit)            (1>>bit)
#endif

#ifndef ROR
#define ROR(addr, num)      (addr=(addr<<(REGISTER_SIZE-num))|(addr>>num))
#endif

#ifndef ROL
#define ROL(addr, num)      (addr=(addr>>(REGISTER_SIZE-num))|(addr<<num))
#endif

#ifndef _IO
#define _IO(addr)           *((volatile byte*)(addr))
#endif

#ifndef MEM_BYTE
#define MEM_BYTE(addr)      *((volatile byte*)(addr))
#endif

#ifndef MEM_WORD
#define MEM_WORD(addr)      *((volatile word*)(addr))
#endif

#ifndef MEM_DWORD
#define MEM_DWORD(addr)     *((volatile dword*)(addr))
#endif

#ifndef MEM_QWORD
#define MEM_QWORD(addr)     *((volatile qword*)(addr))
#endif

#ifndef SET_BIT
#define SET_BIT(addr, bit)  (addr |= (1<<bit))
#endif

#ifndef CLR_BIT
#define CLR_BIT(addr, bit)  (addr &= ~(1<<bit))
#endif

#ifndef TOG_BIT
#define TOG_BIT(addr, bit)  (addr ^= (1<<bit))
#endif

#ifndef READ_BIT
#define READ_BIT(addr, bit) ((addr&(1<<bit))>>bit)
#endif

#ifndef IS_SET_BIT
#define IS_SET_BIT(addr, bit)   (((addr&(1<<bit))>>bit) == 1 ? 1 : 0)
#endif

#ifndef IS_CLR_BIT
#define IS_CLR_BIT(addr, bit)   ((!((addr&(1<<bit))>>bit)) == 0 ? 1 : 0)
#endif

#ifndef SET_HIGH
#define SET_HIGH(addr)      (addr |= 0xF0)
#endif

#ifndef SET_LOW
#define SET_LOW(addr)       (addr |= 0x0F)
#endif

#ifndef SET_BYTE
#define SET_BYTE(addr, val) (addr = val)
#endif

#ifndef CLR_BYTE
#define CLR_BYTE(addr)      (addr = 0x00)
#endif

#ifndef TOG_BYTE
#define TOG_BYTE(addr)      (addr ^= 0xFF)
#endif

#endif
