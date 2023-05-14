#ifndef DISPLAY_FLAG_H
#define DISPLAY_FLAG_H

#include <cstdint>
class DisplayFlag {
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

  uint32_t _renderUpdateHint;
  uint32_t _flags;

  bool getDisplayFlag(DisplayItem res_flag);
  bool getRenderFlag(RenderUpdateHint res_flag);
  void setDisplayFlag(DisplayItem res_flag);
  void setRenderFlag(RenderUpdateHint res_flag);

 public:
  DisplayFlag();
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

  void setRenderNoneFlag(bool flag);
  void setRenderAxisFlag(bool flag);
  void setRenderStarFlag(bool flag);
  void setRenderDesityWavesFlag(bool flag);
  void setRenderVelocityFlag(bool flag);
  void setRenderDustFlag(bool flag);
  void setRenderTextFlag(bool flag);

  bool getRenderNoneFlag();
  bool getRenderAxisFlag();
  bool getRenderStarFlag();
  bool getRenderDesityWavesFlag();
  bool getRenderVelocityFlag();
  bool getRenderDustFlag();
  bool getRenderTextFlag();
  virtual ~DisplayFlag();
};
#endif /* DISPLAY_FLAG_H*/
