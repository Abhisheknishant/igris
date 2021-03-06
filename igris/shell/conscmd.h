#ifndef IGRIS_SYSCMD_H
#define IGRIS_SYSCMD_H

#include <igris/datastruct/dlist.h>

#define SH_INTERNAL_SPLIT 0x01

#define CMDFUNC 0
#define CMDAUTOM 1
#define CMDCOOP 2

#define SYSCMD_OK 0

#define SYSCMD_TBLFIN {NULL,NULL,0,NULL}

namespace igris 
{
	using syscmd_func_t = int (*)(int, char**);

	struct console_command 
	{
		const char* name;
		void * func;
		uint8_t type;
		const char* help;

		constexpr console_command(
			const char* name,
			int (*func)(int, char**),
			uint8_t type,
			const char* help) 
		:
			name(name),
			func(nullptr),
			type(type),
			help(help)
		{
			this->func = (void*)func;
		}		

		constexpr console_command(
			const char* name,
			int (*func)(int, char**),
			const char* help = nullptr) 
		:
			name(name),
			func(nullptr),
			type(CMDFUNC),
			help(help)
		{
			this->func = (void*)func;
		}

		constexpr console_command(
			const char* name,
			void (*func)(),
			const char* help = nullptr) 
		:
			name(name),
			func(nullptr),
			type(CMDFUNC),
			help(help)
		{
			this->func = (void*)func;
		}

		constexpr console_command(
			const char* name,
			void *func,
			const char* help = nullptr) 
		:
			name(name),
			func(nullptr),
			type(CMDFUNC),
			help(help)
		{
			this->func = (void*)func;
		}
	};
}

#define SYSCMD(name, ...) \
igris::console_command name[] {__VA_ARGS__, SYSCMD_TBLFIN}

#endif