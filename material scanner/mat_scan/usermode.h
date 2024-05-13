#include <memory>
#include <Windows.h>
#include <string>
#include <Psapi.h>
#include <TlHelp32.h>

#ifdef _DEBUG
namespace mem::memory {
	typedef struct _module {uint64_t base;uint64_t size;}module_t;
	inline HANDLE process_handle = 0;
	bool setup( );
	void read( uintptr_t, void*, size_t );
	template <typename type>
	inline type read( uintptr_t address ) {type buffer{};read( address, &buffer, sizeof( type ) );return buffer;}
	void write( uintptr_t, void*, size_t );
	template <typename type>
	inline void write( uintptr_t address, type buffer ) {write( address, &buffer, sizeof( buffer ) );}
	module_t get_module( const std::wstring& name );
}
#endif // _DEBUG
