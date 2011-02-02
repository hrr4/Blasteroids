#ifndef FONTENGINE_H
#define FONTENGINE_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <FTGL/ftgl.h>
#include <string>
#include <map>

class FontEngine {
public:
    FontEngine();
    FontEngine(const std::string& filename);
    ~FontEngine();
    void Draw(const std::string& text, int size, const std::string& ident, float X, float Y, float Z=0);
    void AddFont(const std::string& filename);
    void RemoveFont(const std::string& filename);
    FTBBox GetBBox(const std::string& _text, const std::string& _filename);
private:
    FTPoint point;
    FTFont* Font;
    std::map<std::string, FTFont*> fontMap;
    std::map<std::string, FTFont*>::const_iterator fIt;
};

#endif
