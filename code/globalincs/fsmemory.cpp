
#include "globalincs/pstypes.h"


// throw
void * operator new (size_t size)
{
	void *p = vm_malloc_q(size);

	if ( !p ) {
		throw std::bad_alloc();
	}

	return p;
}

void operator delete (void *p) throw()
{
	vm_free(p);
}

void * operator new [] (size_t size)
{
	void *p = vm_malloc_q(size);

	if ( !p ) {
		throw std::bad_alloc();
	}

	return p;
}

void operator delete [] (void *p) throw()
{
	vm_free(p);
}

// no-throw
void * operator new (size_t size, const std::nothrow_t&) throw()
{
	return vm_malloc_q(size);
}

void operator delete (void *p, const std::nothrow_t&) throw()
{
	vm_free(p);
}

void * operator new [] (size_t size, const std::nothrow_t&) throw()
{
	return vm_malloc_q(size);
}

void operator delete [] (void *p, const std::nothrow_t&) throw()
{
	vm_free(p);
}

void* operator new[](size_t size, const char*, int, unsigned, const char* file, int line)
{
#ifndef NDEBUG
	return _vm_malloc(size, const_cast<char*>(file), line);
#else
	return vm_malloc(size);
#endif
}

void* operator new[](size_t size, size_t, size_t, const char*, int, unsigned, const char* file, int line)
{
#ifndef NDEBUG
	return _vm_malloc(size, const_cast<char*>(file), line);
#else
	return vm_malloc(size);
#endif
}
