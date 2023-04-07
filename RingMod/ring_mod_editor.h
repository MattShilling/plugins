#pragma once

#include "ring_mod_processor.h"

/**
 * @brief Editor.
 */
class RingModEditor : public juce::AudioProcessorEditor {
public:
  explicit RingModEditor(RingModProcessor &);
  ~RingModEditor() override {}

  /**
   * @brief Draw the GUI.
   */
  void paint(juce::Graphics &) override;

  /**
   * @brief Window has been resized.
   */
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  RingModProcessor &processorRef;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RingModEditor)
};
