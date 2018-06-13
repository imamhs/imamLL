#!/bin/bash 

echo "Compiling imamLL library..."
sleep 1

cd src

gcc -c -Wall -Werror -fpic imamll.c

if [ "$?" -ne 0 ]
then
echo "Error compiling imamll.c"
exit 1
fi

gcc -shared -o libimamll.so imamll.o

if [ "$?" -ne 0 ]
then
echo "Error creating libimamll.so"
exit 1
fi

exit 0
