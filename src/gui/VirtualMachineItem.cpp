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

#include "VirtualMachineItem.h"
#include <QGraphicsScene>

/**
 * Contructor
 * by default, this svg item is showed as VmHost
 */
VirtualMachineItem::VirtualMachineItem(VmType type) 
	: QGraphicsSvgItem(QString::fromUtf8(":/svg/vm_host"))
{
	/* Fill the filemap */
	svgFiles.insert(Host, QString::fromUtf8(":/svg/vm_host"));
	svgFiles.insert(Router, QString::fromUtf8(":/svg/vm_router"));
	
	/* Set the default svg file: VmHost */
	renderer()->load(svgFiles.value(type));
	
	setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
	setZValue(1000);
}

/**
 * Deconstructor
 */
VirtualMachineItem::~VirtualMachineItem()
{
}

/**
 * [PUBLIC-SLOT]
 * Change the visualization for this vm
 */
void VirtualMachineItem::changeSvgFile(VmType type)
{
	if(!svgFiles.contains(type))
	{
		qWarning() << "VmType" << type << "NOT FOUND INSIDE THE MAP";
		return;
	}
	
	renderer()->load(svgFiles.value(type));
}

/**
 * [PROTECTED]
 * Control the moviment of this item and don't permit that it's drowed outside
 * the scene rect
 */
QVariant VirtualMachineItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionChange && scene())
	{
		// value is the new position.
		QPointF newPos = value.toPointF();
		QRectF rect = scene()->sceneRect();

		// Keep the item inside the scene rect.
		newPos.setX(qMin(rect.right()-48, qMax(newPos.x(), rect.left())));
		newPos.setY(qMin(rect.bottom()-48, qMax(newPos.y(), rect.top())));
		qDebug() << value << "scene:" << scene()->sceneRect();
		return newPos;
	}
	
	return QGraphicsItem::itemChange(change, value);
}

