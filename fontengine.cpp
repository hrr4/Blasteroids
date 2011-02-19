#include "fontengine.h"

FontEngine::FontEngine() {}

FontEngine::FontEngine(const std::string& filename) {
    fIt = fontMap.begin();
    AddFont(filename);
}

FontEngine::~FontEngine() {}

void FontEngine::AddFont(const std::string& filename) {
    std::string text = filename.substr(0, filename.find_last_of("."));
    fontMap.insert(std::make_pair(text, new FTTextureFont(filename.c_str())));
}

void FontEngine::RemoveFont(const std::string& filename) {
    fontMap.erase(filename.c_str());
}

void FontEngine::Draw(const std::string& text, int size, const std::string& ident, float X, float Y, float Z) {
glPushMatrix();    glScalef(1, -1, 1);

    point.X(X);
    point.Y(-Y);
    if (Z != 0) 
        point.Z(Z);
    if (fontMap.find(ident) != fontMap.end()) {
      fontMap[ident]->FaceSize(size);
      fontMap[ident]->Render(text.c_str(),text.size(), point);
    }
glPopMatrix();
}

FTBBox FontEngine::GetBBox(const std::string& _text, const std::string& _filename) {
  FTBBox tempBox;
    std::string filename;
    /*if (_filename.find_first_of(".")) {
        filename = filename.substr(0, _filename.find_last_of("."));
    } else {*/
        filename = _filename;
    //}
        // PROBLEM WITH BBOX
        // NEED TO INPUT SIZE OR POSITION OR SOMETHING.... WILL FIND MORE LATAR
    for (fIt = fontMap.begin(); fIt != fontMap.end(); ++fIt) {
        if (fIt->first == filename) {
            return (*fIt).second->BBox(_text.c_str());
        }
    }
    return tempBox;
}