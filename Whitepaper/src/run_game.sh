#!/bin/bash
cd "$(dirname "$0")"

gnome-terminal -- /bin/bash -c "java -cp .:../lib/* Server 8000; exec bash"
gnome-terminal -- /bin/bash -c "java -cp .:../lib/* PlayerConnection localhost 8000; exec bash"
gnome-terminal -- /bin/bash -c "java -cp .:../lib/* PlayerConnection localhost 8000; exec bash"
gnome-terminal -- /bin/bash -c "java -cp .:../lib/* PlayerConnection localhost 8000; exec bash"
gnome-terminal -- /bin/bash -c "java -cp .:../lib/* PlayerConnection localhost 8000; exec bash"
gnome-terminal -- /bin/bash -c "java -cp .:../lib/* PlayerConnection localhost 8000; exec bash"