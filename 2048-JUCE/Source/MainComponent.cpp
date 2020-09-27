#include "MainComponent.h"

#include "../../src/2048.h"

//==============================================================================
MainComponent::MainComponent() : qBackground(true), qRoundTiles(true)
{
    e_init (0, 0, 0, 0, 0);
    setSize (340, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    if (qBackground) {
        g.fillAll (juce::Colour(COLOR_BOARD));
    } else {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    }

    for (int y = 0; y < LINE_SIZE; ++y)
	    for (int x = 0; x < LINE_SIZE; ++x)
	        drawTile (g);

	drawFinal(g);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

//==============================================================================
void MainComponent::drawTile (juce::Graphics& g)
{
    
}
    
void MainComponent::drawFinal (juce::Graphics& g)
{
    
}
