#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shaders/lightingShader.h"
#include "shaders/shadowMapShader.h"
#include "object.h"
#include "shadowMapFBO.h"
#include "cubeMapTexture.h"
#include "skybox.h"

class Graphics {
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();
    void ShadowRenderPass();
    void SkyboxRenderPass();
    void LightingRenderPass();
    void Keyboard(SDL_Keycode keycode, bool shiftKeyPressed, bool ctrlKeyPressed);

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    LightingShader *m_shader;
    ShadowMapShader *m_shadowMapShader;
    ShadowMapFBO *m_shadowMapFBO;

    Object *m_cube;
    Object *m_floor;

    Light m_spotlight;

    // DEBUGGING
    Skybox *skybox;
};

#endif /* GRAPHICS_H */