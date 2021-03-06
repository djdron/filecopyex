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

#ifndef	__DLGCLASS_H__
#define	__DLGCLASS_H__

#pragma once

#include "../object.h"
#include "../valuelist.h"
#include "interface/plugin.hpp"

class FarDlgObject;
class FarDialog;

class FarDlgObjectClass : public ObjectClass
{
protected:
	void DefineProperties();

public:
	virtual void InitItem(FarDialogItem&, FarDlgObject&) { ; }
	virtual void RetrieveProperties(FarDlgObject&, HANDLE) { ; }
	virtual void BeforeAdd(FarDialogItem&, FarDlgObject&) { ; }
	virtual void LoadState(PropertyList &state, FarDlgObject&) { ; }
	virtual void SaveState(PropertyList &state, FarDlgObject&) { ; }
};

struct Attribute
{
	const char* Name;
	int Flag;
};
const Attribute& Attrib(int i);
int AttribCount();

class FarDlgLineClass : public FarDlgObjectClass
{
	DEFINE_CLASS("FarDlgLine", FarDlgObject)
	void DefineProperties()
	{
		FarDlgObjectClass::DefineProperties();
	}
	void InitItem(FarDialogItem& item, FarDlgObject& obj)
	{
		item.Type=DI_TEXT;
		item.Flags|=DIF_SEPARATOR | DIF_BOXCOLOR;
	}
};

int lablen(FarDialogItem& item);
String FormatWidth(const String& v, int len);

class FarDlgLabelClass : public FarDlgObjectClass
{
	DEFINE_CLASS("FarDlgLabel", FarDlgObject)
	void DefineProperties()
	{
		FarDlgObjectClass::DefineProperties();
		AddProperty("Shorten", 0);
	}
	void InitItem(FarDialogItem& item, FarDlgObject& obj)
	{
		item.Type=DI_TEXT;
		if(!obj("Shorten"))
			item.X2=item.X1+lablen(item)-1;
		else item.X2=item.X1-1;
	}
	void BeforeAdd(FarDialogItem& item, FarDlgObject& obj)
	{
//		if (obj("Shorten"))
//			FormatWidth(item.PtrData, __min(item.X2-item.X1+1, 500))
//			.ToAnsi(item.PtrData, sizeof(item.PtrData));
	}
};

class FarDlgButtonClass : public FarDlgObjectClass
{
	DEFINE_CLASS("FarDlgButton", FarDlgObject)
	void DefineProperties()
	{
		FarDlgObjectClass::DefineProperties();
		AddProperty("Default", 0);
		AddProperty("Result", -1);
	}
	virtual void InitItem(FarDialogItem& item, FarDlgObject& obj)
	{
		item.Type=DI_BUTTON;
		item.X2=item.X1+lablen(item)+4-1;
		if (obj("Default")) item.DefaultButton=1;
	}
};

class FarDlgPanelClass : public FarDlgObjectClass
{
	DEFINE_CLASS("FarDlgPanel", FarDlgContainer)
	void DefineProperties()
	{
		FarDlgObjectClass::DefineProperties();
	}
};

class FarDlgCheckboxClass : public FarDlgObjectClass
{
	DEFINE_CLASS("FarDlgCheckbox", FarDlgObject)
	void DefineProperties()
	{
		FarDlgObjectClass::DefineProperties();
		AddProperty("Selected", 0);
	}
	void InitItem(FarDialogItem& item, FarDlgObject& obj)
	{
		item.Type=DI_CHECKBOX;
		item.X2=item.X1+lablen(item)+4-1;
		item.Selected=obj("Selected");
	}
	void RetrieveProperties(FarDlgObject& obj, HANDLE dlg);
	void LoadState(PropertyList &state, FarDlgObject& obj)
	{
		obj("Selected")=state[obj.Name()];
	}
	void SaveState(PropertyList &state, FarDlgObject& obj)
	{
		state[obj.Name()]=obj("Selected");
	}
};

class FarDlgRadioButtonClass : public FarDlgCheckboxClass
{
	DEFINE_CLASS("FarDlgRadioButton", FarDlgObject)
	void DefineProperties()
	{
		FarDlgCheckboxClass::DefineProperties();
	}
	void InitItem(FarDialogItem& item, FarDlgObject& obj)
	{
		FarDlgCheckboxClass::InitItem(item, obj);
		item.Type=DI_RADIOBUTTON;
	}
};

class FarDlgEditClass : public FarDlgObjectClass
{
	DEFINE_CLASS("FarDlgEdit", FarDlgEdit)
	void DefineProperties()
	{
		FarDlgObjectClass::DefineProperties();
		AddProperty("HistoryId", "FarFramework\\DefaultEditHistory");
		AddProperty("Width", 10);
	}
	void InitItem(FarDialogItem& item, FarDlgObject& obj);
	void RetrieveProperties(FarDlgObject& obj, HANDLE dlg);
	void LoadState(PropertyList &state, FarDlgObject& obj)
	{
		obj("Text")=state[obj.Name()];
	}
	void SaveState(PropertyList &state, FarDlgObject& obj)
	{
		state[obj.Name()]=obj("Text");
	}
	void BeforeAdd(FarDialogItem& item, FarDlgObject& obj)
	{
		if (obj("History"))
			item.X2--;
	}
};

class FarDlgComboboxClass : public FarDlgObjectClass
{
	DEFINE_CLASS("FarDlgCombobox", FarDlgCombobox)
	void DefineProperties()
	{
		FarDlgObjectClass::DefineProperties();
		AddProperty("Width", 10);
		AddProperty("Items", "");
	}
	void InitItem(FarDialogItem& item, FarDlgObject& obj);
	void RetrieveProperties(FarDlgObject& obj, HANDLE dlg);
	void LoadState(PropertyList &state, FarDlgObject& obj)
	{
		obj("Text")=state[obj.Name()];
	}
	void SaveState(PropertyList &state, FarDlgObject& obj)
	{
		state[obj.Name()]=obj("Text");
	}
	void BeforeAdd(FarDialogItem& item, FarDlgObject& obj)
	{
		item.X2--;
	}
};

class FarDialogClass : public FarDlgObjectClass
{
	DEFINE_CLASS("FarDialog", FarDialog)
	void DefineProperties()
	{
		FarDlgObjectClass::DefineProperties();
		AddProperty("HelpTopic", "NoTopic");
		AddProperty("Title", "");
		AddProperty("Warning", 0);
	}
};

void InitObjMgr();
void DoneObjMgr();

#endif//__DLGCLASS_H__
