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

#ifndef PLUGINIPV4_H_
#define PLUGINIPV4_H_

#include <QObject>
#include <QString>
#include <QSettings>
#include "PluginInterface.h"
#include "PluginProxy.h"
#include "PluginProperty.h"

/**
 * A simple plugin that do nothing
 */
class PluginIPv4 : public PluginInterface
{
	
private:
	QMap<QString, PluginProperty*> properties;
	QSettings *mySettings;
	PluginProxy *myProxy;
	QString myName;

	bool fetchProperties();
	
public:
	PluginIPv4();
	virtual ~PluginIPv4();
	bool saveProperty(QTableWidgetItem* property, QString *pluginAlertMsg = NULL) { return false; };
	QSettings* getMySettings() { return mySettings; };
	QString getTemplateLocation();
	QString getTemplate();
	QMap<QString, PluginProperty*> getPluginProperties() { return properties; };
	PluginProxy* getProxy() { return myProxy; };
	
	void setGroupID(qint32 id) { Q_UNUSED(id) /* do nothing */ };	
	qint32 getGroupID() { return -1; /* Unused */ };
	
	bool updateLabel();
	QString getName() { return myName; };
};


/******************* PLUGIN FACTORIES ***********************/

/* Factory (creator) */
extern "C" PluginInterface* createPlugin()
{
    return new PluginIPv4();
}

/* Factory (destroyer) */
extern "C" void destroyPlugin(PluginInterface* p)
{
	delete p;
	qDebug() << "PluginIPv4 destroyed";
}


#endif