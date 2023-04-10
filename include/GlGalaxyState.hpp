#ifndef GLGALAXYSTATE_H
#define GLGALAXYSTATE_H

#include <functional>
#include "Galaxy.hpp"
#include "TextBuffer.hpp"
#include "VertexBufferLines.hpp"
#include "VertexBufferStars.hpp"
class GlGalaxyState {
 private:
  enum class DisplayItem : uint32_t {
    NONE = 0,
    AXIS = 1 << 1,
    STARS = 1 << 2,
    PAUSE = 1 << 3,
    HELP = 1 << 4,
    DENSITY_WAVES = 1 << 5,
    VELOCITY = 1 << 6,
    DUST = 1 << 7,
    H2 = 1 << 8,
    FILAMENTS = 1 << 9,
  };

  enum RenderUpdateHint : uint32_t {
    ruhNONE = 0,
    ruhDENSITY_WAVES = 1 << 1,
    ruhAXIS = 1 << 2,
    ruhSTARS = 1 << 3,
    ruhDUST = 1 << 4,
    ruhCREATE_VELOCITY_CURVE = 1 << 5,
    ruhCREATE_TEXT = 1 << 7
  };

  Galaxy _galaxy;
  std::vector<Galaxy::GalaxyParam> _predefinedGalaxies;

  uint32_t _renderUpdateHint;
  uint32_t _flags;

  VertexBufferLines _vertDensityWaves;
  VertexBufferLines _vertAxis;
  VertexBufferLines _vertVelocityCurve;
  VertexBufferStars _vertStars;

  TextBuffer _textHelp;
  TextBuffer _textAxisLabel;
  TextBuffer _textGalaxyLabels;

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
  void UpdateAxis(const float fov);
  void UpdateStars();
  void UpdateVelocityCurve(const float timeStepSize);
  void UpdateText(const float fov, int width, int height);
};

#endif /* GLGALAXYSTATE_H */
