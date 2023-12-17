#include "sfx_manager.hpp"

SfxManager::SfxManager() {
  InitAudioDevice();
  rotateSound = LoadSound("resources/sfx/rotate.wav");
  putSound = LoadSound("resources/sfx/block_put.wav");
  speedUpSound = LoadSound("resources/sfx/speed_up.wav");
  scoreSound = LoadSound("resources/sfx/score.wav");
  gameOverSound = LoadSound("resources/sfx/game_over.wav");
}

SfxManager::~SfxManager() {
  UnloadSound(rotateSound);
  UnloadSound(putSound);
  UnloadSound(speedUpSound);
  UnloadSound(scoreSound);
  UnloadSound(gameOverSound);
  CloseAudioDevice();
}

void SfxManager::PlayRotateSound() {
  PlaySound(rotateSound);
}

void SfxManager::PlayPutSound() {
  PlaySound(putSound);
}

void SfxManager::PlayScoreSound() {
  PlaySound(scoreSound);
}

void SfxManager::PlaySpeedUpSound() {
  PlaySound(speedUpSound);
}

void SfxManager::PlayGameOverSound() {
  PlaySound(gameOverSound);
}
