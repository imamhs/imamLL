#!/bin/bash 

echo "Compiling examples..."
sleep 1

cd examples

gcc -Wall -o number_list number_list.c -limamll

if [ "$?" -ne 0 ]
then
echo "Error compiling number_list.c"
fi

gcc -Wall -o product_list product_list.c -limamll

if [ "$?" -ne 0 ]
then
echo "Error compiling product_list.c"
fi

gcc -Wall -o student_book student_book.c -limamll

if [ "$?" -ne 0 ]
then
echo "Error compiling student_book.c"
fi

exit 0
