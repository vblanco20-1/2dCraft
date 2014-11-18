#include <iostream>
#include "ResourceManager.h"

// Constructors/Destructors
//  

ResourceManager::ResourceManager ( ) {
	theme = "default";
}

ResourceManager::~ResourceManager() { Clear(); }

bool ResourceManager::LoadAssetFile(std::string File)
{
	themefy(File);
	return false;
}

sf::Texture* ResourceManager::GetTexture(std::string filename)
{
	
	themefy(filename);
	if (TextureMap.find(filename) == TextureMap.end())
	{
		// texture not found in the map, create a new one

		sf::Texture  newTex;// = new sf::Texture();
		if ( newTex.loadFromFile(filename) )
		{
			TextureMap[filename] = newTex;

			return &TextureMap[filename];
		}
		else
		{
			std::cout << "Error!!! Couldn't load texture: " << filename << std::endl;
		}


	}
	else
	{
		return &TextureMap[filename];
	}

	return nullptr;
}
sf::Font * ResourceManager::GetFont(std::string filename)
{
	themefy(filename);
	if (FontMap.find(filename) == FontMap.end())
	{
		// texture not found in the map, create a new one

		sf::Font  newFont;// = new sf::Font();

		if (newFont.loadFromFile(filename))
		{
			FontMap[filename] = newFont;

			return &FontMap[filename];
		}
		else
		{
			//error
		}
	}
	else
	{
		return &FontMap[filename];
	}
	return nullptr;
}





ResourceManager * ResourceManager::Instance = nullptr;

ResourceManager * ResourceManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new ResourceManager();
	}

	return Instance;	
}

void ResourceManager::Clear()
{
	//for (auto pair : TextureMap)
	//{
	//	//delete the texture
	//	delete pair.second;
	//}
	//for (auto pair : FontMap)
	//{
	//	//delete the texture
	//	delete pair.second;
	//}

	FontMap.clear();
	TextureMap.clear();
}


void ResourceManager::setTheme(std::string str) {
	theme = str;
}



void ResourceManager::themefy(std::string &path) {
	size_t pos = 0;
	std::string search = "$THEME";
    while ((pos = path.find(search, pos)) != std::string::npos) {
         path.replace(pos, search.length(), theme);
         pos += theme.length();
    }
}