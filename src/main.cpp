#include <iostream>
#include "gui/window.h"
#include "gui/renderer.h"
#include "core/document.h"

void onKey(const char* key);

int main() {
    std::cout << "Hello, Editor!" << std::endl;
    Input i(onKey);
    Window w(400, 700, "New File", i);
    Renderer r(w.renderer(), 400, 400);
    Document d;

    while(w.running())
    {
        w.clear();
        r.render("Yolo");
        w.update();
        w.poll();
    }

    return 0;
}


void onKey(const char* key) {
    std::cout << key << std::endl;
}
