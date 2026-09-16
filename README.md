# Corewar

> Un jeu de programmation où des champions écrits en assembleur s'affrontent dans une mémoire circulaire partagée, jusqu'à ce qu'un seul survive.

---

## Le concept

**Corewar** est un jeu où plusieurs programmes, appelés **champions**, s'exécutent simultanément dans un même espace mémoire circulaire (la **arène**, généralement 6 Ko). Chaque champion est écrit dans un langage assembleur dédié, le **Champion Assembly Language**, puis compilé en bytecode `.cor`.

L'objectif de chaque champion est simple : **survivre le plus longtemps possible** et **éliminer les autres**, en écrivant par-dessus leur code, en modifiant leur exécution, ou en les empêchant de signaler leur présence via l'instruction `live`.

Le jeu se déroule en deux grandes parties :

1. **L'assembleur (`asm`)** — transforme le code source `.s` d'un champion en bytecode exécutable `.cor`.
2. **La machine virtuelle (`corewar`)** — charge plusieurs champions `.cor` dans l'arène mémoire et simule leur exécution cycle par cycle jusqu'à déterminer un vainqueur.

---

## Architecture du projet

### 1. L'assembleur

- Parsing du fichier `.s` (labels, instructions, commentaires, directives `.name` et `.comment`)
- Vérification syntaxique et sémantique du code
- Génération du header du champion (nom, commentaire, taille du programme)
- Encodage des instructions et de leurs paramètres selon le codage d'octets définis par le sujet
- Écriture du fichier binaire `.cor` final

### 2. La machine virtuelle

- Chargement d'un ou plusieurs champions `.cor` dans la mémoire circulaire de l'arène
- Gestion des **processus** (un par champion au départ, avec possibilité de forker via `fork`/`zjmp` etc.)
- Boucle de cycles : à chaque cycle, chaque processus exécute son instruction courante si son délai d'attente est écoulé
- Décodage des **opcodes** et exécution de leurs effets (lecture/écriture mémoire, arithmétique, sauts, comparaisons...)
- Gestion du **mécanisme `live`** : un champion qui ne s'annonce pas assez souvent est éliminé
- Détection de fin de partie et annonce du vainqueur
- Mode `-dump` pour afficher l'état de la mémoire à un cycle donné (debug)

---

## Compilation

```bash
make            # compile le binaire corewar
make clean      # supprime les fichiers objets et de coverage
make fclean     # supprime en plus les binaires (corewar, unit_tests)
make re         # recompile tout depuis zéro
make tests_run  # compile et lance les tests unitaires (Criterion)
make epiclang   # lance epiclang sur les sources et les tests
```

---

## Utilisation

**Assembler un champion :**

```bash
./asm champion.s
# génère champion.cor
```

**Lancer une partie :**

```bash
./corewar champion1.cor champion2.cor [champion3.cor ...]
```

**Options utiles :**

```bash
./corewar -dump N champion1.cor champion2.cor   # affiche l'état de l'arène après N cycles
```

---

## Structure du projet

```
.
├── asm/                # Sources de l'assembleur
├── corewar/            # Sources de la machine virtuelle
├── include/            # Headers communs (op.h, etc.)
├── champions/          # Exemples de champions .s
├── Makefile
└── README.md
```

---

## Avancement

- [x] Assembleur — parsing, vérification et génération du `.cor`
- [ ] Machine virtuelle — structures de données, boucle de cycles, décodage des opcodes, parsing du binaire `.cor`

---

## Ce que ce projet apporte

- Manipulation bas niveau de la mémoire et des bits
- Compréhension fine du fonctionnement d'un assembleur et d'une VM
- Rigueur sur le parsing et la gestion d'erreurs
- Bonnes bases pour la sécurité offensive/défensive (compréhension d'un exécuteur de bytecode, exploitation de comportements mémoire)

---

## Auteur

Projet réalisé dans le cadre du cursus **Epitech**.
