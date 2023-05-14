#ifndef GLGALAXYSTATE_H
#define GLGALAXYSTATE_H

#include <functional>

#include "Galaxy.hpp"
#include "GalaxyFlags.hpp"
#include "TextBuffer.hpp"
#include "VertexBufferLines.hpp"
#include "VertexBufferStars.hpp"

class GlGalaxyState {
 private:
  Galaxy _galaxy;
  std::vector<Galaxy::GalaxyParam> _predefinedGalaxies;

  const float TimeStepSize = 100000.0f;

  float _time;
  float _fov;
  int _fps;

  glm::mat4 _matProjection;
  glm::mat4 _matView;

  glm::vec3 _camOrient;
  glm::vec3 _camPos;
  glm::vec3 _camLookAt;

  VertexBufferLines _vertDensityWaves;
  VertexBufferLines _vertVelocityCurve;
  VertexBufferStars _vertStars;

  void addEllipsisVertices(std::vector<VertexColor> &vert,
                           std::vector<int> &vertIdx, float a, float b,
                           float angle, uint32_t pertNum, float pertAmp,
                           Color col) const;
  void updateDensityWaves();
  void updateStars();
  void updateVelocityCurve(const float timeStepSize);

 public:
  GlGalaxyState(
      std::function<glm::vec2(GLfloat, GLfloat, GLfloat)> windowPosFunc);
  virtual ~GlGalaxyState();

  void initSimulation();

  void update(GalaxyFlags gf, Galaxy galaxy);

  void render(GalaxyFlags gf, Galaxy galaxy, int width, int height);
};

#endif /* GLGALAXYSTATE_H */
