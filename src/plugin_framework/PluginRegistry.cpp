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

#include <QMap>
#include <QDir>

#include "PluginRegistry.h"
#include "PluginLoaderFactory.h"
#include "../common/CommonConfigs.h"


/* Init the instance field to NULL */
PluginRegistry* PluginRegistry::instance = NULL;

/**
 * Constructor
 */
PluginRegistry::PluginRegistry()
{
}

/**
 * Deconstructor
 */
PluginRegistry::~PluginRegistry()
{
}

/**
 * [STATIC]
 * Singleton
 */
PluginRegistry* PluginRegistry::getInstance()
{
	if (instance == NULL) 
	{
		instance = new PluginRegistry();
	}
	return instance;
}

/**
 * Registers a plugin proxy in the register and returns it.
 * 
 * @return the proxy of the registered element, or NULL if the plugins name
 * doesn't extst.
 */
PluginProxy* PluginRegistry::registerPlugin(QString pluginName, QObject* baseElement)
{	
	if(!factories.contains(pluginName))
	{
		qWarning() << "Plugin:" << pluginName << "not found its Factory.";
		return NULL;
	}
	
	bool foundValidElement = false;
	
	PluginProxy* proxy = factories.value(pluginName)->createPlugin();
	
	//Virtual machine
	VirtualMachine *vm = dynamic_cast<VirtualMachine*>(baseElement);
	if ( vm != NULL )
	{
		vmAssociations.insertMulti(vm, proxy);
		foundValidElement = true;
	}
	
	//Collision domain
	CollisionDomain *cd = dynamic_cast<CollisionDomain*>(baseElement);
	if ( cd != NULL )
	{
		cdAssociations.insertMulti(cd, proxy);
		foundValidElement = true;
	}
	
	//Hardware interface
	HardwareInterface *hi = dynamic_cast<HardwareInterface*>(baseElement);
	if ( hi != NULL )
	{
		hiAssociations.insertMulti(hi, proxy);
		foundValidElement = true;
	}
	
	if(!foundValidElement)
		qWarning() << "PluginRegistry::registerPlugin" << "Decasting failed. returning NULL." << baseElement;

	
	return proxy;
}

/**
 * Fetches all plugins in the plugin directory.
 */
bool PluginRegistry::fetchPlugins()
{
	bool allok = true;
					
	// checks if directory exists
	QDir pluginDir(DEFAULT_PLUGIN_DIR);
	if (!pluginDir.exists())
	{
		qWarning() << "Cannot find the plugin directory" << DEFAULT_PLUGIN_DIR;
		qDebug() << pluginDir.path();
		allok = false;
	}	
	else
	{
		pluginDir.setFilter( QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot );

		// gets plugins list in the dir
		QStringList list = pluginDir.entryList();
		QRegExp rx("*.so");
		rx.setPatternSyntax(QRegExp::Wildcard);
		QStringList filteredList = list.filter(rx);
		if (!filteredList.empty()) 
		{
			for (int i = 0; i < filteredList.size(); i++)
			{
				//loads the i-th plugin
				qDebug() << "Loading" << filteredList.at(i);
				
				//inserts plugin and factory in factories map
				PluginLoaderFactory* factory =
					new PluginLoaderFactory(pluginDir.filePath(filteredList.at(i)));
				
				if (factory->initPluginLibrary()) 
				{
					factories.insert(factory->getName(), factory);
				}
				else
				{
					delete factory;
				}
			}
		}
		else
		{
			qWarning() << "No plugins in" << DEFAULT_PLUGIN_DIR;
			allok = false;
		}
	}
	
	return allok;
}

/**
 * Get the associated base element, passed the proxy
 */
QObject* PluginRegistry::getBaseElement(PluginProxy* proxy)
{
	QObject* be;
	
	be = vmAssociations.key(proxy, NULL);
	if( be != NULL )
		return be;
	
	be = cdAssociations.key(proxy, NULL);
	if( be != NULL )
		return be;
	
	be = hiAssociations.key(proxy, NULL);
	if( be != NULL )
		return be;
	
	qWarning() << "PluginRegistry: unknown base element for PluginProxy" << proxy;
	
	return be;
}

/**
 * Unregister a list of vm plugins and return proxies
 */
QList<PluginProxy*> PluginRegistry::unregisterVmPlugins(VirtualMachine *vm, QStringList toDelete,
		QStringList *paths)
{
	QList<PluginProxy*> deletedAll, deleted;
	
	/* Save paths before all */
	foreach(PluginProxy* pp, vmAssociations.values(vm))
		if(toDelete.contains(pp->getPlugin()->getName()))
			*paths << pp->getTemplates().keys();
		
	/* take all before */
	for(int i=0; i<vmAssociations.values(vm).size(); i++)
	{
		deletedAll << vmAssociations.take(vm);
	}
	
	/* now, delete plugins and restore others */
	for(int j=0; j<deletedAll.size(); j++)
	{
		if(toDelete.contains(deletedAll.at(j)->getPlugin()->getName()))
		{
			//sure to delete
			deleted << deletedAll.takeAt(j);
		}
		else
		{
			//restore
			vmAssociations.insertMulti(vm, deletedAll.takeAt(j));
		}
	}
	
	return deleted;
}

/**
 * Get all paths (unique entries) used by plugins
 */ 
QSet<QString> PluginRegistry::getAllUsedPaths()
{
	QStringList paths;
	QList<PluginProxy*> allPlugins;
	
	//get all plugins
	allPlugins << vmAssociations.values() << cdAssociations.values() << hiAssociations.values();
	
	QListIterator<PluginProxy*> i(allPlugins);
	while(i.hasNext())
	{
		paths << i.next()->getTemplates().keys();
	}
	
	return paths.toSet();
}

/**
 * Returns all plugins' proxies in the registry.
 */
QList<PluginProxy*> PluginRegistry::getAllProxies()
{
	QList<PluginProxy*> proxies(vmAssociations.values() + cdAssociations.values() + hiAssociations.values());
	return proxies;
}

/**
 * Clean all plugins
 */
void PluginRegistry::clean()
{
	qDebug() << "Cleaning plugin registry";
	
	/* Destroy vm plugins */
	foreach(PluginProxy *proxy, vmAssociations.values())
	{
		factories.value(proxy->getPlugin()->getName())->destroyPlugin(proxy);
	}
	
	/* Destroy hi plugins */
	foreach(PluginProxy *proxy, hiAssociations.values())
	{
		factories.value(proxy->getPlugin()->getName())->destroyPlugin(proxy);
	}

	/* Destroy cd plugins */
	foreach(PluginProxy *proxy, cdAssociations.values())
	{
		factories.value(proxy->getPlugin()->getName())->destroyPlugin(proxy);
	}
	
	vmAssociations.clear();
	hiAssociations.clear();
	cdAssociations.clear();
}
