#include <iostream>
#include <memory>
using namespace std;

class Window {
public:
    virtual ~Window() = default;
    virtual void draw() = 0;
};

class Button {
public:
    virtual ~Button() = default;
    virtual void draw() = 0;
};

class Shader {
public:
    virtual ~Shader() = default;
    virtual void compile() = 0;
};

class OpenGLWindow : public Window {
public:
    void draw() override { cout << "OpenGL Window Drawing\n"; }
};

class OpenGLButton : public Button {
public:
    void draw() override { cout << "OpenGL Button Drawing\n"; }
};

class OpenGLShader : public Shader {
public:
    void compile() override { cout << "Compiling OpenGL Shader\n"; }
};

class VulkanWindow : public Window {
public:
    void draw() override { cout << "Vulkan Window Drawing\n"; }
};

class VulkanButton : public Button {
public:
    void draw() override { cout << "Vulkan Button Drawing\n"; }
};

class VulkanShader : public Shader {
public:
    void compile() override { cout << "Compiling Vulkan Shader\n"; }
};

class RenderFactory {
public:
    virtual ~RenderFactory() = default;
    virtual unique_ptr<Window> createWindow() = 0;
    virtual unique_ptr<Button> createButton() = 0;
    virtual unique_ptr<Shader> createShader() = 0;
};

class OpenGLFactory : public RenderFactory {
public:
    unique_ptr<Window> createWindow() override {
        return make_unique<OpenGLWindow>();
    }
    unique_ptr<Button> createButton() override {
        return make_unique<OpenGLButton>();
    }
    unique_ptr<Shader> createShader() override {
        return make_unique<OpenGLShader>();
    }
};

class VulkanFactory : public RenderFactory {
public:
    unique_ptr<Window> createWindow() override {
        return make_unique<VulkanWindow>();
    }
    unique_ptr<Button> createButton() override {
        return make_unique<VulkanButton>();
    }
    unique_ptr<Shader> createShader() override {
        return make_unique<VulkanShader>();
    }
};