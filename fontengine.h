#ifndef FONTENGINE_H
#define FONTENGINE_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <FTGL\ftgl.h>
#include <string>
#include <map>
#include <memory>

class FontEngine {
public:
    FontEngine();
    FontEngine(const std::string& filename);
    ~FontEngine();
    /*FontEngine**/void Draw(const std::string& text, int size, const std::string& ident, float X, float Y, float Z=0);
    void SetFace(int size);
    void AddFont(const std::string& filename);
    //void SetFont(const std::string filename, unsigned int size=24);
    //void Move(float X, float Y, float Z=0);
   
private:
    FTPoint point;
    //std::shared_ptr<FTFont> Font;
    FTFont* Font;
    std::string currentFont;
    /*std::map<std::string, std::shared_ptr<FTFont> > fontMap;
    std::map<std::string, std::shared_ptr<FTFont> >::const_iterator fIt;*/
    std::map<std::string, FTFont*> fontMap;
    std::map<std::string, FTFont*>::const_iterator fIt;
};

#endif