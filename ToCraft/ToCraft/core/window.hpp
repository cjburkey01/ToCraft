#ifndef window_hpp
#define window_hpp

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
	
public:
	Window();				// Default constructor.
	bool initWindow();		// Called to initialize the window. Returns true on success, false on failure.
	void destroyWindow();	// Destroys the window.
	void showWindow();		// Makes the window visible.
	void hideWindow();		// Makes the window hidden.
	void cleanUp();			// Destroys the window if it still exists, and terminates GLFW.
	void beginRender();		// Starts the rendering process.
	void finishRender();	// Finishes the rendering process.
	bool doesWindowExist();	// Returns whether or not the window has either not been created or has been cleaned up.
	bool shouldClose();		// Returns whether or not GLFW says this window should close.
	int getWidth();			// Returns the pixel width of the window.
	int getHeight();		// Returns the pixel height of the window.
	int getScreenWidth();	// Returns the screen width of the window.
	int getScreenHeight();	// Returns the screen height of the window.
	void setHalfSize();		// Sets the window's size to half of the screen's size.
	void centerOnScreen();	// Centers the window on the screen.
	static void onScreenSizeChange(GLFWwindow* window, int width, int height);		// Called when the window is resized, stores screen space coords.
	static void onFrameBufferSizeChange(GLFWwindow* window, int width, int height);	// Called when the window is resized, stores pixel coords.
	
private:
	const GLFWvidmode* getVidMode();	// Returns the VidMode pointer.
	GLFWwindow* window;		// Reference to GLFW window.
	bool exists;			// Whether or not the window exists.
	
};

#endif
