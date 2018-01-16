#include <iostream>
#include "gui/window.h"
#include "gui/renderer.h"
#include "core/document.h"
#include "core/input.h"
#include "core/doccmd.h"

#include "gui/shader.h"


void onKey(Key key);

Document doc;

int main() {
    Window w;
    Renderer r; // Created only after window!
    Input input(w, onKey);

    while(w.running())
    {
        input.poll();
        w.clear();

        //glDrawArrays(GL_TRIANGLES, 0, 6);
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

