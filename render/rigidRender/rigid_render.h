#pragma once
#include <render/qGLWidget/base_renderer.h>
#include <render/qGLWidget/oglwidget.h>

/** This renderer is used to display volume boundary objects (loaded as
 * VDBs). **/
class rigidRender : public Renderer {
public:
	rigidRender(OGLWidget *parent, int32_t index);
  virtual void update() override;
  virtual void render(bool pretty) override;
  virtual bool valid() override;
  virtual void toggle() override;

  cudaGraphicsResource *cuda_vbo_resource;

  QOpenGLShaderProgram *m_program;

  GLuint m_posAttr;
  GLuint m_colAttr;
  GLuint vao;
  GLuint IBO;
  GLuint VXO;
  GLuint VUV;

  int32_t idx;

  Matrix4x4 modelMat;
  GLuint modelUniform = 0;

  int32_t tris = 0;

  bool active = false;
};