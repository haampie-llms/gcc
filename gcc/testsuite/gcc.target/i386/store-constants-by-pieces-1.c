/* { dg-do compile } */
/* { dg-options "-O2 -mavx2 -fno-store-constants-by-pieces" } */

void
foo (char *d)
{
  __builtin_memcpy (d, "/opt/memcpy/0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz/foo", 88);
}

void
bar (void (*f) (char *))
{
  char b[] = "/opt/array/0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz/bar";
  f (b);
}

/* { dg-final { scan-assembler "/opt/memcpy/0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz/foo" } } */
/* { dg-final { scan-assembler "/opt/array/0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz/bar" } } */
