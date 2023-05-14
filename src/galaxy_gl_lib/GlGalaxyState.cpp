#include "GlGalaxyState.hpp"
void GlGalaxyState::addEllipsisVertices(std::vector<VertexColor> &vert,
                                        std::vector<int> &vertIdx, float a,
                                        float b, float angle, uint32_t pertNum,
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

GlGalaxyState::GlGalaxyState(
    std::function<glm::vec2(GLfloat, GLfloat, GLfloat)> windowPosFunc)
    : _galaxy(),
      _vertDensityWaves(2),
      _vertVelocityCurve(1, GL_DYNAMIC_DRAW),
      _vertStars(GL_FUNC_ADD, GL_ONE) {
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
  _vertVelocityCurve.Release();
  _vertStars.Release();
}

void GlGalaxyState::initSimulation() {
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

void GlGalaxyState::update(GalaxyFlags gflags) {
	//TODO
}

//
//
// Individual update wrapper
//
//

void GlGalaxyState::updateStars() {
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

void GlGalaxyState::updateVelocityCurve(float timeStepSize) {
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
}

void GlGalaxyState::updateDensityWaves() {
  std::vector<VertexColor> vert;
  std::vector<int> idx;

  //
  // First add the density waves
  //

  int num = 100;
  float dr = _galaxy.GetFarFieldRad() / num;
  for (int i = 0; i <= num; ++i) {
    float r = dr * (i + 1);
    addEllipsisVertices(vert, idx, r, r * _galaxy.GetExcentricity(r),
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
  addEllipsisVertices(vert, idx, r, r, 0, pertNum, pertAmp, {1, 1, 0, 0.5});

  r = _galaxy.GetRad();
  addEllipsisVertices(vert, idx, r, r, 0, pertNum, pertAmp, {0, 1, 0, 0.5});

  r = _galaxy.GetFarFieldRad();
  addEllipsisVertices(vert, idx, r, r, 0, pertNum, pertAmp, {1, 0, 0, 0.5});

  _vertDensityWaves.CreateBuffer(vert, idx, GL_LINE_STRIP);
}

