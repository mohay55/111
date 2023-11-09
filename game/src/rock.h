#pragma once

namespace engine
{
    class mesh;

    class rock
    {
    public:
        rock(std::vector<glm::vec3> vertices);
        ~rock();

        std::vector<glm::vec3> vertices() const { return m_vertices; }
        ref<engine::mesh> mesh() const { return m_mesh; }

        static ref<rock> create(std::vector<glm::vec3> vertices);

    private:
        std::vector<glm::vec3> m_vertices;
        ref<engine::mesh> m_mesh;
    };
}
