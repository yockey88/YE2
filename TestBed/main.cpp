#include "TestMeshes.hpp"

int main() {
    
    // Parser Configuration
    /* TODO :==> Rewrite these horrible dirty json parsers
        -> yscript and ylang config/build/object files
    */
    YE::ConfigParser config_parser;
    YE::rendering::SDL2_Config sdl2_config = config_parser.ParseConfigFile("config/config.json");

    if (!sdl2_config.valid) {
        std::cout << "Invalid config file!" << std::endl;
        return -1;
    }
    
    // SDL2 window setup and OpenGL context creation
    std::unique_ptr<YE::rendering::SDL2> sdl2 = nullptr;
    sdl2 = std::make_unique<YE::rendering::SDL2>();
    if (sdl2->CreateWindow(&sdl2_config)) {
        std::cout << "SDL2 window created!" << std::endl;
    }
    
    // 1 / <T> = 1 / 60 = 0.01666666666666666666666666666667
    YE::dev::FrameRateEnforcer<60> frame_rate_enforcer{};
    
    // (@)(@)
    YE::rendering::Camera camera{};
    
    // shader setup
    std::unique_ptr<YE::rendering::Shader> light_shader = nullptr;
    std::unique_ptr<YE::rendering::Shader> shader = nullptr;
    std::unique_ptr<YE::rendering::Shader> floor_shader = nullptr;
    std::unique_ptr<YE::rendering::Shader> skybox_shader = nullptr;
    std::unique_ptr<YE::dev::CubeMap> cubemap = nullptr;
    std::unique_ptr<YE::rendering::Texture> tex = nullptr;

    std::unique_ptr<YE::dev::Cube> skycube = nullptr;
    std::unique_ptr<YE::dev::Cube> box = nullptr;
    std::unique_ptr<YE::dev::Cube> box1 = nullptr;
    std::unique_ptr<YE::dev::Cube> box2 = nullptr;
    std::unique_ptr<YE::dev::Cube> box3 = nullptr;
    std::unique_ptr<YE::dev::Cube> box4 = nullptr;
    std::unique_ptr<YE::dev::Cube> box5 = nullptr;
    std::unique_ptr<YE::dev::Cube> box6 = nullptr;
    std::unique_ptr<YE::dev::Cube> floor = nullptr;
    std::unique_ptr<YE::dev::Cube> light_cube = nullptr;

    // Big Bad sciency shtuch
    reactphysics3d::PhysicsCommon physics_common;

    reactphysics3d::PhysicsWorld::WorldSettings physics_world_settings{};
    physics_world_settings.worldName = "TestBed";
    physics_world_settings.defaultVelocitySolverNbIterations = 10;
    physics_world_settings.defaultPositionSolverNbIterations = 10;
    physics_world_settings.defaultBounciness = 0.1f;
    physics_world_settings.isSleepingEnabled = false;
    physics_world_settings.gravity = reactphysics3d::Vector3(0.f, -9.81f, 0.f);

    std::cout << "Physics settings:\n" << physics_world_settings.to_string() << std::endl;

    reactphysics3d::PhysicsWorld* physics_world = physics_common.createPhysicsWorld(physics_world_settings);   

    skybox_shader = std::make_unique<YE::rendering::Shader>("shaders/skybox.vert" , "shaders/skybox.frag");
    floor_shader = std::make_unique<YE::rendering::Shader>("shaders/materials.vert" , "shaders/materials.frag");
    shader = std::make_unique<YE::rendering::Shader>("shaders/tex_materials.vert" , "shaders/tex_materials.frag");
    light_shader = std::make_unique<YE::rendering::Shader>("shaders/light_cube.vert" , "shaders/light_cube.frag");

    // skoi
    std::vector<std::string> faces = {
        "skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/top.jpg",
        "skybox/bottom.jpg",
        "skybox/front.jpg",
        "skybox/back.jpg"
    };

    cubemap = std::make_unique<YE::dev::CubeMap>(faces);

    // box
    tex = std::make_unique<YE::rendering::Texture>("images/container2.png");

    // boxes
    box = std::make_unique<YE::dev::Cube>();
    box1 = std::make_unique<YE::dev::Cube>();
    box2 = std::make_unique<YE::dev::Cube>();
    box3 = std::make_unique<YE::dev::Cube>();
    box4 = std::make_unique<YE::dev::Cube>();
    box5 = std::make_unique<YE::dev::Cube>();
    box6 = std::make_unique<YE::dev::Cube>();
    floor = std::make_unique<YE::dev::Cube>();
    light_cube = std::make_unique<YE::dev::Cube>();

    // camera positions and stuff
    glm::vec3 camera_pos = glm::vec3(0.f , 4.f , 11.f);
    glm::vec3 camera_front = glm::vec3(0.f , 0.f , -1.f);
    glm::vec3 camera_up = glm::vec3(0.f , 1.f , 0.f);

    camera.m_Position = camera_pos;
    camera.m_Front = camera_front;
    camera.m_Up = camera_up;

    glm::mat4 view = glm::mat4(1.f);
    camera.GetViewMatrix(view);
    glm::mat4 proj = glm::mat4(1.f);
    camera.GetProjectionMatrix(proj);

    // this feels sloppy
    sdl2->m_Camera = &camera;

    // where exactly is the sky??
    glm::vec3 skybox_pos = glm::vec3(0.f , 0.f , 0.f);
    glm::vec3 skybox_scale = glm::vec3(3000.f , 3000.f , 3000.f);

    // what shape is the sky???
    glm::mat4 skybox_model = glm::mat4(1.f);
    skybox_model = glm::translate(skybox_model , skybox_pos);
    skybox_model = glm::scale(skybox_model , skybox_scale);
    
    // box positions
    glm::vec3 box_pos = glm::vec3(0.f , 3.f , 0.f);
    glm::vec3 box_pos1 = glm::vec3(0.5f , 6.f , 0.f);
    glm::vec3 box_pos2 = glm::vec3(1.f , 9.f , 0.f);
    glm::vec3 box_pos3 = glm::vec3(-0.5f , 12.f , 0.f);
    glm::vec3 box_pos4 = glm::vec3(-1.f , 15.f , 0.f);
    glm::vec3 box_pos5 = glm::vec3(0.f , 18.f , 1.f);
    glm::vec3 box_pos6 = glm::vec3(0.f , 21.f , 2.f);
    glm::vec3 floor_pos = glm::vec3(0.f , 0.f , -1.f);
    glm::vec3 box_scale = glm::vec3(1.f , 1.f , 1.f);
    glm::vec3 floor_scale = glm::vec3(100.f , 1.f , 100.f);
    
    // box models
    glm::mat4 box_model = glm::mat4(1.f);
    box_model = glm::translate(box_model , box_pos);
    box_model = glm::scale(box_model , box_scale);
    glm::mat4 box_model1 = glm::mat4(1.f);
    box_model1 = glm::translate(box_model1 , box_pos1);
    box_model1 = glm::scale(box_model1 , box_scale);
    glm::mat4 box_model2 = glm::mat4(1.f);
    box_model2 = glm::translate(box_model2 , box_pos2);
    box_model2 = glm::scale(box_model2 , box_scale);
    glm::mat4 box_model3 = glm::mat4(1.f);
    box_model3 = glm::translate(box_model3 , box_pos3);
    box_model3 = glm::scale(box_model3 , box_scale);
    glm::mat4 box_model4 = glm::mat4(1.f);
    box_model4 = glm::translate(box_model4 , box_pos4);
    box_model4 = glm::scale(box_model4 , box_scale);
    glm::mat4 box_model5 = glm::mat4(1.f);
    box_model5 = glm::translate(box_model5 , box_pos5);
    box_model5 = glm::scale(box_model5 , box_scale);
    glm::mat4 box_model6 = glm::mat4(1.f);
    box_model6 = glm::translate(box_model6 , box_pos6);
    box_model6 = glm::scale(box_model6 , box_scale);

    // flor model
    glm::mat4 floor_model = glm::mat4(1.f);
    floor_model = glm::translate(floor_model , floor_pos);
    floor_model = glm::scale(floor_model , floor_scale);


    // Genesis 1:3 -|- And God said, Let there be light: and there was light.
    glm::vec3 light_pos = glm::vec3(0.f , 10.f , 0.f);
    glm::vec3 light_color = glm::vec3(1.f , 1.f , 1.f);
    glm::vec3 light_diffuse_color = light_color * glm::vec3(0.5f , 0.5f , 0.5f);
    glm::vec3 light_ambient_color = light_diffuse_color * glm::vec3(0.2f , 0.2f , 0.2f);
    glm::vec3 light_specular_color = glm::vec3(1.f , 1.f , 1.f);

    glm::mat4 light_model = glm::mat4(1.f);
    light_model = glm::translate(light_model , light_pos);
    light_model = glm::scale(light_model , glm::vec3(0.33f , 0.33f , 0.33f));

    // shaders for boxes
    shader->Bind();
    shader->SetUniformInt("tex" , 0);
    shader->SetUniformFloat("material.shininess" , 32.f);
    shader->SetUniformVec3("material.ambient" , glm::vec3(1.f , 0.5f , 0.31f));
    shader->SetUniformVec3("material.diffuse" , glm::vec3(1.f , 0.5f , 0.31f));
    shader->SetUniformVec3("material.specular" , glm::vec3(0.5f , 0.5f , 0.5f));
    shader->SetUniformVec3("light.position" , light_pos);
    shader->SetUniformVec3("light.ambient" , light_ambient_color);
    shader->SetUniformVec3("light.diffuse" , light_diffuse_color);
    shader->SetUniformVec3("light.specular" , light_specular_color);
    shader->SetUniformMat4("view" , view);
    shader->SetUniformMat4("proj" , proj);
    shader->Unbind();

    // shaders for floor
    floor_shader->Bind();
    floor_shader->SetUniformFloat("material.shininess" , 22.f);
    floor_shader->SetUniformVec3("material.ambient" , glm::vec3(1.f , 0.5f , 0.31f));
    floor_shader->SetUniformVec3("material.diffuse" , glm::vec3(1.f , 0.5f , 0.31f));
    floor_shader->SetUniformVec3("material.specular" , glm::vec3(0.5f , 0.5f , 0.5f));
    floor_shader->SetUniformVec3("light.position" , light_pos);
    floor_shader->SetUniformVec3("light.ambient" , light_ambient_color);
    floor_shader->SetUniformVec3("light.diffuse" , light_diffuse_color);
    floor_shader->SetUniformVec3("light.specular" , light_specular_color);
    floor_shader->SetUniformMat4("model" , floor_model);
    floor_shader->SetUniformMat4("view" , view);
    floor_shader->SetUniformMat4("proj" , proj);
    floor_shader->Unbind();

    // shaders for light box  
    light_shader->Bind();
    light_shader->SetUniformVec3("view_pos" , camera.m_Position);
    light_shader->SetUniformMat4("model" , light_model);
    light_shader->SetUniformMat4("view" , view);
    light_shader->SetUniformMat4("proj" , proj);
    light_shader->Unbind();

    // rigid body creation
    reactphysics3d::Vector3 position(box_pos.x , box_pos.y , box_pos.z); 
    reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity(); 
    reactphysics3d::Transform prev_transform(position, orientation);
    reactphysics3d::Transform transform(position, orientation); 

    reactphysics3d::Vector3 position1(box_pos1.x , box_pos1.y , box_pos1.z); 
    reactphysics3d::Transform prev_transform1(position1 , orientation);
    reactphysics3d::Transform transform1(position1 , orientation); 

    reactphysics3d::Vector3 position2(box_pos2.x , box_pos2.y , box_pos2.z); 
    reactphysics3d::Transform prev_transform2(position2 , orientation);
    reactphysics3d::Transform transform2(position2 , orientation); 

    reactphysics3d::Vector3 position3(box_pos3.x , box_pos3.y , box_pos3.z);  
    reactphysics3d::Transform prev_transform3(position3 , orientation);
    reactphysics3d::Transform transform3(position3 , orientation); 

    reactphysics3d::Vector3 position4(box_pos4.x , box_pos4.y , box_pos4.z); 
    reactphysics3d::Transform prev_transform4(position4 , orientation);
    reactphysics3d::Transform transform4(position4 , orientation); 

    reactphysics3d::Vector3 position5(box_pos5.x , box_pos5.y , box_pos5.z); 
    reactphysics3d::Transform prev_transform5(position5 , orientation);
    reactphysics3d::Transform transform5(position5 , orientation); 

    reactphysics3d::Vector3 position6(box_pos6.x , box_pos6.y , box_pos6.z);  
    reactphysics3d::Transform prev_transform6(position6 , orientation);
    reactphysics3d::Transform transform6(position6 , orientation); 

    reactphysics3d::Vector3 floor_position(floor_pos.x , floor_pos.y , floor_pos.z); 
    reactphysics3d::Quaternion floor_orientation = reactphysics3d::Quaternion::identity(); 
    reactphysics3d::Transform floor_transform(floor_position , floor_orientation); 

    reactphysics3d::RigidBody* body = physics_world->createRigidBody(transform);
    body->setType(reactphysics3d::BodyType::DYNAMIC);
    reactphysics3d::RigidBody* body1 = physics_world->createRigidBody(transform1);
    body->setType(reactphysics3d::BodyType::DYNAMIC);
    reactphysics3d::RigidBody* body2 = physics_world->createRigidBody(transform2);
    body->setType(reactphysics3d::BodyType::DYNAMIC);
    reactphysics3d::RigidBody* body3 = physics_world->createRigidBody(transform3);
    body->setType(reactphysics3d::BodyType::DYNAMIC);
    reactphysics3d::RigidBody* body4 = physics_world->createRigidBody(transform4);
    body->setType(reactphysics3d::BodyType::DYNAMIC);
    reactphysics3d::RigidBody* body5 = physics_world->createRigidBody(transform5);
    body->setType(reactphysics3d::BodyType::DYNAMIC);
    reactphysics3d::RigidBody* body6 = physics_world->createRigidBody(transform6);
    body->setType(reactphysics3d::BodyType::DYNAMIC);

    reactphysics3d::RigidBody* floor_body = physics_world->createRigidBody(floor_transform);
    floor_body->setType(reactphysics3d::BodyType::STATIC);

    reactphysics3d::Vector3 box_half_extents(box_scale.x / 2.f , box_scale.y / 2.f , box_scale.z / 2.f);
    reactphysics3d::Vector3 floor_half_extents(floor_scale.x / 2.f , floor_scale.y / 2.f , floor_scale.z / 2.f);

    reactphysics3d::BoxShape* box_shape = physics_common.createBoxShape(box_half_extents);
    reactphysics3d::BoxShape* floor_shape = physics_common.createBoxShape(floor_half_extents);

    reactphysics3d::Transform box_local_transform = reactphysics3d::Transform::identity();
    reactphysics3d::Transform floor_local_transform = reactphysics3d::Transform::identity();

    // more like COOLIDERS, am I right !?
    reactphysics3d::Collider* box_collider = body->addCollider(box_shape , box_local_transform);
    reactphysics3d::Collider* box_collider1 = body1->addCollider(box_shape , box_local_transform);
    reactphysics3d::Collider* box_collider2 = body2->addCollider(box_shape , box_local_transform);
    reactphysics3d::Collider* box_collider3 = body3->addCollider(box_shape , box_local_transform);
    reactphysics3d::Collider* box_collider4 = body4->addCollider(box_shape , box_local_transform);
    reactphysics3d::Collider* box_collider5 = body5->addCollider(box_shape , box_local_transform);
    reactphysics3d::Collider* box_collider6 = body6->addCollider(box_shape , box_local_transform);
    reactphysics3d::Collider* floor_collider = floor_body->addCollider(floor_shape , floor_local_transform);

    const reactphysics3d::decimal time_step = 1.f / 60.f;
    reactphysics3d::decimal accumulator = 0.f;

    std::chrono::time_point<std::chrono::high_resolution_clock> prev_time = std::chrono::high_resolution_clock::now();

    while (sdl2->m_Running) {
        sdl2->BeginRender();

        std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<long double> elapsed = now - prev_time;
        long double delta_time = (long double)elapsed.count();
        prev_time = now;

        accumulator += delta_time;

        while (accumulator >= time_step) {
            physics_world->update(time_step);
            accumulator -= time_step;
        }

        reactphysics3d::decimal factor = accumulator / time_step;

        // THis feels like its gona get supper expensive :(
        const reactphysics3d::Transform& transform = body->getTransform();
        const reactphysics3d::Transform& inter_transform = reactphysics3d::Transform::interpolateTransforms(prev_transform , transform , factor);
        reactphysics3d::decimal inter_transform_matrix[16];
        inter_transform.getOpenGLMatrix(inter_transform_matrix);
        
        const reactphysics3d::Transform& transform1 = body1->getTransform();
        const reactphysics3d::Transform& inter_transform1 = reactphysics3d::Transform::interpolateTransforms(prev_transform1 , transform1 , factor);
        reactphysics3d::decimal inter_transform_matrix1[16];
        inter_transform1.getOpenGLMatrix(inter_transform_matrix1);
        
        const reactphysics3d::Transform& transform2 = body2->getTransform();
        const reactphysics3d::Transform& inter_transform2 = reactphysics3d::Transform::interpolateTransforms(prev_transform2 , transform2 , factor);
        reactphysics3d::decimal inter_transform_matrix2[16];
        inter_transform2.getOpenGLMatrix(inter_transform_matrix2);
        
        const reactphysics3d::Transform& transform3 = body3->getTransform();
        const reactphysics3d::Transform& inter_transform3 = reactphysics3d::Transform::interpolateTransforms(prev_transform3 , transform3 , factor);
        reactphysics3d::decimal inter_transform_matrix3[16];
        inter_transform3.getOpenGLMatrix(inter_transform_matrix3);
        
        const reactphysics3d::Transform& transform4 = body4->getTransform();
        const reactphysics3d::Transform& inter_transform4 = reactphysics3d::Transform::interpolateTransforms(prev_transform4 , transform4 , factor);
        reactphysics3d::decimal inter_transform_matrix4[16];
        inter_transform4.getOpenGLMatrix(inter_transform_matrix4);
        
        const reactphysics3d::Transform& transform5 = body5->getTransform();
        const reactphysics3d::Transform& inter_transform5 = reactphysics3d::Transform::interpolateTransforms(prev_transform5 , transform5, factor);
        reactphysics3d::decimal inter_transform_matrix5[16];
        inter_transform5.getOpenGLMatrix(inter_transform_matrix5);
        
        const reactphysics3d::Transform& transform6 = body6->getTransform();
        const reactphysics3d::Transform& inter_transform6 = reactphysics3d::Transform::interpolateTransforms(prev_transform6 , transform6 , factor);
        reactphysics3d::decimal inter_transform_matrix6[16];
        inter_transform6.getOpenGLMatrix(inter_transform_matrix6);

        light_model = glm::mat4(1.f);
        light_model = glm::translate(light_model , light_pos);
        light_model = glm::scale(light_model , glm::vec3(0.33f , 0.33f , 0.33f));

        box_model = glm::mat4(1.f);
        box_pos = glm::vec3(position.x , position.y , position.z);
        box_model = glm::make_mat4(inter_transform_matrix);

        box_model1 = glm::mat4(1.f);
        box_pos1 = glm::vec3(position1.x , position1.y , position1.z);
        box_model1 = glm::make_mat4(inter_transform_matrix1);

        box_model2 = glm::mat4(1.f);
        box_pos2 = glm::vec3(position2.x , position2.y , position2.z);
        box_model2 = glm::make_mat4(inter_transform_matrix2);

        box_model3 = glm::mat4(1.f);
        box_pos3 = glm::vec3(position3.x , position3.y , position3.z);
        box_model3 = glm::make_mat4(inter_transform_matrix3);

        box_model4 = glm::mat4(1.f);
        box_pos4 = glm::vec3(position4.x , position4.y , position4.z);
        box_model4 = glm::make_mat4(inter_transform_matrix4);

        box_model5 = glm::mat4(1.f);
        box_pos5 = glm::vec3(position5.x , position5.y , position5.z);
        box_model5 = glm::make_mat4(inter_transform_matrix5);
        
        box_model6 = glm::mat4(1.f);
        box_pos6 = glm::vec3(position6.x , position6.y , position6.z);
        box_model6 = glm::make_mat4(inter_transform_matrix6);

        camera.GetViewMatrix(view);
        camera.GetProjectionMatrix(proj);

        {   
            // Drawcalls
            // setup calls
            shader->Bind();
            shader->SetUniformVec3("light.position" , light_pos);
            shader->SetUniformVec3("light.ambient" , light_ambient_color);
            shader->SetUniformVec3("light.diffuse" , light_diffuse_color);
            shader->SetUniformVec3("light.specular" , light_specular_color);
            shader->SetUniformVec3("view_pos" , camera.m_Position);
            shader->SetUniformMat4("view" , view);
            shader->SetUniformMat4("proj" , proj);
            shader->Unbind();
            
            // box calls
            tex->Bind();
            shader->Bind();
            shader->SetUniformMat4("model" , box_model);
            box->Draw();
            shader->SetUniformMat4("model" , box_model1);
            box1->Draw();
            shader->SetUniformMat4("model" , box_model2);
            box2->Draw();
            shader->SetUniformMat4("model" , box_model3);
            box3->Draw();
            shader->SetUniformMat4("model" , box_model4);
            box4->Draw();
            shader->SetUniformMat4("model" , box_model5);
            box5->Draw();
            shader->SetUniformMat4("model" , box_model6);
            box6->Draw();
            shader->Unbind();
            tex->Unbind();

            // floor calls
            floor_shader->Bind();
            floor_shader->SetUniformVec3("light.position" , light_pos);
            floor_shader->SetUniformVec3("light.ambient" , light_ambient_color);
            floor_shader->SetUniformVec3("light.diffuse" , light_diffuse_color);
            floor_shader->SetUniformVec3("light.specular" , light_specular_color);
            floor_shader->SetUniformVec3("view_pos" , camera.m_Position);
            floor_shader->SetUniformMat4("view" , view);
            floor_shader->SetUniformMat4("proj" , proj);
            floor_shader->SetUniformMat4("model" , floor_model);
            floor->Draw();
            floor_shader->Unbind();

            // light calls
            light_shader->Bind();
            light_shader->SetUniformVec3("light.diffuse" , light_diffuse_color);
            light_shader->SetUniformMat4("model" , light_model);
            light_shader->SetUniformMat4("view" , view);
            light_shader->SetUniformMat4("proj" , proj);
            light_cube->Draw();
            light_shader->Unbind();

            // cube call (praise the cube)
            cubemap->Draw(view , proj);
            
            // gui-shmui! (Hah-poo!)
            LightGUI(light_pos , light_ambient_color , light_diffuse_color , light_specular_color);
            CameraGUI(camera);
        }

        // update previous transforms
        prev_transform = transform;
        prev_transform1 = transform1;
        prev_transform2 = transform2;
        prev_transform3 = transform3;
        prev_transform4 = transform4;
        prev_transform5 = transform5;
        prev_transform6 = transform6;
        
        // render thems shots
        sdl2->EndRender();
    }    
    frame_rate_enforcer.Enforce(); // (strictly enforced (@)(@))

    return 0;
}

void LightGUI(glm::vec3& light_pos , glm::vec3& ambient_color , glm::vec3& diffuse_color , glm::vec3& specular_color) {
    ImGui::Begin("Light");
    
    static float gui_light_pos[] = { light_pos.x , light_pos.y , light_pos.z };
    ImGui::SliderFloat3("Light Position" , gui_light_pos , -10.f , 10.f);
    light_pos = glm::vec3(gui_light_pos[0] , gui_light_pos[1] , gui_light_pos[2]);

    static float gui_ambient_color[] = { ambient_color.x , ambient_color.y , ambient_color.z };
    ImGui::ColorEdit3("Ambient Color" , gui_ambient_color);
    ambient_color = glm::vec3(gui_ambient_color[0] , gui_ambient_color[1] , gui_ambient_color[2]);

    static float gui_diffuse_color[] = { diffuse_color.z , diffuse_color.y , diffuse_color.z };
    ImGui::ColorEdit3("Diffuse Color" , gui_diffuse_color);
    diffuse_color = glm::vec3(gui_diffuse_color[0] , gui_diffuse_color[1] , gui_diffuse_color[2]);

    static float gui_specular_color[] = { specular_color.x , specular_color.y , specular_color.z };
    ImGui::ColorEdit3("Specular Color" , gui_specular_color);
    specular_color = glm::vec3(gui_specular_color[0] , gui_specular_color[1] , gui_specular_color[2]);
    
    ImGui::End();
}

void CameraGUI(YE::rendering::Camera& camera) {
    ImGui::Begin("Camera");
    ImGui::Text("Camera Position: (%.1f , %.1f , %.1f)" , camera.m_Position.x , camera.m_Position.y , camera.m_Position.z);
    ImGui::Text("Camera Front: (%.1f , %.1f , %.1f)" , camera.m_Front.x , camera.m_Front.y , camera.m_Front.z);
    ImGui::Text("Camera Up: (%.1f , %.1f , %.1f)" , camera.m_Up.x, camera.m_Up.y , camera.m_Up.z);
    ImGui::End();
}

void BoxGUI(glm::vec3& box_pos , glm::vec3& box_scale) {
    ImGui::Begin("Box");
    static float gui_box_pos[] = { box_pos.x , box_pos.y , box_pos.z };
    ImGui::SliderFloat3("Box Position" , gui_box_pos , -10.f , 10.f);
    box_pos = glm::vec3(gui_box_pos[0] , gui_box_pos[1] , gui_box_pos[2]);

    static float gui_box_scale[] = { box_scale.x , box_scale.y , box_scale.z };
    ImGui::SliderFloat3("Box Scale" , gui_box_scale , 0.1f , 10.f);
    box_scale = glm::vec3(gui_box_scale[0] , gui_box_scale[1] , gui_box_scale[2]);
    ImGui::End();
}