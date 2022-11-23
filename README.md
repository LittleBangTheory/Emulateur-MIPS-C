# Projet CS351 (2022-2023): Émulateur MIPS

---
title: Projet CS351 (2022-2023): Émulateur MIPS
author: Robin Lafage, Gabin Chognot
date: 18/10/2022
---

## Rendu 1

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Vérifié que `make test-cli` ne renvoie pas d'erreur.
  - [x] Vérifié que `make tests` se plaint sur le nombre d'instructions et pas
      sur l'existence des fichiers de sortie.
  - [x] Vu que les soumissions se font avec `make tar`.


## Rendu 2

(Une dizaine de lignes devrait suffire à chaque fois)

* Comment avez-vous choisi de programmer l'analyse de texte (dont la lecture
des opérandes entières) ?

Nous avons fait le choix de lire le fichier d'entrée ligne par ligne, puis d'écrire des fonctions qui permettent de récupérer les informations contenues dans l'instrucion c'est à dire le type de l'instruction, l'opcode, et les opérandes entières.
Pour le type, nous avons implémenté 3 tableaux, chacun contenant la liste des instructions du même type, puis après lecture du premier mot de la ligne (c'est à dire l'instruction), parcours chaque tableau pour déterminer son type.
Pour l'opcode, nous avons fait un disjonction de cas pour toutes les instructions
possibles car il n'y a pas de modèle général.
Enfin, pour les opérandes entières, nous avons fait le choix d'implémenter 3 fonctions : une récupère les opérandes d'une instruction de type I, une pour le type J et une pour le type R. Les trois fonctionnent de la manière suivante :
-L'instruction et l'opérande voulu (rd, rs, rt, ...) sont passés en paramètre
-Selon l'opérande voulu, on parcours la chaine de caractère jusqu'au premier, deuxieme, ou troisieme dollar, puis on renvoie sous forme d'entier la valeur de l'opérande. Dans le cas ou l'opérande n'est pas précédée d'un dollar, on renvoie la valeur située apres un espace, une fois que tous les dollars ont été parcours.

* Avez-vous vu des motifs récurrents émerger ? Avez-vous "factorisé" ces motifs
pour éviter de les répéter ? Si non, serait-ce difficile ?

Les instructions sont encodées de la même manière selon le type, nous avons donc "factorisé" l'encodage en binaire de l'instruction selon son type, sauf pour le type R où nous avons dû différencier quelques cas qui sortaient du modèle général. C'est le cas notamment des instructions type R qui ne prennent que 1 ou 2 arguments au lieu de 3 par exemple.
Idem pour la lecture des opérandes entières qui se fait pareillement suivant le type, sauf pour le type R qui admet quelques différences de la même manière que pour l'encodage.
Sans cette "factorisation", il aurait été long et fastidieux de traiter les instructions au cas par cas, et difficilement maintenable si on veux ajouter une instruction au jeu d'instructions.

* Comment avez-vous procédé pour écrire les tests ? Étes-vous confiant·e·s que
toutes les instructions gérées sont couvertes ? 

[COMPLÉTER ICI]

* Quelle a été votre expérience avec l'utilisation et la compréhension de la
documentation (ie. des annexes) ?

Notre expérience a été dans l'ensemble positive avec la documentation, celle-ci étant claire et complète. Pour chacune des instruction, la manière dont elle est encodée est indiquée avec précision, ce qui nous a permis d'y voir clair quant à l'écriture de nos fonctions.

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [ ] Implémenté la traduction pour des instructions de toutes les catéories
      (calcul, comparaisons, sauts, HI/LO, mémoire)
  - [ ] Implémenté la traduction pour toutes les instructions de l'annexe 2
  - [ ] Pris en compte les cas particuliers : valeurs négatives, hors limites,
      noms d'instructions ou opérandes invalides...


## Rendu 3

(10/15 lignes devrait suffire à chaque fois)

* Quelle structure en modules planifiez-vous d'utiliser pour l'émulateur ?

[COMPLÉTER ICI]

* Quelles seront les fonctions principales de chaque module ?

[COMPLÉTER ICI]

* Quels avantages voyez vous à cette structure (à comparer à un unique fichier)?

[COMPLÉTER ICI]


## Rendu 4

* Avez-vous réussi à suivre la structure prévue au rendu 3 ? Quelles
modifications ont été nécessaires ? Rétrospectivement, est-ce que cette
structure était bien prévue ?

[COMPLÉTER ICI]

* Avez-vous compris le fonctionnement de chaque instruction à partir de la
documentation fournie ? Si non, quels sont les points obscurs ?

[COMPLÉTER ICI]

* Quels exemples de programmes avez-vous choisi pour tester le calcul ? Les
comparaisons et sauts ? La mémoire ?

[COMPLÉTER ICI]

* Le sujet spécifie-t-il tous les détails nécessaires pour bien implémenter la
mémoire ? Quels choix avec-vous faits ?

[COMPLÉTER ICI]

* Reste-t-il des bugs que vous avez découverts et pas corrigés ?

[COMPLÉTER ICI]

* D'autres remarques sur votre programme ?

[COMPLÉTER ICI]

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :**
  - [ ] Implémenté l'émulation de toutes les instructions gérées par le rendu 2.
  - [ ] Implémenté l'émulation de toutes les instructions.
  - [ ] Tous vos tests qui passent.
  - [ ] Vérifié que vous tests couvrent toutes les instructions émulées.
  - [ ] Testé les cas particuliers : valeurs négatives, overflows...
  - [ ] Testé les cas d'erreur : division par zéro, sauts invalides...
  - [ ] Un port fonctionnel de DOOM pour votre émulateur.

* Des retours sur le projet en général ?

[COMPLÉTER ICI]
