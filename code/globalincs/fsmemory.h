
#ifndef _FSMEMORY_H
#define _FSMEMORY_H

#include <new>

// throw
extern void * operator new (size_t size);

extern void operator delete (void *p) throw();

extern void * operator new [] (size_t size);

extern void operator delete [] (void *p) throw();

// no-throw
extern void * operator new (size_t size, const std::nothrow_t&) throw();

extern void operator delete (void *p, const std::nothrow_t&) throw();

extern void * operator new [] (size_t size, const std::nothrow_t&) throw();

extern void operator delete [] (void *p, const std::nothrow_t&) throw();

// Definitions for EASTL
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);


#endif	// _FSMEMORY_H
