
if(CROSS_COMPILING)
	return()
endif(CROSS_COMPILING)

include(CheckCXXSourceCompiles)

CHECK_CXX_SOURCE_COMPILES("#include <type_traits>
int main()
{
	return std::is_trivial<int>::value ? 1 : 0;
}
" HAS_CXX11_IS_TRIVIAL)

CHECK_CXX_SOURCE_COMPILES("#include <type_traits>
int main()
{
	return std::is_trivially_copyable<int>::value ? 1 : 0;
}
" HAS_CXX11_IS_TRIVIALLY_COPYABLE)

CHECK_CXX_SOURCE_COMPILES("
int main()
{
	static_assert(true, \"dummy\");
	return 0;
}
" HAS_CXX11_STATIC_ASSERT)

CHECK_CXX_SOURCE_COMPILES("
int main()
{
	auto a = 42;
	return a;
}
" HAS_CXX11_AUTO)

CHECK_CXX_SOURCE_COMPILES("
class base
{
	virtual void a() = 0;
};
class deriv : public base
{
	virtual void a() override {}
};

int main() {return 0;}
" HAS_CXX11_OVERRIDE)

CHECK_CXX_SOURCE_COMPILES("int main() noexcept {return 0;}" HAS_CXX11_NOEXCEPT)

configure_file(${CODE_HEADERS}/compiler.h.in ${GENERATED_SOURCE_DIR}/compiler.h)
