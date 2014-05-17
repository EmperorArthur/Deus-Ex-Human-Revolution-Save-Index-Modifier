//This operates on the DeusEx Human Revolution saveindex file
//To Run:
//	indexer filename
//Copyright Arthur Moore 2013 GPL V3

//Fun header files
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>	//For exit
#include <cassert>
#include "indexfile.hpp"

//Can't forget this
using namespace std;

//cout the help information
void printHelp(){
cout << "Description:" << endl;
cout << "	This program is used to modify Deus Ex: Human Revolution saveindex files" << endl;
cout << "	It can not (yet) build a saveindex file from scratch." << endl;
cout << "	The primary purpose is to allow a user to archive old gamesaves easily" << endl;
cout << endl;
cout << "Default Usage:" << endl;
cout << "	Removes all saves except the autosaves and Save 99 from \"saveindex\"" << endl;
cout << "	It then renames Save 99 to Save 1, and outputs the file as \"saveindex.new\"" << endl;
cout << endl;
cout << "Arguments:" << endl;
cout << "	-h		This help statement" << endl;
cout << "	-nA		Do not include autosaves in the output file" << endl;
cout << "	-f		Overide the default input file name" << endl;
}

//And now the main function
int main(int argc, char *argv[]){
	//Program is designed around  a write temp, delete original, copy temp->original ,delete temp approach
	//User can overide this behavior
	string inFileName = "saveindex";
	string outFileName = "saveindex.new";
	indexFile mySaves;
	fstream outFile;	//Output file
	
	//Argument bools
	bool includeAutosaves = true;
	
	//Handle arguments passed to the program
	//WARNING:  Only handles the first argument for now
	if(argc >= 2){
		if(!string("-f").compare(argv[1])) {
			if(argc >= 3){
				inFileName = argv[2];
			}else{
				cerr << "Error: No filename provided!" << endl;
				exit(1);
			}
		}else if(!string("-nA").compare(argv[1])){
			includeAutosaves = false;
			cout << "Excluding Autosaves" << endl;
		}else if(!string("-h").compare(argv[1])){
			printHelp();
			exit(0);
		}else{
			cerr << "Command not recognized:  " << argv[1] << endl;
			cout << endl;
			printHelp();
			exit(1);
		}
	}
	
	mySaves.read(inFileName);
	

	//This just leaves me with the user data 2 autosaves and the last manual save
	int newNumberOfSaves = 4;
	//Knock that number down to 2 if not including the autosaves
	if(!includeAutosaves){
		newNumberOfSaves = 2;
	}

	//Make sure that we're not going to look at an empty array
	assert(mySaves.size() >= newNumberOfSaves);
	
	//Open the output file
	outFile.open(outFileName,ios::out|ios::binary);
	outFile.write((char *) &newNumberOfSaves,4);
	int temp=-1;
	//User data
	temp=mySaves.findIndex("USER");
	assert(temp != -1);
	mySaves[temp].write(outFile);
	//Can choose not to include these
	if(includeAutosaves){
		//Autosave 1
		temp=mySaves.findIndex("GAMEA1_4");
		assert(temp != -1);
		mySaves[temp].write(outFile);
		//Autosave 2
		temp=mySaves.findIndex("GAMEA2_4");
		assert(temp != -1);
		mySaves[temp].write(outFile);
	}
	//Last save (It should be the highest numbered save)
	//Rename it so that it's save #1
	temp=mySaves.findIndex("GAMER99_4");
	assert(temp != -1);
	mySaves[temp].name = "GAMER1_4";
	mySaves[temp].write(outFile);
	outFile.close();

	return 0;
}
