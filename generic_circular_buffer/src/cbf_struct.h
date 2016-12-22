#ifndef CBF_STRUCT_H  // Guards against multiple inclusion
#define CBF_STRUCT_H

struct CBF_BUFFER_S
{
    void* buffer;
    void* write;
    void* read;
    void* end;
};


#endif
