#pragma once

#include "mission/dialogs/ShipEditorDialogModel.h"

#include "ui/FredView.h"

#include <QtWidgets/QDialog>

#include <memory>

namespace fso {
namespace fred {
namespace dialogs {

namespace Ui {
class ShipEditorDialog;
}

class ShipEditorDialog : public QDialog {

 Q_OBJECT
 public:
	explicit ShipEditorDialog(FredView* parent, EditorViewport* viewport);
	~ShipEditorDialog() override;

 protected:
	bool event(QEvent* event) override;

 private:
	void updateUI();

	std::unique_ptr<Ui::ShipEditorDialog> ui;
	std::unique_ptr<ShipEditorDialogModel> _model;
};

}
}
}
