#include <Windows.h>
#include <winternl.h>
#include <Psapi.h>
#ifdef _DEBUG
#include "usermode.h"

bool mem::memory::setup( ) {
	HANDLE ss = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
	if ( ss ) 
	{
		HANDLE process = NULL;
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof( PROCESSENTRY32 );
		if ( Process32First( ss, &pe ) ) {do {if ( !wcscmp( pe.szExeFile, ( L"RustClient.exe" ) ) ) {process = OpenProcess( PROCESS_ALL_ACCESS, false, pe.th32ProcessID );}} while ( Process32Next( ss, &pe ) );}
		CloseHandle( ss );
		process_handle = process;
	}
	return process_handle;
}

void mem::memory::read( uintptr_t address, void* buffer, size_t size ) {
	if ( process_handle )
		ReadProcessMemory( process_handle, ( LPCVOID )address, buffer, size, 0 );
}

void mem::memory::write( uintptr_t address, void* buffer, size_t size ) {
	if ( process_handle )
		WriteProcessMemory( process_handle, ( LPVOID )address, &buffer, size, NULL );
}

mem::memory::module_t mem::memory::get_module( const std::wstring& name ) {
	module_t mod = { 0 };
	HANDLE ss = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, GetProcessId( process_handle ) );
	if ( ss ) {
		MODULEENTRY32 me;
		me.dwSize = sizeof( MODULEENTRY32 );
		if ( Module32First( ss, &me ) ) {do {if ( !wcscmp( me.szModule, name.data( ) ) ) {mod.base = ( uint64_t )me.modBaseAddr;mod.size = ( uint64_t )me.modBaseSize;break;}} while ( Module32Next( ss, &me ) );}
		CloseHandle( ss );
	}
	return mod;
}
#endif // _DEBUG
