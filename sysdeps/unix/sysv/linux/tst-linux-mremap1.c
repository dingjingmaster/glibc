/* Test mremap with MREMAP_DONTUNMAP.
   Copyright (C) 2024-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <sys/mman.h>
#include <support/xstdlib.h>
#include <support/xunistd.h>
#include <support/check.h>
#include <support/test-driver.h>
#include <mremap-failure.h>

static int
do_test (void)
{
  size_t old_size = getpagesize ();
  size_t new_size = old_size;
  char *old_addr = xmmap (NULL, old_size, PROT_READ | PROT_WRITE,
			  MAP_PRIVATE | MAP_ANONYMOUS, -1);
  old_addr[0] = 1;
  old_addr[old_size - 1] = 2;

  /* Create an available 64-page mmap region.  */
  size_t fixed_size = old_size * 64;
  char *fixed_addr = xmmap (NULL, fixed_size, PROT_READ | PROT_WRITE,
			    MAP_PRIVATE | MAP_ANONYMOUS, -1);
  xmunmap (fixed_addr, fixed_size);

  /* Add 3 * pagesize.  */
  fixed_size += 3 * old_size;

  /* Test MREMAP_DONTUNMAP.  It should return FIXED_ADDR created above.  */
  char *new_addr = mremap (old_addr, old_size, new_size,
			   MREMAP_DONTUNMAP | MREMAP_MAYMOVE,
			   fixed_addr);
  if (new_addr == MAP_FAILED)
    return mremap_failure_exit (errno);
  TEST_VERIFY_EXIT (fixed_addr == new_addr);
  old_addr[0] = 3;
  old_addr[old_size - 1] = 4;
  new_addr[0] = 1;
  new_addr[new_size - 1] = 2;
  xmunmap (new_addr, new_size);
  xmunmap (old_addr, old_size);

  return 0;
}

#include <support/test-driver.c>
