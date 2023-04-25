#ifndef GLAXIS_H
#define GLAXIS_H

#include "Galaxy.hpp"
#include "TextBuffer.hpp"
#include "VertexBufferLines.hpp"
class GlAxisState {
 private:
  TextBuffer _textAxisLabel;
  TextBuffer _textGalaxyLabels;

  VertexBufferLines _vertAxis;

 public:
  GlAxisState();
  virtual ~GlAxisState();

  void updateAxisLabel(Galaxy _galaxy);

  void UpdateAxis(const float fov);
};

#endif /* GLAXIS_H */
