#ifndef _VMALLOCATOR_H_INCLUDED_
#define _VMALLOCATOR_H_INCLUDED_

/* SCP_vm_allocator - maintained by portej05 (i.e. please don't patch this one yourself!) */

#include "globalincs/fsmemory.h"

#include <EASTL/vector.h>
#include <EASTL/list.h>
#include <EASTL/map.h>
#include <EASTL/string.h>
#include <EASTL/queue.h>
#include <EASTL/deque.h>
#include <EASTL/hash_map.h>
#include <sstream>

template< typename T >
using SCP_vector = eastl::vector<T>;

template< typename T >
using SCP_list = eastl::list<T>;

typedef eastl::string SCP_string;

template< typename T, typename U >
using SCP_map = eastl::map<T, U>;

template< typename T, typename U >
using SCP_multimap = eastl::multimap<T, U>;

template< typename T >
using SCP_queue = eastl::queue<T>;

template< typename T >
using SCP_deque = eastl::deque<T>;

template< typename Key, typename T, typename Hash = eastl::hash<Key>, typename KeyEqual = eastl::equal_to<Key> >
using SCP_unordered_map = eastl::hash_map<Key, T, Hash, KeyEqual>;

class SCP_stringstream : public std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >
{
public:
	SCP_string str() { return SCP_string(std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >::str().c_str()); }
};

template<typename A, typename B>
using SCP_pair = eastl::pair<A, B>;

template<typename A, typename B>
SCP_pair<A, B> scp_make_pair(A a, B b)
{
	return SCP_pair<A, B>(a, b);
}

#endif // _VMALLOCATOR_H_INCLUDED_
