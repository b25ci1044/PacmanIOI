#pragma once

#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>

static const unsigned SAMPLE_RATE = 44100;

inline float blopSoundValue(float t, float d) {
  float frequency = 480.f + 320.f * (t / d);
  float wave = std::sin(2 * 3.14159f * frequency * t);
  float envelope = std::exp(-t * 28.f);
  float result = wave * envelope;
  return result;
}

inline float powerupSoundValue(float t, float d) {
  float f = 300.f + 900.f * (t / d);

  float e = 0.0f;
  if (t < d * 0.5f) {
    e = t / (d * 0.5f);
  } else {
    e = std::exp(-(t - d * 0.5f) * 8.f);
  }

  float wave1 = std::sin(2 * 3.14159f * f * t);
  float wave2 = 0.4f * std::sin(4 * 3.14159f * f * t);
  float result = (wave1 + wave2) * e;
  return result;
}

inline float shieldSoundValue(float t, float d) {
  float e = std::exp(-t * 5.f);
  float wave1 = std::sin(2 * 3.14159f * 523.f * t);
  float wave2 = std::sin(2 * 3.14159f * 659.f * t);
  float wave3 = std::sin(2 * 3.14159f * 784.f * t);
  float result = (wave1 + wave2 + wave3) / 3.f * e;
  return result;
}

inline float ghostEatSoundValue(float t, float d) {
  float f = 600.f * std::exp(-t * 9.f) + 80.f;
  float e = std::exp(-t * 12.f);
  float wave1 = std::sin(2 * 3.14159f * f * t);
  float wave2 = std::sin(2 * 3.14159f * f * 2.7f * t) * 0.4f;
  float result = (wave1 + wave2) * e;
  return result;
}

inline float deathSoundValue(float t, float d) {
  float f = 600.f * std::pow(0.15f, t / d);

  float e = 0.0f;
  if (t < 0.1f) {
    e = t / 0.1f;
  } else {
    e = std::exp(-(t - 0.1f) * 2.2f);
  }

  float vibrato = 1.f + 0.04f * std::sin(2 * 3.14159f * 8.f * t);
  float result = std::sin(2 * 3.14159f * f * vibrato * t) * e;
  return result;
}

inline sf::SoundBuffer makeBlopSound()
{
  float duration_of_sound = 0.055f;
  float volume_level = 0.35f;

  unsigned total_samples = (unsigned)(SAMPLE_RATE * duration_of_sound);

  std::vector<int16_t> sample_data(total_samples);

  unsigned i = 0;
  while (i < total_samples) {
    float t = i / (float)SAMPLE_RATE;
    float v = blopSoundValue(t, duration_of_sound) * volume_level;

    if (v > 1.f) { v = 1.f; }
    if (v < -1.f) { v = -1.f; }

    sample_data[i] = (int16_t)(v * 32767.f);

    i = i + 1;
  }

  sf::SoundBuffer buf;
  if (!buf.loadFromSamples(sample_data.data(), total_samples, 1, SAMPLE_RATE, {sf::SoundChannel::Mono})) {
    std::cerr << "Failed to load blop sound buffer" << std::endl;
  }
  return buf;
}

inline sf::SoundBuffer makePowerupSound()
{
  float duration_of_sound = 0.38f;
  float volume_level = 0.55f;
  unsigned total_samples = (unsigned)(SAMPLE_RATE * duration_of_sound);
  std::vector<int16_t> sample_data(total_samples);

  unsigned i = 0;
  while (i < total_samples) {
    float t = i / (float)SAMPLE_RATE;
    float v = powerupSoundValue(t, duration_of_sound) * volume_level;
    if (v > 1.f) { v = 1.f; }
    if (v < -1.f) { v = -1.f; }
    sample_data[i] = (int16_t)(v * 32767.f);
    i = i + 1;
  }

  sf::SoundBuffer buf;
  if (!buf.loadFromSamples(sample_data.data(), total_samples, 1, SAMPLE_RATE, {sf::SoundChannel::Mono})) {
    std::cerr << "Failed to load powerup sound buffer" << std::endl;
  }
  return buf;
}

inline sf::SoundBuffer makeShieldSound()
{
  float duration_of_sound = 0.5f;
  float volume_level = 0.6f;
  unsigned total_samples = (unsigned)(SAMPLE_RATE * duration_of_sound);
  std::vector<int16_t> sample_data(total_samples);


  unsigned i = 0;
  while (i < total_samples) {
    float t = i / (float)SAMPLE_RATE;
    float v = shieldSoundValue(t, duration_of_sound) * volume_level;
    if (v > 1.f) { v = 1.f; }
    if (v < -1.f) { v = -1.f; }
    sample_data[i] = (int16_t)(v * 32767.f);
    i = i + 1;
  }

  sf::SoundBuffer buf;
  if (!buf.loadFromSamples(sample_data.data(), total_samples, 1, SAMPLE_RATE, {sf::SoundChannel::Mono})) {
    std::cerr << "Failed to load shield sound buffer" << std::endl;
  }
  return buf;
}

inline sf::SoundBuffer makeGhostEatSound()
{
  float duration_of_sound = 0.28f;
  float volume_level = 0.7f;
  unsigned total_samples = (unsigned)(SAMPLE_RATE * duration_of_sound);
  std::vector<int16_t> sample_data(total_samples);

  unsigned i = 0;
  while (i < total_samples) {
    float t = i / (float)SAMPLE_RATE;
    float v = ghostEatSoundValue(t, duration_of_sound) * volume_level;
    if (v > 1.f) { v = 1.f; }
    if (v < -1.f) { v = -1.f; }
    sample_data[i] = (int16_t)(v * 32767.f);
    i = i + 1;
  }

  sf::SoundBuffer buf;
  if (!buf.loadFromSamples(sample_data.data(), total_samples, 1, SAMPLE_RATE, {sf::SoundChannel::Mono})) {
    std::cerr << "Failed to load ghost eat sound buffer" << std::endl;
  }
  return buf;
}

inline sf::SoundBuffer makeDeathSound()
{
  float duration_of_sound = 1.1f;
  float volume_level = 0.8f;
  unsigned total_samples = (unsigned)(SAMPLE_RATE * duration_of_sound);
  std::vector<int16_t> sample_data(total_samples);

  unsigned i = 0;
  while (i < total_samples) {
    float t = i / (float)SAMPLE_RATE;
    float v = deathSoundValue(t, duration_of_sound) * volume_level;
    if (v > 1.f) { v = 1.f; }
    if (v < -1.f) { v = -1.f; }
    sample_data[i] = (int16_t)(v * 32767.f);
    i = i + 1;
  }

  sf::SoundBuffer buf;
  if (!buf.loadFromSamples(sample_data.data(), total_samples, 1, SAMPLE_RATE, {sf::SoundChannel::Mono})) {
    std::cerr << "Failed to load death sound buffer" << std::endl;
  }
  return buf;
}

inline sf::SoundBuffer makeWinSound()
{
  float note_frequencies[4];
  note_frequencies[0] = 523.25f;
  note_frequencies[1] = 659.25f;
  note_frequencies[2] = 783.99f;
  note_frequencies[3] = 1046.5f;

  float total_duration = 1.2f;
  unsigned total_number_of_samples = (unsigned)(SAMPLE_RATE * total_duration);
  std::vector<int16_t> sample_data(total_number_of_samples, 0);

  int note_index = 0;
  while (note_index < 4)
  {
    float start_time = note_index * 0.22f;
    float freq = note_frequencies[note_index];

    unsigned sample_index = 0;
    while (sample_index < total_number_of_samples)
    {
      float t = sample_index / (float)SAMPLE_RATE - start_time;

      if (t < 0 || t > 0.35f) {
        sample_index = sample_index + 1;
        continue;
      }

      float e = 0.0f;
      if (t < 0.01f) {
        e = t / 0.01f;
      } else {
        e = std::exp(-(t - 0.01f) * 4.5f);
      }

      float wave1 = std::sin(2 * 3.14159f * freq * t);
      float wave2 = 0.5f * std::sin(4 * 3.14159f * freq * t);
      float wave3 = 0.25f * std::sin(6 * 3.14159f * freq * t);
      float v = (wave1 + wave2 + wave3) / 1.75f * e * 0.7f;

      if (v > 1.f) { v = 1.f; }
      if (v < -1.f) { v = -1.f; }

      sample_data[sample_index] = sample_data[sample_index] + (int16_t)(v * 32767.f);

      sample_index = sample_index + 1;
    }

    note_index = note_index + 1;
  }

  sf::SoundBuffer buf;
  if (!buf.loadFromSamples(sample_data.data(), total_number_of_samples, 1, SAMPLE_RATE, {sf::SoundChannel::Mono})) {
    std::cerr << "Failed to load win sound buffer from samples" << std::endl;
  }
  return buf;
}
