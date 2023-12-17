#pragma once

#include <raylib.h>

class SfxManager {
public:
  SfxManager();
  ~SfxManager();

  void PlayRotateSound();
  void PlayPutSound();
  void PlayScoreSound();
  void PlaySpeedUpSound();
  void PlayGameOverSound();
private:
  Sound rotateSound;
  Sound putSound;
  Sound scoreSound;
  Sound speedUpSound;
  Sound gameOverSound;
};
