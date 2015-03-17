# UML class diagram #
![http://www.capponcino.it/alessio/files/universita/tesi-visual-netkit/plugin_framework_uml.png](http://www.capponcino.it/alessio/files/universita/tesi-visual-netkit/plugin_framework_uml.png)
# Introduction #
As you can see on the previous UML diagram, all wheel around the `PluginRegistry` _Singleton_ class. This is the controller of mappings between BaseElement and the plugins attached, where BaseElement is a Virtual machine, Collision domain or a link.

The Registry offer a directory service to get and init a new plugin passing its name. In this case, the loader fartory class initialize a new instance of the selected plugins returning its Proxy.

The unique way that plugins has to send/receive data with the system is through the proxy, because it is coupled with mappings and other main controllers.

# The Plugin Interface #
```
class PluginInterface
{
        
public:
        virtual ~PluginInterface() {};
        
        /**
         * pluginAlertMsg is a pointer to QString to show to the user an alert
         * if the returned value is false.
         * If it is initialized, the function returns the result of consistency check.
         * If some check fail, you have to returns false and an error string.
         * If the pluginAlertMsg doesn't passed (default as NULL) the property is
         * saved without any consistent check, and allways return TRUE.
         */
        virtual bool saveProperty(QString propUniqueId, QString propValue,
                        QString *pluginAlertMsg = NULL) = 0;
        
        /**
         * Get a QString that contains the resource name of XML plugin conf file
         * example: ":/pluginName/xml-config
         */
        virtual QString getXMLResource() = 0;
        
        /**
         * Get a map of templates: the KEY is the template path relative to the laboratory
         * root; the Value represent the content of the file.
         */
        virtual QMap<QString, QString> getTemplates() = 0;
        
        /**
         * This function return a list of top level properties owned by this plugin
         * (properties are root levels of a tree-structure)
         */
        virtual QList<PluginProperty*> getPluginProperties() = 0;
        
        /**
         * Return my proxy
         */
        virtual PluginProxy* getProxy() = 0;
        
        /**
         * Set my proxy
         * Called by the system at initialization time
         */
        virtual void setProxy(PluginProxy* p) = 0;
        
        /**
         * This function is the way that the system use to know the element group.
         * Default unused and return -1
         */
        virtual void setGroupID(qint32 id) { Q_UNUSED(id) };
        virtual qint32 getGroupID() { return -1; };
        
        /**
         * This function is called by the system (through the proxy) when the plugin
         * is created and attached to a base element. If you don't want show a label
         * on plugin startup, you have to return a empty QString()
         */
        virtual QString getDefaultGraphisLabel() = 0;
        
        /**
         * Get the name of this plugin, normally it's the name inside the plugin.ini
         * file
         */
        virtual QString getName() = 0;
        
        /**
         * This function is called by the system (through the proxy) when the plugin
         * is created and attached to a base element during laboratory open.
         * Normally inside this function you have to parse config files (lab path is
         * passed as argument), initialize properties and finally if you want you can
         * set your own graphics label, through the proxy changeGraphicsLabel()
         * function.
         * The function return true if the parser is able to recognize datas fetching
         * own files.
         * (also used with 3rd part laboratory)
         */
        virtual bool init(QString laboratoryPath) = 0;
        
        /**
         * This function is called by the system (through the proxy) when the user
         * want remove a property. The control of minimum occurrence is delegated by
         * plugin it self. Return an empty QString() if all is ok and the property
         * is correctly deleted; an error string to show to the users as alert
         * otherwise.
         */ 
        virtual QString deleteProperty(QString propertyUniqueId) = 0;
        
        /**
         * This function is called by the system (through the proxy) when the user
         * want add a new property as child of anther one. The control of maximum
         * occurrence is delegated by plugin it self.
         * Return PluginProperty *  with the created property pointer, or NULL on
         * error. On error write the error string inside the second member of the
         * QPair, or return an empty string if all goes well.
         */
        virtual QPair<PluginProperty*, QString> addProperty(QString propertyIdToAdd,
                        QString parentPropertyUniqueId) = 0;
        
};

/**
 * The types of factories
 */
typedef PluginInterface* createPlugin_t();
typedef void destroyPlugin_t(PluginInterface*);
```

The most impontant part is the last `typedef`. Each concrete plugin must have two `extern "C"` functions than represents the constructor and the deconstructor of the plugin.

These two function are used by the loader factory (resolving the two simbols **createPlugin** and **destroyPlugin**) to load and destroy instances of your plugin.

A tipical use of these two extern functions is showed:
```
/* Factory (creator) */
extern "C" PluginInterface* createPlugin()
{
    return new YourContretePluginClass();
}

/* Factory (destroyer) */
extern "C" void destroyPlugin(PluginInterface* p)
{
        delete p;
}
```

Each plugin can be configured by an XML file that contains the plugin description and the properties in a nested structure (n-ari tree)

Here is presented a fac-simile of plugin config file:
```
<plugin name="Test">
        
        <global type="vm" version="1.1" author="Alessio Di Fazio" dependencies="">
                <![CDATA[This is a test plugin.]]>
        </global>
        
        <properties>
                
                <property id="test-0" name="property-1" default_value="1" min="1" max="1000">
                        <![CDATA[Property 1. Min 1 Max 1000]]>
                        <childs>
                                <property id="test-1" name="property-1-1" default_value="1-1" min="1" max="2">
                                        <![CDATA[A sub property (1-1). Min 1 Max 2]]>
                                        <childs>
                                                <property id="test-2" name="property-1-1-1" default_value="1-1-1" min="1" max="10">
                                                        <![CDATA[A sub property (1-1-1). Min 1 Max 10]]>
                                                        <childs>
                                                                <property id="test-3" name="property-1-1-1-1" default_value="1-1-1-1" min="1" max="1">
                                                                        <![CDATA[A sub property (1-1-1-1). Min 1 Max 1]]>
                                                                        <childs />
                                                                </property>
                                                                <property id="test-8" name="property-1-1-1-2" default_value="1-1-1-2" min="0" max="3">
                                                                        <![CDATA[A sub property (1-1-1-2). Min 0 Max 3]]>
                                                                        <childs />
                                                                </property>

                                                        </childs>
                                                </property>
                                        </childs>
                                </property>     
                        </childs>
                </property>
                
                <property id="test-4" name="property-2" default_value="2" min="0" max="3">
                        <![CDATA[Property 2. Min 0 Max 3]]>
                        <childs />
                </property>
                
                <property id="test-5" name="property-3" default_value="3" min="1" max="3">
                        <![CDATA[Property 3. Min 1 Max 3]]>
                                <childs>
                                        <property id="test-6" name="property-3-1" default_value="3-1" min="1" max="1">
                                                <![CDATA[A sub property (3-1). Min 1 Max 1]]>
                                                <childs>
                                                        <property id="test-7" name="property-3-1-1" default_value="3-1-1" min="1" max="5">
                                                                <![CDATA[A sub property (3-1-1). Min 1 Max 5]]>
                                                                <childs />
                                                        </property>
                                                </childs>
                                        </property>
                                </childs>
                </property>
                
        </properties>
        
</plugin>
```

The property expert class can be used by a plugin and offer some convenient functions to manipulate the n-ary tree structure of properties:

```
class PropertyExpert
{
        
private:
        //...

public:
        PropertyExpert(QString &xmlRes);
        virtual ~PropertyExpert();
        QList<PluginProperty*> buildBaseProperties();
        QMap<QString, QString> parseXmlGlobalInfo();
        bool isXmlConfValid() { return isXmlValid; };
        PluginProperty * searchProperty(QList<PluginProperty*> properties, QString pUid);
        QList<PluginProperty*> searchPropertiesById(QList<PluginProperty*> properties, QString pId);
        QMap<QString, QString> getPropertyInfo(QString propertyId);
        PluginProperty * newProperty(QString propName, QString defValue, QString desc,
                        QString idVal, quint16 minOcc, quint16 maxOcc);
        
        // pair: <child name, child id>
        QList< QPair<QString, QString> > getChildsByParentId(QString id);
        QList< QPair<QString, QString> > getRootChilds();
};
```