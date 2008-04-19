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

#ifndef CDHANDLER_H_
#define CDHANDLER_H_

#include "../../core/handles/LabFacadeController.h"
#include "LabHandler.h"
#include <QPointF>

/**
 * This class is the controller for the collision domain operations
 */
class CdHandler : public QObject
{
	Q_OBJECT
	
private:
	LabFacadeController *labFacadeController;
	LabHandler *labHandler;
	static CdHandler *instance;

public:
	CdHandler();
	virtual ~CdHandler();
	static CdHandler* getInstance();
	bool cdNameExist(QString cdNameToCheck);
	
public slots:
	void handleAddNewCd(QString cdName, NetworkAddress *subnet, QPointF pos);
	
};

#endif /*CDHANDLER_H_*/
