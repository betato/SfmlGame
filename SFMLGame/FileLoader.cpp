#include "FileLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace FileIO
{
	bool readText(vector<string>& text, string path)
	{
		string line;
		ifstream inputStream(path);
		if (inputStream.is_open())
		{
			while (getline(inputStream, line))
			{
				text.push_back(line);
			}
			inputStream.close();
			return true;
		}
		return false;
	}

	void writeText(vector<string> text, string path)
	{
		ofstream outputStream(path);
		for (auto it = text.begin(); it != text.end(); it++)
		{
			outputStream << *it << std::endl; // File ends with newline
		}
		outputStream.close();
	}
	
	bool readEntity(sf::VertexArray& vertices, sf::Vector2u textureSize, string path)
	{
		std::vector<std::string> fileText;
		if (!FileIO::readText(fileText, path))
		{
			return false;
		}

		vertices.clear();

		int i = 0;
		vector<string>::iterator it;
		for (it = fileText.begin(); it < fileText.end(); it++)
		{
			char begin = it->at(0);
			std::string str = it->erase(0, 1);
			istringstream iss(str);

			float x, y;
			char sep;
			iss >> x;
			iss >> sep;
			iss >> y;
			if (begin == 'v')
			{
				// Vertex
				vertices.append(sf::Vector2f(x, y));
			}
			else if (begin == 't')
			{
				// Texture
				vertices[i].texCoords = sf::Vector2f(x * textureSize.x, y * textureSize.y);
				i++;
			}
		}

		return true;
	}

	bool readPhysics(b2PolygonShape& shape, string path)
	{
		std::vector<std::string> fileText;
		if (!FileIO::readText(fileText, path))
		{
			return false;
		}

		vector<string>::iterator it;
		std::vector<b2Vec2> vertices;
		for (it = fileText.begin(); it < fileText.end(); it++)
		{
			istringstream iss(*it);

			float x, y;
			char sep;
			iss >> x;
			iss >> sep;
			iss >> y;
			vertices.push_back(b2Vec2(x, y));
		}
		// Set vertices to the vector array
		shape.Set(&vertices[0], vertices.size());
		return true;
	}

	void writeEntity(sf::VertexArray vertices, sf::Vector2u textureSize, string path)
	{
		std::vector<std::string> fileText;
		// Verticies
		for (int i = 0; i < vertices.getVertexCount(); i++)
		{
			sf::Vector2f pos = vertices[i].position;
			fileText.push_back("v" + std::to_string(pos.x) + "," + std::to_string(pos.y));
		}
		// Texture
		for (int i = 0; i < vertices.getVertexCount(); i++)
		{
			sf::Vector2f tex = vertices[i].texCoords;
			fileText.push_back("t" + std::to_string(tex.x / textureSize.x) + "," + std::to_string(tex.y / textureSize.y));
		}
		writeText(fileText, path);
	}

	void writePhysics(sf::VertexArray shape, string path)
	{
		std::vector<std::string> fileText;
		int verticies = shape.getVertexCount();
		for (unsigned int i = 0; i < verticies; i++)
		{
			sf::Vector2f vertex = shape[i].position;
			fileText.push_back(std::to_string(vertex.x) + ',' + std::to_string(vertex.y));
		}
		writeText(fileText, path);
	}
}
