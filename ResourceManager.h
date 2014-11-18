
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"

/**
  * class ResourceManager
  * 
  */



class ResourceManager
{

public:
  virtual ~ResourceManager ( );


  //for preloading everything at once
  bool LoadAssetFile(std::string File );


  sf::Texture * GetTexture(std::string filename );

  sf::Font * GetFont(std::string filename);

  

  //Delete EVERYTHING
  void Clear();

  static  ResourceManager * GetInstance();

  void setTheme(std::string str);
  void themefy(std::string &path);

private:
	//this strange thing is an std map, allows us to get the textures from the filename string
	std::map<std::string, sf::Texture> TextureMap;

	//this strange thing is an std map, allows us to get the textures from the filename string
	std::map<std::string, sf::Font> FontMap;


	//private constructor, we want no one to create it but itself
	ResourceManager();

	static ResourceManager * Instance ;

	std::string theme;
};

#endif // RESOURCEMANAGER_H
