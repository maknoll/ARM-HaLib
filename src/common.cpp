#include <cstring>

extern "C" void* memset(void* buffer, int c, size_t s)
{
    unsigned int pat4;
    pat4  = c&0xff << 24;
    pat4 |= c&0xff << 16;
    pat4 |= c&0xff <<  8;
    pat4 |= c&0xff <<  0;
    unsigned int* ptr4 = reinterpret_cast<unsigned int*>(buffer);
    for(unsigned int i=0;i<s/4-1;i++)
        ptr4[i]=pat4;

    char* ptr1 = reinterpret_cast<char*>(buffer);
    for(unsigned int i=s-(s%4);i<s;i++)
        ptr1[i]=c;

    return buffer;
}
