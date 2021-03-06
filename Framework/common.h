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

#ifndef	__FWCOMMON_H__
#define	__FWCOMMON_H__

#pragma once

typedef void (*ErrorHandler)(const wchar_t*);

class String;

void FWError(const String&);
void FWError(const wchar_t*);
extern ErrorHandler errorHandler;

#define MAKEINT64(low, high) ((((__int64)(high))<<32)|((__int64)low))

extern int WinNT, WinNT4, Win2K, WinXP;
extern HANDLE hInstance;

BOOL __stdcall DllMain(HANDLE hInst, ULONG reason, LPVOID);

#endif//__FWCOMMON_H__
