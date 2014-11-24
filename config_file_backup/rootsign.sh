#!/bin/sh

#   make sure environment exists
if [ ! -d newcerts ]; then
    mkdir newcerts
fi
if [ ! -f serial ]; then
    echo '01' >serial
fi
if [ ! -f index.txt ]; then
    cp /dev/null index.txt
fi

