//
//

#include "ShipEditorDialog.h"

#include "ui_ShipEditorDialog.h"

namespace fso {
namespace fred {
namespace dialogs {

ShipEditorDialog::ShipEditorDialog(QWidget* parent, const Qt::WindowFlags& f) :
	QDialog(parent, f), ui(new Ui::ShipEditorDialog()) {
	// Since this dialog is modeless it needs to be deleted when it is closed
	setAttribute(Qt::WA_DeleteOnClose);

	ui->setupUi(this);

	// Resize the dialog to the minimum size
	resize(QDialog::sizeHint());
}
ShipEditorDialog::~ShipEditorDialog() = default;

}
}
}
