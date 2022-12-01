#!/bin/bash

NC="\033[0m"
GREEN="\033[0;32m"
RED="\033[0;31m"

printf "\t======= MEMENTO MORI =======\t\n"
printf "\t   --Philosopher tester-- \t\n\n"

make philo

printf "\n\t =ROUND 1 - arg count=\n"

declare -a input_return
./philo 2> /dev/null
input_return[0]=$?
./philo 5 2> /dev/null
input_return[1]=$?
./philo 5 2 2> /dev/null
input_return[2]=$?
./philo 5 2 3 2> /dev/null
input_return[3]=$?
./philo 5 2 3 4 1 5 2> /dev/null
input_return[4]=$?
./philo 5 2 3 4 1 5 90 200 10000 2007 4000 100 2> /dev/null
input_return[5]=$?

sleep .2
for ((i=0; i < 6; i++))
do
	printf "TEST $i:\t"
	if [[ ${input_return[$i]} -eq 1 ]]; then
		printf "$GREEN [OK] $NC\n"
	else
		printf "$RED [KO] $NC\n"
	fi
done

printf "\n\t =ROUND 1.1 - negative arg=\n"
./philo -5 1000 5000 2000 2> /dev/null
input_return[0]=$?
./philo 5 -1000 5000 2000 2> /dev/null
input_return[1]=$?
./philo 5 1000 -5000 2000 2> /dev/null
input_return[2]=$?
./philo 5 1000 5000 -2000 2> /dev/null
input_return[3]=$?
./philo 5 1000 5000 -2000 2> /dev/null
input_return[4]=$?
./philo 5 1000 5000 2000 -9 2> /dev/null
input_return[5]=$?
./philo -5 -1000 -5000 -2000 -9 2> /dev/null
input_return[6]=$?
./philo -5 -1000 -5000 2000 2> /dev/null
input_return[7]=$?
./philo -5 -1000 5000 2000 2> /dev/null
input_return[8]=$?
./philo -5 1000 -5000 2000 2> /dev/null
input_return[9]=$?

sleep .2
for ((i=0; i < 10; i++))
do
	printf "TEST $i:\t"
	if [[ ${input_return[$i]} -eq 2 ]]; then
		printf "$GREEN [OK] $NC\n"
	else
		printf "$RED [KO] $NC\n"
	fi
done

printf "\n\t =ROUND 1.2 - out of bounds args=\n"
./philo 999999999999 3000 5000 6000 2> /dev/null
input_return[0]=$?;
./philo 3000 999999999999 5000 6000 2> /dev/null
input_return[1]=$?;
./philo 3000 5000 999999999999 6000 2> /dev/null
input_return[2]=$?;
./philo 3000 5000 6000 999999999999 2> /dev/null
input_return[3]=$?;
./philo 3000 5000 6000 40000 999999999999 2> /dev/null
input_return[4]=$?;

sleep .2
for ((i=0; i < 5; i++))
do
	printf "TEST $i:\t"
	if [[ ${input_return[$i]} -eq 3 ]]; then
		printf "$GREEN [OK] $NC\n"
	else
		printf "$RED [KO] $NC\n"
	fi
done
