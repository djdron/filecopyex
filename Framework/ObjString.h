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

#ifndef	__OBJSTRING_H__
#define	__OBJSTRING_H__

#pragma once

#include "lowlevelstr.h"
#include <string>

class String
{
public:
	String() {}
	String(const char* v)
	{
		str.resize(strlen(v), '\0');
		_atowcs((wchar_t*)ptr(), str.length()+1, v);
	}
	String(wchar_t ch, int len)
	{
		str.resize(len, ch);
	}
	String(const wchar_t* v)
	{
		str = v;
	}
	String(const std::wstring& v)
	{
		str = v;
	}
	inline bool operator==(const String& v) const { return cmp(v)==0; }
	inline bool operator!=(const String& v) const { return cmp(v)!=0; }
	inline bool operator<(const String& v) const { return cmp(v)<0; }
	inline bool operator>(const String& v) const { return cmp(v)>0; }
	inline bool operator<=(const String& v) const { return cmp(v)<=0; }
	inline bool operator>=(const String& v) const { return cmp(v)>=0; }
	inline void operator+=(const String& v) { str += v.str; }
	const String operator+(const String& v) const { return str + v.str; }

	inline int len() const { return (int)str.length(); }
	inline bool empty() const { return str.empty(); }

	inline wchar_t operator[] (int i) const
	{
		if (i>=0 && i<(int)str.length()) return str[i];
		else return 0;
	}

	int AsInt() const { return _wtoi(ptr()); }
	float AsFloat() const { return (float)_wtof(ptr()); }
	bool AsBool() const { return (*this) == L"1"; } 
	void ToUnicode(wchar_t* buf, size_t sz) const { CopyTo(buf, sz); }
	void CopyTo(wchar_t* buf, size_t sz) const { wcscpy_s(buf, sz, ptr()); }

	explicit String(int v)
	{
		wchar_t buf[64];
		_itow_s(v, buf, 64, 10);
		str = buf;
	}
	explicit String(__int64 v)
	{
		wchar_t buf[64];
		_i64tow_s(v, buf, 64, 10);
		str = buf;
	}
	explicit String(float v)
	{
		wchar_t buf[64];
		swprintf_s(buf, 64, L"%g", v);
		str = buf;
	}
	explicit String(bool v)
	{
		if (v) str = L"1";
		else str = L"0";
	}

	int cmp(const String& v) const { return ncmp(v, 0x7FFFFFFF); }
	int icmp(const String& v) const { return nicmp(v, 0x7FFFFFFF); }
	int ncmp(const String& v, int sz) const { return wcsncmp(ptr(), v.ptr(), sz); }
	int nicmp(const String& v, int sz) const { return _wcsnicmp(ptr(), v.ptr(), sz); }
	// bug #46 fixed by axxie
	const bool isbadchar(wchar_t c) const { return c >= '\0' && c <= ' '; }

	const String substr(int s, int l = 0x7FFFFFFF) const;
	const String left(int n) const { return substr(0, n); }
	const String right(int n) const { return substr(len()-n, n); }

	const String trim() const;
	const String ltrim() const;
	const String rtrim() const;
	const String trimquotes() const;

	const String rev() const;

	const String replace(const String& what, const String& with, int nocase=0) const;
	const String toUpper() const;
	const String toLower() const;

	int find(const String& v, int start=0) const
	{
		const wchar_t* p=ptr(), *rp=wcsstr(p+start, v.ptr());
		if (!rp) return -1; 
		else return (int)(rp-p);
	}
	int cfind(wchar_t v, int start=0) const
	{
		const wchar_t* p=ptr(), *rp=wcschr(p+start, v);
		if (!rp) return -1; 
		else return (int)(rp-p);
	}
	int crfind(wchar_t v) const
	{
		const wchar_t* p=ptr(), *rp=wcsrchr(p, v);
		if (!rp) return -1; 
		else return (int)(rp-p);
	}
	int cfind(const String& v, int start=0) const
	{
		const wchar_t* p=ptr(), *rp=wcspbrk(p+start, v.ptr());
		if (!rp) return -1; 
		else return (int)(rp-p);
	}
	int crfind(const String& v) const 
	{ 
		const wchar_t* p=ptr(), *rp=_tcsrpbrk(p, v.ptr());
		if (!rp) return -1; 
		else return (int)(rp-p);
	}
	const wchar_t* ptr() const { return str.c_str(); }
private:
	std::wstring str;
};

#endif//__OBJSTRING_H__
