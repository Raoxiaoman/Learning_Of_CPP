#include <iostream>
using namespace std;
class Screen{
    public:
        Screen &home(){cout << "home" << endl;return *this;};
        Screen &up(){cout << "up" << endl;return *this;};
        Screen &down(){cout << "down" << endl;return *this;};
        Screen &left(){cout << "left" << endl;return *this;};
        Screen &right(){cout << "right" << endl;return *this;};
        using Action = Screen &(Screen::*)();
        enum Directions {HOME,UP,DOWN,LEFT,RIGHT};
        Screen &move(Directions);
    private:
        static Action Menu[];
};

Screen::Action Screen::Menu[] = {
    &Screen::home,&Screen::up,&Screen::down,&Screen::left,&Screen::right
};


Screen& Screen::move(Directions d){
    return (this->*Menu[d])();
}


int main(){
    Screen myScreen;
    myScreen.move(Screen::HOME);
    myScreen.move(Screen::UP);
    myScreen.move(Screen::DOWN);
    myScreen.move(Screen::LEFT);
    myScreen.move(Screen::RIGHT);
    return 0;
}
