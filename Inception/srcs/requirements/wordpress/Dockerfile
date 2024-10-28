FROM debian:bullseye

# update and install packages
RUN apt-get update -y && apt-get install -y \
    wget \
    php7.4 \
    php-fpm \
    php-mysql \
    mariadb-client \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

# install wordpress 
RUN wget https://fr-be.wordpress.org/latest-fr_BE.tar.gz -P /var/www/ \
 && cd /var/www && tar -xzf latest-fr_BE.tar.gz && rm latest-fr_BE.tar.gz \
 && chown -R root:root /var/www/wordpress

# Configuration pour PHP-FPM
RUN	mkdir -p /run/php

# Install WP-CLI to not have to configure host all the time
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
 && chmod +x wp-cli.phar \
 && mv wp-cli.phar /usr/local/bin/wp

# cp initialization script and add permissions to the script
COPY ./tools/wp_script.sh /bin/
RUN chmod +x /bin/wp_script.sh

ENTRYPOINT ["sh", "/bin/wp_script.sh"]


