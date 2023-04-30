#include "temp_testing/TestMeshes.hpp"

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
    
    // 1 / <T> = 1 / 60 = 0.0166666666666666666666666666666......
    YE::dev::FrameRateEnforcer<60> frame_rate_enforcer{};
    
    // always watching (@)(@) 
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
    physics_world_settings.gravity = reactphysics3d::Vector3(0.f, -9.81f, 0.f);
    physics_world_settings.persistentContactDistanceThreshold = 0.3f;
    physics_world_settings.defaultFrictionCoefficient = 0.3f;
    physics_world_settings.defaultBounciness = 0.3f;
    physics_world_settings.restitutionVelocityThreshold = 0.5f;
    physics_world_settings.isSleepingEnabled = false;
    physics_world_settings.defaultVelocitySolverNbIterations = 32;
    physics_world_settings.defaultPositionSolverNbIterations = 32;
    physics_world_settings.defaultTimeBeforeSleep = true;
    physics_world_settings.defaultSleepLinearVelocity = 0.02f;
    physics_world_settings.defaultSleepAngularVelocity = 0.0523599f;
    physics_world_settings.cosAngleSimilarContactManifold = 0.95f;

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

    // box texture
    tex = std::make_unique<YE::rendering::Texture>("images/container2.png");

    // boxes and shtuff
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
    /* 
        Hate this ******* skybox. How to make look not weird when moving relative to box?
       especially corners. The hoeizon is inconsistent and the way NW,SW,SE,NE look is way 
       tf off
    */
    glm::vec3 skybox_scale = glm::vec3(100000.f , 100000.f , 100000.f); // how big to make this to avoid weird sube effects from movement relative to distance??

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

    // Genesis 1:3 -|- 
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
    reactphysics3d::Vector3 box_scale_react(box_scale.x , box_scale.y , box_scale.z);

    reactphysics3d::Vector3 box_pos_react(box_pos.x , box_pos.y , box_pos.z);
    reactphysics3d::Quaternion box_rot_react = reactphysics3d::Quaternion::identity();
    reactphysics3d::Transform box_transform(box_pos_react , box_rot_react);
    reactphysics3d::Transform prev_transform(box_pos_react , box_rot_react);
    reactphysics3d::RigidBody* body = physics_world->createRigidBody(box_transform);
    body->setType(reactphysics3d::BodyType::DYNAMIC);

    reactphysics3d::Vector3 box_pos1_react(box_pos1.x , box_pos1.y , box_pos1.z);
    reactphysics3d::Quaternion box_rot1_react = reactphysics3d::Quaternion::identity();
    reactphysics3d::Transform box_transform1(box_pos1_react , box_rot1_react);
    reactphysics3d::Transform prev_transform1(box_pos1_react , box_rot1_react);
    reactphysics3d::RigidBody* body1 = physics_world->createRigidBody(box_transform1);
    body1->setType(reactphysics3d::BodyType::DYNAMIC);

    reactphysics3d::Vector3 box_pos2_react(box_pos2.x , box_pos2.y , box_pos2.z);
    reactphysics3d::Quaternion box_rot2_react = reactphysics3d::Quaternion::identity();
    reactphysics3d::Transform box_transform2(box_pos2_react , box_rot2_react);
    reactphysics3d::Transform prev_transform2(box_pos2_react , box_rot2_react);
    reactphysics3d::RigidBody* body2 = physics_world->createRigidBody(box_transform2);

    reactphysics3d::Vector3 box_pos3_react(box_pos3.x , box_pos3.y , box_pos3.z);
    reactphysics3d::Quaternion box_rot3_react = reactphysics3d::Quaternion::identity();
    reactphysics3d::Transform box_transform3(box_pos3_react , box_rot3_react);
    reactphysics3d::Transform prev_transform3(box_pos3_react , box_rot3_react);
    reactphysics3d::RigidBody* body3 = physics_world->createRigidBody(box_transform3);
    body3->setType(reactphysics3d::BodyType::DYNAMIC);

    reactphysics3d::Vector3 box_pos4_react(box_pos4.x , box_pos4.y , box_pos4.z);
    reactphysics3d::Quaternion box_rot4_react = reactphysics3d::Quaternion::identity();
    reactphysics3d::Transform box_transform4(box_pos4_react , box_rot4_react);
    reactphysics3d::Transform prev_transform4(box_pos4_react , box_rot4_react);
    reactphysics3d::RigidBody* body4 = physics_world->createRigidBody(box_transform4);
    body4->setType(reactphysics3d::BodyType::DYNAMIC);

    reactphysics3d::Vector3 box_pos5_react(box_pos5.x , box_pos5.y , box_pos5.z);
    reactphysics3d::Quaternion box_rot5_react = reactphysics3d::Quaternion::identity();
    reactphysics3d::Transform box_transform5(box_pos5_react , box_rot5_react);
    reactphysics3d::Transform prev_transform5(box_pos5_react , box_rot5_react);
    reactphysics3d::RigidBody* body5 = physics_world->createRigidBody(box_transform5);
    body5->setType(reactphysics3d::BodyType::DYNAMIC);
    
    reactphysics3d::Vector3 box_pos6_react(box_pos6.x , box_pos6.y , box_pos6.z);
    reactphysics3d::Quaternion box_rot6_react = reactphysics3d::Quaternion::identity();
    reactphysics3d::Transform box_transform6(box_pos6_react , box_rot6_react);
    reactphysics3d::Transform prev_transform6(box_pos6_react , box_rot6_react);
    reactphysics3d::RigidBody* body6 = physics_world->createRigidBody(box_transform6);
    body6->setType(reactphysics3d::BodyType::DYNAMIC);

    reactphysics3d::Vector3 floor_pos_react(floor_pos.x , floor_pos.y , floor_pos.z);
    reactphysics3d::Quaternion floor_rot_react = reactphysics3d::Quaternion::identity();
    reactphysics3d::Transform floor_transform(floor_pos_react , floor_rot_react);
    reactphysics3d::RigidBody* floor_body = physics_world->createRigidBody(floor_transform);
    floor_body->setType(reactphysics3d::BodyType::STATIC);

    // more like COOLIDERS, am I right !?
    reactphysics3d::Vector3 box_half_extents(box_scale.x / 2.f , box_scale.y / 2.f , box_scale.z / 2.f);
    reactphysics3d::Vector3 floor_half_extents(floor_scale.x / 2.f , floor_scale.y / 2.f , floor_scale.z / 2.f);

    reactphysics3d::BoxShape* box_shape = physics_common.createBoxShape(box_half_extents);
    reactphysics3d::BoxShape* floor_shape = physics_common.createBoxShape(floor_half_extents);

    reactphysics3d::Transform box_local_transform = reactphysics3d::Transform::identity();
    reactphysics3d::Transform floor_local_transform = reactphysics3d::Transform::identity();

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

        const reactphysics3d::Transform& box_transform = body->getTransform();
        const reactphysics3d::Transform inter_transform = reactphysics3d::Transform::interpolateTransforms(prev_transform , box_transform , factor);
        reactphysics3d::decimal inter_transform_mat[16];
        inter_transform.getOpenGLMatrix(inter_transform_mat);

        const reactphysics3d::Transform& box_transform1 = body1->getTransform();
        const reactphysics3d::Transform& inter_transform1 = reactphysics3d::Transform::interpolateTransforms(prev_transform1 , box_transform1 , factor);
        reactphysics3d::decimal inter_transform_mat1[16];
        inter_transform1.getOpenGLMatrix(inter_transform_mat1);

        const reactphysics3d::Transform& box_transform2 = body2->getTransform();
        const reactphysics3d::Transform& inter_transform2 = reactphysics3d::Transform::interpolateTransforms(prev_transform2 , box_transform2 , factor);
        reactphysics3d::decimal inter_transform_mat2[16];
        inter_transform2.getOpenGLMatrix(inter_transform_mat2);

        const reactphysics3d::Transform& box_transform3 = body3->getTransform();
        const reactphysics3d::Transform& inter_transform3 = reactphysics3d::Transform::interpolateTransforms(prev_transform3 , box_transform3 , factor);
        reactphysics3d::decimal inter_transform_mat3[16];
        inter_transform3.getOpenGLMatrix(inter_transform_mat3);


        const reactphysics3d::Transform& box_transform4 = body4->getTransform();
        const reactphysics3d::Transform& inter_transform4 = reactphysics3d::Transform::interpolateTransforms(prev_transform4 , box_transform4 , factor);
        reactphysics3d::decimal inter_transform_mat4[16];
        inter_transform4.getOpenGLMatrix(inter_transform_mat4);

        const reactphysics3d::Transform& box_transform5 = body5->getTransform();
        const reactphysics3d::Transform& inter_transform5 = reactphysics3d::Transform::interpolateTransforms(prev_transform5 , box_transform5 , factor);
        reactphysics3d::decimal inter_transform_mat5[16];
        inter_transform5.getOpenGLMatrix(inter_transform_mat5);

        const reactphysics3d::Transform& box_transform6 = body6->getTransform();
        const reactphysics3d::Transform& inter_transform6 = reactphysics3d::Transform::interpolateTransforms(prev_transform6 , box_transform6 , factor);
        reactphysics3d::decimal inter_transform_mat6[16];
        inter_transform6.getOpenGLMatrix(inter_transform_mat6);
    
        box_model = glm::mat4(1.f);
        box_model = glm::make_mat4(inter_transform_mat);

        box_model1 = glm::mat4(1.f);
        box_model1 = glm::make_mat4(inter_transform_mat1);

        box_model2 = glm::mat4(1.f);
        box_model2 = glm::make_mat4(inter_transform_mat2);

        box_model3 = glm::mat4(1.f);
        box_model3 = glm::make_mat4(inter_transform_mat3);

        box_model4 = glm::mat4(1.f);
        box_model4 = glm::make_mat4(inter_transform_mat4);

        box_model5 = glm::mat4(1.f);
        box_model5 = glm::make_mat4(inter_transform_mat5);

        box_model6 = glm::mat4(1.f);
        box_model6 = glm::make_mat4(inter_transform_mat6);

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
        }

        // update previous transforms
        prev_transform = box_transform;
        prev_transform1 = box_transform1;
        prev_transform2 = box_transform2;
        prev_transform3 = box_transform3;
        prev_transform4 = box_transform4;
        prev_transform5 = box_transform5;
        prev_transform6 = box_transform6;

        sdl2->EndRender();

        frame_rate_enforcer.Enforce(); // (strictly enforced (@)(@))
    }    

    return 0;
}