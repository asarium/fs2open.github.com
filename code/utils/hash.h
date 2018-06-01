#pragma once

#include <functional>
#include <type_traits>

namespace util {

template <typename T>
struct EnumHasher {
	std::size_t operator()(T value) const
	{
		return ::std::hash<typename ::std::underlying_type<T>::type>()(
		    static_cast<typename ::std::underlying_type<T>::type>(value));
	}
};

} // namespace util

#if __cplusplus < 201402L
/**
 * @brief Defines a std::hash specialization for the specified enum class
 *
 * This can be used for making enum class types usable as keys in unordered maps.
 *
 * @note C++14 provides automatic definition of enum hashes. For every version before that this macro can be used to
 * define an equivalent hash
 *
 * @warning A usage of this macro must appear in the global scope since it defines types in the std namespace!
 */
#define DEFINE_ENUM_HASH(enum_cls)                                                                                     \
	namespace std {                                                                                                    \
	template <>                                                                                                        \
	struct hash<enum_cls> : public ::util::EnumHasher<enum_cls> {                                                      \
	};                                                                                                                 \
	}
#else
#define DEFINE_ENUM_HASH(enum_cls)
#endif
