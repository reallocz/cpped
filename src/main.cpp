#include <iostream>
#include "gui/window.h"
#include "gui/renderer.h"
#include "core/document.h"
#include "core/input.h"

void onKey(Key key);

Document d;

int main() {
    std::cout << "Hello, Editor!" << std::endl;
    Renderer r;
    Window w;
    Input input(w, onKey);

    while(w.running())
    {
        input.poll();
        w.clear();

        r.render(w.getCanvas(), d);

        w.update();

    }

    return 0;
}


void onKey(Key key) {
    if(key.type == Keytype::Insert)
    {
        d.insert(key.c);
    }
}
