#ifndef INDEXFILE_H
#define INDEXFILE_H

#include <string>
#include <vector>

struct saveIndex{
	public:
		void read(std::fstream& inFile);
		void write(std::fstream& outFile);
		static const int TOTALSIZE = 53;		//Total index size is 53 bytes
		static const int MAXSTRINGSIZE = 33;	//Maximum size of a string
		static const int RAWDATASIZE = 20;		//Size of the raw data section
		std::string name;						//The Save Filename
		char rawData[RAWDATASIZE];				//The raw data section (aka things I haven't decoded yet)
};

class indexFile{
	public:
		void read(std::string inFileName);
		void write(std::string outFileName);
		int size();									//How many saves are in the index file
		int findIndex(std::string findName);		//Find an index with a certain name
		void append(saveIndex & anIndex);			//Append an index to the end of the file
		saveIndex & operator[](int i);
	private:
		std::vector<saveIndex> allIndeces;
		
};


#endif //INDEXFILE_H