#!/bin/bash
# SO IS1 214b LAB07
# Marian Strilets
# sm51174@zut.edu.pl




if [ $1 = '-p' ]
then
	for i in  /proc/[0-9]*
	do
		cd $i
	    #pid
	     cat status | head | cut -d: -f2 | head -n6  | tail -n1 | tr '\n' '\t'
		#ppid
		 cat status | head | cut -d: -f2 | head -n7 | tail -n1 | tr '\n' '\t'
    	#uid
        cat status | head | cut -d: -f2 | head -n9 | tail -n1 | cut -f2 | tr '\n' '\t'
		#program name
         cat status | head | cut -d: -f2 | head -n1  
	done
elif [ $1 = '-u' ]
then
    echo '-u'

	for i in  /proc/[0-9]*
    do
        cd $i
        #pid
         cat status | head | cut -d: -f2 | head -n6  | tail -n1 | tr '\n' '\t'
        #program name
         cat status | head | cut -d: -f2 | head -n1  | tr '\n' '\t'
      	#workspace
      	pwd
    done
else
    echo 'Brak parametrow'
fi
