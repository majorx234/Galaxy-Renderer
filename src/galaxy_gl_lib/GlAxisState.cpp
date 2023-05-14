#include "GlAxisState.hpp"

#include "Galaxy.hpp"
#include "TextBuffer.hpp"

GlAxisState::GlAxisState()
    : _vertAxis(), _textAxisLabel(), _textGalaxyLabels() {}

void GlAxisState::UpdateAxis(const float fov) {
  std::vector<VertexColor> vert;
  std::vector<int> idx;

  GLfloat s = (GLfloat)std::pow(10, (int)(std::log10(fov / 2)));
  GLfloat l = fov / 100, p = 0;

  float r = 0.3, g = 0.3, b = 0.3, a = 0.8;
  for (int i = 0; p < fov; ++i) {
    p += s;
    idx.push_back((int)vert.size());
    vert.push_back({p, -l, 0, r, g, b, a});

    idx.push_back((int)vert.size());
    vert.push_back({p, l, 0, r, g, b, a});

    idx.push_back((int)vert.size());
    vert.push_back({-p, -l, 0, r, g, b, a});

    idx.push_back((int)vert.size());
    vert.push_back({-p, 0, 0, r, g, b, a});

    idx.push_back((int)vert.size());
    vert.push_back({-l, p, 0, r, g, b, a});

    idx.push_back((int)vert.size());
    vert.push_back({0, p, 0, r, g, b, a});

    idx.push_back((int)vert.size());
    vert.push_back({-l, -p, 0, r, g, b, a});

    idx.push_back((int)vert.size());
    vert.push_back({0, -p, 0, r, g, b, a});
  }

  idx.push_back((int)vert.size());
  vert.push_back({-fov, 0, 0, r, g, b, a});

  idx.push_back((int)vert.size());
  vert.push_back({fov, 0, 0, r, g, b, a});

  idx.push_back((int)vert.size());
  vert.push_back({0, -fov, 0, r, g, b, a});

  idx.push_back((int)vert.size());
  vert.push_back({0, fov, 0, r, g, b, a});

  _vertAxis.CreateBuffer(vert, idx, GL_LINES);

  //
  // Update Axis Labels
  //

  _textAxisLabel.BeginUpdate();

  s = (GLfloat)std::pow(10, (int)(std::log10(fov / 2)));
  l = fov / 100, p = 0;

  for (int i = 0; p < fov; ++i) {
    p += s;
    if (i % 2 == 0) {
      _textAxisLabel.AddText(1, GetWindowPos(p - l, -4.f * l, 0), "%2.0f", p);
    } else {
      _textAxisLabel.AddText(1, GetWindowPos(p - l, 2 * l, 0), "%2.0f", p);
    }
  }
  _textAxisLabel.EndUpdate();

  _renderUpdateHint &= ~ruhAXIS;
}

void GlAxisState::updateAxisLabel(Galaxy _galaxy) {
  _textGalaxyLabels.BeginUpdate();
  _textGalaxyLabels.AddText(1, GetWindowPos(0, _galaxy.GetCoreRad() + 500.f, 0),
                            "Core");
  _textGalaxyLabels.AddText(
      1, GetWindowPos(0, _galaxy.GetRad() + 500 + 500.f, 0), "Disk");
  _textGalaxyLabels.AddText(
      1, GetWindowPos(0, _galaxy.GetFarFieldRad() + 500 + 500.f, 0),
      "Intergalactic medium");
  _textGalaxyLabels.EndUpdate();
}
