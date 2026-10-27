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
    void draw() override { cout << "Dibujo en ventana OpenGL\n"; }
};

class OpenGLButton : public Button {
public:
    void draw() override { cout << "Dibujo de botones en OpenGL\n"; }
};

class OpenGLShader : public Shader {
public:
    void compile() override { cout << "Compilando sombreador OpenGL\n"; }
};

class VulkanWindow : public Window {
public:
    void draw() override { cout << "Dibujo en ventana con Vulkan\n"; }
};

class VulkanButton : public Button {
public:
    void draw() override { cout << "Dibujo de botones en Vulkan\n"; }
};

class VulkanShader : public Shader {
public:
    void compile() override { cout << "Compilando sombreador Vulkan\n"; }
};

class RenderFactory {
public:
    virtual ~RenderFactory() = default;
    virtual unique_ptr<Window> creaWindow() = 0;
    virtual unique_ptr<Button> creaButton() = 0;
    virtual unique_ptr<Shader> creaShader() = 0;
};

class OpenGLFactory : public RenderFactory {
public:
    unique_ptr<Window> creaWindow() override {
        return make_unique<OpenGLWindow>();
    }
    unique_ptr<Button> creaButton() override {
        return make_unique<OpenGLButton>();
    }
    unique_ptr<Shader> creaShader() override {
        return make_unique<OpenGLShader>();
    }
};

class VulkanFactory : public RenderFactory {
public:
    unique_ptr<Window> creaWindow() override {
        return make_unique<VulkanWindow>();
    }
    unique_ptr<Button> creaButton() override {
        return make_unique<VulkanButton>();
    }
    unique_ptr<Shader> creaShader() override {
        return make_unique<VulkanShader>();
    }
};