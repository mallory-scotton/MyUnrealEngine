# Nom du projet

Unreal Banana

# Contexte et but du projet

Dans un monde où le développement de jeux est parfois compliqué, des solutions sont apparues et aident au quotidien les développeurs : les moteurs de jeux. Certains sont simplement des librairies pour faciliter le développement, d'autres sont des logiciels à part entière. Ce monde nous fascine, nous avons décidé de créer notre propre petit moteur de jeux, ce dernier prend son inspiration d'Unreal Engine, un moteur qu'on ne présente plus.
Notre projet ne vise pas à recréer Unreal Engine, ce serait une tâche vraisemblablement irréalisable. Notre projet est une version allégée pour des jeux 2D uniquement et une logique d'exécution simplifiée.

# Domaines concernés

- Bas niveau
- Logiciel lourd
- Jeux vidéos

# Membres

- mallory.scotton@epitech.eu
- hugo.cathelain@epitech.eu
- ossan.msoili@epitech.eu
- nathan.fievet@epitech.eu
- raphael.ostier@epitech.eu

# Objectifs fonctionnales

Fonctionnalités principales du moteur:

En tant que développeur de jeux, je souhaite créer et gérer des objets de jeu via un système d'acteurs afin de pouvoir concevoir des éléments de jeu interactifs.
    - Supporter la création d'acteurs avec des propriétés
    - Permettre l'héritage des acteurs (AActor, APawn)
    - Gérer les événements du cycle de vie des acteurs (BeginPlay, Tick, EndPlay)


En tant que développeur, je souhaite un système de programmation visuel basé sur des nœuds afin de pouvoir créer la logique du jeu sans écrire de code.
    - Créer différents types de nœuds (arithmétiques, événements, flux de contrôle, nœuds d'acteurs)
    - Connecter les nœuds via des liens entre les broches
    - Supporter le flux d'exécution et le flux de données entre les nœuds

En tant que développeur, je souhaite gérer les événements d'entrée afin de pouvoir faire en sorte que mon jeu réponde aux actions de l'utilisateur.
    - Capturer les événements du clavier (KeyPressed, KeyReleased)
    - Acheminer les événements vers les acteurs appropriés
    - Permettre aux nœuds d'événements de répondre aux événements d'entrée

En tant que développeur, je souhaite un système de rendu utilisant SFML afin de pouvoir afficher les éléments du jeu à l'écran.
    - Rendre les acteurs dans une fenêtre
    - Supporter un rendu personnalisé pour différents types d'acteurs
    - Gérer la gestion de la fenêtre et la boucle de rendu

Gestion de projet:

En tant que développeur, je souhaite créer et gérer des projets afin de pouvoir organiser mes ressources et mon code de jeu.
    - Créer de nouveaux projets avec une structure de dossiers appropriée
    - Sauvegarder et charger des fichiers de projet (.uproject)
    - Suivre les modifications du projet avec la gestion de l'état modifié

En tant que développeur, je souhaite un navigateur de contenu afin de pouvoir gérer les ressources du jeu.
    - Parcourir le répertoire de contenu du projet
    - Importer et gérer les ressources
    - Sélectionner les ressources à utiliser dans le jeu

Éditeur de graphes visuel:

En tant que développeur, je souhaite créer des graphes de nœuds visuellement afin de pouvoir concevoir la logique du jeu de manière intuitive.
    - Ajouter, connecter et supprimer des nœuds dans un éditeur visuel
    - Modifier les propriétés des nœuds via l'interface utilisateur
    - Sauvegarder et charger des graphes de nœuds

En tant que développeur, je souhaite concevoir des modèles de classes afin de pouvoir définir un comportement réutilisable des acteurs.
    - Créer et modifier des définitions de classes
    - Ajouter des variables, des fonctions et des événements aux classes
    - Instancier des classes en tant qu'acteurs dans le monde

Systèmes d'évaluation et d'exécution:

En tant que développeur, je souhaite un système de contexte d'évaluation afin que les nœuds puissent communiquer et partager des données pendant l'exécution.
   - Définir et obtenir des valeurs de broches entre les nœuds
   - Stocker et récupérer des propriétés par nom
   - Mettre en file d'attente les nœuds pour l'exécution

En tant que joueur, je souhaite que le moteur exécute mon jeu afin que je puisse y jouer et le tester.
    - Initialiser le monde du jeu et les objets
    - Exécuter la boucle de jeu avec un timing approprié
    - Gérer les entrées utilisateur pendant le jeu
    - Rendre le jeu à des fréquences d'images appropriées

# Environement d'éxécution / stack / matériel

Langages utilisés:
C++, C, Shell, Makefile

Compilation:
Via Makefile

Librairies utilisées:
SFML, ImGui, Stb Image, CrudeJSON

# Cursus

PGE

# Temps estimé

90 Jours (3 mois)

# Date de livraison estimée

20/06/2025

# Release 1 (25%)

Au début du projet, nous nous concentrons sur les fonctionnalités fondamentales du moteur de jeu. Nous avons implémenté le système de gestion des acteurs, permettant leur création avec des propriétés de base. La gestion des événements du cycle de vie des acteurs (BeginPlay, Tick, EndPlay) est fonctionnelle. Le moteur peut également gérer les entrées clavier pour réagir aux actions de l'utilisateur, et un rendu de base a été mis en place via SFML, affichant les éléments simples à l'écran. Le projet est déjà structuré pour permettre l'ajout ultérieur de fonctionnalités plus avancées.

# Release 2 (50%)

À mi-parcours du projet, nous avons élargi le système d'acteurs pour supporter l'héritage, permettant une hiérarchisation des types d'acteurs (AActor, APawn). Le système de programmation visuelle avec des nœuds a également été intégré, avec des nœuds arithmétiques et de contrôle de flux de base. L'éditeur de graphes visuels commence à prendre forme, permettant aux développeurs d'ajouter et connecter des nœuds. Les événements d'entrée sont désormais acheminés vers les acteurs appropriés, et nous avons commencé à implémenter la gestion de projet avec la création de nouveaux projets et la gestion des ressources de manière basique.

# Release 3 (75%)

À ce stade, le moteur commence à devenir pleinement fonctionnel. L'éditeur de graphes visuels permet de manipuler les nœuds et de définir des logiques de jeu plus complexes. Le système de gestion de contenu est désormais opérationnel, facilitant l'importation et l'organisation des ressources du jeu. Les nœuds d'acteurs peuvent interagir avec les événements d'entrée en temps réel, et les propriétés des acteurs peuvent être modifiées directement dans l'éditeur visuel. La gestion des classes et modèles d'acteurs, permettant de définir des comportements réutilisables, est en place. Le moteur est maintenant capable d'exécuter des jeux simples avec un rendu fluide et un système de gestion des événements.

# Release 4 (100%)

La version finale du projet est maintenant complète et prête pour une utilisation en production. Toutes les fonctionnalités sont intégrées et fonctionnent de manière fluide : gestion des acteurs avec héritage complet, système de programmation visuelle avec nœuds avancés, gestion des événements d'entrée et de sortie, et rendu des objets via SFML avec performances optimisées. Le moteur prend en charge l'exécution de jeux avec un système de boucle de jeu complet, incluant la gestion des entrées, le rendu à des fréquences d'images appropriées, et l'exécution du code via les nœuds. Le projet peut désormais être facilement utilisé pour créer des jeux 2D en toute simplicité, avec une interface de développement intuitive et un système d'évaluation et d'exécution robuste.
