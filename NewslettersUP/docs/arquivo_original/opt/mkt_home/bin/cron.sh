#!/bin/bash

# Verifica se o script está sendo executado como www-data
if [ "$(whoami)" != "rodolfo" ]; then
	echo "Este script deve ser executado como rodolfo."
	exit 1
fi

cd /opt/mkt_home/bin

for i in $(/opt/mkt_home/sbin/lista-instancias-mautic); do
	/opt/mkt_home/bin/get-publications-new.py ${i}
done
