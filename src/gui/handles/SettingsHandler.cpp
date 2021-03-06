/**
 * VisualNetkit is an advanced graphical tool for NetKit <http://www.netkit.org>
 * Copyright (C) 2008  Alessio Di Fazio, Paolo Minasi
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SettingsHandler.h"

/**
 * Init the null instance pointer
 */
SettingsHandler *SettingsHandler::instance = NULL;

/**
 * Constructor
 */
SettingsHandler::SettingsHandler() : QObject()
{
	/* get the setting controller */
	settingsController = SettingsFacadeController::getInstance();
	
	// foreward the signal
	connect(settingsController, SIGNAL(historyChanged()), this, SIGNAL(historyChanged()));
}

/**
 * Deconstructor
 */
SettingsHandler::~SettingsHandler()
{
}

/**
 * [STATIC]
 * Get the singletone instance
 */
SettingsHandler * SettingsHandler::getInstance()
{
	if(instance == NULL)
		instance = new SettingsHandler();

	return instance;
}

/**
 * Foreward the action to the facade controller
 */
void SettingsHandler::saveWindowSettings(const QByteArray &windowState,
		const QByteArray &windowGeometry)
{
	settingsController->saveWindowSettings(windowState, windowGeometry);
}

/**
 * Foreward the action to the facade controller
 */
QByteArray SettingsHandler::restoreWindowGeometry()
{
	return settingsController->restoreWindowGeometry();
}

/**
 * Foreward the action to the facade controller
 */
QByteArray SettingsHandler::restoreWindowState()
{
	return settingsController->restoreWindowState();
}
