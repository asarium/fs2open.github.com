//
//
#include "wxGraphicsOperations.h"

#if !wxUSE_GLCANVAS
#error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

namespace wxfred {

class wxOpenGLContext: public os::OpenGLContext {
 private:
	static void* loaderFunction(const char* funcName) {
		return SDL_GL_GetProcAddress(funcName);
	}

 public:
	/**
	 * @brief The context constructor. Must have a valid wxGLCanvas as input
	 */
	explicit wxOpenGLContext(wxGLCanvas* win) {
		Assertion(win != nullptr,
				  "Could not create wxOpenGLContext! Must have a valid wxGLCanvas class (or derivative)\n");

		_context.reset(new wxGLContext(win));
	}

	/**
	 * @brief The context deconstructor.
	 */
	~wxOpenGLContext() {
	}

	/**
	 * @brief Gets the OpenGL loader function
	 */
	os::OpenGLLoadProc getLoaderFunction() override {
		return loaderFunction;
	}

	/**
	 * @brief Sets the swap interval, used in vsync modes
	 *
	 * @note Unused by wxFRED
	 * @note This might cause problems. wxWidgets doesn't provide a SwapInterval wrapper, so we'd have to use something
	 *  else to get vsync operational
	 */
	void setSwapInterval(int status) override {
	}

	void makeCurrent(wxGLCanvas* canvas) {
		// This causes issues on Linux if the canvas is not visible at the moment
		Assertion(canvas->IsShown(), "The view port must be visible before making a context current on it!");

		canvas->SetCurrent(*_context);
	}
 private:
	std::unique_ptr<wxGLContext> _context;
};

class wxViewport: public os::Viewport {
	wxWindow* _parentWindow = nullptr;
	std::unique_ptr<wxGLCanvas> _canvas;
	os::ViewPortProperties _properties;

 public:
	wxViewport(wxWindow* parentWindow, const os::ViewPortProperties& props) :
		_parentWindow(parentWindow), _properties(props) {
	}

	SDL_Window* toSDLWindow() override {
		return nullptr;
	}
	std::pair<uint32_t, uint32_t> getSize() override {
		auto size = _canvas->GetSize();
		return std::pair<uint32_t, uint32_t>(size.x, size.y);
	}
	void swapBuffers() override {
		_canvas->SwapBuffers();
	}
	void setState(os::ViewportState state) override {
	}
	void minimize() override {
	}
	void restore() override {
	}

	os::ViewPortProperties getViewportProperties() {
		return _properties;
	}
	wxGLCanvas* getCanvas() {
		return _canvas.get();
	}
	void setCanvas(std::unique_ptr<wxGLCanvas>&& newCanvas) {
		Assertion(_canvas == nullptr, "Can't set new OpenGL canvas!");
		_canvas = std::move(newCanvas);
	}
	wxWindow* getParentWindow() const {
		return _parentWindow;
	}
};

wxGraphicsOperations::wxGraphicsOperations(wxWindow* parent) : _parentWin(parent) {
	SDL_VideoInit(nullptr);

	SDL_GL_LoadLibrary(nullptr);
}
wxGraphicsOperations::~wxGraphicsOperations() {
	SDL_GL_UnloadLibrary();

	SDL_VideoQuit();
}

std::unique_ptr<os::OpenGLContext>
wxGraphicsOperations::createOpenGLContext(os::Viewport* viewport, const os::OpenGLContextAttributes& attrs) {
	wxViewport* wxPort = static_cast<wxViewport*>(viewport);
	auto viewProps = wxPort->getViewportProperties();

	if (wxPort->getCanvas() != nullptr) {
		mprintf(("Calling code tried to create multiple contexts on a single view port. That is not supported by wxWidgets!\n"));
		return nullptr;
	}

	int attributeList[] = { WX_GL_RGBA,
							WX_GL_DOUBLEBUFFER,
							WX_GL_MIN_RED,
							(int) viewProps.pixel_format.red_size,
							WX_GL_MIN_GREEN,
							(int) viewProps.pixel_format.green_size,
							WX_GL_MIN_BLUE,
							(int) viewProps.pixel_format.blue_size,
							WX_GL_MIN_ALPHA,
							(int) viewProps.pixel_format.alpha_size,

							WX_GL_DEPTH_SIZE,
							(int) viewProps.pixel_format.depth_size,
							WX_GL_STENCIL_SIZE,
							(int) viewProps.pixel_format.stencil_size,

							WX_GL_SAMPLE_BUFFERS,
							((viewProps.pixel_format.multi_samples == 0) ? 0 : 1),
							WX_GL_SAMPLES,
							(int) viewProps.pixel_format.multi_samples,    // "4 for 2x2 antialiasing supersampling on most graphics cards "

							WX_GL_MAJOR_VERSION,
							(int) attrs.major_version,
							WX_GL_MINOR_VERSION,
							(int) attrs.minor_version,

							WX_GL_CORE_PROFILE,
							attrs.profile == os::OpenGLProfile::Core ? 1 : 0,
		// Currently unused
		//			0, attrs.flags,

							0    // attributeList must be 0 terminated. :shrug:
	};

	mprintf(("  Requested GL Video values = R: %d, G: %d, B: %d, depth: %d, stencil: %d, double-buffer: %d, FSAA: %d\n", viewProps.pixel_format.red_size, viewProps.pixel_format.green_size, viewProps.pixel_format.blue_size, viewProps.pixel_format.depth_size, viewProps.pixel_format.stencil_size, 1, viewProps.pixel_format.multi_samples));

	auto canvas = std::unique_ptr<wxGLCanvas>(new wxGLCanvas(_parentWin,
															 wxID_ANY,
															 attributeList,
															 wxDefaultPosition,
															 wxSize(viewProps.width, viewProps.height),
															 0,
															 "GLCanvas",
															 wxNullPalette));
	wxPort->setCanvas(std::move(canvas));

	return std::unique_ptr<os::OpenGLContext>(new wxOpenGLContext(wxPort->getCanvas()));
}

void wxGraphicsOperations::makeOpenGLContextCurrent(os::Viewport* view, os::OpenGLContext* ctx) {
	wxViewport* wxPort = static_cast<wxViewport*>(view);
	wxOpenGLContext* wxContext = static_cast<wxOpenGLContext*>(ctx);

	wxPort->getCanvas()->Show();
	wxContext->makeCurrent(wxPort->getCanvas());
}

std::unique_ptr<os::Viewport> wxGraphicsOperations::createViewport(const os::ViewPortProperties& props) {
	if (_mainViewPortCreated) {
		return nullptr;
	}

	_mainViewPortCreated = true;

	return std::unique_ptr<os::Viewport>(new wxViewport(_parentWin, props));
}

}
