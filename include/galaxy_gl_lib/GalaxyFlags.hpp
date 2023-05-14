#ifndef DISPLAY_FLAG_H
#define DISPLAY_FLAG_H

#include <cstdint>
class GalaxyFlags {
 public:
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
    ruhCREATE_TEXT = 1 << 6
  };
  GalaxyFlags();
  virtual ~GalaxyFlags();
  // Display Flag Setter and Getter

  void setDisplayNoneFlag(bool flag);
  void setDisplayAxisFlag(bool flag);
  void setDisplayStarFlag(bool flag);
  void setDisplayPauseFlag(bool flag);
  void setDisplayHelpFlag(bool flag);
  void setDisplayDensityWavesFlag(bool flag);
  void setDisplayVelocityFlag(bool flag);
  void setDisplayDustFlag(bool flag);
  void setDisplayH2Flag(bool flag);
  void setDisplayFilamentsFlag(bool flag);

          
  bool getDisplayNoneFlag();
  bool getDisplayAxisFlag();
  bool getDisplayStarFlag();
  bool getDisplayPauseFlag();
  bool getDisplayHelpFlag();
  bool getDisplayDensityWavesFlag();
  bool getDisplayVelocityFlag();
  bool getDisplayDustFlag();
  bool getDisplayH2Flag();
  bool getDisplayFilamentsFlag();

  // RenderUpdate Flag Setter and Getter

  void setUpdateNoneFlag(bool flag);
  void setUpdateAxisFlag(bool flag);
  void setUpdateStarFlag(bool flag);
  void setUpdateDensityWavesFlag(bool flag);
  void setUpdateVelocityFlag(bool flag);
  void setUpdateDustFlag(bool flag);
  void setUpdateTextFlag(bool flag);

  bool getUpdateNoneFlag();
  bool getUpdateAxisFlag();
  bool getUpdateStarFlag();
  bool getUpdateDensityWavesFlag();
  bool getUpdateVelocityFlag();
  bool getUpdateDustFlag();
  bool getUpdateTextFlag();
 private:

  uint32_t _renderUpdateHint;
  uint32_t _flags;

  bool getDisplayFlag(DisplayItem res_flag);
  bool getUpdateFlag(RenderUpdateHint res_flag);
  void setDisplayFlag(DisplayItem res_flag);
  void setUpdateFlag(RenderUpdateHint res_flag);

};
#endif /* DISPLAY_FLAG_H*/
