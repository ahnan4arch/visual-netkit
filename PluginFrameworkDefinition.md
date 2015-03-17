# Plugin framework definition #

## Introduzione ##

Va detto prima di ogni cosa che il tool nella sua versione base, ossia senza la presenza di qualsiasi plug-in, puo' dare all'utente la possibilita' di creare e definire la struttura topologica di una rete di computers (vista a livello 2).

Tale rete e' quindi composta da 3 elementi base: Virtual Machines, Collision Domain e links tra questi (dave i links rappresentano interfacce ethernet di una virtual machine).

Le infarmazioni celate dietro a questi 3 componenti, sono solamente le loro etichette che sono viste come identificatori (nomi) univoci nel loro genere.

## Definizione di un plug-in ##

E' importante definire la linea di demarcazione tra cosa puo' e cosa non puo' richiedere un plugin al sistema.

Un plugin e' sostanzialmente una caratterizzazione di qualche tipo, applicata a uno o piu' dei tre componenti fondamentali citati prima. Quindi in base al tipo di "plugin applicato" ad un elemento, tale plugin sara' responsabile ad offrire ulteriori caratteristiche all'elemento a cui e' applicato, rendendolo via via sempre meno generico (ossia salendo la pila ISO-OSI). Su un elemento possono essere attivi piu' plugins, dove ognuno di questi plasma una parte di comportamento ma stando attenti a non creare conflitti tra i vari plugins attivi sul medesimo componente.

La natura di un plugin, ossia qual'e' il suo compito e su quali elementi e' applicato, viene definita in vari modi:
  * una volta scelto un componente, l'utente decide se a questo va associato un certo plugin; questo implica che il plugin opera sull'oggetto richiedente
  * un plugin puo' essere un plugin di gruppo, ossia puo' operare su piu' componenti e addirittura sulla totalita' del laboratorio. Questo processo e' deciso dal plugin stesso, che dopo essere stato creato per operare su un determinato componente, puo' egli stesso chiedere al sistema di essere "collegato" ad altri componenti. (si pensi alla macchina virtuale e alle interfacce di rete collegate ad essa)

### Cosa un plugin deve offrire ###

Ogni plugin deve offrire alcune caratteristiche al sistema che provvedera' ad applicare tali azioni verso gli elementi di cui il plugin e' responsabile, caratterizzandone il comportamento.
Il plugin deve quindi offrire:

  * una lista (coppie key-value) di proprieta' di cui l'elemento dovra' disporre;
  * una descrizione (meta-descrizione) di queste proprieta' per far si che il sistema riesca a ricavarne una interfaccia grafica per la manipolazione; ad esempio esporre i valiri di default, ecc... Il controllo su tali valori e' per giunta delegato al plugin stesso, e la "connessione" tra l'interfaccia grafica e il plugin-handler e' delegato al sistema di gestione dei plugins.
  * Il plugin deve offrire eventuali templates testuali (files di configurazione o parti di essi) nonche' il path di collocazione all'interno del laboratorio; Se il laboratorio possiede gia' quel determinato file di configurazione, il sistema stesso dovra' provvedere ad effettuare un marge (nella maggior parte dei casi un append) tra il file esistente e le informazioni offerte dal plugin.
  * Il plugin deve offrire una descrizione (un'etichetta) da collocare all'elemento a livello grafico.
  * Il plugin puo' avere un meccanismo di "monitoring" sui file di configurazione di cui lui e' responsabile; tale sistema di monitoraggio puo' provvedere ad aggiornare le informazioni dell'elemento/i in real-time. (Si pensi all'intervento dell'utente che modifica le informazioni di un file di configurazione al di fuori dell'IDE).

### Cosa il sistema offre ai plugins ###

Ogni volta che si sceglie di ampliare le caratteristiche di un elemento base (VirtualMachine, CollisionDomain, HardwareInterface) tramite l'applicazione di un determinato plugin ad esso, il sistema provvede a passare il riferimento dell'oggetto base al plugin stesso.

Per come e' strutturato a basso livello il sistema, partendo da un qualsiasi elemento e' possibile raggiungere tutti gli altri nodi qualora la rete creata (ossia il lab) rappresenti un grafo connesso. In questo modo un plugin puo' sostanzialmente ha un grado di liberta' molto elevato potendo agire su piu' oggetti oltre che quello a cui e' stato assegnato. Tuttavia questa e' una possibilita' che offre il sistema, ma non e' detto che sia sempre necessaria.

Come ipotizzato ogni plugin conosce uno (o piu', indirettamente) degli oggetti base situati nello strato business del sistema. Il sistema tuttavia deve fornire la possibilita' al plugin di interagire con gli oggetti "grafici" che rappresentano graficamente all'utente lo stato degli oggetti di business; per fare questo il plugin manager deve dare la possibilita' al proxy plugin (il rappresentante del plugin vero e proprio) di recuperare l'oggetto grafico passando l'oggetto di business a cui e' collegato. Questo e' possibile grazie al framework composto dagli oggetti "mappers" di cui il sistema e' gia' dotato. Un mapper non e' altro che uno strato di indirezione che collega due oggetti che rappresentano lo stesso concetto ma a livelli differenti (si pensi all'oggetto VirtualMachine - di business e l'oggetto VirtualMachineItem - presente nella scena grafica)

Va sottolineato che per come si stanno definendo le cose, su di un componente base possono operare piu' plugin di natura diversa allo stesso tempo. Questo fa si' che l'utente dovra' poter interagire (modificarle sostanzialmente) con le proprieta' di ogni plugin collegato ad ogni singolo elemento.
Questo ci porta a fare alcune considerazioni:

  1. L'elemento grafico deve prevedere la possibilita' di mostrare una label per ogni plugin (se necessario);
  1. L'elemento grafico deve dare la possibilita' all'utente di selezionare i plugins che vuole siano "attivi" per quel determinato elemento
  1. Ogni volta selezionato l'elemento grafica (tramite il tree scene view) nella property dock devono apparire sia gli attributi base che tutti gli attributi dettati dai vari plugins attivi su quel componente, opportunamente distinti.

Per concludere il sistema deve poter colloquiare con tutte le instanze proxy dei vari plugins attivi nonche' prevedere un meccanismo di riconoscimento delle dipendenze tra plugins applicati ad un stesso elemento base. Tale informazione di "dipendenza" risiede all'interno del plugin.

### Come funziona l'architettura ###

  1. L'oggetto X di tipo PluginProxy viene dichiarato e viene invocato il costruttore
  1. Il costruttore registra un nuovo mapping presso il plugin manager/controller per il plugin del tipo BasicMappingFactory<Plugin, X> e le relative informazioni (nome, eventuali dipendenze...).
  1. L'utente specifica se il plugin X debba essere incluso (o verrà comunque sempre incluso dall'applicazione e poi usato o meno) in un file di configurazione o a runtime in una adeguata struttura dati.
  1. Per risolvere le dipendenze, il manager/controller viene invocato e ritorna una lista di PluginProxy dps delle dipendenze. Il metodo creator del PluginProxy Y (ove Y è un elemento tra le dipendenze) viene invocato per creare l'oggetto. Si ripetono gli stessi passi per ogni plugin Y in dps.

### Plugin configuration file ###

```
[global]
name=PlugiName
type=vm|cd|link
description="a long Plugin destription
that take more then a single line!"
version=1.0
dependencies="plugin1 plugin2 plugin3"
author="author1, author2, author3"

[properties]
propName1/p_default_value=DefaultValue1
propName1/p_description="Property Description1"
propName1/p_init_order=a

propName2/p_default_value=DefaultValue2
propName2/p_description="Property Description2"
propName2/p_init_order=c

propName3/p_default_value=DefaultValue3
propName3/p_description="Property Description3"
propName3/p_init_order=b
```
**NOTE:** se il valore di una proprieta' richiede piu' parole e caratteri separati da uno spazio (vedi dependencies), ricordarsi di avvolgere il tutto con un doppio apice.

Ogni proprieta' puo' avere un p\_init\_order che rappresenta un carattere (ordinamento alfabetico) che descrive la posizione della property al momento di inizializzazione/presentazione della lista di properties per il plugins.

Nell'esempio le properties verrebbero presentate nel seguente ordine:
  1. propName1
  1. propName3
  1. propName2