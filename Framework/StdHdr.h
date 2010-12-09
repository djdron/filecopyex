/*
FileCopyEx - Extended File Copy plugin for Far 2 file manager

Copyright (C) 2004 - 2010 Serge Cheperis aka craZZy
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


#pragma once

#ifdef _WINXP
#define _WIN2K
#endif

#ifdef _WIN2K
#define _WINNT
#endif

#if defined(_WINXP)
#define _WIN32_WINNT 0x0501
#elif defined(_WIN2K)
#define _WIN32_WINNT 0x0500
#elif defined(_WINNT)
#define _WIN32_WINNT 0x0400
#endif

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#include <windows.h>
#include <winioctl.h>

//#pragma hdrstop