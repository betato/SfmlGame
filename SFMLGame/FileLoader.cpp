#include "FileLoader.h"

#include <iostream>
#include <fstream>

namespace FileIO
{
	bool readText(vector<string>& file, string path)
	{
		string line;
		ifstream fileStream(path);
		if (fileStream.is_open())
		{
			while (getline(fileStream, line))
			{
				file.push_back(line);
			}
			fileStream.close();
			return true;
		}
		return false;
	}
}
