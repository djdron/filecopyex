#include "stdhdr.h"
#include "lowlevelstr.h"

void _wtoacs(char *d, const wchar_t *s, size_t size)
{
  WideCharToMultiByte(CP_ACP, 0, s, -1, d, (int)size, NULL, NULL);
  d[size-1]=0;
}

void _atowcs(wchar_t *d, const char *s, size_t size)
{
  MultiByteToWideChar(CP_ACP, 0, s, -1, d, (int)size);
  d[size-1]=0;
}

wchar_t *_trim(wchar_t *arg)
{
  while (*arg && (*arg==' '||*arg=='\t'||*arg=='\n'||*arg=='\r')) arg++;
  wchar_t *p=arg+_tcslen(arg)-1;
  while (p>=arg && (*p==' '||*p=='\t'||*p=='\n'||*p=='\r')) *p--=0;
  return arg;
}

wchar_t *_trimquotes(wchar_t *arg)
{
  if (*arg && (*arg=='"')) arg++;
  wchar_t *p=arg+_tcslen(arg)-1;
  if (p>=arg && (*p=='"')) *p--=0;
  return arg;
}

int _truestr(const wchar_t *s)
{
  return s && (!_tcscmp(s, _T("1")) || !_tcsicmp(s, _T("yes")) 
    || !_tcsicmp(s, _T("true")));
}

void _tooem(char *s)
{
  CharToOemBuffA(s, s, (int)strlen(s));
}

void _toansi(char *s)
{
  OemToCharBuffA(s, s, (int)strlen(s));
}

wchar_t* _tcsrstr(const wchar_t* wcs1, const wchar_t* wcs2)
{
  wchar_t *cp=(wchar_t*)_tcsend(wcs1)-1;
  wchar_t *s1, *s2;
  if (!*wcs2) return cp;
  while (cp>=wcs1)
  {
    s1=cp;
    s2=(wchar_t*) wcs2;
    while (*s1 && *s2 && !(*s1-*s2)) s1++, s2++;
    if (!*s2) return cp;
    cp--;
  }
  return NULL;
}

wchar_t* _tcsrpbrk(const wchar_t* string, const wchar_t* control)
{
  wchar_t *wcset;
  wchar_t *str=(wchar_t*)_tcsend(string)-1;
  /* 1st char in control string stops search */
  while (str>=string) 
  {
    for (wcset=(wchar_t*)control; *wcset; wcset++) 
      if (*wcset==*str) 
        return str;
    str--;
  }
  return NULL;
}

wchar_t* _tcsrspnp(const wchar_t* string, const wchar_t* control)
{
  wchar_t *str=(wchar_t*)_tcsend(string)-1;
  wchar_t *ctl;
  /* 1st char not in control string stops search */
  while (str>=string) 
  {
    for (ctl=(wchar_t*)control; *ctl!=*str; ctl++) 
      if (*ctl==(wchar_t)0) 
        /* reached end of control string without finding a match */
        return str;
    str--;
  }
  /* The whole string consisted of characters from control */
  return NULL;
}
