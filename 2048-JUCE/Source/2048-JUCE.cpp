/*
  ==============================================================================

    2048-JUCE.cpp
    Created: 28 Sep 2020 1:08:22am
    Author:  exl

  ==============================================================================
*/

#include <JuceHeader.h>

#include "../../src/2048.h"

static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class GameComponent : public juce::Component, public juce::KeyListener
{
public:
    //==============================================================================
    GameComponent() : qBackground(true), qRoundTiles(true) 
    {
        e_init (juce::KeyPress::escapeKey, juce::KeyPress::leftKey, juce::KeyPress::rightKey, juce::KeyPress::upKey, juce::KeyPress::downKey);
        setSize (340, 400);
    }

    ~GameComponent() override
    {
    }

    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        if (qBackground) {
            g.fillAll (juce::Colour (COLOR_BOARD));
        } else {
            // (Our component is opaque, so we must completely fill the background with a solid colour)
            g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
        }
        
        const auto rect = getLocalBounds();

        for (int y = 0; y < LINE_SIZE; ++y)
	        for (int x = 0; x < LINE_SIZE; ++x)
	            drawTile (g, rect, e_board[x + y * LINE_SIZE], x, y);

	    drawFinal (g, rect);
    }

    void resized() override
    {
        // This is called when the GameComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

    bool keyPressed (const juce::KeyPress &key, juce::Component *originatingComponent) override
    {
        if (key.isValid())
        {
            e_key (key.getKeyCode());
            repaint();
        }
        return true;
    }

private:
    //==============================================================================
    bool qBackground;
    bool qRoundTiles;
    
    //==============================================================================
    void drawTile (juce::Graphics& g, const juce::Rectangle<int>& rect, int value, int x, int y)
    {
        const int xOffset = offsetCoord (x, rect.getWidth(), 0), yOffset = offsetCoord (y, rect.getHeight(), TILE_MARGIN * 2);
        g.setColour (juce::Colour (e_background (value)));
        if (qRoundTiles)
            g.fillRoundedRectangle (xOffset, yOffset, TILE_SIZE, TILE_SIZE, 10);
        else
            g.fillRect (xOffset, yOffset, TILE_SIZE, TILE_SIZE);
        if (value)
        {
            const int size = (value < 100) ? 32 : (value < 1000) ? 28 : 22;
            const auto font = juce::Font (size, juce::Font::bold);
            const auto strValue = juce::String (value);
            g.setColour (juce::Colour (e_foreground (value)));
            g.setFont (font);
            const int w = font.getStringWidth (strValue), h = (value < 100) ? size - 6 : (value < 1000) ? size - 4 : size - 5;
            g.drawSingleLineText (strValue, xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2);
        }
    }
    
    void drawFinal (juce::Graphics& g, const juce::Rectangle<int>& rect)
    {
        const int width = rect.getWidth(), height = rect.getHeight();
        if (e_win || e_lose)
        {
            g.setColour (juce::Colour (COLOR_OVERLAY));
            g.setOpacity (0.5f);
            g.fillRect (rect);
            const juce::String strFinal = (e_win) ? "You Won!" : "Game Over!";
            const auto font = juce::Font (32, juce::Font::bold);
            g.setColour (juce::Colour (COLOR_FINAL));
            g.setFont (font);
            const int w = font.getStringWidth (strFinal);
            g.drawSingleLineText (strFinal, width / 2 - w / 2, height / 2);
        }
        g.setColour (juce::Colour (COLOR_TEXT));
        const auto font = juce::Font (22);
        g.setFont (font);
        const juce::String strScore = juce::String("Score: ") + juce::String (e_score);
        const int w = font.getStringWidth (strScore);
        g.drawSingleLineText ("ESC to Restart!", TILE_MARGIN, height - 20);
        g.drawSingleLineText (strScore, width - w - TILE_MARGIN, height - 20);
    }
    
    inline int offsetCoord(int coord, int size, int offset) {
		const int start = (size / 2) - (((TILE_SIZE * LINE_SIZE) + (TILE_MARGIN * (LINE_SIZE - 1))) / 2);
		return coord * (TILE_MARGIN + TILE_SIZE) + start - offset;
	}

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GameComponent)
};

//==============================================================================
/*
    
    This section contains the basic startup code for a JUCE application.
*/
class Application : public juce::JUCEApplication
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
    class GameWindow : public juce::DocumentWindow
    {
    public:
        GameWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            const auto gameComponent = new GameComponent();
            setContentOwned (gameComponent, true);
            addKeyListener (gameComponent);

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
