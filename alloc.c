#include "internal.h"
#include <assert.h>

#undef malloc
#undef free
#undef realloc
#undef calloc
#undef strdup
#undef wcsdup

#ifdef _WIN32
static HANDLE rb_global_heap;
#undef _msize
#endif

void rb_init_global_heap(void)
{
#ifdef _WIN32
    rb_global_heap = HeapCreate(0, 0, 0);
    /* TODO: Better error handling */
    assert(rb_global_heap);
#endif
}

void rb_cleanup_global_heap(void)
{
#ifdef _WIN32
    BOOL fOk = HeapDestroy(rb_global_heap);
    /* TODO: Better error handling */
    assert(fOk);
#endif
}

void* rb_malloc(size_t n)
{
#ifdef _WIN32
    if (!rb_global_heap)
    {
        rb_init_global_heap();
    }
    return HeapAlloc(rb_global_heap, 0, n);
#else
    return malloc(n);
#endif
}

void* rb_realloc(void* ptr, size_t n)
{
#ifdef _WIN32
    if (!rb_global_heap)
    {
        rb_init_global_heap();
    }

    if (ptr)
    {
        return HeapReAlloc(rb_global_heap, 0, ptr, n);
    }
    else
    {
        /* Protect against NULL ptr on input. HeapReAlloc doesn't handle that */
        return HeapAlloc(rb_global_heap, 0, n);
    }
    
    return HeapAlloc(rb_global_heap, 0, n);
#else
    return realloc(ptr, n);
#endif
}

void* rb_calloc(size_t num, size_t size)
{
#ifdef _WIN32
    if (!rb_global_heap)
    {
        rb_init_global_heap();
    }
    return HeapAlloc(rb_global_heap, HEAP_ZERO_MEMORY, num * size);
#else
    return calloc(num, size);
#endif
}

void rb_free(void* p)
{
#ifdef _WIN32
    HeapFree(rb_global_heap, 0, p);
#else
    free(p);
#endif
}

char* rb_strdup(const char* s)
{
    const int len = strlen(s);
    char* ret = rb_malloc(len+1);
    if (!ret)
    {
        return ret;
    }
    memcpy(ret, s, len+1);
    return ret;
}

wchar_t* rb_wcsdup(const wchar_t* s)
{
    const int len = wcslen(s);
    wchar_t* ret = rb_malloc((len+1)*sizeof(*s));
    if (!ret)
    {
        return ret;
    }
    memcpy(ret, s, (len+1)*sizeof(*s));
    return ret;
}

#ifdef _WIN32
size_t rb_w32_msize(void* p)
{
    return HeapSize(rb_global_heap, 0, p);
}
#endif
