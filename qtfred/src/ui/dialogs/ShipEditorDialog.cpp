//
//

#include "ShipEditorDialog.h"

#include "ui_ShipEditorDialog.h"

#include "ui/util/SignalBlockers.h"

namespace fso {
namespace fred {
namespace dialogs {

ShipEditorDialog::ShipEditorDialog(FredView *parent, EditorViewport *viewport)
    : QDialog(parent), ui(new Ui::ShipEditorDialog()), _model(new ShipEditorDialogModel(this, viewport)) {

	ui->setupUi(this);

	connect(this, &QDialog::accepted, _model.get(), &ShipEditorDialogModel::apply);
	connect(this, &QDialog::rejected, _model.get(), &ShipEditorDialogModel::reject);

	connect(parent, &FredView::viewWindowActivated, _model.get(), &ShipEditorDialogModel::apply);

	connect(_model.get(), &AbstractDialogModel::modelChanged, this, &ShipEditorDialog::updateUI);

	// Resize the dialog to the minimum size
	resize(QDialog::sizeHint());
}

void ShipEditorDialog::updateUI() {
	util::SignalBlockers blockers(this);

	ui->nameEdit->setText(QString::fromStdString(_model->getShipName()));
}

ShipEditorDialog::~ShipEditorDialog() = default;

bool ShipEditorDialog::event(QEvent* event) {
	switch(event->type()) {
	case QEvent::WindowDeactivate:
		_model->apply();
		event->accept();
		return true;
	default:
		return QDialog::event(event);
	}
}
}
}
}
