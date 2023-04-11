#include "DisplayFlags.hpp"

DisplayFlag::DisplayFlag()
    : _renderUpdateHint(ruhDENSITY_WAVES | ruhAXIS | ruhSTARS | ruhDUST |
                        ruhCREATE_VELOCITY_CURVE | ruhCREATE_TEXT),
      _flags((int)DisplayItem::STARS | (int)DisplayItem::AXIS |
             (int)DisplayItem::HELP | (int)DisplayItem::DUST |
             (int)DisplayItem::H2 | (int)DisplayItem::FILAMENTS) {}

bool DisplayFlag::getDisplayFlag(DisplayItem get_flag)
{
  bool tmp = (this->_flags & (int)get_flag);
  return tmp;
}
bool DisplayFlag::getRenderFlag(RenderUpdateHint get_flag)
{
  bool tmp = (this->_flags & (int)get_flag);
  /* TODO: maybe remove and add functionality for other classes <10-04-23, nikl>
   */
  this->_renderUpdateHint &= ~(int)get_flag;
  return tmp;
}
void DisplayFlag::setDisplayFlag(DisplayItem set_flag)
{
      this->_flags |= (int)set_flag;
}
void DisplayFlag::setRenderFlag(RenderUpdateHint set_flag)
{
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
