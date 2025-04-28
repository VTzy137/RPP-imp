// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//     if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
//         run_algorithm();
//     }
// }
// glfwSetKeyCallback(window, key_callback);

// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
//     if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//         double x, y;
//         glfwGetCursorPos(window, &x, &y);
//         handle_click(x, y);
//     }
// }
// glfwSetMouseButtonCallback(window, mouse_button_callback);

// void guiControl(GLFWwindow* window)
// {
//     ImGui::Begin("Control Panel");
//     if (ImGui::Button("Run Algorithm"))
//     {
//         run_algorithm();
//     }
//     ImGui::SliderFloat("Speed", &algo_speed, 0.1f, 5.0f);
//     ImGui::End();
// }