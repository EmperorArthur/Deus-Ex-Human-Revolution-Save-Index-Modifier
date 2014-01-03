//This operates on the DeusEx Human Revolution saveindex file
//To Run:
//	indexer filename
//Copyright Arthur Moore 2013 GPL V3

//Fun header files
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
//#include <cmath>
//#include <iomanip>

//Can't forget this
using namespace std;

void StringRead(fstream& inFile,string& aString){
	char readChar = '0';
	aString.clear();
	//This reads untill a null charachter is read in.
	while(readChar != '\0'){
		inFile.read(&readChar,1);
		aString.append(1,readChar);
		assert(inFile.good());
	}
}
void StringWrite(fstream& outFile,string& aString){
	char temp = '\0';
	for(int i=0; i< aString.size();i++){
		temp = aString[i];
		outFile.write(&temp,1);
	}
	//Not needed, but it shouldn't hurt
	// if(temp != '\0'){
		// temp = '\0';
		// outFile.write(&temp,1);
	// }
};

struct saveIndex{
	public:
		//Total index size is 53 bytes
		static const int TOTALSIZE = 53;
		string name;
		int rawDataSize;
		char rawData[TOTALSIZE];
		void read(fstream& inFile);
		void write(fstream& outFile);
};
void saveIndex::read(fstream& inFile){
	StringRead(inFile,name);
	rawDataSize=TOTALSIZE-name.size();
	inFile.read((char *) &rawData,rawDataSize);
};
void saveIndex::write(fstream& outFile){
	StringWrite(outFile,name);
	outFile.write((char *) &rawData,rawDataSize);
};

//And now the main function
int main(int argc, char *argv[]){
	fstream myFile;		//The file to work with
	fstream outFile;	//Temporary output file (Using a write temp,delete original, copy temp->original,delete temp approach)
	int numberOfSaves;
	
	//Make sure the filename is given
	if(argc < 2){
		cerr << "ERROR:  No file name given" << endl;
		cerr << "Usage:" << endl;
		cerr << "	" << argv[0] << " " << "filename" << endl;
		return 1;
	}
	
	//Open the file (if it doesn't exist, complain and exit
	myFile.open(argv[1],ios::in|ios::binary);
	if(!myFile.is_open()){
		cerr << "ERROR:  Unable to open file  \"" << argv[1] << "\"" << endl;
		return 2;
	}
	
	//The first byte is the number of save indeces
	myFile.seekg(ios_base::beg);
	myFile.read((char *) &numberOfSaves,4);
	numberOfSaves = numberOfSaves;
	cout << "There are " << numberOfSaves << " save files."<<endl;
	//Read in all the save index data
	saveIndex * allIndeces = new saveIndex[numberOfSaves];
	for(int i=0;i<(int) numberOfSaves;i++){
		cout << "Reading:  " << i << endl;
		allIndeces[i].read(myFile);
		cout << allIndeces[i].name << endl;
	}
	myFile.close();
	
	//This just leaves me with the user data 2 autosaves and the last manual save
	int newNumberOfSaves = 4;
	
	//Open the output file
	outFile.open("tempSaveIndex",ios::out|ios::binary);
	outFile.seekg(ios_base::beg);
	outFile.write((char *) &newNumberOfSaves,4);
	//0 is the user data file
	allIndeces[0].write(outFile);
	allIndeces[1].write(outFile);
	allIndeces[2].write(outFile);
	allIndeces[numberOfSaves-1].write(outFile);
	outFile.close();
	
	delete[] allIndeces;
	return 0;
}
