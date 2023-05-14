#include "GalaxyFlags.hpp"

GalaxyFlags::GalaxyFlags()
    : _renderUpdateHint(ruhDENSITY_WAVES | ruhAXIS | ruhSTARS | ruhDUST |
                        ruhCREATE_VELOCITY_CURVE | ruhCREATE_TEXT),
      _flags((int)DisplayItem::STARS | (int)DisplayItem::AXIS |
             (int)DisplayItem::HELP | (int)DisplayItem::DUST |
             (int)DisplayItem::H2 | (int)DisplayItem::FILAMENTS) {}

bool GalaxyFlags::getDisplayFlag(DisplayItem get_flag) {
  return (this->_flags & (int)get_flag);
}
bool GalaxyFlags::getUpdateFlag(RenderUpdateHint get_flag) {
  return (this->_flags & (int)get_flag);
}
void GalaxyFlags::setDisplayFlag(DisplayItem set_flag) {
  this->_flags |= (int)set_flag;
}
void GalaxyFlags::setUpdateFlag(RenderUpdateHint set_flag) {
  this->_renderUpdateHint |= (int)set_flag;
}

bool GalaxyFlags::getDisplayAxisFlag() {
  return this->getDisplayFlag(DisplayItem::AXIS);
}
bool GalaxyFlags::getDisplayStarFlag() {
  return this->getDisplayFlag(DisplayItem::STARS);
}
bool GalaxyFlags::getDisplayPauseFlag() {
  return this->getDisplayFlag(DisplayItem::PAUSE);
}
bool GalaxyFlags::getDisplayH2Flag() {
  return this->getDisplayFlag(DisplayItem::H2);
}
bool GalaxyFlags::getDisplayDustFlag() {
  return this->getDisplayFlag(DisplayItem::DUST);
}
bool GalaxyFlags::getDisplayHelpFlag() {
  return this->getDisplayFlag(DisplayItem::HELP);
}
bool GalaxyFlags::getDisplayNoneFlag() {
  return this->getDisplayFlag(DisplayItem::NONE);
}
bool GalaxyFlags::getDisplayVelocityFlag() {
  return this->getDisplayFlag(DisplayItem::VELOCITY);
}
bool GalaxyFlags::getDisplayFilamentsFlag() {
  return this->getDisplayFlag(DisplayItem::FILAMENTS);
}
bool GalaxyFlags::getDisplayDensityWavesFlag() {
  return this->getDisplayFlag(DisplayItem::DENSITY_WAVES);
}

void GalaxyFlags::setDisplayAxisFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::AXIS);
}
void GalaxyFlags::setDisplayStarFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::STARS);
}
void GalaxyFlags::setDisplayPauseFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::PAUSE);
}
void GalaxyFlags::setDisplayH2Flag(bool flag) {
  return this->setDisplayFlag(DisplayItem::H2);
}
void GalaxyFlags::setDisplayDustFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::DUST);
}
void GalaxyFlags::setDisplayHelpFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::HELP);
}
void GalaxyFlags::setDisplayNoneFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::NONE);
}
void GalaxyFlags::setDisplayVelocityFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::VELOCITY);
}
void GalaxyFlags::setDisplayFilamentsFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::FILAMENTS);
}
void GalaxyFlags::setDisplayDensityWavesFlag(bool flag) {
  return this->setDisplayFlag(DisplayItem::DENSITY_WAVES);
}

bool GalaxyFlags::getUpdateAxisFlag() {
  return this->getUpdateFlag(RenderUpdateHint::ruhAXIS);
}
bool GalaxyFlags::getUpdateStarFlag() {
  return this->getUpdateFlag(RenderUpdateHint::ruhSTARS);
}
bool GalaxyFlags::getUpdateDustFlag() {
  return this->getUpdateFlag(RenderUpdateHint::ruhDUST);
}
bool GalaxyFlags::getUpdateNoneFlag() {
  return this->getUpdateFlag(RenderUpdateHint::ruhNONE);
}
bool GalaxyFlags::getUpdateVelocityFlag() {
  return this->getUpdateFlag(RenderUpdateHint::ruhCREATE_VELOCITY_CURVE);
}
bool GalaxyFlags::getUpdateDensityWavesFlag() {
  return this->getUpdateFlag(RenderUpdateHint::ruhDENSITY_WAVES);
}
bool GalaxyFlags::getUpdateTextFlag() {
  return this->getUpdateFlag(RenderUpdateHint::ruhCREATE_TEXT);
}


void GalaxyFlags::setUpdateAxisFlag(bool flag) {
  this->setUpdateFlag(RenderUpdateHint::ruhAXIS);
}
void GalaxyFlags::setUpdateStarFlag(bool flag) {
  this->setUpdateFlag(RenderUpdateHint::ruhSTARS);
}
void GalaxyFlags::setUpdateDustFlag(bool flag) {
  this->setUpdateFlag(RenderUpdateHint::ruhDUST);
}
void GalaxyFlags::setUpdateNoneFlag(bool flag) {
  this->setUpdateFlag(RenderUpdateHint::ruhNONE);
}
void GalaxyFlags::setUpdateVelocityFlag(bool flag) {
  this->setUpdateFlag(RenderUpdateHint::ruhCREATE_VELOCITY_CURVE);
}
void GalaxyFlags::setUpdateDensityWavesFlag(bool flag) {
  this->setUpdateFlag(RenderUpdateHint::ruhDENSITY_WAVES);
}
void GalaxyFlags::setUpdateTextFlag(bool flag) {
  this->setUpdateFlag(RenderUpdateHint::ruhCREATE_TEXT);
}
