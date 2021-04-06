#!/usr/bin/env sh
# handle siquit

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <pid>"
    exit 1
fi

kill -QUIT "$1"
