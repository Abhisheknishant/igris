#ifndef IGRIS_DATASTRUCT_POOL_H
#define IGRIS_DATASTRUCT_POOL_H

#include <igris/datastruct/slist.h>
#include <assert.h>

struct pool_head
{
	struct slist_head free_blocks;
};

__BEGIN_DECLS

static inline void pool_init(struct pool_head* head)
{
	slist_init(&head->free_blocks);
}

static inline void pool_engage(struct pool_head* pool,
                               void* zone, size_t size, size_t elemsz)
{
	assert(size % elemsz == 0);

	char* stop = (char*)zone + size;
	char* it = (char*)zone;

	while (it < stop)
	{
		slist_add((slist_head*)it, &pool->free_blocks);
		it += elemsz;
	}
}

static inline void* pool_alloc(struct pool_head* head)
{
	if (slist_empty(&head->free_blocks))
		return nullptr;

	return (void*) slist_pop_first(&head->free_blocks);
}

static inline void pool_free(struct pool_head* head, void* ptr)
{
	slist_add((slist_head*) ptr, &head->free_blocks);
}

static inline size_t pool_avail(const struct pool_head* head)
{
	dprln("EEEE");
	return slist_size(&head->free_blocks);
}

__END_DECLS

#endif