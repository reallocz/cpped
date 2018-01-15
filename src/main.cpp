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
    Renderer r;
    Window w;
    Input input(w, onKey);

//###
    Shader s;
    unsigned int VAO, VBO, EBO;
    float vertices[] = {
        0, 0, 0,
        0.5, 0, 0,
        0.5, 0.5, 0,
    };
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    s.use();
    glBindVertexArray(VAO);




//####    


    while(w.running())
    {
        input.poll();
        w.clear();

        glDrawArrays(GL_TRIANGLES, 0, 3);
        //r.renderdoc(w.getCanvas(), doc);

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

