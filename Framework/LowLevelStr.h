/*
FileCopyEx - Extended File Copy plugin for Far 2 file manager

Copyright (C) 2004 - 2010
Idea & core: Max Antipin
Coding: Serge Cheperis aka craZZy
Bugfixes: slst, CDK, Ivanych, Alter, Axxie and Nsky
Special thanks to Vitaliy Tsubin
Far 2 (32 & 64 bit) full unicode version by djdron

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef	__LOWLEVELSTR_H__
#define	__LOWLEVELSTR_H__

#pragma once

#include <string.h>

void _atowcs(wchar_t *d, size_t size, const char *s);

inline const wchar_t* _tcsend(const wchar_t* s) { return s + wcslen(s); }

const wchar_t* _tcsrpbrk(const wchar_t* string, const wchar_t* control);

#endif//__LOWLEVELSTR_H__
