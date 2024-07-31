#!/bin/bash

opt=1

while [ "$opt" -lt 6 ]
do
	echo -e "Choose one of the following\n1. Create a new address Book\n2. View Records\n3. Insert new Records\n4. Delete a record\n5. Modify a record\n6. Exit"
	read opt

	case $opt in
		1)
			echo "Enter Filename:"
			read fileName
			if [ -e "$fileName" ]; then
				rm "$fileName"  # Remove the file if it already exists
			fi
			cont=1
			echo -e "Name\tNumber\t\tAddress\n=====================\n"| cat  >> "$fileName"

			#cont=1
			while [ "$cont" -gt 0 ]
			do
				echo -e "\nEnter Name:"
				read name
				echo "Enter the phone no of $name:"
				read number
				echo "Enter address of $name:"
				read address
				echo -e "$name\t$number\t\t$address" | cat >> "$fileName"
				echo "Enter 0 to stop, 1 to enter Next:"
				read cont
			done
			;;
			
		2)
			cat $fileName
			;;
		3)
			echo  "\nEnter Name:"
			read name
			echo "Enter the phone no of $name:"
			read number
			echo "Enter address of $name:"
			read address
			echo "$name\t$number\t\t$address" >> "$fileName"
			;;
		4)
			echo "Delete record \n Enter name /Phone number"
			
			read pattern
			temp="temp"
			grep -v $pattern $fileName | cat >> $temp
			rm $fileName
			cat $temp | cat >> $fileName
			rm $temp
			;;
		5)
			echo "Modify record \n Enter name /Phone number"
			
			read pattern
			temp="temp"
			grep -v $pattern $fileName | cat >> $temp
			rm $fileName
			cat $temp | cat >> $fileName
			rm $temp
			
			echo "Enter name"
			read name
			echo "Enter Phone number of $name"
			read number
			echo "Enter Address of $name"
			read address
			
			echo -e "$name\t$number\t\t$address" | cat >> "$fileName"
			;;
		
	esac
done

