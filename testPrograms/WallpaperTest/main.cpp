/* Copyright (C) 2010 MoSync AB

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/

#include <ma.h>
#include <conprint.h>
#include <MAUtil/Graphics.h>
#include "MAHeaders.h"

/*
  Author: mikael.kindborg@mosync.com
  Program that tests wallpaper syscalls.
  Works on Android 2.0 and above.
  Press back to exit.
  Note that the Android permission "Home Screen and Wallpaper access"
  must be set in the MoSync project.
*/

int gWallpaperCounter = 0;

static void SwitchWallpaper()
{
	++gWallpaperCounter;
	if (gWallpaperCounter % 2)
	{
		maWallpaperSet(RESOURCE_WALLPAPER);
	}
	else
	{
		maWallpaperSet(RESOURCE_WALLPAPER2);
	}
}

static void PaintScreen()
{
	if (gWallpaperCounter % 2)
	{
		maDrawImage(RESOURCE_WALLPAPER, 0, 0);
	}
	else
	{
		maDrawImage(RESOURCE_WALLPAPER2, 0, 0);
	}
	maUpdateScreen();
}

static void InitApplication()
{
	PaintScreen();
	maNotificationAdd(
		NOTIFICATION_TYPE_APPLICATION_LAUNCHER,
		1,
		"My Application",
		"Touch to launch My Application");
	maHomeScreenEventsOn();
}

static void ExitApplication()
{
	maNotificationRemove(1);
	maHomeScreenEventsOff();
	maExit(0);
}

extern "C" int MAMain()
{
	InitApplication();

	while (1)
	{
		MAEvent event;

		maWait(0);
		while(maGetEvent(&event))
		{
			if (event.type == EVENT_TYPE_CLOSE)
			{
				ExitApplication();
			}
			else if (event.type == EVENT_TYPE_KEY_PRESSED)
			{
				// Exit application on pressing zero or back keys.
				if (event.key == MAK_0 || event.key == MAK_BACK)
				{
					ExitApplication();
				}
			}
			else if (event.type == EVENT_TYPE_FOCUS_LOST)
			{
				lprintfln("EVENT_TYPE_FOCUS_LOST");

				// Here we don't do anything.
			}
			else if (event.type == EVENT_TYPE_FOCUS_GAINED)
			{
				lprintfln("EVENT_TYPE_FOCUS_GAINED");

				PaintScreen();
			}
			else if (event.type == EVENT_TYPE_SCREEN_CHANGED)
			{
				lprintfln("EVENT_TYPE_SCREEN_CHANGED");

				PaintScreen();
			}
			else if (event.type == EVENT_TYPE_HOMESCREEN_SHOWN)
			{
				lprintfln("EVENT_TYPE_HOMESCREEN_SHOWN");

				// Here we don't do anything.
			}
			else if (event.type == EVENT_TYPE_HOMESCREEN_HIDDEN)
			{
				lprintfln("EVENT_TYPE_HOMESCREEN_HIDDEN");

				// Here we switch the wall paper.
				SwitchWallpaper();
			}
		}
	}

	return 0;
}