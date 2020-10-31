#!/bin/bash

# autoindex check
if [ ${AUTO_INDEX} = 1 ]; then
	sed -i "s/autoindex on;/autoindex off;/g" ./etc/nginx/sites-available/default
fi

# make openssl
openssl req -newkey rsa:4096 -days 365 -nodes -x509 -subj "/C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=Gam/CN=localhost" -keyout localhost.dev.key -out localhost.dev.crt
mv localhost.dev.crt /etc/ssl/certs/
mv localhost.dev.key /etc/ssl/private/
chmod 600 /etc/ssl/certs/localhost.dev.crt /etc/ssl/private/localhost.dev.key

# rename phpMyAdmin
mv /var/www/html/phpMyAdmin-5.0.2-all-languages /var/www/html/phpmyadmin

service mysql start
service php7.3-fpm start

# setting phpMyAdmin & add database
echo "CREATE DATABASE IF NOT EXISTS wordpress;" | mysql -u root --skip-password
echo "show databases;" | mysql -u root --skip-password
echo "SET PASSWORD FOR root@'localhost' = PASSWORD('42'); FLUSH PRIVILEGES;" | mysql -u root -p

# start server
service nginx start

bash
