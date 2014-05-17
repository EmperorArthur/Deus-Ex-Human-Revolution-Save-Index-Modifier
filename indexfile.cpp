#include "indexfile.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <algorithm>

void saveIndex::read(std::fstream& inFile){
	//Read in the name
	getline(inFile,name,'\0');
	//Make sure the string isn't too long
	assert(name.size() < MAXSTRINGSIZE);
	//Skip padding zeros (getline chomps the terminating char)
	inFile.seekg(MAXSTRINGSIZE - (name.size() + 1),std::ios_base::cur);
	//Read Raw Data
	inFile.read((char *) &rawData,RAWDATASIZE);
};
void saveIndex::write(std::fstream& outFile){
	//Make sure the string isn't too long
	assert(name.size() < MAXSTRINGSIZE);
	//Write out the name
	outFile.write(name.c_str(),name.size());
	//Add the padding zeros
	char temp = '\0';
	for(int i=name.size();i<MAXSTRINGSIZE;i++){
		outFile.write(&temp,1);
	}
	//Write Raw Data
	outFile.write((char *) &rawData,RAWDATASIZE);
};

void indexFile::read(std::string inFileName = "saveindex"){
	std::fstream inFile;
	unsigned int numberOfSaves = 0;
	
	//Open the file (if it doesn't exist, complain and exit)
	inFile.open(inFileName,std::ios::in|std::ios::binary);
	if(!inFile.is_open()){
		std::cerr << "ERROR:  Unable to open file  \"" << inFileName << "\"" << std::endl;
		exit(1);
	}
	//The first byte is the number of save indeces
	inFile.read((char *) &numberOfSaves,4);
	std::cout << "There are " << numberOfSaves - 1 << " save files, and 1 USER file."<<std::endl;
	data.reserve(numberOfSaves);
	
	//Read in all the save index data
	for(unsigned int i=0;i<numberOfSaves;i++){
		saveIndex temp;
		temp.read(inFile);
		data.push_back(temp);
		std::cout << "    Name: " << data[i].name << std::endl;
	}
	
	inFile.close();
};

void indexFile::write(std::string outFileName = "saveindex.new"){
	std::fstream outFile;
	unsigned int numberOfSaves = data.size();
	//Make sure that at least user data exists
	assert(IndexByName(data,"USER") != data.end());
	
	outFile.open(outFileName,std::ios::out|std::ios::binary);
	outFile.write((char *) &numberOfSaves,4);
	
	//Write out all the save index data
	for(unsigned int i=0;i<numberOfSaves;i++){
		data[i].write(outFile);
	}
	
	outFile.close();
};

//Returns the first index with a given name
//If more than one index has the same name, then this only returns the first one
//WARNING:  This just up and asserts when it can't find it (BAD JUJU)
std::vector<saveIndex>::iterator IndexByName(std::vector<saveIndex> & indexes,const std::string & findName){
	auto pred = [findName](const saveIndex& index){
		return (index.name.compare(findName) == 0);
	};
	auto foundIndex = find_if(indexes.begin(),indexes.end(),pred);
	assert(foundIndex != indexes.end());
	return foundIndex;
}
