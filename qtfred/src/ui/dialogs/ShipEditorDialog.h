#pragma once

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
	explicit ShipEditorDialog(QWidget* parent = nullptr, const Qt::WindowFlags& f = Qt::WindowFlags());
	~ShipEditorDialog() override;

 private:
	std::unique_ptr<Ui::ShipEditorDialog> ui;
};

}
}
}
