#include <functional>

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>
#include <smk/Input.hpp>

class Button {
private:
    int x;
    int y;
    int width;
    int height;
    smk::Window *window;
    smk::Transformable button;
public:
    Button(int, int, int, int, smk::Window&);
    void setX(int);
    void setY(int);
    int getX();
    int getY();
    smk::Transformable &getButton();
    bool click();
    bool hover();
    void onClick(std::function<void()>);
    void onHover(std::function<void()>);
};