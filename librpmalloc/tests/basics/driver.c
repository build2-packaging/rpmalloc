#include <string.h>

#include <rpmalloc/rpmalloc.h>

#undef NDEBUG
#include <assert.h>

int main (void)
{
  assert (rpmalloc_initialize (0) == 0);

  /* Allocate, reallocate, and free.
   */
  {
    char *p = rpmalloc (16);
    assert (p != 0 && rpmalloc_usable_size (p) >= 16);
    memcpy (p, "Hello, World!", 14);

    p = rprealloc (p, 4096);
    assert (p != 0 && strcmp (p, "Hello, World!") == 0);

    rpfree (p);
  }

  rpmalloc_finalize ();
  return 0;
}
