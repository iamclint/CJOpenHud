#include "pch.h"
#include "hook_wrapper.h"

void hook::replace(int addr, int dest)
{
	if (*(BYTE*)addr == 0xE9 || *(BYTE*)addr == 0xE8)
	{
		destination = (DWORD)dest;
		address = (DWORD)addr;
		trampoline = mem::instruction_to_absolute_address(addr);
		DWORD old;
		VirtualProtect((LPVOID)addr, 0x5, PAGE_EXECUTE_READWRITE, &old);
		memcpy(p_orig, (LPVOID)addr, 5);
		*(DWORD*)(addr + 1) = dest - addr - 5;
		VirtualProtect((LPVOID)addr, 0x5, old, NULL);
	}
}

void hook::detour(int addr, int dest)
{
	//PLH::ZydisDisassembler dis(PLH::Mode::x86);
	phook = new PLH::x86Detour((uint64_t)addr, (uint64_t)dest, (uint64_t*)&trampoline);
	phook->hook();

	mem::copy((int)&local_orig, (BYTE*)dest, 5);
}

bool hook::is_local_hooked()
{
	BYTE local[5];
	mem::copy((int)&local, (BYTE*)destination, 5);
	return memcmp(local, local_orig, 5) != 0;
}

void hook::replace_call(int addr, int dest)
{
	replace(addr, dest);
	mem::copy((int)&local_orig, (BYTE*)dest, 5);
}
void hook::rehook()
{

	if (hook_type == hook_type_detour)
	{
		//phook->reHook();
		detour(address, destination);
	}
	else
		replace_call(address, destination);
}

void hook::remove()
{
	if (hook_type != hook_type_detour)
		mem::copy(address, p_orig, 5);
	else
		if (phook)
		{
			phook->unHook();
			delete phook;
		}
}
