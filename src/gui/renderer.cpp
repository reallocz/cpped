#include "gui/renderer.h"

    const float vertices[] = {
        0, 0, 0, 0, 1,
        1, 0, 0, 1, 1,
        1, 1, 0, 1, 0,

        //0, 0, 0, 0, 1,
        0, 1, 0, 0, 0,
        //1, 1, 0, 1, 0,
    };

    const int indices[] = {
        0, 1, 2,
        0, 3, 2
    };

Renderer::Renderer() 
{
    std::cout << "init renderer!" << std::endl;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    // Textuer
    const Bitmap& bm = _font.getGlyph('B').bitmap;
    glGenTextures(1, &tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //????
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bm.width(), bm.rows(), 0, GL_RED, GL_UNSIGNED_BYTE, bm.buffer());
    glGenerateMipmap(GL_TEXTURE_2D);

    s.use();
    glBindVertexArray(VAO);

}


Renderer::~Renderer()
{
}


// Draws the document to canvas
void Renderer::renderdoc(Canvas& canvas, Document& d)
{
    unsigned int numlines = d.numlines();
    renderLine(canvas, d[0]);

#if 0
    for(unsigned int i = 0; i < numlines; ++i)
    {
        const Line& line = d[i];
        if(!line.isempty())
        {
            renderLine(canvas, line);
        }
    }
#endif

}


void Renderer::renderLine(Canvas& canvas, const Line& line)
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

