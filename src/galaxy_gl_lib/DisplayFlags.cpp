#include "DisplayFlags.hpp"

DisplayFlag::DisplayFlag()
    : _renderUpdateHint(ruhDENSITY_WAVES | ruhAXIS | ruhSTARS | ruhDUST |
                        ruhCREATE_VELOCITY_CURVE | ruhCREATE_TEXT),
      _flags((int)DisplayItem::STARS | (int)DisplayItem::AXIS |
             (int)DisplayItem::HELP | (int)DisplayItem::DUST |
             (int)DisplayItem::H2 | (int)DisplayItem::FILAMENTS) {}

bool DisplayFlag::getDisplayFlag(DisplayItem get_flag) {
  bool tmp = (this->_flags & (int)get_flag);
  return tmp;
}
bool DisplayFlag::getRenderFlag(RenderUpdateHint get_flag) {
  bool tmp = (this->_flags & (int)get_flag);
  /* TODO: maybe remove and add functionality for other classes <10-04-23, nikl>
   */
  this->_renderUpdateHint &= ~(int)get_flag;
  return tmp;
}
void DisplayFlag::setDisplayFlag(DisplayItem set_flag) {
  this->_flags |= (int)set_flag;
}
void DisplayFlag::setRenderFlag(RenderUpdateHint set_flag) {
  this->_renderUpdateHint |= (int)set_flag;
}

bool DisplayFlag::getDisplayAxisFlag() {
  return this->getDisplayFlag(DisplayItem::AXIS);
}
bool DisplayFlag::getDisplayStarFlag() {
  return this->getDisplayFlag(DisplayItem::STARS);
}
bool DisplayFlag::getDisplayPauseFlag() {
  return this->getDisplayFlag(DisplayItem::PAUSE);
}
bool DisplayFlag::getDisplayH2Flag() {
  return this->getDisplayFlag(DisplayItem::H2);
}
bool DisplayFlag::getDisplayDustFlag() {
  return this->getDisplayFlag(DisplayItem::DUST);
}
bool DisplayFlag::getDisplayHelpFlag() {
  return this->getDisplayFlag(DisplayItem::HELP);
}
bool DisplayFlag::getDisplayNoneFlag() {
  return this->getDisplayFlag(DisplayItem::NONE);
}
bool DisplayFlag::getDisplayVelocityFlag() {
  return this->getDisplayFlag(DisplayItem::VELOCITY);
}
bool DisplayFlag::getDisplayFilamentsFlag() {
  return this->getDisplayFlag(DisplayItem::FILAMENTS);
}
bool DisplayFlag::getDisplayDensityWavesFlag() {
  return this->getDisplayFlag(DisplayItem::DENSITY_WAVES);
}

void DisplayFlag::setDisplayAxisFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::AXIS);
}
void DisplayFlag::setDisplayStarFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::STARS);
}
void DisplayFlag::setDisplayPauseFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::PAUSE);
}
void DisplayFlag::setDisplayH2Flag(bool flag) {
  return this->setDisplayFlag(DisplayItem::H2);
}
void DisplayFlag::setDisplayDustFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::DUST);
}
void DisplayFlag::setDisplayHelpFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::HELP);
}
void DisplayFlag::setDisplayNoneFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::NONE);
}
void DisplayFlag::setDisplayVelocityFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::VELOCITY);
}
void DisplayFlag::setDisplayFilamentsFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::FILAMENTS);
}
void DisplayFlag::setDisplayDensityWavesFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::DENSITY_WAVES);
}

bool DisplayFlag::getRenderAxisFlag() {
  return this->getRenderFlag(RenderUpdateHint::ruhAXIS);
}
bool DisplayFlag::getRenderStarFlag() {
  return this->getRenderFlag(RenderUpdateHint::ruhSTARS);
}
bool DisplayFlag::getRenderDustFlag() {
  return this->getRenderFlag(RenderUpdateHint::ruhDUST);
}
bool DisplayFlag::getRenderNoneFlag() {
  return this->getRenderFlag(RenderUpdateHint::ruhNONE);
}
bool DisplayFlag::getRenderVelocityFlag() {
  return this->getRenderFlag(RenderUpdateHint::ruhCREATE_VELOCITY_CURVE);
}
bool DisplayFlag::getRenderDesityWavesFlag() {
  return this->getRenderFlag(RenderUpdateHint::ruhDENSITY_WAVES);
}
bool DisplayFlag::getRenderTextFlag() {
  return this->getRenderFlag(RenderUpdateHint::ruhCREATE_TEXT);
}


void DisplayFlag::setRenderAxisFlag(bool flag) {
  this->setRenderFlag(RenderUpdateHint::ruhAXIS);
}
void DisplayFlag::setRenderStarFlag(bool flag) {
  this->setRenderFlag(RenderUpdateHint::ruhSTARS);
}
void DisplayFlag::setRenderDustFlag(bool flag) {
  this->setRenderFlag(RenderUpdateHint::ruhDUST);
}
void DisplayFlag::setRenderNoneFlag(bool flag) {
  this->setRenderFlag(RenderUpdateHint::ruhNONE);
}
void DisplayFlag::setRenderVelocityFlag(bool flag) {
  this->setRenderFlag(RenderUpdateHint::ruhCREATE_VELOCITY_CURVE);
}
void DisplayFlag::setRenderDesityWavesFlag(bool flag) {
  this->setRenderFlag(RenderUpdateHint::ruhDENSITY_WAVES);
}
void DisplayFlag::setRenderTextFlag(bool flag) {
  this->setRenderFlag(RenderUpdateHint::ruhCREATE_TEXT);
}
