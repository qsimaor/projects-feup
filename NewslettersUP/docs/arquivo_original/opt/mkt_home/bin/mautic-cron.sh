#!/bin/bash

sudo -u www-data bash -c : && RUNAS="sudo -u www-data"

echo 1: $USER

$RUNAS bash<<_
echo 2: \$USER
_
echo 3: $USER
