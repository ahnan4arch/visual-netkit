/**
 * A simple test plugin for Visual Netkit 
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

#include <QDebug>
#include <QResource>
#include <QFile>

#include "Plugin.h"


/** 
 * Constructor 
 */
Plugin::Plugin() : PluginInterface()
{
	mySettings = new QSettings(":/ini", QSettings::NativeFormat);
	
	/* Save the name of this plugin for future uses */
	mySettings->beginGroup("global");
	myName = mySettings->value("name").toString();
	mySettings->endGroup();
	
	myProxy = new PluginProxy();
	fetchProperties();
}

/**
 * Deconstructor
 */
Plugin::~Plugin()
{
	delete myProxy;
	qDeleteAll(properties);
	delete mySettings;
}

/**
 * Returns the plugin template if resource file exists,
 * otherwise returns an empty QString.
 */
QString Plugin::getTemplate()
{
	QString templateContent;
	
	QFile data(":/basic_tpl");
	if (data.open(QFile::ReadOnly)) 
	{
		QTextStream in(&data);
		templateContent = in.readAll();
	}
	else
	{
		qWarning() << "The plugin getTemplate() failed:" << data.errorString();
	}
		
	return templateContent;
}

/**
 * Returns the path where save/append the template content
 */
QString Plugin::getTemplateLocation()
{
	VirtualMachine *vm = dynamic_cast<VirtualMachine*>(myProxy->getBaseElement());
	if (vm == NULL)
	{
		qWarning() << "Plugin::getTemplateLocation(): null VirtualMachine name.";
		return QString();
	}
	
	return QString(vm->getName() + "/etc/basic.conf");
}

/**
 * Fetches plugin properties and stores them in the properties map.
 */
bool Plugin::fetchProperties()
{
	bool allok = true;
	
	mySettings->beginGroup("properties");
	QStringList childgroups = mySettings->childGroups();

	if (!childgroups.empty()) 
	{
		for (int i = 0; i < childgroups.size(); i++)
		{
			QString p_name = childgroups.at(i);
			QString p_default_value = mySettings->value(childgroups.at(i) + "/p_default_value").toString();
			QString p_description = mySettings->value(childgroups.at(i) + "/p_description").toString();
			
			PluginProperty *pp = new PluginProperty(p_name, p_default_value, p_description);
			properties.insert(p_name, pp);
		}
	} else {
		qWarning() << "No properties for plugin:" << myName;
		allok = false;
	}
	mySettings->endGroup();
	
	return allok;
}
