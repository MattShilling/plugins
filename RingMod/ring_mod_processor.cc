#include <cmath>

#include "ring_mod_editor.h"
#include "ring_mod_processor.h"

//==============================================================================
void RingModProcessor::prepareToPlay([[maybe_unused]] double sampleRate,
                                     [[maybe_unused]] int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
}

void RingModProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

bool RingModProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo()) {
    return false;
  }

  // This checks if the input layout matches the output layout
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet()) {
    return false;
  }

  return true;
}

static float sgn(float x) {
  if (x < 0) {
    return -1.0;
  }
  if (x > 0) {
    return 1.0;
  }
  return 0.0;
}

void RingModProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                    juce::MidiBuffer &midiMessages) {
  juce::ignoreUnused(midiMessages);

  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  // Clear any output channels that didn't contain corresponding input data,
  // (because these aren't guaranteed to be empty - they may contain garbage).
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i) {
    buffer.clear(i, 0, buffer.getNumSamples());
  }

  // Compute phase step per sample.
  constexpr float frequency = 1000.0;
  const float phase_step = juce::MathConstants<float>::twoPi * frequency /
                           static_cast<float>(getSampleRate());

  for (int sample_idx = 0; sample_idx < buffer.getNumSamples(); ++sample_idx) {
    // Compute carrier for left and right channels.
    float sine[2] = {std::sin(phase_),
                     // Apply phase offset to the right channel.
                     std::sin(phase_ + phase_offset_)};
    float square[2] = {sgn(sine[0]), sgn(sine[1])};

    // Update phase.
    phase_ = std::fmod(phase_ + phase_step, juce::MathConstants<float>::twoPi);

    for (int channel_idx = 0; channel_idx < num_channels; ++channel_idx) {
      // Get input sample.
      float input_sample = buffer.getSample(channel_idx, sample_idx);

      // Apply ring modulation.
      float processed_sample = input_sample * square[channel_idx];

      // Apply dry/wet mix.
      float output_sample =
          input_sample * (1.0f - mix_) + processed_sample * mix_;

      // Set output sample.
      buffer.setSample(channel_idx, sample_idx, output_sample);
    }
  }
}

//==============================================================================

juce::AudioProcessorEditor *RingModProcessor::createEditor() {
  return new RingModEditor(*this);
}

//==============================================================================
void RingModProcessor::getStateInformation(juce::MemoryBlock &destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
  juce::ignoreUnused(destData);
}

void RingModProcessor::setStateInformation(const void *data, int sizeInBytes) {
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
  juce::ignoreUnused(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new RingModProcessor();
}
