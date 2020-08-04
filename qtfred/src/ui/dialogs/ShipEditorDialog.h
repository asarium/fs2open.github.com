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

  public:
	void accept() override;
	void reject() override;

  private:
	void applyChanges();

	std::unique_ptr<Ui::ShipEditorDialog> ui;

	SCP_string m_ship_name;
	SCP_string m_cargo1;
	bool m_single_mission = false;  // indicates if single player(1) or multiplayer(0)
	int m_ship_class = -1;
	int m_team = -1;
	int m_arrival_location = -1;
	int m_departure_location = -1;
	int m_ai_class = -1;
	int m_hotkey = -1;
	bool m_update_arrival = false;
	bool m_update_departure = false;
	int m_arrival_target = -1;
	int m_departure_target = -1;
	int m_persona = -1;

	bool multi_edit = false;

	void initialize_data();
};

}
}
}
