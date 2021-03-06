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

#ifndef PLUGINPROXY_H_
#define PLUGINPROXY_H_

#include <QString>
#include <QMap>
#include <QSettings>
#include <QObject>
#include <QTableWidgetItem>

#include "../core/VirtualMachine.h"
#include "PluginProperty.h"
#include "PluginInterface.h"
#include "PropertyExpert.h"

class PluginRegistry;
class PluginInterface;

class PluginProxy : public QObject
{
	Q_OBJECT
	
private:
	PluginInterface *pluginInterface;
	PluginRegistry *registry;
	QString labPath;	//This is updated by the slot setLabPath()
	PropertyExpert *pExpert;
	void initPropertyExpert();

public:
	PluginProxy(PluginRegistry *r);
	virtual ~PluginProxy();

	bool saveProperty(QString propUniqueId, QString propValue, QString *pluginAlertMsg = NULL);
	QList<PluginProperty*> getPluginProperties();
	QMap<QString, QString> getTemplates();
	void setPluginInterface(PluginInterface *pi) { pluginInterface = pi; initPropertyExpert(); };
	QObject* getBaseElement();
	PluginInterface * getPlugin() { return pluginInterface; };
	void setPluginGroupID(qint32 id);
	qint32 getPluginGroupID();
	void changeGraphicsLabel(QString label);
	void showDefaultGraphicsLabel();
	bool initPlugin(QString path) { return pluginInterface->init(path); };
	PropertyExpert* getPropertyExpert() { return pExpert; };
	bool validateXmlPluginConfFile();
	QString deleteProperty(QString propertyUniqueId) { return pluginInterface->deleteProperty(propertyUniqueId); };
	QPair<PluginProperty*, QString> addProperty(QString propertyIdToAdd, QString parentPropertyUniqueId);
	
signals:
	void needLabelChangedVm(VirtualMachine *vm, QString pluginName, QString label);
	void needLabelChangedHi(HardwareInterface *hi, QString pluginName, QString label);
	void needLabelChangedCd(CollisionDomain *cd, QString pluginName, QString label);
};

#endif /*PLUGINPROXY_H_*/
