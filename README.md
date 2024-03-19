SuperReso
=========

Ce projet a pour but de simuler l'envoie de trames au sein d'un réseau local.
Il est donc possible de lui fournir un graphe de réseau composé de routeurs et de stations et de faire communiquer ces stations entre-elles a l'aide de l'interface présenté dans l'invité de commande.

Installation
============

Après avoir récupérer le code de ce dépot il vous suffit d'écrire "make projet" pour que le code source soit compilé.

Ensuite il ne vous reste plus qu'à exécuter le projet en donnant en argument le nom du fichier de configuration du réseau.
On pourra par exemple écrire `./projet mylan_no_cycle.lan.txt`.
