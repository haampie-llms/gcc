/* { dg-do compile { target { ! ia32 } } } */
/* { dg-options "-O2 -mgeneral-regs-only -fno-split-string-constants" } */

/* -fno-split-string-constants only affects strings longer than a word:
   short strings and constants that are not strings are still materialized
   as immediates.  */

struct s { long a, b, c; };
static const struct s k = { 0x1122334455667788, 2, 3 };

void
copy_struct (struct s *d)
{
  __builtin_memcpy (d, &k, sizeof k);
}

void
copy_short (char *d)
{
  __builtin_memcpy (d, "/usr/lib", 8);
}

/* { dg-final { scan-assembler {movabsq\s+\$1234605616436508552,} } } */
/* { dg-final { scan-assembler {movabsq\s+\$7091318039310988591,} } } */
