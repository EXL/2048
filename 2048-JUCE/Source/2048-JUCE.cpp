/*
  ==============================================================================

    2048-JUCE.cpp
    Created: 28 Sep 2020 1:08:22am
    Author:  exl

  ==============================================================================
*/

#include <JuceHeader.h>

#include "../../src/2048.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class GameComponent  : public juce::Component
{
public:
    //==============================================================================
    GameComponent() : qBackground(true), qRoundTiles(true) 
    {
        e_init (0, 0, 0, 0, 0);
        setSize (340, 400);
    }
    ~GameComponent() override
    {
    }

    //==============================================================================
    void paint (juce::Graphics& g) override
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
    void resized() override
    {
        // This is called when the GameComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

private:
    //==============================================================================
    bool qBackground;
    bool qRoundTiles;
    
    //==============================================================================
    void drawTile (juce::Graphics& g)
    {
    
    }
    
    void drawFinal (juce::Graphics& g)
    {
    
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GameComponent)
};

//==============================================================================
/*
    
    This section contains the basic startup code for a JUCE application.
*/
class Application  : public juce::JUCEApplication
{
public:
    //==============================================================================
    Application() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        gameWindow.reset (new GameWindow (getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        gameWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our GameComponent class.
    */
    class GameWindow    : public juce::DocumentWindow
    {
    public:
        GameWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new GameComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GameWindow)
    };

private:
    std::unique_ptr<GameWindow> gameWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (Application)
