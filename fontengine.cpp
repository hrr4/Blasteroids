#include "fontengine.h"

FontEngine::FontEngine() {
    fIt = fontMap.begin();
}

FontEngine::FontEngine(const std::string filename) {
    fIt = fontMap.begin();
    AddFont(filename);
}

FontEngine::~FontEngine() {
    delete Font;
}

void FontEngine::AddFont(const std::string filename) {
    std::string text;
    fIt = fontMap.begin();
    text = filename.substr(0, filename.find_last_of("."));
    fontMap.insert(fIt, std::pair<std::string, FTFont* >(text, new FTTextureFont(filename.c_str())));
}

// Gotta make into some sort of object thing or something i dunno
// Gotta be able to manipulate this shit
/*FontEngine**/void FontEngine::Draw(const std::string text, int size, const std::string ident, float X, float Y, float Z) {
    point.X(X);
    point.Y(Y);
    if (Z != 0)
        point.Z(Z);
    //if (currentFont != ident) {
        for (fIt = fontMap.begin(); fIt != fontMap.end(); ++fIt) {
            if (fIt->first == ident) {
                (*fIt).second->FaceSize(size);
                (*fIt).second->Render(text.c_str(),text.size(), point);
                currentFont = (*fIt).first;
                //return *fIt;
            }
        }
    /*} else {
        (*fIt).second->FaceSize(size);
        (*fIt).second->Render(text.c_str(),text.size(), point);
    }*/
}
/*
void FontEngine::Move(float X, float Y, float Z) {
    point.X(X);
    point.Y(Y);
}
*/

void FontEngine::SetFace(int size) {
    Font->FaceSize(size);
}

/*
void FontEngine::SetFont(const std::string filename, unsigned int size) {
    Font = new FTBitmapFont(filename.c_str());
    Font->FaceSize(size);
}
*/
