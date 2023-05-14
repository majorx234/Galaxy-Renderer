#include "GlGalaxyState.hpp"

GlGalaxyState::GlGalaxyState(std::function<glm::vec2(GLfloat, GLfloat, GLfloat)> windowPosFunc)
    : _flags((int)DisplayItem::STARS | (int)DisplayItem::AXIS |
             (int)DisplayItem::HELP | (int)DisplayItem::DUST |
             (int)DisplayItem::H2 | (int)DisplayItem::FILAMENTS),
      _galaxy(),
      _renderUpdateHint(ruhDENSITY_WAVES | ruhAXIS | ruhSTARS | ruhDUST |
                        ruhCREATE_VELOCITY_CURVE | ruhCREATE_TEXT),
      _vertDensityWaves(2),
      _vertAxis(),
      _vertVelocityCurve(1, GL_DYNAMIC_DRAW),
      _vertStars(GL_FUNC_ADD, GL_ONE),
      _GetWindowPos(windowPosFunc)
 {
  _predefinedGalaxies.push_back(
      {13000, 4000, .0004f, .85f, .95f, 40000, true, 2, 40, 90, 3600});
  _predefinedGalaxies.push_back(
      {16000, 4000, .0003f, .8f, .85f, 40000, true, 0, 40, 100, 4500});
  _predefinedGalaxies.push_back(
      {13000, 4000, .00064f, .9f, .9f, 40000, true, 0, 0, 85, 4100});
  _predefinedGalaxies.push_back(
      {13000, 4000, .0004f, 1.35f, 1.05f, 40000, true, 0, 0, 70, 4500});
  _predefinedGalaxies.push_back(
      {13000, 4500, .0002f, .65f, .95f, 40000, true, 3, 72, 90, 4000});
  _predefinedGalaxies.push_back(
      {15000, 4000, .0003f, 1.45f, 1.0f, 40000, true, 0, 0, 100, 4500});
  _predefinedGalaxies.push_back(
      {14000, 12500, .0002f, 0.65f, 0.95f, 40000, true, 3, 72, 85, 2200});
  _predefinedGalaxies.push_back(
      {13000, 1500, .0004f, 1.1f, 1.0f, 40000, true, 1, 20, 80, 2800});
  _predefinedGalaxies.push_back(
      {13000, 4000, .0004f, .85f, .95f, 40000, true, 1, 20, 80, 4500});
}

GlGalaxyState::~GlGalaxyState() {
  _vertDensityWaves.Release();
  _vertAxis.Release();
  _vertVelocityCurve.Release();
  _vertStars.Release();
}

void GlGalaxyState::InitSimulation() {
  _galaxy.Reset(
      {13000,    // radius of the galaxy
       4000,     // radius of the core
       0.0004f,  // angluar offset of the density wave per parsec of radius
       0.85f,    // excentricity at the edge of the core
       0.95f,    // excentricity at the edge of the disk
       100000,   // total number of stars
       true,     // has dark matter
       2,        // Perturbations per full ellipse
       40,       // Amplitude damping factor of perturbation
       70,       // dust render size in pixel
       4000});
}

void GlGalaxyState::UpdateStars() {
  std::vector<VertexStar> vert;
  std::vector<int> idx;

  const auto &stars = _galaxy.GetStars();

  float a = 1;
  Color color = {1, 1, 1, a};

  for (int i = 1; i < stars.size(); ++i) {
    const Color &col = Helper::ColorFromTemperature(stars[i].temp);
    color = {col.r, col.g, col.b, a};

    idx.push_back((int)vert.size());
    vert.push_back({stars[i], color});
  }
}

void GlGalaxyState::UpdateAxis(float fov) {
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
      _textAxisLabel.AddText(1, _GetWindowPos(p - l, -4.f * l, 0), "%2.0f", p);
    } else {
      _textAxisLabel.AddText(1, _GetWindowPos(p - l, 2 * l, 0), "%2.0f", p);
    }
  }
  _textAxisLabel.EndUpdate();

  _renderUpdateHint &= ~ruhAXIS;
}

void GlGalaxyState::UpdateText(float fov, int width, int height) {
  float x0 = 10, y0 = 60, dy = 20;
  int line = 0;
  float y = y0 - 60;

  y0 = 60;
  float dy1 = _textHelp.GetFontSize(1) + 8;
  float dy2 = _textHelp.GetFontSize(2) + 6;

  _textHelp.BeginUpdate();
  _textHelp.AddText(0, {x0, y0 - 60}, "Spiral Galaxy Renderer");

  y = y0;
  _textHelp.AddText(1, {x0, y}, "Geometry:");
  y += dy1;
  _textHelp.AddText(2, {x0, y}, "[r],[f] RadCore:     %d pc",
                    (int)_galaxy.GetCoreRad());
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[t],[g] RadGalaxy:   %d pc",
                    (int)_galaxy.GetRad());
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "        RadFarField: %d pc",
                    (int)_galaxy.GetFarFieldRad());
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[q],[a] ExInner:     %2.2f",
                    _galaxy.GetExInner());
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[w],[s] ExOuter:     %2.2f",
                    _galaxy.GetExOuter());
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[e],[d] AngOff:      %1.4g deg/pc",
                    _galaxy.GetAngularOffset());
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[+],[-] FoV:         %1.2f pc", fov);

  y += dy1;
  _textHelp.AddText(1, {x0, y}, "Spiral Arms:");
  y += dy1;
  _textHelp.AddText(2, {x0, y}, "[Home],[End]    Num pert:  %d",
                    _galaxy.GetPertN());
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[PG_UP],[PG_DN] pertDamp:  %1.2f",
                    _galaxy.GetPertAmp());

  y += dy1;
  _textHelp.AddText(1, {x0, y}, "Display Features:");
  y += dy1;
  _textHelp.AddText(2, {x0, y}, "[b],[n]  Dust render size:  %2.2lf",
                    _galaxy.GetDustRenderSize());
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[F1]  Help Screen");
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[F2]  Toggle Axis");
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[F3]  Toggle Dust");
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[F4]  Toggle H2 Regions");
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[F5]  Toggle Filaments");
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[F6]  Toggle Density Waves");
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[F10] Exit");

  y += dy1;
  _textHelp.AddText(1, {x0, y}, "Physics:");
  y += dy1;
  _textHelp.AddText(2, {x0, y}, "[z],[h] Base Temp.:  %2.2lf K",
                    _galaxy.GetBaseTemp());
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[m] Toggle Dark Matter: %s",
                    _galaxy.HasDarkMatter() ? "ON" : "OFF");
  y += dy2;
  _textHelp.AddText(
      2, {x0, y}, "[v] Display Velocity Curve: %s",
      ((_flags & (int)DisplayItem::VELOCITY) != 0) ? "ON" : "OFF");

  y += dy1;
  _textHelp.AddText(1, {x0, y}, "Predefined Galaxies:");
  y += dy1;
  _textHelp.AddText(2, {x0, y}, "[KP1] - [KP8] Predefined Galaxies");
  y += dy2;
  _textHelp.AddText(2, {x0, y}, "[Pause],[Space]       Halt simulation");

  _textHelp.AddText(1, {(float)width - 180, (float)height - 30},
                    " (C) 2020 Ingo Berg");
  _textHelp.EndUpdate();

  _renderUpdateHint &= ~ruhCREATE_TEXT;
}

void GlGalaxyState::UpdateVelocityCurve(const float timeStepSize) {
  // I don't need every star for the curve.
  const auto &stars = _galaxy.GetStars();

  std::vector<VertexColor> vert;
  vert.reserve(1000);

  std::vector<int> idx;
  idx.reserve(1000);

  float dt_in_sec = timeStepSize * Helper::SEC_PER_YEAR;
  float r = 0, v = 0;
  float cr = 0.5, cg = 1, cb = 1, ca = 1;
  for (int r = 0; r < _galaxy.GetFarFieldRad(); r += 100) {
    idx.push_back((int)vert.size());

    if (_galaxy.HasDarkMatter())
      vert.push_back({(float)r, Helper::VelocityWithDarkMatter((float)r) * 10.f,
                      0, cr, cg, cb, ca});
    else
      vert.push_back({(float)r,
                      Helper::VelocityWithoutDarkMatter((float)r) * 10.f, 0, cr,
                      cg, cb, ca});
  }

  _vertVelocityCurve.CreateBuffer(vert, idx, GL_POINTS);
  _renderUpdateHint &= ~ruhCREATE_VELOCITY_CURVE;
}

void GlGalaxyState::UpdateDensityWaves() {
  std::vector<VertexColor> vert;
  std::vector<int> idx;

  //
  // First add the density waves
  //

  int num = 100;
  float dr = _galaxy.GetFarFieldRad() / num;
  for (int i = 0; i <= num; ++i) {
    float r = dr * (i + 1);
    AddEllipsisVertices(vert, idx, r, r * _galaxy.GetExcentricity(r),
                        Helper::RAD_TO_DEG * _galaxy.GetAngularOffset(r),
                        _galaxy.GetPertN(), _galaxy.GetPertAmp(),
                        {1, 1, 1, 0.2f});
  }

  //
  // Add three circles at the boundaries of core, galaxy and galactic medium
  //

  int pertNum = 0;
  float pertAmp = 0;
  auto r = _galaxy.GetCoreRad();
  AddEllipsisVertices(vert, idx, r, r, 0, pertNum, pertAmp, {1, 1, 0, 0.5});

  r = _galaxy.GetRad();
  AddEllipsisVertices(vert, idx, r, r, 0, pertNum, pertAmp, {0, 1, 0, 0.5});

  r = _galaxy.GetFarFieldRad();
  AddEllipsisVertices(vert, idx, r, r, 0, pertNum, pertAmp, {1, 0, 0, 0.5});

  _vertDensityWaves.CreateBuffer(vert, idx, GL_LINE_STRIP);

  //
  // Update Labels
  //

  _textGalaxyLabels.BeginUpdate();
  _textGalaxyLabels.AddText(1, _GetWindowPos(0, _galaxy.GetCoreRad() + 500.f, 0),
                            "Core");
  _textGalaxyLabels.AddText(
      1, _GetWindowPos(0, _galaxy.GetRad() + 500 + 500.f, 0), "Disk");
  _textGalaxyLabels.AddText(
      1, _GetWindowPos(0, _galaxy.GetFarFieldRad() + 500 + 500.f, 0),
      "Intergalactic medium");
  _textGalaxyLabels.EndUpdate();

  _renderUpdateHint &= ~ruhDENSITY_WAVES;
}

void GlGalaxyState::AddEllipsisVertices(std::vector<VertexColor> &vert,
                                    std::vector<int> &vertIdx, float a, float b,
                                    float angle, uint32_t pertNum,
                                    float pertAmp, Color col) const {
  const int steps = 100;
  const float x = 0;
  const float y = 0;

  // Angle is given by Degree Value
  float beta = -angle * Helper::DEG_TO_RAD;
  float sinbeta = std::sin(beta);
  float cosbeta = std::cos(beta);

  int firstPointIdx = static_cast<int>(vert.size());
  for (int i = 0; i < 360; i += 360 / steps) {
    float alpha = i * Helper::DEG_TO_RAD;
    float sinalpha = std::sin(alpha);
    float cosalpha = std::cos(alpha);

    GLfloat fx =
        (GLfloat)(x + (a * cosalpha * cosbeta - b * sinalpha * sinbeta));
    GLfloat fy =
        (GLfloat)(y + (a * cosalpha * sinbeta + b * sinalpha * cosbeta));

    if (pertNum > 0) {
      fx += (GLfloat)((a / pertAmp) * std::sin(alpha * 2 * pertNum));
      fy += (GLfloat)((a / pertAmp) * std::cos(alpha * 2 * pertNum));
    }

    vertIdx.push_back((int)vert.size());

    VertexColor vc = {fx, fy, 0, col.r, col.g, col.b, col.a};
    vert.push_back(vc);
  }

  // Close the loop and reset the element index array
  vertIdx.push_back(firstPointIdx);
  vertIdx.push_back(0xFFFF);
}