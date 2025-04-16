#!/bin/bash

# Caminho para o seu script Python
SCRIPT_PATH="main.py"

# Adicionando a tarefa ao cron
(crontab -l 2>/dev/null; echo "0 0 * * * /usr/bin/python3 $SCRIPT_PATH") | crontab -
echo "Tarefa agendada no cron para executar diariamente à meia-noite."
