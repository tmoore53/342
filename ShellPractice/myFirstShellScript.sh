#! /usr/bin/bash

#          <---- This is a single lined comment in shell


# ECHO COMMAND
echo "Hello Shell World"

#VARIABLES
#UPPERCASE By convention
#Ltters, numbers, and underscore
: 'No spaces in between assigning the variable name and its value'

NAME="Tyler Moore"
echo "My name is ${NAME}"

: '
This is a multi-
level comment in
a shell file.
Make sure you have a space between the : and the single quotes '

echo "Did you see the comment?"

echo " "
read -p "Enter your name: " NAMETWO

echo "This should pause here"


#Stops the code and waits/allows for the user to enter text 
: ' Adding double quotes allows the variable to store the text the user
inputed' 

read -i "" ANSWER

echo "If it did pause you should be able to see your answer: ${ANSWER}"


echo  "The Name you entered was: ${NAMETWO}" 