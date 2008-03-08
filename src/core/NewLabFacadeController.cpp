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

#include "NewLabFacadeController.h"

/**
 * Init the null instance for the singletone controller
 */
NewLabFacadeController* NewLabFacadeController::instance = NULL;

/**
 * Constructor
 */
NewLabFacadeController::NewLabFacadeController()
{
	currentLab = NULL;
}

/**
 * Deconstructor
 */
NewLabFacadeController::~NewLabFacadeController()
{
}

/**
 * Singletone get instance
 */
NewLabFacadeController* NewLabFacadeController::getInstance()
{
	if (instance == NULL)
	{
		instance = new NewLabFacadeController();
	}

	return instance;
}

/**
 * Create a new laboratory and set it as current laboratory
 * This is also the Factory for laboratory instances
 */
Laboratory * NewLabFacadeController::newLaboratory(QString newName, QString newVersion, QString newAutors)
{
	//TODO: first check in the currentLab allready exist 
	currentLab = new Laboratory(newName, newVersion, newAutors);
	
	return currentLab;
}
