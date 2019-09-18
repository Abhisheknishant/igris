#ifndef NOS_UTIL_LOCATION_H
#define NOS_UTIL_LOCATION_H

//Определение позиции в коде. Для трассировки.
#include <igris/dprint.h>
#include <igris/compiler.h>

struct location {
	int line;
	const char* file;
	const char* func;
};

#define CURRENT_LOCATION(name)				\
	struct location name = { __LINE__, __FILE__, __func__ };

#define CURRENT_LOCATION_INITARGS __LINE__,__FILE__,__func__

__BEGIN_DECLS

static inline void debug_print_location(struct location location) {
	dpr("file: "); dpr(location.file); dln();
	dpr("func: "); dpr(location.func); dln();
	dpr("line: "); dpr(location.line); dln();
}

__END_DECLS

#endif
