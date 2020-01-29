#!/bin/bash

insert()
{	
	echo "Enter Movie Name"
	read mName
	echo "Enter Movie Id"
	read mId
	echo "Enter Movie Genre"
	read mGenre
	echo "Enter Movie Rating"
	read mRating
	echo "Enter Movie Likes"
	read mLikes
	
	echo $mId "\t" $mName "\t" $mGenre "\t" $mRating "\t" $mLikes >> Movies.txt
	

		
}

display(){
	echo "Name \t\t Id \t Genre \t\t Rating \t Likes\n----------------------------------------------\n"
	sort Movies.txt > temp.txt
	rm Movies.txt
	mv temp.txt Movies.txt
	cat Movies.txt
}	

search(){
	echo "Enter Id of Movie:"
	read searchBy
	grep $searchBy Movies.txt -w
	r=`echo $?`
	if test $r -eq 1;
	then echo "Record Not Found"
	fi
}	


delete()
{
	echo "enter Id of movie to be deleted\n"
	read deleteBy
	grep -v $deleteBy Movies.txt > temp.txt
	mv temp.txt Movies.txt
}
modify(){
	echo "enter Id of Movie to be modified"
	read modifyId
	movie= `grep $modifyId Movies.txt -w`
	r=`echo $?` 
	if test $r -ne 1;
	then
		grep -v $modifyId Movies.txt > temp.txt
			rm Movies.txt
		mv temp.txt Movies.txt
		echo $movie
		echo "Enter New Movie Name"
		read mName
		echo "Enter New Movie Genre"
		read mGenre
		echo "Enter New Movie Rating"
		read mRating
		echo "Enter New Movie Likes"
		read mLikes
	
		echo $modifyId "\t" $mName "\t" $mGenre "\t" $mRating "\t" $mLikes >> Movies.txt
	else
		echo "No records found!"
		fi	
}
echo "Welcome"
choice=1;
while test $choice -ne 6
do 
echo "1.Insert Movie \n2.Display Records\n3.Search Movie \n4.Delete Movie\n5.Modify \n6.exit \n"
read choice
echo "selected option $choice"
case $choice in 
	1)insert;;
	2)display;;
	3)search;;
	4)delete;;
	5)modify;;
	6)echo "Thank You!"
		exit;;
esac  
done	

