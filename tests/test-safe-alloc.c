/*
 * Test the safe-alloc macros
 *
 * Copyright (C) 2009 Free Software Foundation, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 * Author: David Lutterkort <lutter@redhat.com>
 */

#include <config.h>

#include <stdio.h>

#include <safe-alloc.h>

#define ASSERT(expr) \
  do									     \
    {									     \
      if (!(expr))							     \
        {								     \
          fprintf (stderr, "%s:%d: assertion failed\n", __FILE__, __LINE__); \
          fflush (stderr);						     \
          abort ();							     \
        }								     \
    }									     \
  while (0)

int main()
{
  struct tst {
    int a;
    int b;
  };

  struct tst *p = NULL;
  int r;

  r = ALLOC(p);
  ASSERT(r >= 0);

  ASSERT(p->a == 0 && p->b == 0);

  p->a = p->b = 42;
  r = REALLOC_N(p, 5);

  ASSERT(p[0].a == 42 && p[0].b == 42);

  FREE(p);
  ASSERT(p == NULL);
}