#include <iostream>
#include "gui/window.h"
#include "gui/renderer.h"
#include "core/document.h"

void onKey(const char* key);

Document d;

int main() {
    std::cout << "Hello, Editor!" << std::endl;
    Input i(onKey);
    Renderer r;
    Window w(400, 700, "New File", i);

    while(w.running())
    {
        w.clear();

        r.render(w.getCanvas(), d);

        w.update();

        w.poll();
    }

    return 0;
}


void onKey(const char* key) {
    std::cout << key << std::endl;
    d.insert('a'); 
    std::cout << d;
}
