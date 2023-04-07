#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class RingModProcessor : public juce::AudioProcessor {
public:
  RingModProcessor()
      : AudioProcessor(
            BusesProperties()
                .withInput("Input", juce::AudioChannelSet::stereo(), true)
                .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
        phase_(0.0), phase_offset_(0.0), mix_(1.0) {}

  ~RingModProcessor() override {}

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
  using AudioProcessor::processBlock;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override { return true; }

  //==============================================================================
  const juce::String getName() const override { return JucePlugin_Name; }

  bool acceptsMidi() const override { return false; }

  bool producesMidi() const override { return false; }

  bool isMidiEffect() const override { return false; }

  double getTailLengthSeconds() const override { return 0.0; }

  //==============================================================================

  int getNumPrograms() override { return 1; }

  int getCurrentProgram() override { return 0; }

  void setCurrentProgram([[maybe_unused]] int index) override {}

  const juce::String getProgramName([[maybe_unused]] int index) override {
    return {};
  }

  void
  changeProgramName([[maybe_unused]] int index,
                    [[maybe_unused]] const juce::String &newName) override {}

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

private:
  //==============================================================================
  static constexpr int num_channels = 2;

  float phase_;
  float phase_offset_;

  float mix_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RingModProcessor)
};
