#!/bin/sh

# start maria db service
service mariadb start

# execute next commands as root
mariadb -v -u root <<EOF

CREATE DATABASE IF NOT EXISTS $DB_NAME;

CREATE USER IF NOT EXISTS '$DB_USER'@'%' IDENTIFIED BY '$DB_PASSWORD';

GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'%';

GRANT ALL PRIVILEGES ON $DB_NAME.* TO 'root'@'%' IDENTIFIED BY '$DB_PASS_ROOT';

SET PASSWORD FOR 'root'@'localhost' = PASSWORD('$DB_PASS_ROOT');

FLUSH PRIVILEGES;

EOF

# wait 5 sec that everything is done 
sleep 5

# stops maria db service , needs to be started from docker compose
service mariadb stop

# Exécute all comands fron file
exec "$@"
