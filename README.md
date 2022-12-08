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
Pour le type, nous avons implémenté 3 tableaux, chacun contenant la liste des instructions du même type, puis après lecture du premier mot de la ligne (c'est à dire l'instruction), nous parcourons chaque tableau pour déterminer son type.
Pour l'opcode, nous avons fait un disjonction de cas pour toutes les instructions possibles car il n'y a pas de modèle général.
Enfin, pour les opérandes entières, nous avons fait le choix d'implémenter 3 fonctions : une récupère les opérandes d'une instruction de type I, une pour le type J et une pour le type R. Les trois fonctionnent de la manière suivante :
-L'instruction et l'opérande voulu (rd, rs, rt, ...) sont passés en paramètre
-Selon l'opérande voulu, on parcourt la chaine de caractère jusqu'au premier, deuxieme, ou troisieme $, puis on renvoie sous forme d'entier la valeur de l'opérande. Dans le cas ou l'opérande n'est pas précédée d'un $, on renvoie la valeur située apres un espace, une fois que tous les $ ont été parcours.

* Avez-vous vu des motifs récurrents émerger ? Avez-vous "factorisé" ces motifs
pour éviter de les répéter ? Si non, serait-ce difficile ?

Les instructions sont encodées de la même manière selon le type, nous avons donc "factorisé" l'encodage en binaire de l'instruction selon son type, sauf pour le type R où nous avons dû différencier quelques cas qui sortaient du modèle général. C'est le cas notamment des instructions type R qui ne prennent que 1 ou 2 arguments au lieu de 3 par exemple.
Idem pour la lecture des opérandes entières qui se fait pareillement suivant le type, sauf pour le type R qui admet quelques différences de la même manière que pour l'encodage.
Sans cette "factorisation", il aurait été long et fastidieux de traiter les instructions au cas par cas, et difficilement maintenable si on veux ajouter une instruction au jeu d'instructions.

* Comment avez-vous procédé pour écrire les tests ? Étes-vous confiant·e·s que
toutes les instructions gérées sont couvertes ? 

Nous avons rédigé deux autre fichiers sur le modèle du fichier test arithmetics.s déjà fourni avec le sujet, un fichier logic.s qui contient toutes les instructions logiques, et un fichier system.s qui contient toutes les instructions de type jump et de rotation/shift de mots. Nous avons supposé que les fichiers commençaient à 0x0000 pour utiliser les instructions de type jump.
Nous avons été attentifs à ce que ces trois fichiers tests contiennent ensemble la totalité du jeu d'instruction MIPS, et certaines instructions se retrouvent même testées plusieurs fois. D'une part pour assurer la cohérence des instructions entre elles (pouvoir déterminer les EXPECTED_FINAL_STATE) pour la suite du projet), et également pour assurer que toutes les configurations d'usage étaient prises en compte.


* Quelle a été votre expérience avec l'utilisation et la compréhension de la
documentation (ie. des annexes) ?

Notre expérience a été dans l'ensemble positive avec la documentation, celle-ci étant claire et complète. Pour chacune des instruction, la manière dont elle est encodée est indiquée avec précision, ce qui nous a permis d'y voir clair quant à l'écriture de nos fonctions.

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Implémenté la traduction pour des instructions de toutes les catéories
      (calcul, comparaisons, sauts, HI/LO, mémoire)
  - [x] Implémenté la traduction pour toutes les instructions de l'annexe 2
  - [x] Pris en compte les cas particuliers : valeurs négatives, hors limites,
      noms d'instructions ou opérandes invalides...


## Rendu 3

(10/15 lignes devrait suffire à chaque fois)

* Quelle structure en modules planifiez-vous d'utiliser pour l'émulateur ?

Nous avons découpé nos modules en 6 parties :

Les modules de mode :
  -Le module pas-à-pas, qui permet de lire un fichier ligne par ligne et de demander validation de l'utilisateur pour passer à la ligne suivante
  -Le module automatique, qui permet de lire un fichier ligne par ligne sans demander d'input utilisateur
  -Le module interactif, qui permet de lire les instructions une par une entrées par l'utilisateur dans la console

Les modules de fonctionnalité :
  -Le module de lecture et de conversion des instructions, qui permet de nettoyer les instructions, de les convertir en binaire puis en hexadécimal, et de les encoder.
  -Le module de récupération des mnémotechniques, des opérandes et des types, qui permet de récupérer le code de l'opération puis le type de l'instruction par disjonction de cas, et les opérandes de l'instruction selon le type.
  -Le module d'execution des instructions, qui permet de récupérer la commande et les opérandes en appelant les fonctions du module de lecture et conversion, et d'executer les instructions selon leur commande et leurs arguments, en mettant à jour les registres. Nous avons choisit de ne pas séparer les instructions par type à l'execution car les instructions de même type ne prennent pas forcément le même nombre d'arguments ni ne s'executent de la même manière.


* Quelles seront les fonctions principales de chaque module ?

Les modules de mode :
  -Le module pas-à-pas, qui contient seulement `pas_a_pas`, qui permet de lire un fichier ligne par ligne en encodant les instructions en hexadécimal et en les éxécutant, puis de demander validation de l'utilisateur pour passer à la ligne suivante.

  -Le module automatique, qui contient seulement `automatique`, qui permet de lire un fichier ligne par ligne en encodant les instructions en hexadécimal et en les éxécutant.

  -Le module interactif, qui contient seulement `interactif`, qui permet de lire les instructions une par une entrées par l'utilisateur dans la console, de les encoder en hexadécimal et de les éxécuter.

  -Le module de lecture et de conversion des instructions contient notamment :
    `clean_instruction` qui permet de supprimer à la fin des instructions les espaces, les tabulations et les retours à la ligne.
    `convert_hexa` qui permet de convertir une instruction binaire en hexadécimal.
    `convert_binaire` qui permet de convertir une instruction décimale en binaire.
    `encoder` qui permet de concaténer les éléments de l'instruction convertis en binaire et de convertir l'ensemble en hexadécimal en appelant convert_hexa.
  -Le module de récupération des mnémotechniques, des opérandes et des types contient notamment :
    `getType` qui permet de récupérer le type de l'instruction.
    `getOpCode` qui permet de récupérer le code opération de l'instruction (le mnémotechnique).
    `getIArgs`, `getJArgs`, et `getRArgs` qui permettent de récupérer les opérandes de l'instruction.
  -Le module d'execution des instructions, qui contient notamment :
    `get_args` qui permet de récupérer la commande et les opérandes de l'instruction en appelant les fonctions du module de lecture et de conversion.
    `execute` qui permet d'executer l'instruction selon la commande et les opérandes récupérées.


* Quels avantages voyez vous à cette structure (à comparer à un unique fichier)?

L'organisation en module permet de séparer les différentes fonctionnalités de l'émulateur, et donc de les développer et de les tester séparément. Cela permet également de mieux comprendre le fonctionnement de l'émulateur, et de le modifier plus facilement au besoin.


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
