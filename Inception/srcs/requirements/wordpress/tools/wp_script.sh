#!/bin/sh

# A small pause is introduced to allow the database service to fully initialize.
# This is a simplistic approach. A more robust script might attempt to make a connection to the database before proceeding.
sleep 10

# Modifies the PHP-FPM configuration to listen on TCP port 9000 instead of the default Unix socket.
# This allows the web server to communicate with PHP-FPM through a network port.
sed -i "s|listen = /run/php/php7.4-fpm.sock|listen = 9000|" /etc/php/7.4/fpm/pool.d/www.conf

# Changes directory to where WordPress should be installed.
cd /var/www/wordpress

# Configures WordPress by creating a wp-config.php file.
# Uses environment variables for database configuration.
# The --allow-root option is used to permit the operation to proceed under the root user, which is generally not recommended for production environments.
# Used to not have to configure the wordpress page
wp config create \
        --dbname="${DB_NAME}" \
        --dbuser="${DB_USER}" \
        --dbpass="${DB_PASSWORD}" \
        --dbhost="${DB_HOST}" \
        --allow-root

# Installs WordPress with initial settings for site title, admin account, etc.
# Again, using --allow-root for WP-CLI under the root user.
# autofulfill second word press page 
wp core install --url="${DOMAIN_NAME}" \
    --title="${WP_TITLE}" \
    --admin_user="${WP_ADMIN_USER}" \
    --admin_password="${WP_ADMIN_PASSWORD}" \
    --admin_email="${WP_ADMIN_EMAIL}" \
    --allow-root

# Creates an additional WordPress user with specified role.
# Useful for setting up non-administrative users automatically.
wp user create "${WP_USER}" "${WP_EMAIL}" \
    --user_pass="${WP_PASSWORD}" \
    --role="${WP_ROLE}" \
    --allow-root

# Starts PHP-FPM to handle PHP requests.
# The -F option runs PHP-FPM in the foreground, and -R applies additional restrictions for improved security.
/usr/sbin/php-fpm7.4 -F -R
