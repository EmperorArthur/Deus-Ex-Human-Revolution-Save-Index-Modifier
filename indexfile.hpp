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

//Returns the first index with a given name
//If more than one index has the same name, then this only returns the first one
//WARNING:  This just up and asserts when it can't find it (BAD JUJU)
std::vector<saveIndex>::iterator IndexByName(std::vector<saveIndex> & indexes,const std::string & findName);

class indexFile{
	public:
		void read(std::string inFileName);
		void write(std::string outFileName);
		std::vector<saveIndex> data;
		
};




#endif //INDEXFILE_H