#ifndef INDEXFILE_H
#define INDEXFILE_H

#include <fstream>
#include <string>

void StringRead(std::fstream& inFile,std::string& aString);
void StringWrite(std::fstream& outFile,std::string& aString);

struct saveIndex{
	public:
		//Total index size is 53 bytes
		static const int TOTALSIZE = 53;
		//Maximum size of a string
		static const int MAXSTRINGSIZE = 33;
		//Size of the raw data section (aka things I haven't decoded yet)
		static const int RAWDATASIZE = 20;
		//The Filename
		std::string name;
		char rawData[RAWDATASIZE];
		void read(std::fstream& inFile);
		void write(std::fstream& outFile);
};

class indexFile{
	public:
		~indexFile();
		void read(std::string inFileName);
		void write(std::string outFileName);
		int size();								//How many saves are in the index file
		int findIndex(std::string findName);				//Find an index with a certain name
		saveIndex & operator[](int i);
	private:
		int numberOfSaves;
		saveIndex * allIndeces;
		
};


#endif //INDEXFILE_H