#pragma once

#include <osapi/osapi.h>

#include <wx/glcanvas.h>

namespace wxfred {

class wxGraphicsOperations : public os::GraphicsOperations {
	wxWindow* _parentWin = nullptr;

	bool _mainViewPortCreated = false; //!< Only one view port may be created at the moment
 public:
	wxGraphicsOperations(wxWindow* parent);
	~wxGraphicsOperations();

	std::unique_ptr<os::OpenGLContext>
	createOpenGLContext(os::Viewport* viewport, const os::OpenGLContextAttributes& gl_attrs) override;

	void makeOpenGLContextCurrent(os::Viewport* view, os::OpenGLContext* ctx) override;

	std::unique_ptr<os::Viewport> createViewport(const os::ViewPortProperties& props) override;
};

}
