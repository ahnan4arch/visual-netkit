#include <QtCore>
#include <QCoreApplication>
#include <QHostAddress>
#include <QDebug>

QHostAddress cidr2netmask(quint8 cidrMask);

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);


//	QMap<quint8, QHostAddress> maskMapping;
//	for(int i=1; i<33; i++)
//		maskMapping.insert(i, cidr2netmask(i));
	
	/**
	 * if key don't exist the map return a QHostAddress empty (verify with isNull()
	 * if the value don't exist, the map return 0 (invalid netmask) 
	 */
	//qDebug() << maskMapping.key(QHostAddress("10.0.0.0"));
	
	QHostAddress full("255.255.255.255");
	QHostAddress some("10.0.2.2");
	QHostAddress some_mask("255.128.0.0");
	
	//get network
	QHostAddress network(some.toIPv4Address() & some_mask.toIPv4Address());
	
	qDebug() << QHostAddress(network.toIPv4Address() | (~some_mask.toIPv4Address() & full.toIPv4Address()));
	
	return 0;
}

QHostAddress cidr2netmask(quint8 cidrMask)
{
	QHostAddress base(QHostAddress::Broadcast);
		
	QHostAddress conv((base.toIPv4Address() << (32 - cidrMask)));
	
	return conv;
}
