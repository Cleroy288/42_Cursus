MyInception

best used :
make clean // removes db also 
make up

if you want to keep the db ::
make down
make up 

Commandes Make Disponibles
make ou make all

Prépare l'environnement en construisant et démarrant les conteneurs Docker nécessaires pour le projet. C'est la commande par défaut si aucune cible n'est spécifiée.
make build

Construit ou reconstruit les services spécifiés dans le fichier docker-compose.yml. Cette commande s'assure que tous les conteneurs sont arrêtés avant de recréer les images et de démarrer les conteneurs. Utile pour appliquer des modifications ou des mises à jour.
make up

Démarre les conteneurs en arrière-plan. Avant de démarrer les conteneurs, cette commande arrête tous les conteneurs en cours d'exécution et met à jour le fichier /etc/hosts pour inclure l'adresse du projet. Idéale pour démarrer le projet après un arrêt ou un nettoyage.
make down

Arrête et supprime les conteneurs Docker définis dans docker-compose.yml. Les images, les volumes et les réseaux créés par docker-compose up sont conservés.
make clean

Nettoie l'environnement en supprimant les conteneurs, les images inutilisées, et les volumes. Cette commande est utile pour repartir de zéro ou pour libérer de l'espace disque.

to acces wordpress is just : link + /wp-admin

to acces mariadb :
- docker exec -it mariadb bash 
- mysql -u root -p or mysql -u <nom_utilisateur> -p

then in MARIADB ;

SHOW DATABASES;
USE inception;
SHOW TABLES;
SELECT * FROM wp_options;

show user1 in mariadb ::
USE mysql;
SELEcT user, host FROM user;
