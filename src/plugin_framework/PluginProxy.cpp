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

#include "PluginProxy.h"
#include "PluginInterface.h"
#include "PluginRegistry.h"

/**
 * Constructor
 */
PluginProxy::PluginProxy(PluginRegistry *r) : QObject()
{
	registry = r;
}

/**
 * Deconstructor
 */
PluginProxy::~PluginProxy()
{
	/*
	 * NOTE: do not destroy the plugin here!
	 * It's the plugin that destroy its proxy
	 */
}

/**
 * Change the label inside the "my" graphics element 
 */
void PluginProxy::changeGraphicsLabel(QString label)
{
	QObject* baseElement = getBaseElement();
	if(baseElement == NULL)
	{
		qWarning() << "PluginProxy::changeGraphicsLabel -> base element is NULL";
		return;
	}
	
	//check the base element type and find the relative mapper
	VirtualMachine *vm = dynamic_cast<VirtualMachine*>(getBaseElement());
	if (vm != NULL)
	{
		emit needLabelChanged(vm, pluginInterface->getName(), label);
	}
	
	CollisionDomain *cd = dynamic_cast<CollisionDomain*>(getBaseElement());
	if (cd != NULL)
	{
		//CdMapper::getInstance()->changeGraphicsLabel(cd, QString("ipv4 su cd"), pluginInterface->getName());
	}
	
	HardwareInterface *hi = dynamic_cast<HardwareInterface*>(getBaseElement());
	if (hi != NULL)
	{
		//LinkMapper::getInstance()->changeGraphicsLabel(hi, QString("ipv4 su link"), pluginInterface->getName());
	}
}

/**
 * Show the default label inside "my" graphics element, if any
 */
void PluginProxy::showDefaultGrophicsLabel()
{
	QString label = pluginInterface->getDefaultGraphisLabel();
	if(!label.isEmpty())
	{
		changeGraphicsLabel(label);
	}
}

/**
 * Just foreward the call
 */
bool PluginProxy::saveProperty(QTableWidgetItem* property, QString *pluginAlertMsg)
{
	return pluginInterface->saveProperty(property, pluginAlertMsg);
}

/**
 * Returns the associated plugin properties.
 */
QMap< QString, PluginProperty* > PluginProxy::getPluginProperties()
{
	return pluginInterface->getPluginProperties();
}

/**
 * Returns the plugin template.
 */
QString PluginProxy::getTemplate()
{
	return pluginInterface->getTemplate();
}

/**
 * Returns template location where to save the file.
 */
QString PluginProxy::getTemplateLocation()
{
	return pluginInterface->getTemplateLocation();
}

/**
 * Return the settings for plugin 
 */
QSettings* PluginProxy::getPluginSettings()
{
	return pluginInterface->getMySettings();
}

/**
 * Return the base element attached to the plugin
 */
QObject* PluginProxy::getBaseElement()
{
	if(registry != NULL)
	{
		return registry->getBaseElement(this);
	}
	return NULL;
}

/**
 * Set the plugin group ID
 */
void PluginProxy::setPluginGroupID(qint32 id)
{
	pluginInterface->setGroupID(id);
}

/**
 * Get the plugin group ID
 * NOTE: return -1 if unused
 */
qint32 PluginProxy::getPluginGroupID()
{
	return pluginInterface->getGroupID();
}

