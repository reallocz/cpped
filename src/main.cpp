#include <iostream>
#include "gui/window.h"
#include "gui/renderer.h"

int main() {
    std::cout << "Hello, Editor!" << std::endl;
    Window w;
    Renderer r(w.renderer(), 400, 400);

    while(w.running())
    {
        w.clear();
        r.render("Yolo");
        w.update();
        w.poll();
    }

    return 0;
}
