# librpmalloc - Lock-free thread-caching memory allocator C library

This is a `build2` package for the [`rpmalloc`](https://github.com/mjansson/rpmalloc)
C library. It provides a cross-platform, lock-free, thread-caching memory
allocator with 16-byte aligned allocations and a `malloc`-style API
(`rpmalloc()`, `rpfree()`, etc.) that can optionally also override the
standard library `malloc()` family.


## Usage

To start using `librpmalloc` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: librpmalloc ^2.0.1
```

Then import the library in your `buildfile`:

```
import libs = librpmalloc%lib{rpmalloc}
```


## Importable targets

This package provides the following importable targets:

```
lib{rpmalloc}
```

The public headers can be included either as `<rpmalloc/rpmalloc.h>` and
`<rpmalloc/rpnew.h>` or, as in the upstream documentation, as `<rpmalloc.h>`
and `<rpnew.h>`.


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.librpmalloc.override          ?= ($c.target.system != 'win32-msvc')
[bool] config.librpmalloc.first_class_heaps ?= false
[bool] config.librpmalloc.heap_statistics   ?= false
[bool] config.librpmalloc.statistics        ?= false
[bool] config.librpmalloc.leak_detection    ?= ($config.librpmalloc.statistics && \
                                                !$config.librpmalloc.override)
[bool] config.librpmalloc.validate_args     ?= false
[bool] config.librpmalloc.asserts           ?= false
```

These variables correspond to the upstream compile-time options (see the
"Configuration options" section in the upstream `README.md` and the
`rpmalloc.h` header for details).

`override` (`ENABLE_OVERRIDE`) overrides the standard library `malloc()`
family (and, on platforms other than Windows, the C++ `new` and `delete`
operators) with automatic process and thread initialization and
finalization. It is disabled by default when targeting the MSVC runtime
since the `malloc()` family imported from its DLL variant (`/MD`), which
`build2` uses by default, cannot be overridden. Enable it when building
with the static runtime (`/MT`).

`first_class_heaps` (`RPMALLOC_FIRST_CLASS_HEAPS`) enables the explicit heap
API (`rpmalloc_heap_*()`). Its declarations in `rpmalloc.h` are made
available to consumers automatically.

`heap_statistics` (`RPMALLOC_HEAP_STATISTICS`) enables collection of the
per-heap statistics returned by `rpmalloc_heap_statistics()`. It only has
an effect together with `first_class_heaps`.

`statistics` (`ENABLE_STATISTICS`) enables collection of detailed memory
page and heap statistics at a small runtime cost.

`leak_detection` (`ENABLE_LEAK_DETECTION`) enables detection of allocations
still outstanding at `rpmalloc_finalize()` and requires `statistics`. By
default, it follows `statistics` unless `override` is enabled.

`validate_args` (`ENABLE_VALIDATE_ARGS`) enables integer overflow checks on
the size arguments.

`asserts` (`ENABLE_ASSERTS`) enables internal consistency asserts.
