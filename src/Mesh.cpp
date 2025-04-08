#include <Mesh.hpp>

Mesh::Mesh()
{
}

void Mesh::load(std::vector<float> vertices, std::vector<float> attributeSlices, const std::vector<unsigned int> indices)
{
    initBuffers();
    loadVertices(vertices);
    unsigned int numAttributes = loadAttributes(attributeSlices);
    numOfPoints = vertices.size() / numAttributes;
    if (indices.size() > 0)
    {
        loadIndices(indices);
    }    
}

int Mesh::loadTexture(unsigned int textureID)
{
    if (textureID != 0)
    {
        textureIDs.push_back(textureID);
        return textureIDs.size() - 1;
    }
    return -1;
}

void Mesh::initBuffers(void)
{   
    // Vertex buffer
    if (vboID == 0)
    {
        glGenBuffers(1, &vboID);
    }

    // Vertex attributes buffer
    if (vaoID == 0)
    {
        glGenVertexArrays(1, &vaoID);
    }

    // Texture properties
    if (textureIDs.size() == 0)
    {
        // Set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

void Mesh::loadVertices(std::vector<float> vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
}

unsigned int Mesh::loadAttributes(const std::vector<float> attributeSlices)
{
    glBindVertexArray(vaoID);
    unsigned int totalCount = 0;
    for (int i = 0; i < attributeSlices.size(); ++i)
    {
        totalCount += attributeSlices[i];
    }

    unsigned int start = 0;
    for (int i = 0; i < attributeSlices.size(); ++i)
    {
        if (i > 0)
        {
            start += attributeSlices[i - 1] * sizeof(float);
        }
        glVertexAttribPointer(i, attributeSlices[i],
                              GL_FLOAT,
                              GL_FALSE,
                              totalCount * sizeof(float),
                              (void*) start);
        glEnableVertexAttribArray(i);
    }
    return totalCount;
}

void Mesh::loadIndices(const std::vector<unsigned int> indices)
{
    // Element buffer
    if (eboID == 0)
    {
        glGenBuffers(1, &eboID);
    }
    
    if (vboID != 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        numOfPoints = indices.size();
    }
    else
    {
        LOG_ERROR("Trying to initialize element buffer without vertices\n");
    }
}

void Mesh::render(void)
{
    if (vboID != 0 || vaoID != 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBindVertexArray(vaoID);
        
        for (int i = 0; i < textureIDs.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
        }

        if (eboID != 0)
        {
            glDrawElements(GL_TRIANGLES, numOfPoints, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, numOfPoints);
        }
    }
    else
    {
        LOG_WARNING("Mesh not loaded\n");
    }
}
