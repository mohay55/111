#include "pch.h"
#include "rock.h"
#include <engine.h>
#include <vector> // Include this if it's not already in "rock.h" or "pch.h"

engine::rock::rock(std::vector<glm::vec3> vertices) : m_vertices(vertices)
{
    // Calculate normals for each face of the cube
    std::vector<glm::vec3> normals;

    // Assuming the vertices are ordered in such a way that the first four are the front face,
    // the next four are the back face, and so on, in counter-clockwise order.
    // Front face normal
    normals.push_back(glm::cross(vertices.at(1) - vertices.at(0), vertices.at(2) - vertices.at(0)));
    // Back face normal
    normals.push_back(glm::cross(vertices.at(5) - vertices.at(4), vertices.at(6) - vertices.at(4)));
    // Left face normal
    normals.push_back(glm::cross(vertices.at(0) - vertices.at(4), vertices.at(7) - vertices.at(4)));
    // Right face normal
    normals.push_back(glm::cross(vertices.at(3) - vertices.at(2), vertices.at(6) - vertices.at(2)));
    // Top face normal
    normals.push_back(glm::cross(vertices.at(2) - vertices.at(3), vertices.at(7) - vertices.at(3)));
    // Bottom face normal
    normals.push_back(glm::cross(vertices.at(1) - vertices.at(0), vertices.at(4) - vertices.at(0)));

    // Normalize the normals
    for (auto& normal : normals) {
        normal = glm::normalize(normal);
    }

    // Define vertices for the cube, with positions, normals, and texture coordinates
    std::vector<mesh::vertex> rock_vertices
        {
        // Front face
        { glm::vec3(-0.5f, -0.5f,  0.5f), normals.at(0), glm::vec2(0.f, 0.f) },
        { glm::vec3(0.5f, -0.5f,  0.5f), normals.at(0), glm::vec2(1.f, 0.f) },
        { glm::vec3(0.5f,  0.5f,  0.5f), normals.at(0), glm::vec2(1.f, 1.f) },
        { glm::vec3(-0.5f,  0.5f,  0.5f), normals.at(0), glm::vec2(0.f, 1.f) },

        // Back face
        { glm::vec3(-0.5f, -0.5f, -0.5f), normals.at(1), glm::vec2(1.f, 0.f) },
        { glm::vec3(-0.5f,  0.5f, -0.5f), normals.at(1), glm::vec2(1.f, 1.f) },
        { glm::vec3(0.5f,  0.5f, -0.5f), normals.at(1), glm::vec2(0.f, 1.f) },
        { glm::vec3(0.5f, -0.5f, -0.5f), normals.at(1), glm::vec2(0.f, 0.f) },

        // Left face
        { glm::vec3(-0.5f, -0.5f, -0.5f), normals.at(2), glm::vec2(0.f, 0.f) },
        { glm::vec3(-0.5f, -0.5f,  0.5f), normals.at(2), glm::vec2(1.f, 0.f) },
        { glm::vec3(-0.5f,  0.5f,  0.5f), normals.at(2), glm::vec2(1.f, 1.f) },
        { glm::vec3(-0.5f,  0.5f, -0.5f), normals.at(2), glm::vec2(0.f, 1.f) },

        // Right face
        { glm::vec3(0.5f, -0.5f,  0.5f), normals.at(3), glm::vec2(0.f, 0.f) },
        { glm::vec3(0.5f, -0.5f, -0.5f), normals.at(3), glm::vec2(1.f, 0.f) },
        { glm::vec3(0.5f,  0.5f, -0.5f), normals.at(3), glm::vec2(1.f, 1.f) },
        { glm::vec3(0.5f,  0.5f,  0.5f), normals.at(3), glm::vec2(0.f, 1.f) },

        // Top face
        { glm::vec3(-0.5f,  0.5f,  0.5f), normals.at(4), glm::vec2(0.f, 1.f) },
        { glm::vec3(0.5f,  0.5f,  0.5f), normals.at(4), glm::vec2(1.f, 1.f) },
        { glm::vec3(0.5f,  0.5f, -0.5f), normals.at(4), glm::vec2(1.f, 0.f) },
        { glm::vec3(-0.5f,  0.5f, -0.5f), normals.at(4), glm::vec2(0.f, 0.f) },

        // Bottom face
        { glm::vec3(-0.5f, -0.5f, -0.5f), normals.at(5), glm::vec2(0.f, 0.f) },
        { glm::vec3(0.5f, -0.5f, -0.5f), normals.at(5), glm::vec2(1.f, 0.f) },
        { glm::vec3(0.5f, -0.5f,  0.5f), normals.at(5), glm::vec2(1.f, 1.f) },
        { glm::vec3(-0.5f, -0.5f,  0.5f), normals.at(5), glm::vec2(0.f, 1.f) },
    };

    // Define indices for the cube (6 faces, each with 2 triangles)
    const std::vector<uint32_t> rock_indices
    {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 13, 14, 14, 15, 12,
        // Top face
        16, 17, 18, 18, 19, 16,
        // Bottom face
        20, 21, 22, 22, 23, 20
    };

    // Create the mesh
    m_mesh = engine::mesh::create(rock_vertices, rock_indices);
}

engine::rock::~rock() {}

engine::ref<engine::rock> engine::rock::create(std::vector<glm::vec3> vertices)
{
    return std::make_shared<engine::rock>(vertices);
}
