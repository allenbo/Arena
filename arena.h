#ifndef __PYARENA_H__
#define __PYARENA_H__

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct _arena Arena;

  Arena * arena_New(void);
  void arena_Free(Arena *);

  void* arena_Malloc(Arena *, size_t size);
#ifdef __cplusplus
}
#endif

#endif /* !Py_PYARENA_H */
