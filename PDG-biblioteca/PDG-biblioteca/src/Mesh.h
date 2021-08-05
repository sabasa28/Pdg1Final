#pragma once
#include "Exports.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "Renderer.h"

#include <iostream>
#include <string>
#include <vector>

using namespace glm;
using namespace std;

struct Vertex {
    vec3 Position;
    vec2 TexCoords;
    vec3 Normal;
    vec3 Tangent;
    vec3 Bitangent;
};

struct meshTexture {
    unsigned int id;
    string type;
    string path;
};

class SABASAENGINE_API Mesh
{
public:
    vector<Vertex> _vertices;
    vector<unsigned int> _indices;
    vector<meshTexture> _textures;
    unsigned int vao;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<meshTexture> textures, bool usesSpecularMaps, Renderer* rend);
    void Draw();
private:
	bool _usesSpecularMaps;
    unsigned int vbo;
    unsigned int ebo;
    Renderer* _rend;
	void setupMesh();
};

