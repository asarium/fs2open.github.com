# top-level files
set (file_root
	docfred.cpp
	docfred.h
	frmFRED2.cpp
	frmFRED2.h
	glcViewport.cpp
	glcViewport.h
	wxfred2.cpp
	wxfred2.h
	wxFredRender.cpp
	wxFredRender.h
	wxfredstubs.cpp
	wxGraphicsOperations.h
	wxGraphicsOperations.cpp
)

# Base files
set (file_root_base
	base/wxFRED_base.cpp
	base/wxFRED_base.h
	base/wxFRED_base.xrc
)

# Editors files
set (file_root_editors
	editors/dlgAsteroidFieldEditor.cpp
	editors/dlgAsteroidFieldEditor.h
	editors/dlgBackgroundEditor.cpp
	editors/dlgBackgroundEditor.h
	editors/dlgEventsEditor.cpp
	editors/dlgEventsEditor.h
	editors/dlgFictionViewer.cpp
	editors/dlgFictionViewer.h
	editors/dlgMissionObjectivesEditor.cpp
	editors/dlgMissionObjectivesEditor.h
	editors/dlgMissionSpecsEditor.cpp
	editors/dlgMissionSpecsEditor.h
	editors/dlgObjectEditor.cpp
	editors/dlgObjectEditor.h
	editors/dlgReinforcementsEditor.cpp
	editors/dlgReinforcementsEditor.h
	editors/dlgReinforcementsPicker.cpp
	editors/dlgReinforcementsPicker.h
	editors/dlgSetGlobalShipFlagsEditor.cpp
	editors/dlgSetGlobalShipFlagsEditor.h
	editors/dlgShieldSystemEditor.cpp
	editors/dlgShieldSystemEditor.h
	editors/dlgSoundEnvironment.cpp
	editors/dlgSoundEnvironment.h
	editors/dlgVoiceActingManager.cpp
	editors/dlgVoiceActingManager.h
	editors/frmBriefingEditor.cpp
	editors/frmBriefingEditor.h
	editors/frmCampaignEditor.cpp
	editors/frmCampaignEditor.h
	editors/frmCommandBriefingEditor.cpp
	editors/frmCommandBriefingEditor.h
	editors/frmDebriefingEditor.cpp
	editors/frmDebriefingEditor.h
	editors/frmShipsEditor.cpp
	editors/frmShipsEditor.h
	editors/frmTeamLoadoutEditor.cpp
	editors/frmTeamLoadoutEditor.h
	editors/frmWaypointEditor.cpp
	editors/frmWaypointEditor.h
	editors/frmWingEditor.cpp
	editors/frmWingEditor.h
)

# Help files
set (file_root_help
	help/dlgAboutBox.cpp
	help/dlgAboutBox.h
	help/dlgSexpHelp.cpp
	help/dlgSexpHelp.h
)

# Misc files
set (file_root_misc
	misc/dlgMissionStats.cpp
	misc/dlgMissionStats.h
)

set(file_root_res_pngs
	res/bitmap1.png
	res/black_do.png
	res/bmp00001.png
	res/chained_directive.png
	res/chained.png
	res/constx.png
	res/constxy.png
	res/constxz.png
	res/consty.png
	res/constyz.png
	res/constz.png
	res/data00.png
	res/data05.png
	res/data10.png
	res/data15.png
	res/data20.png
	res/data25.png
	res/data30.png
	res/data35.png
	res/data40.png
	res/data45.png
	res/data50.png
	res/data55.png
	res/data60.png
	res/data65.png
	res/data70.png
	res/data75.png
	res/data80.png
	res/data85.png
	res/data90.png
	res/data95.png
	res/data.png
	res/fred_app.png
	res/fred_debug.png
	res/fredknows.png
	res/fred_splash.png
	res/green_do.png
	res/orbitsel.png
	res/play.png
	res/root_directive.png
	res/root.png
	res/rotlocal.png
	res/selectlist.png
	res/selectlock.png
	res/selectmove.png
	res/select.png
	res/selectrot.png
	res/showdist.png
	res/toolbar1.png
	res/toolbar.png
	res/variable.png
	res/V_fred.png
	res/wingdisband.png
	res/wingform.png
	res/wxFREDIcon.png
	res/zoomext.png
	res/zoomsel.png
)

set(file_root_res
	${file_root_res_pngs}
	res/fred.ico
	res/freddoc.ico
	res/V_fred.ico
	res/wxFREDicon.rc
	res/wxfred_icon-d.ico
	res/wxfred_icon.ico
)

# the source groups
source_group(""                                   FILES ${file_root})
source_group("Base"                               FILES ${file_root_base})
source_group("Editors"                            FILES ${file_root_editors})
source_group("Help"                               FILES ${file_root_help})
source_group("Misc"                               FILES ${file_root_misc})
source_group("Resources"                          FILES ${file_root_res})

# append all files to the file_root
set (file_root
	${file_root}
	${file_root_base}
	${file_root_editors}
	${file_root_help}
	${file_root_misc}
	${file_root_res}
)
