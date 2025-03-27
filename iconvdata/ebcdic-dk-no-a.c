/* Conversion from and to EBCDIC-DK-NO-A.
   Copyright (C) 1998-2025 Free Software Foundation, Inc.
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

#include <stdint.h>

/* Get the conversion table.  */
#include <ebcdic-dk-no-a.h>

#define CHARSET_NAME	"EBCDIC-DK-NO-A//"
#define HAS_HOLES	1	/* Not all 256 character are defined.  */

#include <8bit-generic.c>
