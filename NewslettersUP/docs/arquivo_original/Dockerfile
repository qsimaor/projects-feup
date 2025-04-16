FROM php:8.0-apache
RUN docker-php-ext-install pdo pdo_mysql
RUN a2enmod rewrite

# Instalar o cliente MariaDB
RUN apt-get update && \
    apt-get install -y mariadb-client && \
    rm -rf /var/lib/apt/lists/*

# Copiar o código do seu aplicativo e os arquivos web para o contêiner
COPY opt/ /opt/
COPY var/www/ /var/www/html/

# Expõe a porta 80 para acessar o servidor Apache
EXPOSE 80
