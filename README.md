Projet 2022-2023 : Émulateur MIPS

Analyse de texte (dont lecture des opérandes entières) :
Lecture ligne par ligne + écriture fonctions pourrécupérer les informations contenues dans l'instrucion (type, opcode, opérandes). 
- Type : 3 tableaux, contenant les instructions de type R, I et J. 
  * Quelques cas particuliers pour le type R.

- Opcode : Disjonction de cas pour toutes les instructions possibles (pas de modèle général).

- Opérandes entières : 3 fonctions pour récupérer les instructions de type I, J et R :
  * L'instruction et l'opérande voulu (rd, rs, rt, ...) sont passés en paramètre
  
  * Selon l'opérande voulu, on parcourt la chaine de caractère jusqu'au premier, deuxieme, ou troisieme $ 
  
  * Return la valeur de l'opérande (int).
  
  * Si l'opérande n'est pas précédée d'un $, on renvoie la valeur située apres un espace, une fois que tous les $ ont été parcouru.


Fichiers test :
  * Fichier test arithmetics.s : contient toutes les instructions arithmétiques
  
  * Fichier test logic.s : contient toutes les instructions logiques
  
  * Fichiers test system.s et jump_ops.s : contient toutes les instructions de type jump et de rotation/shift de mots
  
  * Fichier test delay_slot.s : contient toutes les instructions de type jump et de rotation/shift de mots, avec des instructions dans le delay slot
  
  * Fichier test EDGE_overflow.s : contient toutes les instructions arithmétiques, avec des valeurs d'opérandes qui dépassent les limites de la mémoire

Contiennent des instructions test, les expected outputs, et les valeurs hexadécimales des instructions.


Modes de l'emulateur :
- Les modules de mode
  * Le module pas-à-pas, qui permet de lire un fichier ligne par ligne et de demander validation de l'utilisateur pour passer à la ligne suivante
  
  * Le module automatique, qui permet de lire un fichier ligne par ligne sans demander d'input utilisateur
  
  * Le module interactif, qui permet de lire les instructions une par une entrées par l'utilisateur dans la console

- Les modules de fonctionnalité :
  * Le module de lecture et de conversion des instructions, qui permet de nettoyer les instructions, de les convertir en binaire puis en hexadécimal, et de les encoder.

  * Le module de récupération des mnémotechniques, des opérandes et des types, qui permet de récupérer le code de l'opération puis le type de l'instruction par disjonction de cas, et les opérandes de l'instruction selon le type.
  
  * Le module d'execution des instructions, qui permet de récupérer la commande et les opérandes en appelant les fonctions du module de lecture et conversion, et d'executer les instructions selon leur commande et leurs arguments, en mettant à jour les registres. Nous avons choisit de ne pas séparer les instructions par type à l'execution car les instructions de même type ne prennent pas forcément le même nombre d'arguments ni ne s'executent de la même manière.
  
  * Le module de mémoire, qui permet de simuler la mémoire à l'aide de listes chainées, qui va contenir les données via l'instruction SW et les récupérer via l'instruction LW.


Fonctions des modules :
- Les modules de mode :
  * Le module pas-à-pas, qui contient seulement `pas_a_pas`, qui permet de lire un fichier ligne par ligne en encodant les instructions en hexadécimal et en les éxécutant, puis de demander validation de l'utilisateur pour passer à la ligne suivante.

  * Le module automatique, qui contient seulement `automatique`, qui permet de lire un fichier ligne par ligne en encodant les instructions en hexadécimal et en les éxécutant.

  * Le module interactif, qui contient seulement `interactif`, qui permet de lire les instructions une par une entrées par l'utilisateur dans la console, de les encoder en hexadécimal et de les éxécuter.

- Le module de lecture et de conversion des instructions contient notamment :
    `clean_instruction` qui permet de supprimer à la fin des instructions les espaces, les tabulations et les retours à la ligne.
    `convert_hexa` qui permet de convertir une instruction binaire en hexadécimal.
    `convert_binaire` qui permet de convertir une instruction décimale en binaire.
    `encoder` qui permet de concaténer les éléments de l'instruction convertis en binaire et de convertir l'ensemble en hexadécimal en appelant convert_hexa.
  
- Le module de récupération des mnémotechniques, des opérandes et des types contient notamment :
    `getType` qui permet de récupérer le type de l'instruction.
    `getOpCode` qui permet de récupérer le code opération de l'instruction (le mnémotechnique).
    `getIArgs`, `getJArgs`, et `getRArgs` qui permettent de récupérer les opérandes de l'instruction.
  
- Le module d'execution des instructions, qui contient notamment :
    `get_args` qui permet de récupérer la commande et les opérandes de l'instruction en appelant les fonctions du module de lecture et de conversion.
    `execute` qui permet d'executer l'instruction selon la commande et les opérandes récupérées.