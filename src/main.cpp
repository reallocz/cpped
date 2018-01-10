#include <iostream>
#include "gui/window.h"
#include "gui/renderer.h"
#include "core/document.h"
#include "core/input.h"
#include "core/doccmd.h"

void onKey(Key key);

Document doc;

int main() {
    Renderer r;
    Window w;
    Input input(w, onKey);

    while(w.running())
    {
        input.poll();
        w.clear();

        r.renderdoc(w.getCanvas(), doc);

        w.update();
    }

    return 0;
}


void onKey(Key key) {
    if(key.type == Keytype::Insert)
    {
        Doccmd cmd {
            Doccmd::Type::Insertchar,
            Doccmd::Insertchar {key.c}
        };
        doc.exec(cmd);
    }
}
