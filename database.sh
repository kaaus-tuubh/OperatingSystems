#/bin/sh

create()
{
	if [ -e "record.txt" ]
	then
	rm record.txt
	fi
	
	touch record.txt
}

show()
{
	echo "-------------------------------------------------------------------------"
	cat -n record.txt
	if [ $? -ne 0 ]
	then
	echo "           Empty Databse                      "
	fi
	echo "-------------------------------------------------------------------------"
}

insert()
{
	echo "\nEnter Roll no  "
	read roll
	echo "\nEnter Name     "
	read name
	echo "\nEnter marks    "
	read marks
	
	echo "$roll\t$name\t$marks" >> record.txt

}

search()
{
	echo "\nEnter pattern to search "
	read pat
	
	grep $pat record.txt
}

del()
{
	echo "\nEnter roll no to delete "
	read r1
	
	grep -v $r1 record.txt > temp.txt
	cp temp.txt record.txt
	rm temp.txt
}

update()
{
	echo "\nEnter roll to update "
	read r2
	
	grep $r2 record.txt > temp.txt
	if [ $? -eq 0 ]
	then
		old_line=$(grep $r2 record.txt)
		oname=$(echo $old_line | cut -d " " -f2)
		omarks=$(echo $old_line | cut -d " " -f3)
		
		echo $oname 
		echo $omarks
		
		ch1=1
		while [ $ch1 -ne 0 ]
		do
			echo "\nWhat do you want to update ? "
			echo "\n1.Name"
			echo "\n2.Marks"
			
			read ch1
			
			case $ch1 in
			
			1) 	echo "\nEnter new Name "
				read nname
				sed -i "s/${oname}/${nname}/g" temp.txt
				new_line=$(grep -m1 "" temp.txt)
				sed -i "s/${old_line}/${new_line}/g" record.txt
				old_line=$new_line;;
				
			2)	echo "\nEnter new Marks "
				read nmarks
				sed -i "s/${omarks}/${nmarks}/g" temp.txt
				new_line=$(grep -m1 "" temp.txt)
				sed -i "s/${old_line}/${new_line}/g" record.txt
				old_line=$new_line;;
				
			3)	ch1=0;;
			
			*);;
			esac
		done
	else
		echo "\nNot found "
		
	fi
		
}	
				 
				
			   


ch=1

while [ $ch -ne 0 ]
do
	echo "|---------MENU---------|"
	echo "|1.Create Database     |"
	echo "|2.Show Databse        |"
	echo "|3.Insert              |"
	echo "|4.Search              |"
	echo "|5.Delete              |"
	echo "|6.Update              |"
	echo "|7.Exit                |"
	echo "|----------------------|"
	
	read ch
	
	case $ch in
	
	1) create ;;
	2) show ;;
	3) insert ;;
	4) search ;;
	5) del ;;
	6) update ;;
	7) ch=0;;
	
	*);;
	esac
done
	

