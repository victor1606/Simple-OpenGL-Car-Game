#include "lab_m1/tema2/tema2.h"
#include "lab_m1/tema2/lab_camera.h"

#include <vector>
#include <string>
#include <iostream>
#include <time.h>

#include "lab_m1/tema2/transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

void Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // TODO(student): Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    // TODO(student): Create the VBO and bind it
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // TODO(student): Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    // TODO(student): Create the IBO and bind it
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // TODO(student): Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO(student): Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}

Mesh* Tema2::CreateTrack()
{
    glm::vec3 color = glm::vec3(50.f / 255, 50.f / 255, 50.f / 255);

    middle = {
        VertexFormat(glm::vec3(0.36, 0, 2.8), color), //
        VertexFormat(glm::vec3(0, 0, 5), color), //z1

        VertexFormat(glm::vec3(0, 0, 6), color),
        VertexFormat(glm::vec3(0, 0, 7), color),
        VertexFormat(glm::vec3(0, 0, 8), color),
        VertexFormat(glm::vec3(0, 0, 10), color),

        VertexFormat(glm::vec3(0, 0, 12), color), //c
        VertexFormat(glm::vec3(-0.5, 0, 13), color), //d
        VertexFormat(glm::vec3(-1.6, 0, 14.5), color), //e
        VertexFormat(glm::vec3(-3, 0, 15), color), //f
        VertexFormat(glm::vec3(-4.3, 0, 15.6), color), //g
        VertexFormat(glm::vec3(-6, 0, 16), color), //h
        VertexFormat(glm::vec3(-12, 0, 16), color), //i
        VertexFormat(glm::vec3(-13, 0, 15.7), color), //j
        VertexFormat(glm::vec3(-13.6, 0, 15.3), color), //k
        VertexFormat(glm::vec3(-14, 0, 14.8), color), //l
        VertexFormat(glm::vec3(-14.5, 0, 14), color), //m
        VertexFormat(glm::vec3(-15, 0, 11.5), color), //n
        VertexFormat(glm::vec3(-14.8, 0, 10), color), //o
        VertexFormat(glm::vec3(-14.5, 0, 9.2), color), //p
        VertexFormat(glm::vec3(-13.9, 0, 8.5), color), //q
        VertexFormat(glm::vec3(-12.7, 0, 8.1), color), //r
        VertexFormat(glm::vec3(-12, 0, 8), color), //s
        VertexFormat(glm::vec3(-11.2, 0, 8), color), //t
        VertexFormat(glm::vec3(-10, 0, 7.7), color), //u
        VertexFormat(glm::vec3(-9.5, 0, 7), color), //v
        VertexFormat(glm::vec3(-9.3, 0, 6.4), color), //w
        VertexFormat(glm::vec3(-9, 0, 5.7), color), //z
        VertexFormat(glm::vec3(-9, 0, 5), color), //a1

        VertexFormat(glm::vec3(-9, 0, 4), color),
        VertexFormat(glm::vec3(-9, 0, 3), color),
        VertexFormat(glm::vec3(-9, 0, 2), color),

        VertexFormat(glm::vec3(-9, 0, 0), color), //b1

        VertexFormat(glm::vec3(-9, 0, -1), color),
        VertexFormat(glm::vec3(-9, 0, -2), color),
        VertexFormat(glm::vec3(-9, 0, -3), color),
        VertexFormat(glm::vec3(-9, 0, -4), color),
        VertexFormat(glm::vec3(-9, 0, -5), color),

        VertexFormat(glm::vec3(-9, 0, -6), color), //c1
        VertexFormat(glm::vec3(-8.8, 0, -6.6), color), //d1
        VertexFormat(glm::vec3(-8.6, 0, -7.2), color), //e1
        VertexFormat(glm::vec3(-8.1, 0, -7.7), color), //f1
        VertexFormat(glm::vec3(-7.2, 0, -7.8), color), //g1
        VertexFormat(glm::vec3(-2.5, 0, -8), color), //h1
        VertexFormat(glm::vec3(-1.5, 0, -7.7), color), //i1
        VertexFormat(glm::vec3(-0.8, 0, -7.3), color), //j1
        VertexFormat(glm::vec3(-0.3, 0, -6.4), color), //k1
        VertexFormat(glm::vec3(0, 0, -5.3), color), //l1
        VertexFormat(glm::vec3(0, 0, -4.5), color), //m1
        VertexFormat(glm::vec3(0.3, 0, -3.8), color), //n1
        VertexFormat(glm::vec3(0.8, 0, -3.3), color), //o1
        VertexFormat(glm::vec3(1.6, 0, -3), color), //p1
        VertexFormat(glm::vec3(2.3, 0, -2.8), color), //q1

        VertexFormat(glm::vec3(3, 0, -2.8), color),
        VertexFormat(glm::vec3(4, 0, -2.8), color),
        VertexFormat(glm::vec3(5, 0, -2.8), color),
        VertexFormat(glm::vec3(6, 0, -2.8), color),
        VertexFormat(glm::vec3(7, 0, -2.8), color),
        VertexFormat(glm::vec3(8, 0, -2.8), color),

        VertexFormat(glm::vec3(9.6, 0, -2.8), color), //r1
        VertexFormat(glm::vec3(10.4, 0, -2.4), color), //s1
        VertexFormat(glm::vec3(10.7, 0, -1.6), color), //t1
        VertexFormat(glm::vec3(10.6, 0, -0.9), color), //u1
        VertexFormat(glm::vec3(10.3, 0, -0.4), color), //v1
        VertexFormat(glm::vec3(10, 0, 0), color), //w1
        VertexFormat(glm::vec3(9.4, 0, 0.5), color), //z2

        VertexFormat(glm::vec3(8, 0, 0.6), color),
        VertexFormat(glm::vec3(7, 0, 0.8), color),

        VertexFormat(glm::vec3(6, 0, 1), color), //a2 sau b

        VertexFormat(glm::vec3(5, 0, 1), color),
        VertexFormat(glm::vec3(4, 0, 1), color),
        VertexFormat(glm::vec3(3, 0, 1), color),

        VertexFormat(glm::vec3(2.65, 0, 1), color), //n2
        VertexFormat(glm::vec3(1.9, 0, 1.16), color), //o2
        VertexFormat(glm::vec3(1.34, 0, 1.38), color), //p2
        VertexFormat(glm::vec3(1, 0, 1.75), color), //q2
        VertexFormat(glm::vec3(0.5, 0, 2.4), color), //r2
        VertexFormat(glm::vec3(0.3, 0, 3), color), //s2
        VertexFormat(glm::vec3(0, 0, 3.6), color), //t2
    };

    unsigned int size = middle.size();

    float dist = 0.75f;

    for (unsigned int i = 0; i < size; ++i) {
        glm::vec3 p1 = middle[i].position;
        glm::vec3 p2;

        if (i == size - 1) {
            p2 = middle[0].position;
        }
        else {
            p2 = middle[i + 1].position;
        }

        glm::vec3 d = p2 - p1;
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 p = glm::normalize(glm::cross(d, up));

        glm::vec3 r = p1 + dist * p;
        glm::vec3 a = p1 - dist * p;

        vertices.push_back(VertexFormat(r, color));
        vertices.push_back(VertexFormat(a, color));
    }

    std::vector<unsigned int> indices;

    for (int i = 0; i < vertices.size() - 4; i++) {
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i);
    }

    Mesh* track = new Mesh("track");
    track->SetDrawMode(GL_TRIANGLES);
    track->InitFromData(vertices, indices);

    return track;
}

Mesh* Tema2::CreateField()
{
    glm::vec3 color = glm::vec3(130.f / 255, 214.f / 255, 84.f / 255);

    int l = 100;

    std::vector<VertexFormat> vertices{
        VertexFormat(glm::vec3(-l, -0.01, -l), color),
        VertexFormat(glm::vec3(-l, -0.01, l), color),
        VertexFormat(glm::vec3(l, -0.01, -l), color),
        VertexFormat(glm::vec3(l, -0.01, l), color)
    };

    std::vector<unsigned int> indices{
        0, 1, 2,
        1, 2, 3
    };

    Mesh* field = new Mesh("field");
    field->SetDrawMode(GL_TRIANGLES);
    field->InitFromData(vertices, indices);

    return field;

}

void Tema2::Init()
{
    car_coords = glm::vec3(35, 0.7f, -15);

    camera_coords = glm::vec3(15, 1, -5.33);
    camera_center = glm::vec3(0, 0.7f, -5);

    camera = new implemented::CustomCamera();
    camera->Set(camera_coords, camera_center, glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    camera_map = new implemented::CustomCamera();
    camera_map->Set(glm::vec3(15, 10, -5.33),
        glm::vec3(15, 0.7f, -5.33), glm::vec3(-1, 1, 0));
    projectionMatrix2 = glm::ortho(left, right, bottom, top, z_near, z_far);

    polygonMode = GL_FILL;

    Mesh* track = CreateTrack();
    AddMeshToList(track);

    Mesh* field = CreateField();
    AddMeshToList(field);

    Mesh* car = new Mesh("car");
    car->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "car.obj");
    meshes[car->GetMeshID()] = car;

    Mesh* tree = new Mesh("tree");
    tree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "tree.obj");
    meshes[tree->GetMeshID()] = tree;

    srand(time(NULL));
    int lower = -800;
    int upper = 800;
    int limit = 1;


    for (int i = 0; i < TREE_COUNT; ++i) {
        int x = (rand() % (upper - lower + 1)) + lower;
        int y = 0;

        if (x < limit && x > -limit) {
            y = -30;
        }


        int z = (rand() % (upper - lower + 1)) + lower;

        if (z < limit && z > -limit) {
            y = -30;
        }
        tree_pos[i] = glm::vec3(x, y, z);
    }

    for (int i = 0; i < middle.size() - 2; ++i) {
        float x1 = middle[i].position.x;
        float y1 = middle[i].position.z;
        float x2 = middle[i + 1].position.x;
        float y2 = middle[i + 1].position.z;

        for (int k = 0; k < TREE_COUNT; ++k) {
            float x3 = tree_pos[k].x;
            float y3 = tree_pos[k].z;

            glm::vec3 aux = (middle[i + 1].position - middle[i].position);

            float u = ((x3 - x1) * (x2 - x1) + (y3 - y1) * (y2 - y1)) /
                (((aux.x * aux.x + aux.z * aux.z)));

            int x = x1 + u * (x2 - x1);
            int y = y1 + u * (y2 - y1);

            if (sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1)) < 10) {
                tree_pos[k] -= glm::vec3(0, 30, 0);
            }
        }
    }

    angle = 0;

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, 200, 200);

    //const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "textures");

    //Texture2D* car_texture = new Texture2D();
    //car_texture->Load2D(PATH_JOIN(sourceTextureDir, "car.bmp").c_str(), GL_REPEAT);
    //mapTextures["car"] = car_texture;


    //glActiveTexture(GL_TEXTURE0);

    //glBindTexture(GL_TEXTURE_2D, car_texture->GetTextureID());

    //Shader* shader1 = new Shader("CarShader");
    //shader1->AddShader(PATH_JOIN(window->props.selfDir,
    //                    SOURCE_PATH::M1, "tema2", "shaders", "car_shader.glsl"), GL_VERTEX_SHADER);

    //glUniform1i(glGetUniformLocation(shader1->program, "texture_1"), 0);


    //Texture2D* tree_texture = new Texture2D();
    //tree_texture->Load2D(PATH_JOIN(sourceTextureDir, "tree.mtl").c_str(), GL_REPEAT);
    //mapTextures["tree"] = tree_texture;

    //glActiveTexture(GL_TEXTURE1);

    //glBindTexture(GL_TEXTURE_2D, tree_texture->GetTextureID());

    //Shader* shader2 = new Shader("TreeShader");
    //shader2->AddShader(PATH_JOIN(window->props.selfDir,
    //                    SOURCE_PATH::M1, "tema2", "shaders", "tree_shader.glsl"), GL_VERTEX_SHADER);

    //glUniform1i(glGetUniformLocation(shader2->program, "texture_2"), 1);
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(97.f / 255, 162.f / 255, 215.f / 255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::RenderScene(implemented::CustomCamera* camera, glm::mat4 projectionMatrix) {
    modelMatrix = glm::mat4(1);
    RenderMeshCustom(meshes["field"], shaders["VertexColor"], modelMatrix,
        camera, projectionMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Scale(2, 2, 2);
    RenderMeshCustom(meshes["track"], shaders["VertexColor"], modelMatrix,
        camera, projectionMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Scale(0.35f, 0.35f, 0.35f);
    modelMatrix *= transform3D::Translate(car_coords.x, car_coords.y, car_coords.z);
    modelMatrix *= transform3D::RotateOY(M_PI / 2);
    modelMatrix *= transform3D::RotateOY(angle);
    RenderMeshCustom(meshes["car"], shaders["Simple"], modelMatrix,
        camera, projectionMatrix);

    for (int i = 0; i < TREE_COUNT; ++i) {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Scale(0.1f, 0.1f, 0.1f);
        modelMatrix *= transform3D::Translate(tree_pos[i].x, tree_pos[i].y, tree_pos[i].z);
        RenderMeshCustom(meshes["tree"], shaders["Simple"], modelMatrix,
            camera, projectionMatrix);
    }

    //modelMatrix = glm::mat4(1);
    //modelMatrix *= transform3D::Scale(0.35f, 0.35f, 0.35f);
    //modelMatrix *= transform3D::Translate(enemy_x, enemy_y, enemy_z);
    //
    //float enemy_angle = glm::atan(enemy_x / enemy_z);
    //modelMatrix *= transform3D::RotateOY(enemy_angle);
    //RenderMeshCustom(meshes["car"], shaders["Simple"], modelMatrix,
    //    camera, projectionMatrix);
}

void Tema2::RenderMeshCustom(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix,
    implemented::CustomCamera* camera, glm::mat4 projectionMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    viewMap = camera->GetViewMatrix();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMap));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Tema2::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    RenderScene(camera, projectionMatrix);

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    RenderScene(camera_map, projectionMatrix2);
}

void Tema2::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 2.0f, modifier = 2.85;
    cameraSpeed *= 3;

    for (int i = 0; i < vertices.size() - 1; ++i) {
        float x1 = vertices[i].position.x;
        float y1 = vertices[i].position.z;
        float x2 = vertices[i + 1].position.x;
        float y2 = vertices[i + 1].position.z;

        float x3 = car_coords.x;
        float y3 = car_coords.z;

        glm::vec3 aux = (vertices[i + 1].position - vertices[i].position);

        float u = ((x3 - x1) * (x2 - x1) + (y3 - y1) * (y2 - y1)) / (aux.x * aux.x + aux.z * aux.z);

        int x = x1 + u * (x2 - x1);
        int y = y1 + u * (y2 - y1);

        //if (sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1)) < 0.3f) {
        //    hit = true;
        //}
        //else {
        //    hit = false;
        //}
    }

    if (!hit) {
        if (window->KeyHold(GLFW_KEY_W)) {
            camera->TranslateForward(deltaTime * cameraSpeed);

            camera_map->Set(camera->position + glm::vec3(0, 1, 0), camera->position,
                glm::vec3(-1, 1, 0));
            car_coords.x += modifier * deltaTime * cameraSpeed * normalize(camera->forward).x;
            car_coords.z += modifier * deltaTime * cameraSpeed * normalize(camera->forward).z;
        }
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        camera->TranslateForward(-deltaTime * cameraSpeed);

        camera_map->Set(camera->position + glm::vec3(0, 1, 0), camera->position,
            glm::vec3(-1, 1, 0));

        car_coords.x -= modifier * deltaTime * cameraSpeed * normalize(camera->forward).x;
        car_coords.z -= modifier * deltaTime * cameraSpeed * normalize(camera->forward).z;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        camera->RotateThirdPerson_OY(deltaTime * modifier);
        angle += deltaTime * modifier;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        camera->RotateThirdPerson_OY(-deltaTime * modifier);
        angle -= deltaTime * modifier;
    }
}

void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
}

void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
