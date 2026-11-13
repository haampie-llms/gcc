/* { dg-do compile { target { ! ia32 } } } */
/* { dg-options "-O2 -mavx2 -fno-split-string-constants" } */

/* With -fno-split-string-constants, inline copies and comparisons of string
   constants longer than a word read the string from memory instead of
   materializing its bytes as immediates or constant pool entries, so every
   string below is emitted intact.  */

#define P "/opt/prefix_placehold_placehold_placehold_placehold"

void use (char *);

void
copy (char *d)
{
  __builtin_memcpy (d, P "/a", sizeof (P "/a"));
}

void
init (void)
{
  char buf[128] = P "/b";
  use (buf);
}

int
compare (const char *p)
{
  return __builtin_memcmp (p, P "/c", sizeof (P "/c") - 1) == 0;
}

void
pad (char *d)
{
  __builtin_strncpy (d, P "/d", 96);
}

void
merge (char *d)
{
  __builtin_memcpy (d, P "/e", sizeof (P "/e") - 1);
  __builtin_memset (d + sizeof (P "/e") - 1, 'x', 4);
}

/* { dg-final { scan-assembler "\"/opt/prefix_placehold_placehold_placehold_placehold/a\"" } } */
/* { dg-final { scan-assembler "\"/opt/prefix_placehold_placehold_placehold_placehold/b\"" } } */
/* { dg-final { scan-assembler "\"/opt/prefix_placehold_placehold_placehold_placehold/c\"" } } */
/* { dg-final { scan-assembler "\"/opt/prefix_placehold_placehold_placehold_placehold/d\"" } } */
/* { dg-final { scan-assembler "\"/opt/prefix_placehold_placehold_placehold_placehold/e\"" } } */
/* The .rodata.cst check catches the memcmp pieces.  */
/* { dg-final { scan-assembler-not "movabs" } } */
/* { dg-final { scan-assembler-not "\\.rodata\\.cst" } } */
