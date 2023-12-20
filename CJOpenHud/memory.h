#pragma once
#include <Windows.h>
#include <unordered_map>
#include <functional>
#include <string>
namespace mem
{
	struct mem_protect
	{
		DWORD orig;
		size_t size;
		mem_protect()
		{
			orig = 0;
			size = 0;
		}
		mem_protect(DWORD _orig, size_t _size)
		{
			orig = _orig;
			size = _size;
		}
	};

	HMODULE find_module(std::string regex_str);
	uint64_t find_pattern(HMODULE module, const char* pattern);

	template<typename T>
	void write(int target, T value)
	{
		DWORD oldprotect;
		int size = sizeof(value);
		VirtualProtect((PVOID*)target, size, PAGE_EXECUTE_READWRITE, &oldprotect);
		*(T*)target = value;
		VirtualProtect((PVOID*)target, size, oldprotect, &oldprotect);
	}

	BYTE* mem_set(int target, int val, int size);
	BYTE* copy(int target, BYTE* source, int size);
	BYTE* mem_get(int target, int size);
	void unprotect_memory(PVOID target, size_t size);
	void reset_memory_protection(PVOID target);
	extern std::unordered_map<PVOID, mem_protect> protections;
	int instruction_to_absolute_address(int instruction_address); //assumes 32 bit
	template <typename T>
	class function
	{
	public:
		using result_type = typename std::function<T>::result_type;
		std::uintptr_t fn_address;
		function() : func_(reinterpret_cast<T*>(nullptr))
		{
			fn_address = 0;
		};

		function(const std::uintptr_t& address) : func_(reinterpret_cast<T*>(address))
		{
			fn_address = address;
		}

		function(const function<T>& function) : func_(function.func_), fn_address(0)
		{
			//fn_address = (int)&function;
		}

		function& operator=(const std::uintptr_t& address)
		{
			fn_address = address;
			this->func_ = std::function<T>(reinterpret_cast<T*>(address));
			return *this;
		}

		function& operator=(const function<T>& function)
		{
			this->func_ = function.func_;
			return *this;
		}

		template <typename ...Args>
		result_type operator()(Args&& ...args)
		{
			return this->func_(args...);
		}

		result_type operator()(void)
		{
			return this->func_();
		}

		T* get() const
		{
			return func_;
		}

		operator void* () const
		{
			return this->func_;
		}

	protected:
		T* func_;
	};

}