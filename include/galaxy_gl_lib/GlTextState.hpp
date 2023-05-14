#ifndef GLTEXTSTATE_H
#define GLTEXTSTATE_H

#include "TextBuffer.hpp"
class GlTextState
{
private:
  TextBuffer _textHelp;

public:
  GlTextState();
  virtual ~GlTextState();

  void UpdateText(const float fov, int width, int height);
};

#endif /* GLTEXTSTATE_H */
