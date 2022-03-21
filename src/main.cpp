//记得要加上glad
#include <glad/glad.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imnodes.h"


#include<iostream>

#include <GLFW/glfw3.h> // Will drag system OpenGL headers

//glfw出现erroe后的回调函数
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);

    // 初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    //初始化glad
    //重要，一定要加上这个
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImNodes::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    //这里的值是为了界面里的内容设置的
    //因为在while()循环里更新的话值会出现问题，比如一直重新设置为初始值
    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        //设置清除缓冲后的颜色
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        //清除缓冲
        glClear(GL_COLOR_BUFFER_BIT);
        //处理各种输入设备内容
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();



        ImGui::Begin("node editor");

        const int hardcoded_node_id = 1;

        ImNodes::BeginNodeEditor();




        // ImNodes::BeginNode(1);

        // ImNodes::BeginNodeTitleBar();
        // ImGui::TextUnformatted("simple node :)");
        // ImNodes::EndNodeTitleBar();

        // ImNodes::BeginInputAttribute(2);
        // ImGui::Text("input");
        // ImNodes::EndInputAttribute();

        // ImNodes::BeginOutputAttribute(3);
        // ImGui::Indent(40);
        // ImGui::Text("output");
        // ImNodes::EndOutputAttribute();

        // ImNodes::EndNode();
        ImNodes::BeginNode(1);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("output node");
        ImNodes::EndNodeTitleBar();

        const int output_attr_id = 2;
        ImNodes::BeginOutputAttribute(2);
        // in between Begin|EndAttribute calls, you can call ImGui
        // UI functions
        ImGui::Text("output pin");
        ImNodes::EndOutputAttribute();

        ImNodes::EndNode();


        ImNodes::BeginNode(2);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("output node");
        ImNodes::EndNodeTitleBar();
        
        ImNodes::BeginInputAttribute(3);
        ImGui::Text("input pin");
        ImNodes::EndInputAttribute();

        // const int output_attr_id = 2;
        ImNodes::BeginOutputAttribute(4);
        // in between Begin|EndAttribute calls, you can call ImGui
        // UI functions
        ImGui::Text("output pin");
        ImNodes::EndOutputAttribute();

        ImNodes::EndNode();
        
        ImNodes::Link(0,2,3);
        




        ImNodes::EndNodeEditor();
        ImGui::End();

        
        







        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        // if (show_demo_window)
        //     ImGui::ShowDemoWindow(&show_demo_window);

        // // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        // {
        //     static float f = 0.0f;
        //     static int counter = 0;

        //     ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        //     ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        //     ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //     ImGui::Checkbox("Another Window", &show_another_window);

        //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //     ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        //     if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //         counter++;
        //     ImGui::SameLine();
        //     ImGui::Text("counter = %d", counter);

        //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        //     ImGui::End();
        // }

        // // 3. Show another simple window.
        // if (show_another_window)
        // {
        //     ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        //     ImGui::Text("Hello from another window!");
        //     if (ImGui::Button("Close Me"))
        //         show_another_window = false;
        //     ImGui::End();
        // }



        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImNodes::DestroyContext();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}