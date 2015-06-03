
#ifndef _FSMEMORY_H
#define _FSMEMORY_H

#include <new>
#include <cstddef>

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

#endif	// _FSMEMORY_H
