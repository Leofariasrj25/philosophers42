#!/bin/bash

NC="\033[0m"
GREEN="\033[0;32m"
RED="\033[0;31m"

printf "\t======= MEMENTO MORI =======\t\n"
printf "\t   --Philosopher tester-- \t\n\n"

make philo

printf "\n\t =ROUND 1 - arg count=\n"

declare -a input_return
./philo
input_return[0]=$?
./philo 5
input_return[1]=$?
./philo 5 2
input_return[2]=$?
./philo 5 2 3
input_return[3]=$?
./philo 5 2 3 4 1
input_return[4]=$?

sleep .2
for ((i=0; i <= 5; i++))
do
	printf "TEST $i:\t"
	if [[ ${input_return[$i]} -eq 1 ]]; then
		printf "$GREEN [OK] $NC\n"
	else
		printf "$RED [KO] $NC\n"
	fi
done
