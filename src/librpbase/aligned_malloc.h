/***************************************************************************
 * ROM Properties Page shell extension. (librpbase)                        *
 * aligned_malloc.h: Aligned memory allocation compatibility header.       *
 *                                                                         *
 * Copyright (c) 2015-2018 by David Korth                                  *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; either version 2 of the License, or (at your  *
 * option) any later version.                                              *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

#ifndef __ROMPROPERTIES_LIBRPBASE_ALIGNED_MALLOC_H__
#define __ROMPROPERTIES_LIBRPBASE_ALIGNED_MALLOC_H__

// References:
// - http://www.gnu.org/software/libc/manual/html_node/Aligned-Memory-Blocks.html
// - https://msdn.microsoft.com/en-us/library/8z34s9c6.aspx
// - http://linux.die.net/man/3/aligned_alloc (needs _ISOC11_SOURCE ?)

/**
 * TODO: Check if the following functions are present:
 * - _aligned_malloc (MSVC)
 * - aligned_alloc (C11)
 * - posix_memalign
 * - memalign
 * If none of these are present, we'll use our own custom
 * aligned malloc().
 */

#include "librpbase/config.librpbase.h"
#include "librpbase/common.h"

/**
 * This header defines two functions if they aren't present:
 * - aligned_malloc(): Allocate aligned memory.
 *   - Same signature as C11 aligned_alloc().
 *   - Returns NULL and sets errno on error.
 *   - NOTE: When using posix_memalign(), alignment must be a
 *     power of two multiple of sizeof(void*).
 * - aligned_free(): Free aligned memory.
 *   - Required for MSVC and custom implementations.
 */

#include <errno.h>

// Alignment for statically-allocated data.
#if defined(_MSC_VER)
# define ALIGN_ATTR(x) __declspec(align(x))
#elif defined(__GNUC__)
# define ALIGN_ATTR(x) __attribute__ ((aligned (x)))
#else
# error Missing ALIGN_ATTR() implementation for this compiler.
#endif

#if defined(HAVE_MSVC_ALIGNED_MALLOC)

// MSVC _aligned_malloc()
#include <malloc.h>

static FORCEINLINE void *aligned_malloc(size_t alignment, size_t size)
{
	return _aligned_malloc(size, alignment);
}

static FORCEINLINE void aligned_free(void *memptr)
{
	_aligned_free(memptr);
}

#elif defined(HAVE_ALIGNED_ALLOC)

// C11 aligned_alloc()
#include <stdlib.h>

static FORCEINLINE void *aligned_malloc(size_t alignment, size_t size)
{
	return aligned_alloc(alignment, size);
}

static FORCEINLINE void aligned_free(void *memptr)
{
	free(memptr);
}

#elif defined(HAVE_POSIX_MEMALIGN)

// posix_memalign()
#include <stdlib.h>

static FORCEINLINE void *aligned_malloc(size_t alignment, size_t size)
{
	void *ptr;
	int ret = posix_memalign(&ptr, alignment, size);
	if (ret != 0) {
		// posix_memalign() returns errno instead of setting it.
		errno = ret;
		return NULL;
	}
	return ptr;
}

static FORCEINLINE void aligned_free(void *memptr)
{
	free(memptr);
}

#elif defined(HAVE_MEMALIGN)

// memalign()
#include <malloc.h>

static FORCEINLINE void *aligned_malloc(size_t alignment, size_t size)
{
	return memalign(alignment, size);
}

static FORCEINLINE void aligned_free(void *memptr)
{
	free(memptr);
}

#else
# error Missing aligned malloc() function for this system.
#endif

#ifdef __cplusplus

// std::unique_ptr<> wrapper for aligned_malloc().
// Reference: https://embeddedartistry.com/blog/2017/2/23/c-smart-pointers-with-aligned-mallocfree
#include <memory>

// NOTE: MSVC 2010 doesn't support "template using".
// TODO: Check 2012; assuming 2013+ for now.
#if !defined(_MSC_VER) || _MSC_VER >= 1800
template<class T> using unique_ptr_aligned = std::unique_ptr<T, decltype(&aligned_free)>;
# define UNIQUE_PTR_ALIGNED_T unique_ptr_aligned<T>
#else /* _MSC_VER < 1900 */
# define UNIQUE_PTR_ALIGNED_T std::unique_ptr<T, decltype(&aligned_free)>
#endif

template<class T>
static inline UNIQUE_PTR_ALIGNED_T aligned_uptr(size_t align, size_t size)
{
	return UNIQUE_PTR_ALIGNED_T(
		static_cast<T*>(aligned_malloc(align, size)), 
		&aligned_free);
}

#endif /* __cplusplus */

#endif /* __ROMPROPERTIES_LIBRPBASE_ALIGNED_MALLOC_H__ */
