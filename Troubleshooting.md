### Domande, difficoltà, punti critici, dilemmi... ###

Paolo:
  1. come considero le "rotte"? Posso astrarle come _classi_ vere e proprie o come _classi di associazione_ tra le classi "VM" e "Network"? Ricordo che una rotta è così definita:
```
 route add -net 195.11.14.0 netmask 255.255.255.0 gw 100.0.0.9 dev eth1
```
  1. è necessario che in una rotta venga specificata anche l'interfaccia del gateway coinvolta? Se il gw è connesso alla rete mediante una interfaccia ed ad essa è associato un indirizzo univoco (ad es. 100.0.0.9), forse non è necessario che la classe rotta abbia anche tale parametro. -sottolineo che questa è comunque una stupidagine!-
  1. nelle VM, anche se per ora non sono "tipizzate" come router, non sarebbe meglio considerare la possibiltà che esse contengano anche una _tabella di instradamento_?