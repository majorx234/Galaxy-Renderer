#ifndef GLGALAXYSTATE_H
#define GLGALAXYSTATE_H

#include <functional>
#include "Galaxy.hpp"
#include "TextBuffer.hpp"
#include "VertexBufferLines.hpp"
#include "VertexBufferStars.hpp"
class GlGalaxyState {
 private:

  Galaxy _galaxy;
  std::vector<Galaxy::GalaxyParam> _predefinedGalaxies;


  VertexBufferLines _vertDensityWaves;
  VertexBufferLines _vertVelocityCurve;
  VertexBufferStars _vertStars;

  std::function<glm::vec2(GLfloat, GLfloat, GLfloat)> _GetWindowPos;

  void AddEllipsisVertices(std::vector<VertexColor> &vert,
                           std::vector<int> &vertIdx, float a, float b,
                           float angle, uint32_t pertNum, float pertAmp,
                           Color col) const;

 public:
  GlGalaxyState(std::function<glm::vec2(GLfloat, GLfloat, GLfloat)> windowPosFunc);
  virtual ~GlGalaxyState();

  void InitSimulation();

  void UpdateDensityWaves();
  void UpdateStars();
  void UpdateVelocityCurve(const float timeStepSize);
};

#endif /* GLGALAXYSTATE_H */
