# Use Debian Bullseye
FROM debian:bullseye

# update packages and insatll the mariadb server 
RUN apt-get update -y && apt-get install mariadb-server -y

# copy of the config file for mariadb 
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# copy of the naunching script 
COPY tools/script.sh /bin/

# make script executable
RUN chmod +x /bin/script.sh

# define command to execute script and launch maria db server securely 
CMD ["/bin/bash", "-c", "/bin/script.sh && mysqld_safe"]
