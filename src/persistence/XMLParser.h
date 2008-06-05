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

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <QString>
#include <QList>
#include <QMap>

#include "XMLExpert.h"
#include "../gui/VirtualMachineItem.h"
#include "../gui/CollisionDomainItem.h"
#include "../gui/LinkItem.h"
#include "../core/Laboratory.h"

/**
 * This object is a xml parser (using XPath) to read selective infos inside lab.xml
 * This class offer some static functions
 */
class XMLParser
{
	
private:
	XMLExpert *ex;
public:
	XMLParser();
	virtual ~XMLParser();
	static QRectF getSceneSize(QDomDocument *doc, QString *error = NULL);
};

#endif /*XMLPARSER_H_*/
