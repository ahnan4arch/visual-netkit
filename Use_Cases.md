# Introduzione #

Descrizione dei casi d'uso in modo strutturato.


---


# UC-Crea lab `[DONE: 100%]` #

**Attore:** utente finale

**Contesto:** applicazione principale

**Pre-condizioni:** sistema avviato


**Post-condizioni:** è stato creato un nuovo lab ed e' stato associato come corrente


**Scenario Principale di Successo:** l’utente sceglie di creare un nuovo lab dal menu principale. Il nuovo lab viene creato e associato come corrente.

**Variante:**
  * se e' gia' esistente un lab corrente, il sistema provvede a chiedere all'utente (eventualmente se necessario) il salvataggio dello stesso e la conferma a chiudere l'attuale laboratorio e a settare quello nuovo come nuovo lab corrente.



# UC-Modifica proprietà lab `[DONE: 100%]` #

**Attore:** utente finale

**Contesto:** applicazione principale

**Pre-condizioni:** sistema avviato


**Pre-condizioni:** esiste un lab in memoria ed è il lab corrente


**Post-condizioni:** il lab è stato modificato in una delle sue proprietà


**Scenario Principale di Successo:** l'utente vuol modificare alcune proprietà del lab (quali versione, data, descrizione, etc...). L'utente seleziona l'elemento "root" presente all'interno del Tree della dock Laboratory e il sistema dopo la selezione carica nella dock Property editor tutte le varie coppie (chiave, valore).
L'utente accede (doppio click) ad un valore desiderato e lo modifica. Una volta modificato il campo, il sistema provvede ad effettuare la modifica per il campo scelto.


# UC-Crea VM `[DONE: 100%]` #

**Attore:** utente finale

**Contesto:** applicazione principale


**Pre-condizioni:** esiste un lab in memoria ed è il lab corrente


**Post-condizioni:** è stata creata una nuova VM (comprensiva di tutti i plugins scelti) ed è stata associata al lab corrente


**Scenario Principale di Successo:** L'utente seleziona dal menu'/toolbar l'azione di "add virtual machine" che risulta mutuamente esclusiva rispetto alle altre azioni che governano la scena. L'utente clicca con il mouse su un'area della scena e il sistema mostra una form per l'acquisizione dei dati riguardanti la nuova macchina virtuale.
La form in particolare mostra campi per l'inserimento di dati quali: nome della macchina virtuale, plugins che si vogliono utilizzare (e che caratterizzano il "tipo" della vm). L'utente clicca su OK, e il sistema crea tutte le varie instanze degli oggetti, i vari mappings e mostra sulla scena la macchina virtuale etichettata dal suo nome, ed eventuali etichette offerte dai plugins prescelti.
Al momento di creazione l'utente puo' decidere se inizializzare manualmente le varie proprieta' offerte dai plugins attivati, oppure mantenere i valori di default.


# UC-Crea Collision Domain `[DONE: 100%]` #

**Attore:** utente finale

**Contesto:** applicazione principale


**Pre-condizioni:** esiste un lab in memoria ed è il lab corrente


**Post-condizioni:** è stato creato uno nuovo collision domain (comprensivo di tutti i plugins scelti) ed è stato associato al lab corrente


**Scenario Principale di Successo:** L'utente seleziona dal menu'/toolbar l'azione di "add collision domain" che risulta mutuamente esclusiva rispetto alle altre azioni che governano la scena. L'utente clicca con il mouse su un'area della scena e il sistema mostra una form per l'acquisizione dei dati riguardanti il CD.
La form in particolare mostra campi per l'inserimento di dati quali: nome del collision domain e eventuali plugins che si vogliono utilizzare. L'utente clicca su OK, e il sistema crea tutte le varie instanze degli oggetti, i vari mappings e mostra sulla scena il collision domain etichettato dal suo nome, ed eventuali etichette offerte dai plugins prescelti.
Al momento di creazione l'utente puo' decidere se inizializzare manualmente le varie proprieta' offerte dai plugins attivati, oppure mantenere i valori di default.


# UC-Modifica proprieta' di un elemento `[DONE: 100%]` #

**Attore:** utente finale

**Contesto:** applicazione principale


**Pre-condizioni:** esiste un elemento in memoria


**Post-condizioni:** una proprieta' dell'elemento prescelto (o di un suo plugin) è stata cambiata


**Scenario Principale di Successo:** l'utente seleziona uno degli elementi base presenti nella dock della vista ad albero della scena, oppure doppio click sulla scena. Il sistema provvede a mostrare tutte li proprieta' per quell'elemento selezionato all'interno della dock "property editor" seguite dalle proprieta' offerte da eventuali plugins usati. L'utente tramite quest'ultima puo' modificare le varie proprieta' e il sistema provvede ad aggiornare i dati previa validazione.
La validazione offerta dai plugins, non e' restrittiva; l'utente puo' sempre settare un valore di una proprieta' anche se questa risulta sintatticamente errata.


# UC-Aggiungi una interfaccia di rete/link per una VM `[DONE: 100%]` #

**Attore:** utente finale

**Contesto:** applicazione principale

**Pre-condizioni:** esiste una VM in memoria


**Post-condizioni:** e' stata aggiunta una interfaccia di rete (o link) alla macchina selezionata che la collega al collision domain desiderato.


**Scenario Principale di Successo:** l'utente seleziona dalla toolbar o dal menu', l'azione add link. Successivamente puo' cliccare e trascinare il mouse come se volesse tirare una linea tra due elementi della scena (tra una macchina virtuale  e un collision domain). Il sistema traccia questa linea e la mostra di colore giallo. Al momento del rilascio del mouse, il sistema mostra una form che permette di inizializzare le proprieta' del link appena creato. In particolare, il nome dell'interfaccia (_ethX_), lo stato (_up_ or _down_), nonche' permette di selezionare i plugins da collegare al link che si sta creando.

Anche in questo caso l'utente puo' scecliere se inizializzane o meno le varie proprieta' offerde dai singoli plugins selezionati.


---

# UC-Open LAB `[DONE: 100%]` #


**Attore:** utente finale

**Contesto:** applicazione principale

**Pre-condizioni:** non vi e' un lab corrente in memoria (vedi variante)


**Post-condizioni:** è stato caricato in memoria un lab pre-esistente su filesystem (creato precedentemente con il tool)


**Scenario Principale di Successo:** l'utente tramite l'azione "Open Lab" seleziona la directory dov'e' presente il lab precedentemente salvato. Il sistema provvede a "validare" il lab cercando il file lab.xml e lab.conf. Se si ha un esito positivo, il sistema crea in memoria un lab, e inizia ad instanziare gli oggetti (e eventuali plugins per ognuno di essi) e creare tutti i mappings. Il parsing delle informazioni extra presenti nei vari files di configurazione, e' lasciato al singolo plugin tramite la funzione di init().

**Variante:** se vi e' gia' un lab caricato in memoria, il sistema deve mostrare un alert all'utente informandolo che per prima cosa deve chiudere il lab corrente.