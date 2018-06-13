#!/bin/bash

echo "Installing imamLL library..."
sleep 2

cd src

if uname -p | grep -q x86_64; then
        rm /usr/lib/x86_64-linux-gnu/libimamll.*
        cp libimamll.so /usr/lib/x86_64-linux-gnu/
        if [ "$?" -ne 0 ]
        then
            echo "Error installing imamLL library"
            exit 1
        fi
        cp imamll.h /usr/include/
        if [ "$?" -ne 0 ]
        then
            echo "Error installing imamLL header"
            exit 1
        fi
else
        rm /usr/lib/i386-linux-gnu/libimamll.*
        cp libimamll.so /usr/lib/i386-linux-gnu/
        if [ "$?" -ne 0 ]
        then
            echo "Error installing imamLL library"
            exit 1
        fi
        cp imamll.h /usr/include/
        if [ "$?" -ne 0 ]
        then
            echo "Error installing imamLL header"
            exit 1
        fi
fi

exit 0
