#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/lab_camera.h"

#define TREE_COUNT 50

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        Mesh* Tema2::CreateTrack();
        Mesh* Tema2::CreateField();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void Tema2::RenderMeshCustom(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix,
            implemented::CustomCamera *camera, glm::mat4 projectionMatrix);

        void RenderScene(implemented::CustomCamera* camera, glm::mat4 projectionMatrix);

     protected:
        implemented::CustomCamera* camera;
        implemented::CustomCamera* camera_map;
        glm::mat4 projectionMatrix;
        glm::mat4 projectionMatrix2;

        GLfloat fov = 60;
        int projection = 0;

        GLfloat bottom = -20;
        GLfloat right = 20;
        GLfloat left = -20;
        GLfloat top = 20;

        float z_near = 0.1;
        float z_far = 200;

        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        GLenum polygonMode;
        ViewportArea miniViewportArea;
        float angle;

        glm::vec3 car_coords;
        glm::vec3 camera_coords;
        glm::vec3 camera_center;
        glm::mat4 viewMap;

        glm::vec3 tree_pos[TREE_COUNT];
        std::vector<VertexFormat> middle;
        std::vector<VertexFormat> vertices;

        std::unordered_map<std::string, Texture2D*> mapTextures;

        bool hit = false;

        float enemy_x = 0, enemy_y = 0, enemy_z = 0;
    };
}   // namespace m1
