#include "indexfile.hpp"
#include <iostream>
#include <cassert>
#include <cstdlib>

void StringRead(std::fstream& inFile,std::string& aString){
	char readChar = '0';
	aString.clear();
	//This reads untill a null charachter is read in.
	while(readChar != '\0'){
		inFile.read(&readChar,1);
		aString.append(1,readChar);
		assert(inFile.good());
	}
	//Last char read is '\0', so put it back, and remove it from the end of the string
	inFile.putback(readChar);
	aString.pop_back();		//It's so much easier to do this in C++11
}
void StringWrite(std::fstream& outFile,std::string& aString){
	char temp = '\0';
	for(unsigned int i=0; i< aString.size();i++){
		temp = aString[i];
		outFile.write(&temp,1);
	}
};

void saveIndex::read(std::fstream& inFile){
	StringRead(inFile,name);
	//Make sure the string isn't too long
	assert(name.size() < MAXSTRINGSIZE);
	//Skip padding zeros
	inFile.seekg(MAXSTRINGSIZE - name.size(),std::ios_base::cur);
	inFile.read((char *) &rawData,RAWDATASIZE);
};
void saveIndex::write(std::fstream& outFile){
	StringWrite(outFile,name);
	//Make sure the string isn't too long
	assert(name.size() < MAXSTRINGSIZE);
	//Add the padding zeros
	char temp = '\0';
	for(int i=name.size();i<MAXSTRINGSIZE;i++){
		outFile.write(&temp,1);
	}
	outFile.write((char *) &rawData,RAWDATASIZE);
};

indexFile::~indexFile(){
	delete[] allIndeces;
}

//How many saves are in the index file
int indexFile::size(){
	return numberOfSaves;
}

saveIndex & indexFile::operator[](int i){
	assert(i < this->size());
	return allIndeces[i];
}

void indexFile::read(std::string inFileName = "saveindex"){
	std::fstream inFile;
	
	//Open the file (if it doesn't exist, complain and exit
	inFile.open(inFileName,std::ios::in|std::ios::binary);
	if(!inFile.is_open()){
		std::cerr << "ERROR:  Unable to open file  \"" << inFileName << "\"" << std::endl;
		exit(1);
	}
	//The first byte is the number of save indeces
	inFile.read((char *) &numberOfSaves,4);
	std::cout << "There are " << numberOfSaves - 1 << " save files, and 1 USER file."<<std::endl;
	allIndeces = new saveIndex[numberOfSaves];
	
	//Read in all the save index data
	for(int i=0;i<numberOfSaves;i++){
		std::cout << "Reading Index: " << i << std::endl;
		allIndeces[i].read(inFile);
		std::cout << "    Name: " << allIndeces[i].name << std::endl;
		std::cout << "    Name (size): " << allIndeces[i].name.size() << std::endl;
	}
	
	inFile.close();
};

//Find an index with a certain name
//If more than one index has the same name, then this only returns the first one
//If none are found, returns '-1'
int indexFile::findIndex(std::string findName){
	for(int i=0;i<numberOfSaves;i++){
		if(!allIndeces[i].name.compare(findName)){
			return i;
		}
	}
	return -1;
}
