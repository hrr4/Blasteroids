#include "star.h"

Star::Star() {
    Position.x() = static_cast<float>(rand() % Window::Get_Surf()->w); 
    Position.y() = static_cast<float>(rand() % Window::Get_Surf()->h); 
    a = static_cast<float>((rand() % 100) / 100);
}
