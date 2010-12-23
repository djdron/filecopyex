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

#include "../framework/stdhdr.h"
#include "../framework/lowlevelstr.h"
#include "filecopyex.h"
#include "../framework/far/interface/farkeys.hpp"

const String regkey = "\\Software\\Far2\\KeyMacros\\Shell";

int FileCopyExPlugin::isour(const String &key)
{
	String src = regkey + "\\" + key;
	String buf = registry.GetString(src, "Sequence", "");
	return (!buf.nicmp("F11 x", 5) || !buf.icmp("F5") || !buf.icmp("F6"));
}

void FileCopyExPlugin::restore(const String &key)
{
	if (isour(key))
	{
		String src = regkey + ".backup\\" + key;
		String dst = regkey + "\\" + key;
		registry.DeleteKey(dst);
		registry.CopyKey(src, dst);
		registry.DeleteKey(src);
	}
}

void FileCopyExPlugin::dobind(const String& key, const String& seq)
{
	String src = regkey + "\\" + key;
	String dst = regkey + ".backup\\" + key;
	if(!isour(key))
	{
		registry.DeleteKey(dst);
		registry.CopyKey(src, dst);
		registry.DeleteKey(src);
	}
	registry.SetString(src, "Sequence", seq);  
	registry.SetInt(src, "DisableOutput", 1);  
	registry.SetInt(src, "NoPluginPanels", 0);  
	registry.SetInt(src, "PluginPanels", 1);  
}

void FileCopyExPlugin::reloadmacro()
{
	ActlKeyMacro prm;
	memset(&prm, 0, sizeof(prm));
	prm.Command=MCMD_LOADALL;
	Info.AdvControl(Info.ModuleNumber, ACTL_KEYMACRO, &prm);
}

void FileCopyExPlugin::KeyConfig()
{
	FarDialog& dlg = Dialogs()["KeysDialog"];
	dlg.ResetControls();

	int altShift, ctrlShift, ctrlAlt, bind;
	bind = isour("F5") && isour("F6") 
		&& isour("ShiftF5") && isour("ShiftF6");
	altShift = isour("AltShiftF5") && isour("AltShiftF6");
	ctrlShift = isour("CtrlShiftF5") && isour("CtrlShiftF6");
	ctrlAlt = isour("CtrlAltF5") && isour("CtrlAltF6");

	dlg["BindToF5"]("Selected")=bind;
	dlg["AltShiftF5"]("Selected")=!bind || altShift;
	dlg["CtrlShiftF5"]("Selected")=bind && ctrlShift;
	dlg["CtrlAltF5"]("Selected")=bind && ctrlAlt;

	if (dlg.Execute()==-1) return;

	if (dlg["BindToF5"]("Selected") != bind
		|| dlg["AltShiftF5"]("Selected") != altShift
		|| dlg["CtrlShiftF5"]("Selected") != ctrlShift
		|| dlg["CtrlAltF5"]("Selected") != ctrlAlt)
	{
		ActlKeyMacro prm;
		memset(&prm, 0, sizeof(prm));
		prm.Command=MCMD_SAVEALL;
		Info.AdvControl(Info.ModuleNumber, ACTL_KEYMACRO, &prm);

		restore("F5"); restore("F6");
		restore("ShiftF5"); restore("ShiftF6");
		restore("AltShiftF5"); restore("AltShiftF6");
		restore("CtrlShiftF5"); restore("CtrlShiftF6");
		restore("CtrlAltF5"); restore("CtrlAltF6");
		restore("CtrlShiftQ"); restore("AltShiftQ"); 

		if (dlg["BindToF5"]("Selected"))
		{
			dobind("F5", "F11 x 1"); 
			dobind("F6", "F11 x 2");
			dobind("ShiftF5", "F11 x 3"); 
			dobind("ShiftF6", "F11 x 4");
			String key;
			if (dlg["AltShiftF5"]("Selected")) key="AltShift";
			else if (dlg["CtrlShiftF5"]("Selected")) key="CtrlShift";
			else if (dlg["CtrlAltF5"]("Selected")) key="CtrlAlt";
			dobind(key+"F5", "F5");
			dobind(key+"F6", "F6");
		}
		reloadmacro();
	}
}


#ifdef _WIN64
#define VersionStr "version 2.0.0 beta (x64 Unicode), " __DATE__
#else
#define VersionStr "version 2.0.0 beta (x86 Unicode), " __DATE__
#endif

void FileCopyExPlugin::About()
{
	FarDialog& dlg = Dialogs()["AboutDialog"];
	dlg.ResetControls();
	dlg["Label2"]("Text") = String(VersionStr);
	dlg.Execute();
}

void beep(int b)
{
	switch(b)
	{
	case 0:		MessageBeep(MB_ICONWARNING);	break;
	case 1:		MessageBeep(MB_ICONASTERISK);	break;
	case 2:		MessageBeep(MB_OK);				break;
	}
}

void FileCopyExPlugin::Config()
{
	FarDialog& dlg = Dialogs()["SetupDialog"];
	dlg.ResetControls();
	dlg.LoadState(options);

rep:
	int res = dlg.Execute();
	switch(res)
	{
	case 0:
		dlg.SaveState(options);
		break;
	case 1:
		KeyConfig();
		goto rep;
	case 2:
		About();
		goto rep;
	case 3:
		static int bn = 0;
		beep(bn);
		if(++bn > 2)
			bn = 0;
		goto rep;
	}
}
