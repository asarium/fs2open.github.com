#pragma once
//
//


#include "AbstractDialogModel.h"

namespace fso {
namespace fred {
namespace dialogs {


class ShipEditorDialogModel : public AbstractDialogModel {
 public:
	ShipEditorDialogModel(QObject* parent, EditorViewport* viewport);

	bool apply() override;
	void reject() override;

	const SCP_string& getShipName() const;
	void setShipName(const SCP_string& m_ship_name);

 private:
	template<typename T>
	void modify(T &a, const T &b);

	SCP_string m_ship_name;
	SCP_string m_cargo1;
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

template<typename T>
inline void ShipEditorDialogModel::modify(T &a, const T &b) {
	if (a != b) {
		a = b;
		modelChanged();
	}
}

}
}
}

