# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 16:27:48 by jaeylee           #+#    #+#              #
#    Updated: 2020/10/27 16:50:15 by jaeylee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 1. debian:buster
FROM		debian:buster
MAINTAINER	jaeylee@student.42seoul.kr
RUN			apt-get -y update
RUN			apt-get -y upgrade

# 2. nginx install
RUN			apt-get -y install nginx

# 3. openssl install
RUN			apt-get -y install openssl

# 4. php-fpm install
RUN			apt-get -y install php-fpm
RUN			apt-get -y install php
RUN			apt-get -y install mariadb-server
RUN			apt-get -y install php-mysql

# 5. source copy & wordpress, phpmyadmin install
COPY		/srcs/run.sh ./
COPY		/srcs/default /etc/nginx/sites-available/default
ADD			/srcs/phpMyAdmin-5.0.2-all-languages.tar.gz /var/www/html/
COPY		/srcs/config.inc.php /var/www/html/phpMyAdmin-5.0.2-all-languages
ADD			/srcs/wordpress.tar.gz /var/www/html/
COPY		/srcs/wp-config.php /var/www/html/wordpress/

# 6. autoindex
ENV			AUTO_INDEX 0

# ft_server start
CMD			bash run.sh

EXPOSE		80 443
