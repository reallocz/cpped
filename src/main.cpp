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
        0, 0, 0, 0, 1,
        1, 0, 0, 1, 1,
        1, 1, 0, 1, 0,

        0, 0, 0, 0, 1,
        0, 1, 0, 0, 0,
        1, 1, 0, 1, 0,
    };
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    Font f;

    const Bitmap& bm = f.getGlyph('B').bitmap;
    bm.print();

    unsigned int tex;
    glGenTextures(1, &tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //????
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bm.width(), bm.rows(), 0, GL_RED, GL_UNSIGNED_BYTE, bm.buffer());
    glGenerateMipmap(GL_TEXTURE_2D);

    s.use();
    glBindVertexArray(VAO);


//####    


    while(w.running())
    {
        input.poll();
        w.clear();

        glDrawArrays(GL_TRIANGLES, 0, 6);
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

