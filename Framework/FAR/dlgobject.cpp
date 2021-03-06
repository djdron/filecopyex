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

#include "../stdhdr.h"
#include "../valuelist.h"
#include "dlgobject.h"
#include "dlgclass.h"
#include "plugin.h"

FarDlgObject::FarDlgObject(void)
{
	DialogItem=-1;
}

FarDlgObject::~FarDlgObject(void)
{
}

void FarDlgObject::InitItem(FarDialogItem& item)
{ 
	PreInitItem(item);
	Class()->InitItem(item, *this); 
}

void FarDlgObject::RetrieveProperties(HANDLE dlg)
{ 
	Class()->RetrieveProperties(*this, dlg); 
}

void FarDlgObject::BeforeAdd(FarDialogItem& item)
{ 
	Class()->BeforeAdd(item, *this); 
}

void FarDlgObject::LoadState(PropertyList &state)
{ 
	Class()->LoadState(state, *this); 
}

void FarDlgObject::SaveState(PropertyList &state)
{ 
	Class()->SaveState(state, *this); 
}

void FarDlgObject::AddToItems(Array<FarDialogItem>& Items, 
							  Array<RetCode>& RetCodes, 
							  int curX, int curY, int curW)
{
	FarDialogItem item;
	memset(&item, 0, sizeof(item));
	item.X1=curX;
	item.Y1=curY;
	item.Y2=curY;
	InitItem(item);
	item.X2=item.X1+curW-1;
	BeforeAdd(item);
	Items.Add(item);
	DialogItem=Items.Count()-1;
	if (item.Type==DI_BUTTON && !(item.Flags & DIF_BTNNOCLOSE))
	{
		int res=Property("Result");
		if (res!=-1)
		{
			RetCode rc;
			rc.itemNo=Items.Count()-1;
			rc.retCode=res;
			RetCodes.Add(rc);
		}
	}
}

void FarDlgObject::SetItemText(FarDialogItem& item, const String& text)
{
	DestroyItemText(item);
	size_t len = text.len() + 1;
	wchar_t* t = (wchar_t*)malloc(sizeof(wchar_t) * len);
	text.ToUnicode(t, len);
	item.PtrData = t;
	item.MaxLen = 0;
}
void FarDlgObject::DestroyItemText(FarDialogItem& item)
{
	free((wchar_t*)item.PtrData);
	item.PtrData = NULL;
}

void FarDlgObject::PreInitItem(FarDialogItem& item)
{
	//	SetItemText(&item, Name());

	String p=Property("Text");
	if (p=="") 
		p=LOC(Dialog->Name()+"."+Name());
	SetItemText(item, p);

	for (int i=0; i<AttribCount(); i++)
		if (Property(Attrib(i).Name))
			item.Flags |= Attrib(i).Flag;
	if (Property("Focus")) item.Focus=1;
}

void FarDlgObject::DefSize(int& w, int& h, int& fit)
{
	FarDialogItem item;
	memset(&item, 0, sizeof(item));
	InitItem(item);
	fit=Property("FitWidth");
	w=item.X2-item.X1+1;
	h=item.Y2-item.Y1+1;
	DestroyItemText(item);
}

FarDlgObject* FarDlgObject::FindChild(const String& name)
{
	if (Name()==name) return this;
	else return NULL;
}

struct _group
{
	int start, end, w, h, nfit;
};

void FarDlgContainer::DefSize(int& sumw, int& sumh, int& fit)
{
	sumw=sumh=0;
	int groupw=0, grouph=0;
	fit=Property("FitWidth");
	for (int i=0; i<childs.Count(); i++)
	{
		FarDlgObject &obj=Child(i);
		if (obj.Property("Visible"))
		{
			int w, h, f;
			obj.DefSize(w, h, f);
			groupw+=w+2;
			if (h>grouph) grouph=h;
			if (!obj.Property("NoBreak"))
			{
				if (groupw-2>sumw) sumw=groupw-2;
				sumh+=grouph;
				groupw=grouph=0;
			}
		}
	}
}

void FarDlgContainer::AddToItems(Array<FarDialogItem>& Items, 
								 Array<RetCode>& RetCodes,
								 int curX, int curY, int curW)
{
	int sumw=0, sumh=0;
	Array<_group> Groups;
	_group group;
	group.start=group.w=group.h=group.nfit=0;
	for (int i=0; i<childs.Count(); i++)
	{
		FarDlgObject &obj=Child(i);
		if (obj.Property("Visible"))
		{
			int w, h, f;
			obj.DefSize(w, h, f);
			if (f) 
			{
				group.nfit++;
				w=0;
			} 
			group.w+=w+2;
			if (h>group.h) group.h=h;
			if (!obj.Property("NoBreak"))
			{
				group.w-=2;
				if (group.w>sumw) sumw=group.w;
				sumh+=group.h;
				group.end=i;
				Groups.Add(group);
				group.w=group.h=group.nfit=0;
				group.start=i+1;
			}
		}
	}
	int x=curX, y=curY;
	for (int j=0; j<Groups.Count(); j++)
	{
		for (int i=Groups[j].start; i<=Groups[j].end; i++)
		{
			FarDlgObject &obj=Child(i);
			if (obj.Property("Visible"))
			{
				int w, h, f;
				obj.DefSize(w, h, f);
				if (f) 
					w=(curW-Groups[j].w)/Groups[j].nfit;
				obj.AddToItems(Items, RetCodes, x, y, w);
				x+=w+2;
			}
		}
		x=curX;
		y+=Groups[j].h;
	}
}

void FarDlgContainer::LoadState(PropertyList& state)
{
	for (int i=0; i<childs.Count(); i++)
		if (Child(i).IsContainer() || (bool)Child(i)("Persistent"))
			Child(i).LoadState(state);
}

void FarDlgContainer::SaveState(PropertyList& state)
{
	for (int i=0; i<childs.Count(); i++)
		if (Child(i).IsContainer() || (bool)Child(i)("Persistent"))
			Child(i).SaveState(state);
}

void FarDlgContainer::RetrieveProperties(HANDLE dlg)
{
	for (int i=0; i<childs.Count(); i++)
		if (Child(i).DialogItem!=-1 || Child(i).IsContainer())
			Child(i).RetrieveProperties(dlg);
}

void FarDlgContainer::ClearDialogItems(Array<FarDialogItem>& Items)
{
	for(int i = 0; i < Items.Count(); ++i)
	{
		DestroyItemText(Items[i]);
	}
	for (int i=0; i<childs.Count(); i++)
		Child(i).ClearDialogItem();
}

FarDlgObject* FarDlgContainer::FindChild(const String& name)
{
	if (Name()==name) return this;
	for (int i=0; i<childs.Count(); i++)
	{
		FarDlgObject* obj=Child(i).FindChild(name);
		if (obj) return obj;
	}
	return NULL;
}

void FarDlgObject::BeforeLoad()
{
	Dialog=Parent()->Dialog;
}
