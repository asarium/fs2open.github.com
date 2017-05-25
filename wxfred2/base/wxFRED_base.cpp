///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May 22 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxFRED_base.h"

///////////////////////////////////////////////////////////////////////////
using namespace fredBase;

frmFRED::frmFRED( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mbrFRED = new wxMenuBar( 0 );
	mnuFile = new wxMenu();
	wxMenuItem* mnuFileNew;
	mnuFileNew = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("New") ) + wxT('\t') + wxT("Ctrl+N"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileNew );
	
	wxMenuItem* mnuFileOpen;
	mnuFileOpen = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Open...") ) + wxT('\t') + wxT("Ctrl-O"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileOpen );
	
	wxMenuItem* mnuFileSave;
	mnuFileSave = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Save") ) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileSave );
	
	wxMenuItem* mnuFileSaveAs;
	mnuFileSaveAs = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Save As...") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileSaveAs );
	
	wxMenuItem* mnuFileRevert;
	mnuFileRevert = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Revert") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileRevert );
	
	mnuFile->AppendSeparator();
	
	mnuFileSaveFormat = new wxMenu();
	wxMenuItem* mnuFileSaveFormatItem = new wxMenuItem( mnuFile, wxID_ANY, wxT("Save Format"), wxEmptyString, wxITEM_NORMAL, mnuFileSaveFormat );
	wxMenuItem* mnuFileSaveFormatFs2Open;
	mnuFileSaveFormatFs2Open = new wxMenuItem( mnuFileSaveFormat, wxID_ANY, wxString( wxT("FS2 open") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFileSaveFormat->Append( mnuFileSaveFormatFs2Open );
	
	wxMenuItem* mnuFileSaveFormatFs2Retail;
	mnuFileSaveFormatFs2Retail = new wxMenuItem( mnuFileSaveFormat, wxID_ANY, wxString( wxT("FS2 retail") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFileSaveFormat->Append( mnuFileSaveFormatFs2Retail );
	
	mnuFile->Append( mnuFileSaveFormatItem );
	
	mnuFileImport = new wxMenu();
	wxMenuItem* mnuFileImportItem = new wxMenuItem( mnuFile, wxID_ANY, wxT("Import"), wxEmptyString, wxITEM_NORMAL, mnuFileImport );
	wxMenuItem* mnuFileImportFs1Mission;
	mnuFileImportFs1Mission = new wxMenuItem( mnuFileImport, wxID_ANY, wxString( wxT("FS1 mission...") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFileImport->Append( mnuFileImportFs1Mission );
	
	wxMenuItem* mnuFileImportWeaponLoadouts;
	mnuFileImportWeaponLoadouts = new wxMenuItem( mnuFileImport, wxID_ANY, wxString( wxT("FS1 weapon loadouts...") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFileImport->Append( mnuFileImportWeaponLoadouts );
	
	mnuFile->Append( mnuFileImportItem );
	
	mnuFile->AppendSeparator();
	
	wxMenuItem* mnuFileRunFreespace;
	mnuFileRunFreespace = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Run Freespace") ) + wxT('\t') + wxT("Alt+R"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileRunFreespace );
	
	mnuFile->AppendSeparator();
	
	wxMenuItem* mnuFileRecentFiles;
	mnuFileRecentFiles = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Recent File List") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileRecentFiles );
	
	mnuFile->AppendSeparator();
	
	wxMenuItem* mnuFileExit;
	mnuFileExit = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileExit );
	
	mbrFRED->Append( mnuFile, wxT("File") ); 
	
	mnuEdit = new wxMenu();
	wxMenuItem* mnuEditUndo;
	mnuEditUndo = new wxMenuItem( mnuEdit, wxID_ANY, wxString( wxT("Undo") ) + wxT('\t') + wxT("Ctrl+Z"), wxEmptyString, wxITEM_NORMAL );
	mnuEdit->Append( mnuEditUndo );
	
	wxMenuItem* mnuEditDelete;
	mnuEditDelete = new wxMenuItem( mnuEdit, wxID_ANY, wxString( wxT("Delete") ) + wxT('\t') + wxT("Del"), wxEmptyString, wxITEM_NORMAL );
	mnuEdit->Append( mnuEditDelete );
	
	wxMenuItem* mnuEditDeleteWing;
	mnuEditDeleteWing = new wxMenuItem( mnuEdit, wxID_ANY, wxString( wxT("Delete Wing") ) + wxT('\t') + wxT("Ctrl+Del"), wxEmptyString, wxITEM_NORMAL );
	mnuEdit->Append( mnuEditDeleteWing );
	
	mnuEdit->AppendSeparator();
	
	wxMenuItem* mnuEditDisableUndo;
	mnuEditDisableUndo = new wxMenuItem( mnuEdit, wxID_ANY, wxString( wxT("Disable Undo") ) , wxEmptyString, wxITEM_NORMAL );
	mnuEdit->Append( mnuEditDisableUndo );
	
	mbrFRED->Append( mnuEdit, wxT("Edit") ); 
	
	mnuView = new wxMenu();
	wxMenuItem* mnuViewToolbar;
	mnuViewToolbar = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Toolbar") ) , wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewToolbar );
	
	wxMenuItem* mnuViewStatusBar;
	mnuViewStatusBar = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Status Bar") ) , wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewStatusBar );
	
	mnuView->AppendSeparator();
	
	mnuViewDisplayFiter = new wxMenu();
	wxMenuItem* mnuViewDisplayFiterItem = new wxMenuItem( mnuView, wxID_ANY, wxT("Display Filter"), wxEmptyString, wxITEM_NORMAL, mnuViewDisplayFiter );
	wxMenuItem* mnuViewDisplayFilterShowShips;
	mnuViewDisplayFilterShowShips = new wxMenuItem( mnuViewDisplayFiter, wxID_ANY, wxString( wxT("Show Ships") ) , wxEmptyString, wxITEM_NORMAL );
	mnuViewDisplayFiter->Append( mnuViewDisplayFilterShowShips );
	
	wxMenuItem* mnuViewDisplayFilterShowPlayerStarts;
	mnuViewDisplayFilterShowPlayerStarts = new wxMenuItem( mnuViewDisplayFiter, wxID_ANY, wxString( wxT("Show Player Starts") ) , wxEmptyString, wxITEM_NORMAL );
	mnuViewDisplayFiter->Append( mnuViewDisplayFilterShowPlayerStarts );
	
	wxMenuItem* mnuViewDisplayFilterShowWaypoints;
	mnuViewDisplayFilterShowWaypoints = new wxMenuItem( mnuViewDisplayFiter, wxID_ANY, wxString( wxT("Show Waypoints") ) , wxEmptyString, wxITEM_NORMAL );
	mnuViewDisplayFiter->Append( mnuViewDisplayFilterShowWaypoints );
	
	mnuViewDisplayFiter->AppendSeparator();
	
	wxMenuItem* mnuViewDisplayFilterShowFriendly;
	mnuViewDisplayFilterShowFriendly = new wxMenuItem( mnuViewDisplayFiter, wxID_ANY, wxString( wxT("Show Friendly") ) , wxEmptyString, wxITEM_NORMAL );
	mnuViewDisplayFiter->Append( mnuViewDisplayFilterShowFriendly );
	
	wxMenuItem* mnuViewDisplayFilterShowHostile;
	mnuViewDisplayFilterShowHostile = new wxMenuItem( mnuViewDisplayFiter, wxID_ANY, wxString( wxT("Show Hostile") ) , wxEmptyString, wxITEM_NORMAL );
	mnuViewDisplayFiter->Append( mnuViewDisplayFilterShowHostile );
	
	mnuView->Append( mnuViewDisplayFiterItem );
	
	mnuView->AppendSeparator();
	
	wxMenuItem* mnuViewHideMarkedObjects;
	mnuViewHideMarkedObjects = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Hide Marked Objects") ) , wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewHideMarkedObjects );
	
	wxMenuItem* mnuViewShowHiddenObjects;
	mnuViewShowHiddenObjects = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Hidden Objects") ) , wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowHiddenObjects );
	
	mnuView->AppendSeparator();
	
	wxMenuItem* mnuViewShowShipModels;
	mnuViewShowShipModels = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Ship Models") ) + wxT('\t') + wxT("Shift+Alt+M"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowShipModels );
	
	wxMenuItem* mnuViewShowOutlines;
	mnuViewShowOutlines = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Outlines") ) + wxT('\t') + wxT("Shift+Alt+O"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowOutlines );
	
	wxMenuItem* mnuViewShowShipInfo;
	mnuViewShowShipInfo = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Ship Info") ) + wxT('\t') + wxT("Shift+Alt+I"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowShipInfo );
	
	wxMenuItem* mnuViewShowCoordinates;
	mnuViewShowCoordinates = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Coordinates") ) + wxT('\t') + wxT("Shift+Alt+C"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowCoordinates );
	
	wxMenuItem* mnuViewShowGridPositions;
	mnuViewShowGridPositions = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Grid Positions") ) + wxT('\t') + wxT("Shift+Alt+P"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowGridPositions );
	
	wxMenuItem* mnuViewShowDistances;
	mnuViewShowDistances = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Distances") ) + wxT('\t') + wxT("D"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowDistances );
	
	wxMenuItem* mnuViewShowModelPaths;
	mnuViewShowModelPaths = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Model Paths") ) , wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowModelPaths );
	
	wxMenuItem* mnuViewShowModelDockPoints;
	mnuViewShowModelDockPoints = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Model Dock Points") ) , wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowModelDockPoints );
	
	mnuView->AppendSeparator();
	
	wxMenuItem* mnuViewShowGrid;
	mnuViewShowGrid = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Grid") ) + wxT('\t') + wxT("Shift+Alt+G"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowGrid );
	
	wxMenuItem* mnuViewShowHorizon;
	mnuViewShowHorizon = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Horizon") ) + wxT('\t') + wxT("Shift+Alt+H"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowHorizon );
	
	wxMenuItem* mnuViewDoubleFineGridlines;
	mnuViewDoubleFineGridlines = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Double Fine Gridlines") ) , wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewDoubleFineGridlines );
	
	wxMenuItem* mnuViewAntiAliasedGridlines;
	mnuViewAntiAliasedGridlines = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Anti-Aliased Gridlines") ) , wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewAntiAliasedGridlines );
	
	wxMenuItem* mnuViewShow3DCompass;
	mnuViewShow3DCompass = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show 3-D Compass") ) + wxT('\t') + wxT("Shift+Alt+3"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShow3DCompass );
	
	wxMenuItem* mnuViewShowBackground;
	mnuViewShowBackground = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Show Background") ) + wxT('\t') + wxT("Shift+Alt+B"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewShowBackground );
	
	mnuView->AppendSeparator();
	
	mnuViewViewpoint = new wxMenu();
	wxMenuItem* mnuViewViewpointItem = new wxMenuItem( mnuView, wxID_ANY, wxT("Viewpoint\tShift+V"), wxEmptyString, wxITEM_NORMAL, mnuViewViewpoint );
	wxMenuItem* mnuViewViewpointCamera;
	mnuViewViewpointCamera = new wxMenuItem( mnuViewViewpoint, wxID_ANY, wxString( wxT("Camera") ) , wxEmptyString, wxITEM_NORMAL );
	mnuViewViewpoint->Append( mnuViewViewpointCamera );
	
	wxMenuItem* mnuViewViewpointCurrentShip;
	mnuViewViewpointCurrentShip = new wxMenuItem( mnuViewViewpoint, wxID_ANY, wxString( wxT("Current Ship") ) , wxEmptyString, wxITEM_NORMAL );
	mnuViewViewpoint->Append( mnuViewViewpointCurrentShip );
	
	mnuView->Append( mnuViewViewpointItem );
	
	wxMenuItem* mnuViewSaveCameraPos;
	mnuViewSaveCameraPos = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Save Camera Pos") ) + wxT('\t') + wxT("Ctrl+P"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewSaveCameraPos );
	
	wxMenuItem* mnuViewRestoreCameraPos;
	mnuViewRestoreCameraPos = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Restore Camera Pos") ) + wxT('\t') + wxT("Ctrl+R"), wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewRestoreCameraPos );
	
	mnuView->AppendSeparator();
	
	wxMenuItem* mnuViewLightingFromSuns;
	mnuViewLightingFromSuns = new wxMenuItem( mnuView, wxID_ANY, wxString( wxT("Lighting From Suns") ) , wxEmptyString, wxITEM_NORMAL );
	mnuView->Append( mnuViewLightingFromSuns );
	
	mbrFRED->Append( mnuView, wxT("View") ); 
	
	mnuSpeed = new wxMenu();
	mnuSpeedMovement = new wxMenu();
	wxMenuItem* mnuSpeedMovementItem = new wxMenuItem( mnuSpeed, wxID_ANY, wxT("Movement"), wxEmptyString, wxITEM_NORMAL, mnuSpeedMovement );
	wxMenuItem* mnuSpeedMovementX1;
	mnuSpeedMovementX1 = new wxMenuItem( mnuSpeedMovement, wxID_ANY, wxString( wxT("x1") ) + wxT('\t') + wxT("1"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedMovement->Append( mnuSpeedMovementX1 );
	
	wxMenuItem* mnuSpeedMovementX2;
	mnuSpeedMovementX2 = new wxMenuItem( mnuSpeedMovement, wxID_ANY, wxString( wxT("x2") ) + wxT('\t') + wxT("2"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedMovement->Append( mnuSpeedMovementX2 );
	
	wxMenuItem* mnuSpeedMovementX3;
	mnuSpeedMovementX3 = new wxMenuItem( mnuSpeedMovement, wxID_ANY, wxString( wxT("x3") ) + wxT('\t') + wxT("3"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedMovement->Append( mnuSpeedMovementX3 );
	
	wxMenuItem* mnuSpeedMovementX5;
	mnuSpeedMovementX5 = new wxMenuItem( mnuSpeedMovement, wxID_ANY, wxString( wxT("x5") ) + wxT('\t') + wxT("4"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedMovement->Append( mnuSpeedMovementX5 );
	
	wxMenuItem* mnuSpeedMovementX8;
	mnuSpeedMovementX8 = new wxMenuItem( mnuSpeedMovement, wxID_ANY, wxString( wxT("x8") ) + wxT('\t') + wxT("5"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedMovement->Append( mnuSpeedMovementX8 );
	
	wxMenuItem* mnuSpeedMovementX10;
	mnuSpeedMovementX10 = new wxMenuItem( mnuSpeedMovement, wxID_ANY, wxString( wxT("x10") ) + wxT('\t') + wxT("6"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedMovement->Append( mnuSpeedMovementX10 );
	
	wxMenuItem* mnuSpeedMovementX50;
	mnuSpeedMovementX50 = new wxMenuItem( mnuSpeedMovement, wxID_ANY, wxString( wxT("x50") ) + wxT('\t') + wxT("7"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedMovement->Append( mnuSpeedMovementX50 );
	
	wxMenuItem* mnuSpeedMovementX100;
	mnuSpeedMovementX100 = new wxMenuItem( mnuSpeedMovement, wxID_ANY, wxString( wxT("x100") ) + wxT('\t') + wxT("8"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedMovement->Append( mnuSpeedMovementX100 );
	
	mnuSpeed->Append( mnuSpeedMovementItem );
	
	mnuSpeedRotation = new wxMenu();
	wxMenuItem* mnuSpeedRotationItem = new wxMenuItem( mnuSpeed, wxID_ANY, wxT("Rotation"), wxEmptyString, wxITEM_NORMAL, mnuSpeedRotation );
	wxMenuItem* mnuSpeedRotationX1;
	mnuSpeedRotationX1 = new wxMenuItem( mnuSpeedRotation, wxID_ANY, wxString( wxT("x1") ) + wxT('\t') + wxT("Shift+1"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedRotation->Append( mnuSpeedRotationX1 );
	
	wxMenuItem* mnuSpeedRotationX5;
	mnuSpeedRotationX5 = new wxMenuItem( mnuSpeedRotation, wxID_ANY, wxString( wxT("x5") ) + wxT('\t') + wxT("Shift+2"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedRotation->Append( mnuSpeedRotationX5 );
	
	wxMenuItem* mnuSpeedRotationX12;
	mnuSpeedRotationX12 = new wxMenuItem( mnuSpeedRotation, wxID_ANY, wxString( wxT("x12") ) + wxT('\t') + wxT("Shift+3"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedRotation->Append( mnuSpeedRotationX12 );
	
	wxMenuItem* mnuSpeedRotationX25;
	mnuSpeedRotationX25 = new wxMenuItem( mnuSpeedRotation, wxID_ANY, wxString( wxT("x25") ) + wxT('\t') + wxT("Shift+4"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedRotation->Append( mnuSpeedRotationX25 );
	
	wxMenuItem* mnuSpeedRotationX50;
	mnuSpeedRotationX50 = new wxMenuItem( mnuSpeedRotation, wxID_ANY, wxString( wxT("x50") ) + wxT('\t') + wxT("Shift+5"), wxEmptyString, wxITEM_NORMAL );
	mnuSpeedRotation->Append( mnuSpeedRotationX50 );
	
	mnuSpeed->Append( mnuSpeedRotationItem );
	
	mbrFRED->Append( mnuSpeed, wxT("Speed") ); 
	
	mnuEditors = new wxMenu();
	wxMenuItem* mnuEditorsShips;
	mnuEditorsShips = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Ships") ) + wxT('\t') + wxT("Shift+S"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsShips );
	
	wxMenuItem* mnuEditorsWings;
	mnuEditorsWings = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Wings") ) + wxT('\t') + wxT("Shift+W"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsWings );
	
	wxMenuItem* mnuEditorsObjects;
	mnuEditorsObjects = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Objects") ) + wxT('\t') + wxT("Shift+O"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsObjects );
	
	wxMenuItem* mnuEditorsWaypointPaths;
	mnuEditorsWaypointPaths = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Waypoint Paths") ) + wxT('\t') + wxT("Shift+Y"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsWaypointPaths );
	
	wxMenuItem* mnuEditorsMissionObjectives;
	mnuEditorsMissionObjectives = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Mission Objectives") ) + wxT('\t') + wxT("Shift+G"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsMissionObjectives );
	
	wxMenuItem* mnuEditorsEvents;
	mnuEditorsEvents = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Events") ) + wxT('\t') + wxT("Shift+E"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsEvents );
	
	wxMenuItem* mnuEditorsTeamLoadout;
	mnuEditorsTeamLoadout = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Team Loadout") ) + wxT('\t') + wxT("Shift+P"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsTeamLoadout );
	
	wxMenuItem* mnuEditorsBackground;
	mnuEditorsBackground = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Background") ) + wxT('\t') + wxT("Shift+I"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsBackground );
	
	wxMenuItem* mnuEditorsReinforcements;
	mnuEditorsReinforcements = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Reinforcements") ) + wxT('\t') + wxT("Shift+R"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsReinforcements );
	
	wxMenuItem* mnuEditorsAsteroidField;
	mnuEditorsAsteroidField = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Asteroid Field") ) + wxT('\t') + wxT("Shift+A"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsAsteroidField );
	
	wxMenuItem* mnuEditorsMissionSpecs;
	mnuEditorsMissionSpecs = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Mission Specs") ) + wxT('\t') + wxT("Shift+N"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsMissionSpecs );
	
	wxMenuItem* mnuEditorsBriefing;
	mnuEditorsBriefing = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Briefing") ) + wxT('\t') + wxT("Shift+B"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsBriefing );
	
	wxMenuItem* mnuEditorsDebriefing;
	mnuEditorsDebriefing = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Debriefing") ) + wxT('\t') + wxT("Shift+D"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsDebriefing );
	
	wxMenuItem* mnuEditorsCommandBriefing;
	mnuEditorsCommandBriefing = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Command Briefing") ) , wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsCommandBriefing );
	
	wxMenuItem* mnuEditorsFictionViewer;
	mnuEditorsFictionViewer = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Fiction Viewer") ) , wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsFictionViewer );
	
	wxMenuItem* mnuEditorsShieldSystem;
	mnuEditorsShieldSystem = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Shield System") ) , wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsShieldSystem );
	
	wxMenuItem* mnuEditorsSetGlobalShipFlags;
	mnuEditorsSetGlobalShipFlags = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Set Global Ship Flags") ) , wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsSetGlobalShipFlags );
	
	wxMenuItem* mnuEditorsVoiceActingManager;
	mnuEditorsVoiceActingManager = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Voice Manager") ) , wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsVoiceActingManager );
	
	mnuEditors->AppendSeparator();
	
	wxMenuItem* mnuEditorsCampaign;
	mnuEditorsCampaign = new wxMenuItem( mnuEditors, wxID_ANY, wxString( wxT("Campaign") ) + wxT('\t') + wxT("Shift+C"), wxEmptyString, wxITEM_NORMAL );
	mnuEditors->Append( mnuEditorsCampaign );
	
	mbrFRED->Append( mnuEditors, wxT("Editors") ); 
	
	mnuGroups = new wxMenu();
	wxMenuItem* mnuGroupsGroup1;
	mnuGroupsGroup1 = new wxMenuItem( mnuGroups, wxID_ANY, wxString( wxT("Group 1") ) + wxT('\t') + wxT("Ctrl+1"), wxEmptyString, wxITEM_NORMAL );
	mnuGroups->Append( mnuGroupsGroup1 );
	
	wxMenuItem* mnuGroupsGroup2;
	mnuGroupsGroup2 = new wxMenuItem( mnuGroups, wxID_ANY, wxString( wxT("Group 2") ) + wxT('\t') + wxT("Ctrl+2"), wxEmptyString, wxITEM_NORMAL );
	mnuGroups->Append( mnuGroupsGroup2 );
	
	wxMenuItem* mnuGroupsGroup3;
	mnuGroupsGroup3 = new wxMenuItem( mnuGroups, wxID_ANY, wxString( wxT("Group 3") ) + wxT('\t') + wxT("Ctrl+3"), wxEmptyString, wxITEM_NORMAL );
	mnuGroups->Append( mnuGroupsGroup3 );
	
	wxMenuItem* mnuGroupsGroup4;
	mnuGroupsGroup4 = new wxMenuItem( mnuGroups, wxID_ANY, wxString( wxT("Group 4") ) + wxT('\t') + wxT("Ctrl+4"), wxEmptyString, wxITEM_NORMAL );
	mnuGroups->Append( mnuGroupsGroup4 );
	
	wxMenuItem* mnuGroupsGroup5;
	mnuGroupsGroup5 = new wxMenuItem( mnuGroups, wxID_ANY, wxString( wxT("Group 5") ) + wxT('\t') + wxT("Ctrl+5"), wxEmptyString, wxITEM_NORMAL );
	mnuGroups->Append( mnuGroupsGroup5 );
	
	wxMenuItem* mnuGroupsGroup6;
	mnuGroupsGroup6 = new wxMenuItem( mnuGroups, wxID_ANY, wxString( wxT("Group 6") ) + wxT('\t') + wxT("Ctrl+6"), wxEmptyString, wxITEM_NORMAL );
	mnuGroups->Append( mnuGroupsGroup6 );
	
	wxMenuItem* mnuGroupsGroup7;
	mnuGroupsGroup7 = new wxMenuItem( mnuGroups, wxID_ANY, wxString( wxT("Group 7") ) + wxT('\t') + wxT("Ctrl+7"), wxEmptyString, wxITEM_NORMAL );
	mnuGroups->Append( mnuGroupsGroup7 );
	
	wxMenuItem* mnuGroupsGroup8;
	mnuGroupsGroup8 = new wxMenuItem( mnuGroups, wxID_ANY, wxString( wxT("Group 8") ) + wxT('\t') + wxT("Ctrl+8"), wxEmptyString, wxITEM_NORMAL );
	mnuGroups->Append( mnuGroupsGroup8 );
	
	wxMenuItem* mnuGroupsGroup9;
	mnuGroupsGroup9 = new wxMenuItem( mnuGroups, wxID_ANY, wxString( wxT("Group 9") ) + wxT('\t') + wxT("Ctrl+9"), wxEmptyString, wxITEM_NORMAL );
	mnuGroups->Append( mnuGroupsGroup9 );
	
	mnuGroupsSetGroup = new wxMenu();
	wxMenuItem* mnuGroupsSetGroupItem = new wxMenuItem( mnuGroups, wxID_ANY, wxT("Set Group"), wxEmptyString, wxITEM_NORMAL, mnuGroupsSetGroup );
	wxMenuItem* mnuGroupsSetGroupGroup1;
	mnuGroupsSetGroupGroup1 = new wxMenuItem( mnuGroupsSetGroup, wxID_ANY, wxString( wxT("Group 1") ) , wxEmptyString, wxITEM_NORMAL );
	mnuGroupsSetGroup->Append( mnuGroupsSetGroupGroup1 );
	
	wxMenuItem* mnuGroupsSetGroupGroup2;
	mnuGroupsSetGroupGroup2 = new wxMenuItem( mnuGroupsSetGroup, wxID_ANY, wxString( wxT("Group 2") ) , wxEmptyString, wxITEM_NORMAL );
	mnuGroupsSetGroup->Append( mnuGroupsSetGroupGroup2 );
	
	wxMenuItem* mnuGroupsSetGroupGroup3;
	mnuGroupsSetGroupGroup3 = new wxMenuItem( mnuGroupsSetGroup, wxID_ANY, wxString( wxT("Group 3") ) , wxEmptyString, wxITEM_NORMAL );
	mnuGroupsSetGroup->Append( mnuGroupsSetGroupGroup3 );
	
	wxMenuItem* mnuGroupsSetGroupGroup4;
	mnuGroupsSetGroupGroup4 = new wxMenuItem( mnuGroupsSetGroup, wxID_ANY, wxString( wxT("Group 4") ) , wxEmptyString, wxITEM_NORMAL );
	mnuGroupsSetGroup->Append( mnuGroupsSetGroupGroup4 );
	
	wxMenuItem* mnuGroupsSetGroupGroup5;
	mnuGroupsSetGroupGroup5 = new wxMenuItem( mnuGroupsSetGroup, wxID_ANY, wxString( wxT("Group 5") ) , wxEmptyString, wxITEM_NORMAL );
	mnuGroupsSetGroup->Append( mnuGroupsSetGroupGroup5 );
	
	wxMenuItem* mnuGroupsSetGroupGroup6;
	mnuGroupsSetGroupGroup6 = new wxMenuItem( mnuGroupsSetGroup, wxID_ANY, wxString( wxT("Group 6") ) , wxEmptyString, wxITEM_NORMAL );
	mnuGroupsSetGroup->Append( mnuGroupsSetGroupGroup6 );
	
	wxMenuItem* mnuGroupsSetGroupGroup7;
	mnuGroupsSetGroupGroup7 = new wxMenuItem( mnuGroupsSetGroup, wxID_ANY, wxString( wxT("Group 7") ) , wxEmptyString, wxITEM_NORMAL );
	mnuGroupsSetGroup->Append( mnuGroupsSetGroupGroup7 );
	
	wxMenuItem* mnuGroupsSetGroupGroup8;
	mnuGroupsSetGroupGroup8 = new wxMenuItem( mnuGroupsSetGroup, wxID_ANY, wxString( wxT("Group 8") ) , wxEmptyString, wxITEM_NORMAL );
	mnuGroupsSetGroup->Append( mnuGroupsSetGroupGroup8 );
	
	wxMenuItem* mnuGroupsSetGroupGroup9;
	mnuGroupsSetGroupGroup9 = new wxMenuItem( mnuGroupsSetGroup, wxID_ANY, wxString( wxT("Group 9") ) , wxEmptyString, wxITEM_NORMAL );
	mnuGroupsSetGroup->Append( mnuGroupsSetGroupGroup9 );
	
	mnuGroups->Append( mnuGroupsSetGroupItem );
	
	mbrFRED->Append( mnuGroups, wxT("Groups") ); 
	
	mnuMisc = new wxMenu();
	wxMenuItem* mnuMiscLevelObject;
	mnuMiscLevelObject = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Level Object") ) + wxT('\t') + wxT("L"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscLevelObject );
	
	wxMenuItem* mnuMiscAlignObject;
	mnuMiscAlignObject = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Align Object") ) + wxT('\t') + wxT("Ctrl+L"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscAlignObject );
	
	wxMenuItem* mnuMiscMarkWing;
	mnuMiscMarkWing = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Mark Wing") ) + wxT('\t') + wxT("W"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscMarkWing );
	
	wxMenuItem* mnuMiscControlObject;
	mnuMiscControlObject = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Control Object") ) + wxT('\t') + wxT("T"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscControlObject );
	
	wxMenuItem* mnuMiscNextObject;
	mnuMiscNextObject = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Next Object") ) + wxT('\t') + wxT("Tab"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscNextObject );
	
	wxMenuItem* mnuMiscPreviousObject;
	mnuMiscPreviousObject = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Prev Object") ) + wxT('\t') + wxT("Ctrl+Tab"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscPreviousObject );
	
	wxMenuItem* mnuMiscAdjustGrid;
	mnuMiscAdjustGrid = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Adjust Grid") ) , wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscAdjustGrid );
	
	wxMenuItem* mnuMiscNextSubsystem;
	mnuMiscNextSubsystem = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Next Subsystem") ) + wxT('\t') + wxT("K"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscNextSubsystem );
	
	wxMenuItem* mnuMiscPrevSubsystem;
	mnuMiscPrevSubsystem = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Prev Subsystem") ) + wxT('\t') + wxT("Shift+K"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscPrevSubsystem );
	
	wxMenuItem* mnuMiscCancelSubsystem;
	mnuMiscCancelSubsystem = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Cancel Subsystem") ) + wxT('\t') + wxT("Alt+K"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscCancelSubsystem );
	
	wxMenuItem* mnuMiscMissionStatistics;
	mnuMiscMissionStatistics = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Mission Statistics") ) + wxT('\t') + wxT("Ctrl+Shift+D"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscMissionStatistics );
	
	mnuMisc->AppendSeparator();
	
	wxMenuItem* mnuMiscErrorChecker;
	mnuMiscErrorChecker = new wxMenuItem( mnuMisc, wxID_ANY, wxString( wxT("Error Checker") ) + wxT('\t') + wxT("Shift+H"), wxEmptyString, wxITEM_NORMAL );
	mnuMisc->Append( mnuMiscErrorChecker );
	
	mbrFRED->Append( mnuMisc, wxT("Misc") ); 
	
	mnuHelp = new wxMenu();
	wxMenuItem* mnuHelpHelpTopics;
	mnuHelpHelpTopics = new wxMenuItem( mnuHelp, wxID_ANY, wxString( wxT("Help Topics") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	mnuHelp->Append( mnuHelpHelpTopics );
	
	wxMenuItem* mnuHelpShowSexpHelp;
	mnuHelpShowSexpHelp = new wxMenuItem( mnuHelp, wxID_ANY, wxString( wxT("Show SEXP Help") ) , wxEmptyString, wxITEM_NORMAL );
	mnuHelp->Append( mnuHelpShowSexpHelp );
	
	mnuHelp->AppendSeparator();
	
	wxMenuItem* mnuHelpAbout;
	mnuHelpAbout = new wxMenuItem( mnuHelp, wxID_ANY, wxString( wxT("About wxFRED2...") ) , wxEmptyString, wxITEM_NORMAL );
	mnuHelp->Append( mnuHelpAbout );
	
	mbrFRED->Append( mnuHelp, wxT("Help") ); 
	
	this->SetMenuBar( mbrFRED );
	
	tbrFRED = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	tbrFRED->SetToolSeparation( 0 );
	tbrFRED->SetToolPacking( 0 );
	optSelect = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/select.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxT("Select (S)"), wxT("Select objects only."), NULL ); 
	
	optSelectMove = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/selectmove.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxT("Select and Move (M)"), wxT("Select and move selected objects."), NULL ); 
	
	optSelectRotate = tbrFRED->AddTool( wxID_ANY, wxT("Select and Rotate"), wxBitmap( wxT("../res/selectrot.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxT("Select and Rotate (R)"), wxT("Select and rotate selected objects."), NULL ); 
	
	tbrFRED->AddSeparator(); 
	
	chkRotateLocally = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/rotlocal.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_CHECK, wxT("Rotate Locally (X)"), wxT("Enable/disable local rotation for the selected group."), NULL ); 
	
	tbrFRED->AddSeparator(); 
	
	optConstraintX = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/constx.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxT("X Constraint (`)"), wxT("Constrain actions to the global X axis."), NULL ); 
	
	optConstraintY = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/consty.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxT("Y Constraint (`)"), wxT("Constrain actions to the global Y axis."), NULL ); 
	
	optConstraintZ = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/constz.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxT("Z Constraint (`)"), wxT("Constrain actions to the global Z axis."), NULL ); 
	
	optConstraintXZ = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/constxz.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxT("XZ Constraint (`)"), wxT("Constrain actions to the global XZ plane."), NULL ); 
	
	optConstraintYZ = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/constyz.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxT("YZ Constraint (`)"), wxT("Constrain actions to the global YZ plane."), NULL ); 
	
	optConstraintXY = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/constxy.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxT("XY Constraint (`)"), wxT("Constrain actions to the global XY plane."), NULL ); 
	
	tbrFRED->AddSeparator(); 
	
	btnSelectionList = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/selectlist.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Selection List (H)"), wxT("Select object(s) from a list."), NULL ); 
	
	chkSelectionLock = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/selectlock.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_CHECK, wxT("Selection Lock (L)"), wxT("Lock the current selection from changes."), NULL ); 
	
	tbrFRED->AddSeparator(); 
	
	btnWingForm = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/wingform.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Form Wing (Ctrl+W)"), wxT("Adds the current selection to a wing."), NULL ); 
	
	btnWingDisband = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/wingdisband.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Disband Wing (Ctrl+D)"), wxT("Removes the current selection from (any) wing."), NULL ); 
	
	tbrFRED->AddSeparator(); 
	
	btnZoomSelected = tbrFRED->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("../res/zoomsel.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Zoom Selected (Alt+Z)"), wxT("Zoom to view current selection."), NULL ); 
	
	btnZoomExtents = tbrFRED->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("../res/zoomext.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Zoom Extents (Shift+Z)"), wxT("Zoom to view all objects in the mission."), NULL ); 
	
	tbrFRED->AddSeparator(); 
	
	chkShowDistances = tbrFRED->AddTool( wxID_ANY, wxEmptyString, wxBitmap( wxT("../res/showdist.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_CHECK, wxT("Show Distances (D)"), wxT("Show the distances between all selected objects."), NULL ); 
	
	chkOrbitSelected = tbrFRED->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("../res/orbitsel.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_CHECK, wxT("Rotate about Selection (Ctrl+V)"), wxT("Rotate the vieport camera about the current selection."), NULL ); 
	
	tbrFRED->AddSeparator(); 
	
	tbrFRED->Realize(); 
	
	wxBoxSizer* bSizer126;
	bSizer126 = new wxBoxSizer( wxVERTICAL );
	
	m_contentPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer252;
	bSizer252 = new wxBoxSizer( wxVERTICAL );
	
	
	m_contentPanel->SetSizer( bSizer252 );
	m_contentPanel->Layout();
	bSizer252->Fit( m_contentPanel );
	bSizer126->Add( m_contentPanel, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer126 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

frmFRED::~frmFRED()
{
}

frmShipsEditor::frmShipsEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 226, 226, 226 ) );
	
	mbrShipsEditor = new wxMenuBar( 0 );
	selectShip = new wxMenu();
	mbrShipsEditor->Append( selectShip, wxT("Select Ship") ); 
	
	this->SetMenuBar( mbrShipsEditor );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblShipName = new wxStaticText( this, wxID_ANY, wxT("Ship Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblShipName->Wrap( -1 );
	gbSizer1->Add( lblShipName, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtShipName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( txtShipName, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblWing = new wxStaticText( this, wxID_ANY, wxT("Wing:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblWing->Wrap( -1 );
	gbSizer1->Add( lblWing, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtWing = new wxTextCtrl( this, wxID_ANY, wxT("None"), wxDefaultPosition, wxDefaultSize, 0 );
	txtWing->Enable( false );
	
	gbSizer1->Add( txtWing, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblShipClass = new wxStaticText( this, wxID_ANY, wxT("Ship Class:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblShipClass->Wrap( -1 );
	gbSizer1->Add( lblShipClass, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboShipClassChoices;
	cboShipClass = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboShipClassChoices, 0 );
	cboShipClass->SetSelection( 0 );
	gbSizer1->Add( cboShipClass, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblHotkey = new wxStaticText( this, wxID_ANY, wxT("Hotkey:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblHotkey->Wrap( -1 );
	gbSizer1->Add( lblHotkey, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboHotkeyChoices;
	cboHotkey = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboHotkeyChoices, 0 );
	cboHotkey->SetSelection( 0 );
	gbSizer1->Add( cboHotkey, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblAIClass = new wxStaticText( this, wxID_ANY, wxT("AI Class:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAIClass->Wrap( -1 );
	gbSizer1->Add( lblAIClass, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboAIClassChoices;
	cboAIClass = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboAIClassChoices, 0 );
	cboAIClass->SetSelection( 0 );
	gbSizer1->Add( cboAIClass, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblPersona = new wxStaticText( this, wxID_ANY, wxT("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblPersona->Wrap( -1 );
	gbSizer1->Add( lblPersona, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboPersonaChoices;
	cboPersona = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboPersonaChoices, 0 );
	cboPersona->SetSelection( 0 );
	gbSizer1->Add( cboPersona, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblTeam = new wxStaticText( this, wxID_ANY, wxT("Team:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTeam->Wrap( -1 );
	gbSizer1->Add( lblTeam, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboTeamChoices;
	cboTeam = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboTeamChoices, 0 );
	cboTeam->SetSelection( 0 );
	gbSizer1->Add( cboTeam, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblKillScore = new wxStaticText( this, wxID_ANY, wxT("Kill Score:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblKillScore->Wrap( -1 );
	gbSizer1->Add( lblKillScore, wxGBPosition( 3, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtKillscore = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( txtKillscore, wxGBPosition( 3, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblCargoCargo = new wxStaticText( this, wxID_ANY, wxT("Cargo:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCargoCargo->Wrap( -1 );
	gbSizer1->Add( lblCargoCargo, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	cboCargo = new wxComboBox( this, wxID_ANY, wxT("None"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer1->Add( cboCargo, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblAssistPercentage = new wxStaticText( this, wxID_ANY, wxT("Assist %:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAssistPercentage->Wrap( -1 );
	gbSizer1->Add( lblAssistPercentage, wxGBPosition( 4, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtAssistPercentage = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( txtAssistPercentage, wxGBPosition( 4, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblAltName = new wxStaticText( this, wxID_ANY, wxT("Alt Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAltName->Wrap( -1 );
	gbSizer1->Add( lblAltName, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	cboAltName = new wxComboBox( this, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer1->Add( cboAltName, wxGBPosition( 5, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	chkPlayerShip = new wxCheckBox( this, wxID_ANY, wxT("Player Ship"), wxDefaultPosition, wxDefaultSize, 0 );
	chkPlayerShip->Enable( false );
	
	gbSizer1->Add( chkPlayerShip, wxGBPosition( 5, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblCallsign = new wxStaticText( this, wxID_ANY, wxT("Callsign:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCallsign->Wrap( -1 );
	gbSizer1->Add( lblCallsign, wxGBPosition( 6, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	cboCallsign = new wxComboBox( this, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer1->Add( cboCallsign, wxGBPosition( 6, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnMakePlayerShip = new wxButton( this, wxID_ANY, wxT("Set As Player Ship"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( btnMakePlayerShip, wxGBPosition( 6, 3 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	btnTextureReplacement = new wxButton( this, wxID_ANY, wxT("Texture Replacement"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( btnTextureReplacement, wxGBPosition( 7, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	btnAltShipClass = new wxButton( this, wxID_ANY, wxT("Alt Ship Class"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( btnAltShipClass, wxGBPosition( 7, 3 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	btnPrevWing = new wxButton( this, wxID_ANY, wxT("Prev"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer2->Add( btnPrevWing, 0, wxALL|wxEXPAND, 3 );
	
	btnNextWing = new wxButton( this, wxID_ANY, wxT("Next"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer2->Add( btnNextWing, 0, wxALL|wxEXPAND, 3 );
	
	
	gbSizer1->Add( bSizer2, wxGBPosition( 0, 4 ), wxGBSpan( 1, 1 ), wxEXPAND, 3 );
	
	btnDelete = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( btnDelete, wxGBPosition( 1, 4 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	btnReset = new wxButton( this, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( btnReset, wxGBPosition( 2, 4 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	btnWeapons = new wxButton( this, wxID_ANY, wxT("Weapons"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( btnWeapons, wxGBPosition( 3, 4 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	btnPlayerOrders = new wxButton( this, wxID_ANY, wxT("Player Orders"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( btnPlayerOrders, wxGBPosition( 4, 4 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	btnSpecialExplosion = new wxButton( this, wxID_ANY, wxT("Special Exp"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( btnSpecialExplosion, wxGBPosition( 5, 4 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	btnSpecialHits = new wxButton( this, wxID_ANY, wxT("Special Hits"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( btnSpecialHits, wxGBPosition( 6, 4 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	
	bSizer1->Add( gbSizer1, 0, wxALIGN_CENTER, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	btnMiscOptions = new wxButton( this, wxID_ANY, wxT("Misc"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( btnMiscOptions, 1, wxALL, 3 );
	
	btnInitialStatus = new wxButton( this, wxID_ANY, wxT("Initial Status"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( btnInitialStatus, 1, wxALL, 3 );
	
	btnInitialOrders = new wxButton( this, wxID_ANY, wxT("Initial Orders"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( btnInitialOrders, 1, wxALL, 3 );
	
	btnTBLInfo = new wxButton( this, wxID_ANY, wxT("TBL Info"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( btnTBLInfo, 1, wxALL, 3 );
	
	btnHideCues = new wxButton( this, wxID_ANY, wxT("Hide Cues"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( btnHideCues, 1, wxALL, 3 );
	
	
	bSizer1->Add( bSizer3, 0, wxALIGN_CENTER|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Arrival") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblArrivalLocation = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Location:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalLocation->Wrap( -1 );
	fgSizer1->Add( lblArrivalLocation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboArrivalLocationChoices;
	cboArrivalLocation = new wxChoice( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,21 ), cboArrivalLocationChoices, 0 );
	cboArrivalLocation->SetSelection( 0 );
	fgSizer1->Add( cboArrivalLocation, 0, wxALL|wxEXPAND, 3 );
	
	lblArrivalTarget = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Target:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalTarget->Wrap( -1 );
	fgSizer1->Add( lblArrivalTarget, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboArrivalTargetChoices;
	cboArrivalTarget = new wxChoice( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,21 ), cboArrivalTargetChoices, 0 );
	cboArrivalTarget->SetSelection( 0 );
	fgSizer1->Add( cboArrivalTarget, 0, wxALL|wxEXPAND, 3 );
	
	lblArrivalDistance = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Distance:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalDistance->Wrap( -1 );
	fgSizer1->Add( lblArrivalDistance, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtArrivalDistance = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,21 ), 0 );
	fgSizer1->Add( txtArrivalDistance, 0, wxALL, 3 );
	
	lblArrivalDelay = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Delay:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalDelay->Wrap( -1 );
	fgSizer1->Add( lblArrivalDelay, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	spnArrivalDelay = new wxSpinCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( -1,21 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	bSizer5->Add( spnArrivalDelay, 0, wxALL|wxEXPAND, 3 );
	
	lblArrivalDelaySeconds = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalDelaySeconds->Wrap( -1 );
	bSizer5->Add( lblArrivalDelaySeconds, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	fgSizer1->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	sbSizer1->Add( fgSizer1, 0, wxALL|wxEXPAND, 3 );
	
	btnRestrictArrivalPaths = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Restrict Arrival Paths"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( btnRestrictArrivalPaths, 0, wxALL|wxEXPAND, 3 );
	
	lblArrivalCue = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Cue:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalCue->Wrap( -1 );
	sbSizer1->Add( lblArrivalCue, 0, wxALL, 3 );
	
	tctArrivalCues = new wxTreeCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	sbSizer1->Add( tctArrivalCues, 1, wxALL|wxEXPAND, 3 );
	
	chkNoArrivalWarp = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, wxT("No Warp Effect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( chkNoArrivalWarp, 0, wxALL, 5 );
	
	
	bSizer4->Add( sbSizer1, 1, wxEXPAND|wxRIGHT|wxTOP, 3 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Departure") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblDepatureLocation = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Location:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDepatureLocation->Wrap( -1 );
	fgSizer2->Add( lblDepatureLocation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboDepartureLocationChoices;
	cboDepartureLocation = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,21 ), cboDepartureLocationChoices, 0 );
	cboDepartureLocation->SetSelection( 0 );
	fgSizer2->Add( cboDepartureLocation, 0, wxALL|wxEXPAND, 3 );
	
	lblDepartureTarget = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Target:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDepartureTarget->Wrap( -1 );
	fgSizer2->Add( lblDepartureTarget, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboDepartureTargetChoices;
	cboDepartureTarget = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,21 ), cboDepartureTargetChoices, 0 );
	cboDepartureTarget->SetSelection( 0 );
	fgSizer2->Add( cboDepartureTarget, 0, wxALL|wxEXPAND, 3 );
	
	
	fgSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer2->Add( 0, 27, 1, wxEXPAND, 5 );
	
	lblDepartureDelay = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Delay:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDepartureDelay->Wrap( -1 );
	fgSizer2->Add( lblDepartureDelay, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	spnArrivalDelay1 = new wxSpinCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( -1,21 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	bSizer6->Add( spnArrivalDelay1, 0, wxALL|wxEXPAND, 3 );
	
	m_staticText1711 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1711->Wrap( -1 );
	bSizer6->Add( m_staticText1711, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	fgSizer2->Add( bSizer6, 0, wxALL, 3 );
	
	
	sbSizer2->Add( fgSizer2, 0, wxEXPAND, 5 );
	
	btnRestrictDeparturePaths = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Restrict Departure Paths"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( btnRestrictDeparturePaths, 0, wxALL|wxEXPAND, 3 );
	
	lblDepartureCue = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Cue:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDepartureCue->Wrap( -1 );
	sbSizer2->Add( lblDepartureCue, 0, wxALL, 3 );
	
	tctDepartureCues = new wxTreeCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	sbSizer2->Add( tctDepartureCues, 1, wxALL|wxEXPAND, 3 );
	
	chkNoDepartureWarp = new wxCheckBox( sbSizer2->GetStaticBox(), wxID_ANY, wxT("No Warp Effect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( chkNoDepartureWarp, 0, wxALL, 5 );
	
	
	bSizer4->Add( sbSizer2, 1, wxEXPAND|wxLEFT|wxTOP, 3 );
	
	
	bSizer1->Add( bSizer4, 1, wxEXPAND, 3 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
}

frmShipsEditor::~frmShipsEditor()
{
}

frmWingEditor::frmWingEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 226, 226, 226 ) );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	pnlProperties = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridBagSizer* gbSizer2;
	gbSizer2 = new wxGridBagSizer( 0, 0 );
	gbSizer2->SetFlexibleDirection( wxBOTH );
	gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblWingName = new wxStaticText( pnlProperties, wxID_ANY, wxT("Wing Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblWingName->Wrap( -1 );
	gbSizer2->Add( lblWingName, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	txtWingName = new wxTextCtrl( pnlProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( txtWingName, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	lblLeader = new wxStaticText( pnlProperties, wxID_ANY, wxT("Leader:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblLeader->Wrap( -1 );
	gbSizer2->Add( lblLeader, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	wxArrayString cboWingLeaderChoices;
	cboWingLeader = new wxChoice( pnlProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboWingLeaderChoices, 0 );
	cboWingLeader->SetSelection( 0 );
	gbSizer2->Add( cboWingLeader, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	lblWaveNumber = new wxStaticText( pnlProperties, wxID_ANY, wxT("# of Waves"), wxDefaultPosition, wxDefaultSize, 0 );
	lblWaveNumber->Wrap( -1 );
	gbSizer2->Add( lblWaveNumber, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	spnWaveNumber = new wxSpinCtrl( pnlProperties, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999, 0 );
	gbSizer2->Add( spnWaveNumber, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	lblWaveThreshold = new wxStaticText( pnlProperties, wxID_ANY, wxT("Wave Threshold:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblWaveThreshold->Wrap( -1 );
	gbSizer2->Add( lblWaveThreshold, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	spnWaveThreshold = new wxSpinCtrl( pnlProperties, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	gbSizer2->Add( spnWaveThreshold, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	lblHotkey = new wxStaticText( pnlProperties, wxID_ANY, wxT("Hotkey:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblHotkey->Wrap( -1 );
	gbSizer2->Add( lblHotkey, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	wxArrayString cboHotkeyChoices;
	cboHotkey = new wxChoice( pnlProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboHotkeyChoices, 0 );
	cboHotkey->SetSelection( 0 );
	gbSizer2->Add( cboHotkey, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	btnSquadLogo = new wxButton( pnlProperties, wxID_ANY, wxT("Squad Logo"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( btnSquadLogo, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 3 );
	
	txtSquadLogo = new wxTextCtrl( pnlProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( txtSquadLogo, wxGBPosition( 5, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 3 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	chkReinforcement = new wxCheckBox( pnlProperties, wxID_ANY, wxT("Reinforcement Unit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( chkReinforcement, 0, wxALL, 3 );
	
	chkIgnoreForGoals = new wxCheckBox( pnlProperties, wxID_ANY, wxT("Ignore for counting Goals"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( chkIgnoreForGoals, 0, wxALL, 3 );
	
	chkNoArrivalMusic = new wxCheckBox( pnlProperties, wxID_ANY, wxT("No Arrival Music"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( chkNoArrivalMusic, 0, wxALL, 3 );
	
	chkNoArrivalMessage = new wxCheckBox( pnlProperties, wxID_ANY, wxT("No Arrival Message"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( chkNoArrivalMessage, 0, wxALL, 3 );
	
	chkNoDynamicGoals = new wxCheckBox( pnlProperties, wxID_ANY, wxT("No Dynamic Goals"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( chkNoDynamicGoals, 0, wxALL, 3 );
	
	
	gbSizer2->Add( bSizer8, wxGBPosition( 0, 2 ), wxGBSpan( 5, 1 ), wxALIGN_CENTER|wxALL, 3 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	btnPrev = new wxButton( pnlProperties, wxID_ANY, wxT("Prev"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer9->Add( btnPrev, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	btnNext = new wxButton( pnlProperties, wxID_ANY, wxT("Next"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer9->Add( btnNext, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	
	gbSizer2->Add( bSizer9, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnDeleteWing = new wxButton( pnlProperties, wxID_ANY, wxT("Delete Wing"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( btnDeleteWing, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	btnDisbandWing = new wxButton( pnlProperties, wxID_ANY, wxT("Disband Wing"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( btnDisbandWing, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	btnInitialOrders = new wxButton( pnlProperties, wxID_ANY, wxT("Initial Orders"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( btnInitialOrders, wxGBPosition( 3, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	btnHideCues = new wxToggleButton( pnlProperties, wxID_ANY, wxT("Hide Cues"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer2->Add( btnHideCues, wxGBPosition( 4, 3 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	
	gbSizer2->AddGrowableCol( 1 );
	
	pnlProperties->SetSizer( gbSizer2 );
	pnlProperties->Layout();
	gbSizer2->Fit( pnlProperties );
	bSizer7->Add( pnlProperties, 0, wxALL|wxEXPAND, 3 );
	
	pnlCues = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( pnlCues, wxID_ANY, wxT("Delay Between Waves (Seconds)") ), wxHORIZONTAL );
	
	lblMinWaveDelay = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Min:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMinWaveDelay->Wrap( -1 );
	sbSizer3->Add( lblMinWaveDelay, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	spnMinWaveDelay = new wxSpinCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	sbSizer3->Add( spnMinWaveDelay, 1, wxALL, 3 );
	
	lblMaxWaveDelay = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Max:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMaxWaveDelay->Wrap( -1 );
	sbSizer3->Add( lblMaxWaveDelay, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );
	
	spnMaxWaveDelay = new wxSpinCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	sbSizer3->Add( spnMaxWaveDelay, 1, wxALL, 3 );
	
	
	bSizer10->Add( sbSizer3, 0, wxALIGN_CENTER|wxALL, 3 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( pnlCues, wxID_ANY, wxT("Arrival") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblArrivalLocation = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Location:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalLocation->Wrap( -1 );
	fgSizer3->Add( lblArrivalLocation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboArrivalLocationChoices;
	cboArrivalLocation = new wxChoice( sbSizer4->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboArrivalLocationChoices, 0 );
	cboArrivalLocation->SetSelection( 0 );
	fgSizer3->Add( cboArrivalLocation, 0, wxALL|wxEXPAND, 3 );
	
	lblArrivalTarget = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Target:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalTarget->Wrap( -1 );
	fgSizer3->Add( lblArrivalTarget, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboArrivalTargetChoices;
	cboArrivalTarget = new wxChoice( sbSizer4->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboArrivalTargetChoices, 0 );
	cboArrivalTarget->SetSelection( 0 );
	fgSizer3->Add( cboArrivalTarget, 0, wxALL|wxEXPAND, 3 );
	
	lblArrivalDistance = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Distance:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalDistance->Wrap( -1 );
	fgSizer3->Add( lblArrivalDistance, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtArrivalDistance = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( txtArrivalDistance, 0, wxALL, 3 );
	
	lblArrivalDelay = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Delay:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalDelay->Wrap( -1 );
	fgSizer3->Add( lblArrivalDelay, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	spnArrivalDelay = new wxSpinCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	bSizer12->Add( spnArrivalDelay, 0, wxALL|wxEXPAND, 3 );
	
	lblArrivalDelaySeconds = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalDelaySeconds->Wrap( -1 );
	bSizer12->Add( lblArrivalDelaySeconds, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	fgSizer3->Add( bSizer12, 1, wxEXPAND, 5 );
	
	
	sbSizer4->Add( fgSizer3, 0, wxALL|wxEXPAND, 3 );
	
	btnRestrictArrivalPaths = new wxButton( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Restrict Arrival Paths"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( btnRestrictArrivalPaths, 0, wxALL|wxEXPAND, 3 );
	
	lblArrivalCue = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Cue:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArrivalCue->Wrap( -1 );
	sbSizer4->Add( lblArrivalCue, 0, wxALL, 3 );
	
	tctArrivalCues = new wxTreeCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,106 ), wxTR_DEFAULT_STYLE );
	sbSizer4->Add( tctArrivalCues, 1, wxALL|wxEXPAND, 3 );
	
	chkNoArrivalWarp = new wxCheckBox( sbSizer4->GetStaticBox(), wxID_ANY, wxT("No Warp Effect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( chkNoArrivalWarp, 0, wxALL, 5 );
	
	
	bSizer11->Add( sbSizer4, 1, wxEXPAND|wxRIGHT|wxTOP, 3 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( pnlCues, wxID_ANY, wxT("Departure") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblDepatureLocation = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Location:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDepatureLocation->Wrap( -1 );
	fgSizer4->Add( lblDepatureLocation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboDepartureLocationChoices;
	cboDepartureLocation = new wxChoice( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboDepartureLocationChoices, 0 );
	cboDepartureLocation->SetSelection( 0 );
	fgSizer4->Add( cboDepartureLocation, 0, wxALL|wxEXPAND, 3 );
	
	lblDepartureTarget = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Target:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDepartureTarget->Wrap( -1 );
	fgSizer4->Add( lblDepartureTarget, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboDepartureTargetChoices;
	cboDepartureTarget = new wxChoice( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboDepartureTargetChoices, 0 );
	cboDepartureTarget->SetSelection( 0 );
	fgSizer4->Add( cboDepartureTarget, 0, wxALL|wxEXPAND, 3 );
	
	
	fgSizer4->Add( 0, 27, 0, 0, 5 );
	
	
	fgSizer4->Add( 0, 0, 0, 0, 5 );
	
	lblDepartureDelay = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Delay:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDepartureDelay->Wrap( -1 );
	fgSizer4->Add( lblDepartureDelay, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	spnArrivalDelay1 = new wxSpinCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	bSizer13->Add( spnArrivalDelay1, 0, wxALL|wxEXPAND, 3 );
	
	m_staticText1711 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1711->Wrap( -1 );
	bSizer13->Add( m_staticText1711, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	fgSizer4->Add( bSizer13, 0, wxEXPAND, 3 );
	
	
	sbSizer5->Add( fgSizer4, 0, wxALL|wxEXPAND, 3 );
	
	btnRestrictDeparturePaths = new wxButton( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Restrict Departure Paths"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( btnRestrictDeparturePaths, 0, wxALL|wxEXPAND, 3 );
	
	lblDepartureCue = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Cue:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDepartureCue->Wrap( -1 );
	sbSizer5->Add( lblDepartureCue, 0, wxALL, 3 );
	
	tctDepartureCues = new wxTreeCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,106 ), wxTR_DEFAULT_STYLE );
	sbSizer5->Add( tctDepartureCues, 1, wxALL|wxEXPAND, 3 );
	
	chkNoDepartureWarp = new wxCheckBox( sbSizer5->GetStaticBox(), wxID_ANY, wxT("No Warp Effect"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( chkNoDepartureWarp, 0, wxALL, 5 );
	
	
	bSizer11->Add( sbSizer5, 1, wxEXPAND|wxLEFT|wxTOP, 3 );
	
	
	bSizer10->Add( bSizer11, 1, wxEXPAND, 5 );
	
	
	pnlCues->SetSizer( bSizer10 );
	pnlCues->Layout();
	bSizer10->Fit( pnlCues );
	bSizer7->Add( pnlCues, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );
	mbrWingEditor = new wxMenuBar( 0 );
	mnuSelectWing = new wxMenu();
	mbrWingEditor->Append( mnuSelectWing, wxT("Select Wing") ); 
	
	this->SetMenuBar( mbrWingEditor );
	
	
	this->Centre( wxBOTH );
}

frmWingEditor::~frmWingEditor()
{
}

dlgObjectEditor::dlgObjectEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Position") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText217 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText217->Wrap( -1 );
	fgSizer5->Add( m_staticText217, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnPositionX = new wxSpinCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer5->Add( spnPositionX, 0, wxALL, 3 );
	
	m_staticText218 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText218->Wrap( -1 );
	fgSizer5->Add( m_staticText218, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnPositionY = new wxSpinCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer5->Add( spnPositionY, 0, wxALL, 3 );
	
	m_staticText220 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText220->Wrap( -1 );
	fgSizer5->Add( m_staticText220, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnPositionZ = new wxSpinCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer5->Add( spnPositionZ, 0, wxALL, 3 );
	
	
	sbSizer6->Add( fgSizer5, 0, wxEXPAND, 5 );
	
	
	bSizer14->Add( sbSizer6, 0, wxALIGN_CENTER|wxALL, 3 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Orientation") ), wxVERTICAL );
	
	chkPointTo = new wxCheckBox( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Face/Point towards..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer7->Add( chkPointTo, 0, wxALL, 3 );
	
	pnlOrientation = new wxPanel( sbSizer7->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridBagSizer* gbSizer3;
	gbSizer3 = new wxGridBagSizer( 0, 0 );
	gbSizer3->SetFlexibleDirection( wxBOTH );
	gbSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	optObject = new wxRadioButton( pnlOrientation, wxID_ANY, wxT("Object:"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	optObject->SetValue( true ); 
	gbSizer3->Add( optObject, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	wxString cbObjectChoices[] = { wxT("No object") };
	int cbObjectNChoices = sizeof( cbObjectChoices ) / sizeof( wxString );
	cbObject = new wxChoice( pnlOrientation, wxID_ANY, wxDefaultPosition, wxSize( 140,-1 ), cbObjectNChoices, cbObjectChoices, 0 );
	cbObject->SetSelection( 0 );
	gbSizer3->Add( cbObject, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxALL, 3 );
	
	optLocation = new wxRadioButton( pnlOrientation, wxID_ANY, wxT("Location:"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( optLocation, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblLocationX = new wxStaticText( pnlOrientation, wxID_ANY, wxT("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblLocationX->Wrap( -1 );
	lblLocationX->Enable( false );
	
	fgSizer6->Add( lblLocationX, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnLocationX = new wxSpinCtrl( pnlOrientation, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	spnLocationX->Enable( false );
	
	fgSizer6->Add( spnLocationX, 0, wxALL, 3 );
	
	lblLocationY = new wxStaticText( pnlOrientation, wxID_ANY, wxT("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblLocationY->Wrap( -1 );
	lblLocationY->Enable( false );
	
	fgSizer6->Add( lblLocationY, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnLocationY = new wxSpinCtrl( pnlOrientation, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	spnLocationY->Enable( false );
	
	fgSizer6->Add( spnLocationY, 0, wxALL, 3 );
	
	lblLocationZ = new wxStaticText( pnlOrientation, wxID_ANY, wxT("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblLocationZ->Wrap( -1 );
	lblLocationZ->Enable( false );
	
	fgSizer6->Add( lblLocationZ, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnLocationZ = new wxSpinCtrl( pnlOrientation, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	spnLocationZ->Enable( false );
	
	fgSizer6->Add( spnLocationZ, 0, wxALL, 3 );
	
	
	gbSizer3->Add( fgSizer6, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxALL, 3 );
	
	optAngle = new wxRadioButton( pnlOrientation, wxID_ANY, wxT("Angle:"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer3->Add( optAngle, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblPitch = new wxStaticText( pnlOrientation, wxID_ANY, wxT("Pitch:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblPitch->Wrap( -1 );
	lblPitch->Enable( false );
	
	fgSizer7->Add( lblPitch, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnPitch = new wxSpinCtrl( pnlOrientation, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 360, 0 );
	spnPitch->Enable( false );
	
	fgSizer7->Add( spnPitch, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblBank = new wxStaticText( pnlOrientation, wxID_ANY, wxT("Bank:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBank->Wrap( -1 );
	lblBank->Enable( false );
	
	fgSizer7->Add( lblBank, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnBank = new wxSpinCtrl( pnlOrientation, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 360, 0 );
	spnBank->Enable( false );
	
	fgSizer7->Add( spnBank, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblHeading = new wxStaticText( pnlOrientation, wxID_ANY, wxT("Heading:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblHeading->Wrap( -1 );
	lblHeading->Enable( false );
	
	fgSizer7->Add( lblHeading, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnHeading = new wxSpinCtrl( pnlOrientation, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	spnHeading->Enable( false );
	
	fgSizer7->Add( spnHeading, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	gbSizer3->Add( fgSizer7, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	
	pnlOrientation->SetSizer( gbSizer3 );
	pnlOrientation->Layout();
	gbSizer3->Fit( pnlOrientation );
	sbSizer7->Add( pnlOrientation, 0, wxEXPAND, 3 );
	
	
	bSizer14->Add( sbSizer7, 1, wxALL|wxEXPAND, 3 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	bSizer14->Add( m_sdbSizer1, 0, wxALIGN_CENTER|wxALL, 3 );
	
	
	this->SetSizer( bSizer14 );
	this->Layout();
	bSizer14->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgObjectEditor::~dlgObjectEditor()
{
}

frmWaypointEditor::frmWaypointEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 226, 226, 226 ) );
	
	menuWaypoint = new wxMenuBar( 0 );
	menuPaths = new wxMenu();
	menuWaypoint->Append( menuPaths, wxT("Select Waypoint Path") ); 
	
	this->SetMenuBar( menuWaypoint );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	lblWaypointName = new wxStaticText( this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblWaypointName->Wrap( -1 );
	bSizer15->Add( lblWaypointName, 0, wxALIGN_CENTER|wxALL, 3 );
	
	txtWaypointName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( txtWaypointName, 1, wxALIGN_CENTER|wxALL, 3 );
	
	
	this->SetSizer( bSizer15 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

frmWaypointEditor::~frmWaypointEditor()
{
}

dlgMissionObjectivesEditor::dlgMissionObjectivesEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	tctObjectives = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer17->Add( tctObjectives, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer16->Add( bSizer17, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText117 = new wxStaticText( this, wxID_ANY, wxT("Display Types"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText117->Wrap( -1 );
	bSizer19->Add( m_staticText117, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxString m_choice27Choices[] = { wxT("Primary Goals"), wxT("Secondary Goals"), wxT("Bonus Goals") };
	int m_choice27NChoices = sizeof( m_choice27Choices ) / sizeof( wxString );
	m_choice27 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice27NChoices, m_choice27Choices, 0 );
	m_choice27->SetSelection( 0 );
	bSizer19->Add( m_choice27, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer18->Add( bSizer19, 0, wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Current Objective") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer8->AddGrowableCol( 1 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblObjType = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblObjType->Wrap( -1 );
	fgSizer8->Add( lblObjType, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxString cboObjTypeChoices[] = { wxT("Primary Goal"), wxT("Secondary Goal"), wxT("Bonus Goal") };
	int cboObjTypeNChoices = sizeof( cboObjTypeChoices ) / sizeof( wxString );
	cboObjType = new wxChoice( sbSizer8->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboObjTypeNChoices, cboObjTypeChoices, 0 );
	cboObjType->SetSelection( 0 );
	fgSizer8->Add( cboObjType, 0, wxALL|wxEXPAND, 3 );
	
	lblObjName = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblObjName->Wrap( -1 );
	fgSizer8->Add( lblObjName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtObjName = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer8->Add( txtObjName, 0, wxALL|wxEXPAND, 3 );
	
	lblObjText = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Objective Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblObjText->Wrap( -1 );
	fgSizer8->Add( lblObjText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtObjText = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer8->Add( txtObjText, 0, wxALL|wxEXPAND, 3 );
	
	lblObjScore = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Score:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblObjScore->Wrap( -1 );
	fgSizer8->Add( lblObjScore, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtObjScore = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer8->Add( txtObjScore, 0, wxALL|wxEXPAND, 3 );
	
	lblObjTeam = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Team:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblObjTeam->Wrap( -1 );
	fgSizer8->Add( lblObjTeam, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboObjTeamChoices;
	cboObjTeam = new wxChoice( sbSizer8->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboObjTeamChoices, 0 );
	cboObjTeam->SetSelection( 0 );
	fgSizer8->Add( cboObjTeam, 0, wxALL|wxEXPAND, 3 );
	
	
	sbSizer8->Add( fgSizer8, 0, wxEXPAND, 5 );
	
	cboCurrObjInvalid = new wxCheckBox( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Objective Invalid"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( cboCurrObjInvalid, 0, wxALL, 3 );
	
	cboCurrObjNoCompletionSound = new wxCheckBox( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Don't Play Completion Sound"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( cboCurrObjNoCompletionSound, 0, wxALL, 3 );
	
	
	bSizer18->Add( sbSizer8, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	btnNewObjective = new wxButton( this, wxID_ANY, wxT("New Obj."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( btnNewObjective, 0, wxALL, 3 );
	
	btnConfirm = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( btnConfirm, 0, wxALL, 3 );
	
	btnCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( btnCancel, 0, wxALL, 3 );
	
	
	bSizer18->Add( bSizer20, 0, 0, 3 );
	
	
	bSizer16->Add( bSizer18, 1, wxEXPAND, 3 );
	
	
	this->SetSizer( bSizer16 );
	this->Layout();
	bSizer16->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgMissionObjectivesEditor::~dlgMissionObjectivesEditor()
{
}

dlgEventsEditor::dlgEventsEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	pnlEvents = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );
	
	trbSexp = new wxTreeCtrl( pnlEvents, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer23->Add( trbSexp, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );
	
	btnNewEvent = new wxButton( pnlEvents, wxID_ANY, wxT("New Event"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( btnNewEvent, 0, wxALL|wxEXPAND, 3 );
	
	btnInsertEvent = new wxButton( pnlEvents, wxID_ANY, wxT("Insert Event"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( btnInsertEvent, 0, wxALL|wxEXPAND, 3 );
	
	btnDeleteEvent = new wxButton( pnlEvents, wxID_ANY, wxT("Delete Event"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( btnDeleteEvent, 0, wxALL|wxEXPAND, 3 );
	
	lblRepeatCount = new wxStaticText( pnlEvents, wxID_ANY, wxT("Repeat Count:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblRepeatCount->Wrap( -1 );
	bSizer24->Add( lblRepeatCount, 0, wxLEFT|wxTOP, 3 );
	
	txtRepeatCount = new wxTextCtrl( pnlEvents, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( txtRepeatCount, 0, wxALL, 3 );
	
	lblTriggerCount = new wxStaticText( pnlEvents, wxID_ANY, wxT("Trigger Count:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTriggerCount->Wrap( -1 );
	bSizer24->Add( lblTriggerCount, 0, wxLEFT|wxTOP, 3 );
	
	txtTriggerCount = new wxTextCtrl( pnlEvents, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( txtTriggerCount, 0, wxALL, 3 );
	
	lblIntervalTime = new wxStaticText( pnlEvents, wxID_ANY, wxT("Interval Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblIntervalTime->Wrap( -1 );
	bSizer24->Add( lblIntervalTime, 0, wxLEFT|wxTOP, 3 );
	
	txtIntervalTime = new wxTextCtrl( pnlEvents, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( txtIntervalTime, 0, wxALL, 3 );
	
	lblScore = new wxStaticText( pnlEvents, wxID_ANY, wxT("Score:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblScore->Wrap( -1 );
	bSizer24->Add( lblScore, 0, wxLEFT|wxTOP, 3 );
	
	txtScore = new wxTextCtrl( pnlEvents, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( txtScore, 0, wxALL, 3 );
	
	lblTeam = new wxStaticText( pnlEvents, wxID_ANY, wxT("Team:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTeam->Wrap( -1 );
	bSizer24->Add( lblTeam, 0, wxLEFT|wxTOP, 3 );
	
	wxString cboTeamChoices[] = { wxT("Team 1"), wxT("Team 2") };
	int cboTeamNChoices = sizeof( cboTeamChoices ) / sizeof( wxString );
	cboTeam = new wxChoice( pnlEvents, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboTeamNChoices, cboTeamChoices, 0 );
	cboTeam->SetSelection( 0 );
	bSizer24->Add( cboTeam, 1, wxALL|wxEXPAND, 3 );
	
	chkChained = new wxCheckBox( pnlEvents, wxID_ANY, wxT("Chained Event"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( chkChained, 1, wxALL, 5 );
	
	lblChainDelay = new wxStaticText( pnlEvents, wxID_ANY, wxT("Chain Delay:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblChainDelay->Wrap( -1 );
	bSizer24->Add( lblChainDelay, 0, wxLEFT|wxTOP, 3 );
	
	txtChainDelay = new wxTextCtrl( pnlEvents, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( txtChainDelay, 0, wxALL, 3 );
	
	
	bSizer23->Add( bSizer24, 0, wxEXPAND, 5 );
	
	
	bSizer22->Add( bSizer23, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer9->AddGrowableCol( 1 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblDirectiveText = new wxStaticText( pnlEvents, wxID_ANY, wxT("Directive Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDirectiveText->Wrap( -1 );
	fgSizer9->Add( lblDirectiveText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtDirectiveText = new wxTextCtrl( pnlEvents, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( txtDirectiveText, 1, wxALL|wxEXPAND, 3 );
	
	lblDirectiveKeypress = new wxStaticText( pnlEvents, wxID_ANY, wxT("Directive Keypress Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDirectiveKeypress->Wrap( -1 );
	fgSizer9->Add( lblDirectiveKeypress, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtDirectiveKeypress = new wxTextCtrl( pnlEvents, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( txtDirectiveKeypress, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer22->Add( fgSizer9, 0, wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( pnlEvents, wxID_ANY, wxT("Event Logging") ), wxVERTICAL );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	lblStateLogging = new wxStaticText( sbSizer9->GetStaticBox(), wxID_ANY, wxT("States to log to Event.log:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblStateLogging->Wrap( -1 );
	bSizer25->Add( lblStateLogging, 0, wxALIGN_CENTER|wxALL, 3 );
	
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	chkTrue = new wxCheckBox( sbSizer9->GetStaticBox(), wxID_ANY, wxT("True"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( chkTrue, 0, wxALL, 3 );
	
	chkTrueAlways = new wxCheckBox( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Always True"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( chkTrueAlways, 0, wxALL, 3 );
	
	chkRepeatFirst = new wxCheckBox( sbSizer9->GetStaticBox(), wxID_ANY, wxT("First Repeat"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( chkRepeatFirst, 0, wxALL, 3 );
	
	chkTriggerFirst = new wxCheckBox( sbSizer9->GetStaticBox(), wxID_ANY, wxT("First Trigger"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( chkTriggerFirst, 0, wxALL, 3 );
	
	chkFalse = new wxCheckBox( sbSizer9->GetStaticBox(), wxID_ANY, wxT("False"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( chkFalse, 0, wxALL, 3 );
	
	chkFalseAlways = new wxCheckBox( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Always False"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( chkFalseAlways, 0, wxALL, 3 );
	
	chkRepeatLast = new wxCheckBox( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Last Repeat"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( chkRepeatLast, 0, wxALL, 3 );
	
	chkTriggerLast = new wxCheckBox( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Last Trigger"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( chkTriggerLast, 0, wxALL, 3 );
	
	
	bSizer25->Add( fgSizer10, 1, wxEXPAND, 5 );
	
	
	sbSizer9->Add( bSizer25, 1, wxEXPAND, 5 );
	
	
	bSizer22->Add( sbSizer9, 0, wxALL|wxEXPAND, 3 );
	
	
	pnlEvents->SetSizer( bSizer22 );
	pnlEvents->Layout();
	bSizer22->Fit( pnlEvents );
	bSizer21->Add( pnlEvents, 1, wxEXPAND, 3 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	pnlMessages = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( pnlMessages, wxID_ANY, wxT("Messages") ), wxVERTICAL );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	lstMessages = new wxListBox( sbSizer10->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer27->Add( lstMessages, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer28->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnNewMessage = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( btnNewMessage, 0, wxALL|wxEXPAND, 3 );
	
	btnDeleteMessage = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( btnDeleteMessage, 0, wxALL|wxEXPAND, 3 );
	
	
	bSizer27->Add( bSizer28, 0, wxEXPAND, 5 );
	
	
	sbSizer10->Add( bSizer27, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	lblMessageName = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMessageName->Wrap( -1 );
	bSizer29->Add( lblMessageName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtMessageName = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( txtMessageName, 1, wxALL|wxEXPAND, 3 );
	
	
	sbSizer10->Add( bSizer29, 0, wxEXPAND, 3 );
	
	lblMessageText = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Message Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMessageText->Wrap( -1 );
	sbSizer10->Add( lblMessageText, 0, wxLEFT|wxTOP, 3 );
	
	txtMessageText = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,64 ), wxTE_MULTILINE );
	sbSizer10->Add( txtMessageText, 0, wxALL|wxEXPAND, 3 );
	
	wxGridBagSizer* gbSizer4;
	gbSizer4 = new wxGridBagSizer( 0, 0 );
	gbSizer4->SetFlexibleDirection( wxBOTH );
	gbSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblMessageANI = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("ANI File:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMessageANI->Wrap( -1 );
	gbSizer4->Add( lblMessageANI, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	cboMessageANI = new wxComboBox( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer4->Add( cboMessageANI, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	btnANIBrowse = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( btnANIBrowse, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	lblMessageAudio = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Audio File:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMessageAudio->Wrap( -1 );
	gbSizer4->Add( lblMessageAudio, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	cboMessageAudio = new wxComboBox( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer4->Add( cboMessageAudio, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	btnAudioBrowse = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer30->Add( btnAudioBrowse, 0, wxALL, 3 );
	
	btnPlayAudio = new wxBitmapButton( sbSizer10->GetStaticBox(), wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW );
	bSizer30->Add( btnPlayAudio, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	
	gbSizer4->Add( bSizer30, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxEXPAND, 3 );
	
	lblPersona = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblPersona->Wrap( -1 );
	gbSizer4->Add( lblPersona, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	m_comboBox9 = new wxComboBox( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer4->Add( m_comboBox9, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	btnUpdateStuff = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Update Stuff"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( btnUpdateStuff, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	lblMessageTeam = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Team:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMessageTeam->Wrap( -1 );
	gbSizer4->Add( lblMessageTeam, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboTeamMessageChoices;
	cboTeamMessage = new wxChoice( sbSizer10->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboTeamMessageChoices, 0 );
	cboTeamMessage->SetSelection( 0 );
	gbSizer4->Add( cboTeamMessage, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	m_staticText139 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("(TvT only)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText139->Wrap( -1 );
	gbSizer4->Add( m_staticText139, wxGBPosition( 3, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	sbSizer10->Add( gbSizer4, 0, wxALIGN_CENTER, 5 );
	
	
	pnlMessages->SetSizer( sbSizer10 );
	pnlMessages->Layout();
	sbSizer10->Fit( pnlMessages );
	bSizer26->Add( pnlMessages, 2, wxALL|wxEXPAND, 3 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();
	
	bSizer26->Add( m_sdbSizer2, 0, wxEXPAND, 5 );
	
	
	bSizer21->Add( bSizer26, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer21 );
	this->Layout();
	bSizer21->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgEventsEditor::~dlgEventsEditor()
{
}

frmTeamLoadoutEditor::frmTeamLoadoutEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 226, 226, 226 ) );
	
	mnbDialogMenu = new wxMenuBar( 0 );
	mnuSelectTeam = new wxMenu();
	wxMenuItem* mnuTeam1;
	mnuTeam1 = new wxMenuItem( mnuSelectTeam, wxID_ANY, wxString( wxT("Team 1") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSelectTeam->Append( mnuTeam1 );
	
	wxMenuItem* mnuTeam2;
	mnuTeam2 = new wxMenuItem( mnuSelectTeam, wxID_ANY, wxString( wxT("Team 2") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSelectTeam->Append( mnuTeam2 );
	
	mnbDialogMenu->Append( mnuSelectTeam, wxT("Select Team") ); 
	
	m_menu16 = new wxMenu();
	wxMenuItem* meuBalanceTeams;
	meuBalanceTeams = new wxMenuItem( m_menu16, wxID_ANY, wxString( wxT("Balance Teams") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu16->Append( meuBalanceTeams );
	
	mnbDialogMenu->Append( m_menu16, wxT("Options") ); 
	
	this->SetMenuBar( mnbDialogMenu );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );
	
	lblAvailableStartShips = new wxStaticText( this, wxID_ANY, wxT("Available Starting Ships:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAvailableStartShips->Wrap( -1 );
	bSizer33->Add( lblAvailableStartShips, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3 );
	
	lblShipsFromVariable = new wxStaticText( this, wxID_ANY, wxT("From Variable:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblShipsFromVariable->Wrap( -1 );
	bSizer33->Add( lblShipsFromVariable, 0, wxALL, 3 );
	
	lbxStartShipsVariable = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB|wxLB_SINGLE|wxLB_SORT ); 
	bSizer33->Add( lbxStartShipsVariable, 1, wxALL|wxEXPAND, 3 );
	
	lblShipsFromTbl = new wxStaticText( this, wxID_ANY, wxT("From Table Entry:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblShipsFromTbl->Wrap( -1 );
	bSizer33->Add( lblShipsFromTbl, 0, wxALL, 3 );
	
	wxArrayString cklShipsFromTblChoices;
	cklShipsFromTbl = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cklShipsFromTblChoices, wxLB_ALWAYS_SB|wxLB_SINGLE );
	bSizer33->Add( cklShipsFromTbl, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText141 = new wxStaticText( this, wxID_ANY, wxT("Extra Available:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText141->Wrap( -1 );
	bSizer34->Add( m_staticText141, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnExtraShipsAvailable = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 99, 0 );
	bSizer34->Add( spnExtraShipsAvailable, 0, wxALIGN_RIGHT|wxALL, 3 );
	
	
	bSizer33->Add( bSizer34, 0, wxEXPAND, 3 );
	
	lblSetShipAmountFromVariable = new wxStaticText( this, wxID_ANY, wxT("Set amount from variable:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSetShipAmountFromVariable->Wrap( -1 );
	bSizer33->Add( lblSetShipAmountFromVariable, 0, wxALL, 3 );
	
	wxArrayString cboSetShipAmountFromVariableChoices;
	cboSetShipAmountFromVariable = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboSetShipAmountFromVariableChoices, 0 );
	cboSetShipAmountFromVariable->SetSelection( 0 );
	bSizer33->Add( cboSetShipAmountFromVariable, 0, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );
	
	lblAmountOfShipsInWings = new wxStaticText( this, wxID_ANY, wxT("Amount used in Wings:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAmountOfShipsInWings->Wrap( -1 );
	bSizer35->Add( lblAmountOfShipsInWings, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtAmountOfShipsInWings = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer35->Add( txtAmountOfShipsInWings, 0, wxALL, 3 );
	
	
	bSizer33->Add( bSizer35, 0, 0, 3 );
	
	
	bSizer32->Add( bSizer33, 1, wxALL|wxEXPAND, 3 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer32->Add( m_staticline2, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	lblAvailableStartWeapons = new wxStaticText( this, wxID_ANY, wxT("Available Starting Weapons:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAvailableStartWeapons->Wrap( -1 );
	bSizer36->Add( lblAvailableStartWeapons, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3 );
	
	lblWeaponsFromVariable = new wxStaticText( this, wxID_ANY, wxT("From Variable:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblWeaponsFromVariable->Wrap( -1 );
	bSizer36->Add( lblWeaponsFromVariable, 0, wxALL, 3 );
	
	lbxStartWeaponsVariable = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB|wxLB_SINGLE ); 
	bSizer36->Add( lbxStartWeaponsVariable, 1, wxALL|wxEXPAND, 3 );
	
	lblWeaponsFromTbl = new wxStaticText( this, wxID_ANY, wxT("From Table Entry:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblWeaponsFromTbl->Wrap( -1 );
	bSizer36->Add( lblWeaponsFromTbl, 0, wxALL, 3 );
	
	wxArrayString cklWeaponsFromTblChoices;
	cklWeaponsFromTbl = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cklWeaponsFromTblChoices, wxLB_ALWAYS_SB );
	bSizer36->Add( cklWeaponsFromTbl, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1411 = new wxStaticText( this, wxID_ANY, wxT("Extra available"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1411->Wrap( -1 );
	bSizer37->Add( m_staticText1411, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnExtraWeaponsAvailable = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 99999, 0 );
	bSizer37->Add( spnExtraWeaponsAvailable, 0, wxALIGN_RIGHT|wxALL, 3 );
	
	
	bSizer36->Add( bSizer37, 0, wxEXPAND, 3 );
	
	lblSetWeaponAmountFromVariable = new wxStaticText( this, wxID_ANY, wxT("Set amount from variable"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSetWeaponAmountFromVariable->Wrap( -1 );
	bSizer36->Add( lblSetWeaponAmountFromVariable, 0, wxALL, 3 );
	
	wxArrayString cboSetWeaponAmountFromVariableChoices;
	cboSetWeaponAmountFromVariable = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboSetWeaponAmountFromVariableChoices, 0 );
	cboSetWeaponAmountFromVariable->SetSelection( 0 );
	bSizer36->Add( cboSetWeaponAmountFromVariable, 0, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );
	
	lblAmountOfWeaponsInWings = new wxStaticText( this, wxID_ANY, wxT("Amount used in Wings:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAmountOfWeaponsInWings->Wrap( -1 );
	bSizer38->Add( lblAmountOfWeaponsInWings, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtAmountOfWeaponsInWings = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer38->Add( txtAmountOfWeaponsInWings, 0, wxALL, 3 );
	
	
	bSizer36->Add( bSizer38, 0, 0, 3 );
	
	
	bSizer32->Add( bSizer36, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer31->Add( bSizer32, 1, wxEXPAND, 5 );
	
	m_sdbSizer3 = new wxStdDialogButtonSizer();
	m_sdbSizer3OK = new wxButton( this, wxID_OK );
	m_sdbSizer3->AddButton( m_sdbSizer3OK );
	m_sdbSizer3Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer3->AddButton( m_sdbSizer3Cancel );
	m_sdbSizer3->Realize();
	
	bSizer31->Add( m_sdbSizer3, 0, wxALL|wxEXPAND, 3 );
	
	
	this->SetSizer( bSizer31 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

frmTeamLoadoutEditor::~frmTeamLoadoutEditor()
{
}

dlgBackgroundEditor::dlgBackgroundEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString cboBackgroundPresetChoices[] = { wxT("Background 1"), wxT("Background 2") };
	int cboBackgroundPresetNChoices = sizeof( cboBackgroundPresetChoices ) / sizeof( wxString );
	cboBackgroundPreset = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboBackgroundPresetNChoices, cboBackgroundPresetChoices, 0 );
	cboBackgroundPreset->SetSelection( 0 );
	bSizer41->Add( cboBackgroundPreset, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnImportBackground = new wxButton( this, wxID_ANY, wxT("Import"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer41->Add( btnImportBackground, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer40->Add( bSizer41, 0, 0, 5 );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Bitmaps") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );
	
	lclBGBitmaps = new wxListCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON|wxLC_SINGLE_SEL );
	bSizer42->Add( lclBGBitmaps, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxHORIZONTAL );
	
	btnBitmapAdd = new wxButton( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer43->Add( btnBitmapAdd, 1, wxALL|wxEXPAND, 3 );
	
	btnBitmapDelete = new wxButton( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer43->Add( btnBitmapDelete, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer42->Add( bSizer43, 0, wxEXPAND, 3 );
	
	
	sbSizer11->Add( bSizer42, 0, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer45;
	bSizer45 = new wxBoxSizer( wxHORIZONTAL );
	
	lblBitmap = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Bitmap:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmap->Wrap( -1 );
	bSizer45->Add( lblBitmap, 0, wxALIGN_CENTER|wxALL, 5 );
	
	wxArrayString cboBitmapSelectChoices;
	cboBitmapSelect = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboBitmapSelectChoices, 0 );
	cboBitmapSelect->SetSelection( 0 );
	bSizer45->Add( cboBitmapSelect, 0, wxALIGN_CENTER|wxALL, 3 );
	
	
	bSizer44->Add( bSizer45, 0, wxALIGN_CENTER|wxALL, 3 );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblBitmapPitch = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Pitch:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapPitch->Wrap( -1 );
	fgSizer11->Add( lblBitmapPitch, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblBitmapBank = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Bank:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapBank->Wrap( -1 );
	fgSizer11->Add( lblBitmapBank, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblBitmapHeading = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Heading:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapHeading->Wrap( -1 );
	fgSizer11->Add( lblBitmapHeading, 0, wxALIGN_CENTER|wxALL, 3 );
	
	spnBitmapPitch = new wxSpinCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer11->Add( spnBitmapPitch, 0, wxALL, 3 );
	
	spnBitmapBank = new wxSpinCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer11->Add( spnBitmapBank, 0, wxALL, 3 );
	
	spnBitmapHeading = new wxSpinCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer11->Add( spnBitmapHeading, 0, wxALL, 3 );
	
	
	bSizer44->Add( fgSizer11, 0, wxALIGN_CENTER|wxALL, 3 );
	
	wxGridBagSizer* gbSizer5;
	gbSizer5 = new wxGridBagSizer( 0, 0 );
	gbSizer5->SetFlexibleDirection( wxBOTH );
	gbSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblBitmapScale = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Scale (x/y):"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapScale->Wrap( -1 );
	gbSizer5->Add( lblBitmapScale, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER|wxALL, 3 );
	
	spnBitmapScaleX = new wxSpinCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxSize( 74,-1 ), wxSP_ARROW_KEYS, 0, 18, 1 );
	gbSizer5->Add( spnBitmapScaleX, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL, 3 );
	
	spnBitmapScaleY = new wxSpinCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxSize( 74,-1 ), wxSP_ARROW_KEYS, 0, 18, 1 );
	gbSizer5->Add( spnBitmapScaleY, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL, 3 );
	
	
	bSizer44->Add( gbSizer5, 0, wxALIGN_CENTER|wxALL, 3 );
	
	wxGridBagSizer* gbSizer6;
	gbSizer6 = new wxGridBagSizer( 0, 0 );
	gbSizer6->SetFlexibleDirection( wxBOTH );
	gbSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblBitmapDivisions = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("# of Divisions (x/y):"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapDivisions->Wrap( -1 );
	gbSizer6->Add( lblBitmapDivisions, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER|wxALL, 3 );
	
	spnBitmapDivisionsX = new wxSpinCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxSize( 74,-1 ), wxSP_ARROW_KEYS, 0, 18, 1 );
	gbSizer6->Add( spnBitmapDivisionsX, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL, 3 );
	
	spnBitmapDivisionsY = new wxSpinCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxSize( 74,-1 ), wxSP_ARROW_KEYS, 0, 18, 1 );
	gbSizer6->Add( spnBitmapDivisionsY, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER|wxALL, 3 );
	
	
	bSizer44->Add( gbSizer6, 0, wxALIGN_CENTER|wxALL, 3 );
	
	
	sbSizer11->Add( bSizer44, 0, wxEXPAND, 5 );
	
	
	bSizer40->Add( sbSizer11, 1, wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Nebula") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxVERTICAL );
	
	chkFullNebula = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Full Nebula"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer46->Add( chkFullNebula, 0, wxALL, 3 );
	
	chkToggleShipTrails = new wxCheckBox( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Toggle ship trails"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer46->Add( chkToggleShipTrails, 0, wxALL, 3 );
	
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblNebulaRange = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Range:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblNebulaRange->Wrap( -1 );
	fgSizer12->Add( lblNebulaRange, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtNebulaRange = new wxTextCtrl( sbSizer12->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer12->Add( txtNebulaRange, 0, wxALL|wxEXPAND, 3 );
	
	lblNebulaPattern = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Pattern:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblNebulaPattern->Wrap( -1 );
	fgSizer12->Add( lblNebulaPattern, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxString cboNebulaPatternChoices[] = { wxT("nbackblue1"), wxT("nbackblue2"), wxT("nbackcyan"), wxT("nbackgreen"), wxT("nbackpurp1"), wxT("nbackpurp2"), wxT("nbackred"), wxT("nbackblack") };
	int cboNebulaPatternNChoices = sizeof( cboNebulaPatternChoices ) / sizeof( wxString );
	cboNebulaPattern = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboNebulaPatternNChoices, cboNebulaPatternChoices, 0 );
	cboNebulaPattern->SetSelection( 0 );
	fgSizer12->Add( cboNebulaPattern, 0, wxALL|wxEXPAND, 3 );
	
	lblLightningStorm = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Lightning Storm:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblLightningStorm->Wrap( -1 );
	fgSizer12->Add( lblLightningStorm, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxString cboLightningStormChoices[] = { wxT("none"), wxT("s&standard"), wxT("s&active"), wxT("s&emp"), wxT("s&medium") };
	int cboLightningStormNChoices = sizeof( cboLightningStormChoices ) / sizeof( wxString );
	cboLightningStorm = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboLightningStormNChoices, cboLightningStormChoices, 0 );
	cboLightningStorm->SetSelection( 0 );
	fgSizer12->Add( cboLightningStorm, 0, wxALL|wxEXPAND, 3 );
	
	lblNebulaFogNear = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Fog Near:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblNebulaFogNear->Wrap( -1 );
	fgSizer12->Add( lblNebulaFogNear, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	m_spinCtrl49 = new wxSpinCtrl( sbSizer12->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer12->Add( m_spinCtrl49, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblNebulaFogMultiplier = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Fog Multiplier:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblNebulaFogMultiplier->Wrap( -1 );
	fgSizer12->Add( lblNebulaFogMultiplier, 0, wxALL, 5 );
	
	m_spinCtrl50 = new wxSpinCtrl( sbSizer12->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer12->Add( m_spinCtrl50, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer46->Add( fgSizer12, 0, wxEXPAND, 5 );
	
	
	sbSizer12->Add( bSizer46, 0, 0, 5 );
	
	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxVERTICAL );
	
	lblNebulaPoofs = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Nebula Poofs:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblNebulaPoofs->Wrap( -1 );
	bSizer47->Add( lblNebulaPoofs, 0, wxALL, 3 );
	
	wxString clbNebulaPoofsChoices[] = { wxT("PoofGreen01"), wxT("PoofGreen02"), wxT("PoofRed01"), wxT("PoofRed02"), wxT("PoofPurp01"), wxT("PoofPurp02") };
	int clbNebulaPoofsNChoices = sizeof( clbNebulaPoofsChoices ) / sizeof( wxString );
	clbNebulaPoofs = new wxCheckListBox( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, clbNebulaPoofsNChoices, clbNebulaPoofsChoices, wxLB_ALWAYS_SB );
	bSizer47->Add( clbNebulaPoofs, 1, wxALL|wxEXPAND, 3 );
	
	
	sbSizer12->Add( bSizer47, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer40->Add( sbSizer12, 0, wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer13;
	sbSizer13 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("FS1 Nebula") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText160 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Pattern:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText160->Wrap( -1 );
	fgSizer13->Add( m_staticText160, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxString cboNebulaPattern1Choices[] = { wxT("None"), wxT("Pattern01"), wxT("Pattern02"), wxT("Pattern03") };
	int cboNebulaPattern1NChoices = sizeof( cboNebulaPattern1Choices ) / sizeof( wxString );
	cboNebulaPattern1 = new wxChoice( sbSizer13->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboNebulaPattern1NChoices, cboNebulaPattern1Choices, 0 );
	cboNebulaPattern1->SetSelection( 0 );
	fgSizer13->Add( cboNebulaPattern1, 0, wxALL|wxEXPAND, 3 );
	
	m_staticText161 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText161->Wrap( -1 );
	fgSizer13->Add( m_staticText161, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxString cboNebulaColourChoices[] = { wxT("Red"), wxT("Blue"), wxT("Gold"), wxT("Purple"), wxT("Maroon"), wxT("Green"), wxT("Grey Blue"), wxT("Violet"), wxT("Grey Green") };
	int cboNebulaColourNChoices = sizeof( cboNebulaColourChoices ) / sizeof( wxString );
	cboNebulaColour = new wxChoice( sbSizer13->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboNebulaColourNChoices, cboNebulaColourChoices, 0 );
	cboNebulaColour->SetSelection( 0 );
	fgSizer13->Add( cboNebulaColour, 0, wxALL|wxEXPAND, 3 );
	
	
	sbSizer13->Add( fgSizer13, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblBitmapPitch2 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Pitch:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapPitch2->Wrap( -1 );
	fgSizer14->Add( lblBitmapPitch2, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblBitmapBank2 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Bank:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapBank2->Wrap( -1 );
	fgSizer14->Add( lblBitmapBank2, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblBitmapHeading2 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Heading:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapHeading2->Wrap( -1 );
	fgSizer14->Add( lblBitmapHeading2, 0, wxALIGN_CENTER|wxALL, 3 );
	
	spnBitmapPitch2 = new wxSpinCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer14->Add( spnBitmapPitch2, 0, wxALL, 3 );
	
	spnBitmapBank2 = new wxSpinCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer14->Add( spnBitmapBank2, 0, wxALL, 3 );
	
	spnBitmapHeading2 = new wxSpinCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer14->Add( spnBitmapHeading2, 0, wxALL, 3 );
	
	
	sbSizer13->Add( fgSizer14, 0, wxALIGN_CENTER|wxALL, 3 );
	
	
	bSizer40->Add( sbSizer13, 0, wxEXPAND, 3 );
	
	
	bSizer39->Add( bSizer40, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxHORIZONTAL );
	
	btnBGSwap = new wxButton( this, wxID_ANY, wxT("Swap with"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer49->Add( btnBGSwap, 0, wxALL, 3 );
	
	wxString cboBackgroundSwapChoices[] = { wxT("Background 1"), wxT("Background 2") };
	int cboBackgroundSwapNChoices = sizeof( cboBackgroundSwapChoices ) / sizeof( wxString );
	cboBackgroundSwap = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboBackgroundSwapNChoices, cboBackgroundSwapChoices, 0 );
	cboBackgroundSwap->SetSelection( 0 );
	bSizer49->Add( cboBackgroundSwap, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer48->Add( bSizer49, 0, wxALIGN_RIGHT, 5 );
	
	wxStaticBoxSizer* sbSizer14;
	sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Suns") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxVERTICAL );
	
	lclBGSunbitmaps = new wxListCtrl( sbSizer14->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON );
	bSizer50->Add( lclBGSunbitmaps, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );
	
	btnAddSunBitmap = new wxButton( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( btnAddSunBitmap, 1, wxALL|wxEXPAND, 3 );
	
	btnDeleteSunBitmap = new wxButton( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51->Add( btnDeleteSunBitmap, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer50->Add( bSizer51, 0, wxEXPAND, 3 );
	
	
	sbSizer14->Add( bSizer50, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer53;
	bSizer53 = new wxBoxSizer( wxHORIZONTAL );
	
	lblSun = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Sun:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSun->Wrap( -1 );
	bSizer53->Add( lblSun, 0, wxALIGN_CENTER|wxALL, 3 );
	
	wxArrayString cboSunSelectChoices;
	cboSunSelect = new wxChoice( sbSizer14->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboSunSelectChoices, 0 );
	cboSunSelect->SetSelection( 0 );
	bSizer53->Add( cboSunSelect, 0, wxALL, 3 );
	
	
	bSizer52->Add( bSizer53, 0, wxALIGN_CENTER|wxALL, 3 );
	
	wxFlexGridSizer* fgSizer15;
	fgSizer15 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer15->SetFlexibleDirection( wxBOTH );
	fgSizer15->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblBitmapPitch1 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Pitch:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapPitch1->Wrap( -1 );
	fgSizer15->Add( lblBitmapPitch1, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblBitmapBank1 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Bank:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapBank1->Wrap( -1 );
	fgSizer15->Add( lblBitmapBank1, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblBitmapHeading1 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Heading:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapHeading1->Wrap( -1 );
	fgSizer15->Add( lblBitmapHeading1, 0, wxALIGN_CENTER|wxALL, 3 );
	
	spnBitmapPitch1 = new wxSpinCtrl( sbSizer14->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer15->Add( spnBitmapPitch1, 0, wxALL, 3 );
	
	spnBitmapBank1 = new wxSpinCtrl( sbSizer14->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer15->Add( spnBitmapBank1, 0, wxALL, 3 );
	
	spnBitmapHeading1 = new wxSpinCtrl( sbSizer14->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer15->Add( spnBitmapHeading1, 0, wxALL, 3 );
	
	
	bSizer52->Add( fgSizer15, 1, wxALIGN_CENTER|wxALL, 3 );
	
	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText179 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Scale:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText179->Wrap( -1 );
	bSizer54->Add( m_staticText179, 0, wxALIGN_CENTER|wxALL, 3 );
	
	spnSunScale = new wxSpinCtrl( sbSizer14->GetStaticBox(), wxID_ANY, wxT("10"), wxDefaultPosition, wxSize( 74,-1 ), wxSP_ARROW_KEYS, 0, 10, 10 );
	bSizer54->Add( spnSunScale, 0, wxALL, 3 );
	
	
	bSizer52->Add( bSizer54, 0, wxALIGN_CENTER|wxALL|wxSHAPED, 3 );
	
	
	sbSizer14->Add( bSizer52, 1, 0, 5 );
	
	
	bSizer48->Add( sbSizer14, 1, wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer15;
	sbSizer15 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Ambient Light") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer16;
	fgSizer16 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer16->AddGrowableCol( 1 );
	fgSizer16->SetFlexibleDirection( wxBOTH );
	fgSizer16->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblAmbientRed = new wxStaticText( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Red:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAmbientRed->Wrap( -1 );
	fgSizer16->Add( lblAmbientRed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	sldAmbientRed = new wxSlider( sbSizer15->GetStaticBox(), wxID_ANY, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	fgSizer16->Add( sldAmbientRed, 1, wxALL|wxEXPAND, 3 );
	
	spnAmbientRed = new wxSpinCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 48,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer16->Add( spnAmbientRed, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblAmbientGreen = new wxStaticText( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Green:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAmbientGreen->Wrap( -1 );
	fgSizer16->Add( lblAmbientGreen, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	sldAmbientGreen = new wxSlider( sbSizer15->GetStaticBox(), wxID_ANY, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	fgSizer16->Add( sldAmbientGreen, 0, wxALL|wxEXPAND, 3 );
	
	spnAmbientGreen = new wxSpinCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 48,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer16->Add( spnAmbientGreen, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblAmbientBlue = new wxStaticText( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Blue:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAmbientBlue->Wrap( -1 );
	fgSizer16->Add( lblAmbientBlue, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	sldAmbientBlue = new wxSlider( sbSizer15->GetStaticBox(), wxID_ANY, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	fgSizer16->Add( sldAmbientBlue, 0, wxALL|wxEXPAND, 3 );
	
	spnAmbientBlue = new wxSpinCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 48,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer16->Add( spnAmbientBlue, 0, wxALIGN_CENTER|wxALL, 3 );
	
	
	sbSizer15->Add( fgSizer16, 0, wxEXPAND, 5 );
	
	
	bSizer48->Add( sbSizer15, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Skybox") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer17;
	fgSizer17 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer17->AddGrowableCol( 1 );
	fgSizer17->SetFlexibleDirection( wxBOTH );
	fgSizer17->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	btnSkyboxSelect = new wxButton( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Skybox Model"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( btnSkyboxSelect, 0, wxALL|wxEXPAND, 3 );
	
	txtSkybox = new wxTextCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( txtSkybox, 0, wxALL|wxEXPAND, 3 );
	
	btnSkyboxMap = new wxButton( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Skybox Map"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSkyboxMap->Enable( false );
	
	fgSizer17->Add( btnSkyboxMap, 0, wxALL|wxEXPAND, 3 );
	
	m_textCtrl73 = new wxTextCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Coming Soon!"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl73->Enable( false );
	
	fgSizer17->Add( m_textCtrl73, 0, wxALL|wxEXPAND, 3 );
	
	
	sbSizer16->Add( fgSizer17, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblBitmapPitch21 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Pitch:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapPitch21->Wrap( -1 );
	fgSizer18->Add( lblBitmapPitch21, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblBitmapBank21 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Bank:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapBank21->Wrap( -1 );
	fgSizer18->Add( lblBitmapBank21, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblBitmapHeading21 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Heading:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBitmapHeading21->Wrap( -1 );
	fgSizer18->Add( lblBitmapHeading21, 0, wxALIGN_CENTER|wxALL, 3 );
	
	spnBitmapPitch21 = new wxSpinCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer18->Add( spnBitmapPitch21, 0, wxALL, 3 );
	
	spnBitmapBank21 = new wxSpinCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer18->Add( spnBitmapBank21, 0, wxALL, 3 );
	
	spnBitmapHeading21 = new wxSpinCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 58,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 359, 0 );
	fgSizer18->Add( spnBitmapHeading21, 0, wxALL, 3 );
	
	
	bSizer55->Add( fgSizer18, 0, 0, 5 );
	
	wxFlexGridSizer* fgSizer19;
	fgSizer19 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	chkSBNoCull = new wxCheckBox( sbSizer16->GetStaticBox(), wxID_ANY, wxT("No Cull"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( chkSBNoCull, 0, wxALL, 3 );
	
	chkSBNoGlowmaps = new wxCheckBox( sbSizer16->GetStaticBox(), wxID_ANY, wxT("No Glowmaps"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( chkSBNoGlowmaps, 0, wxALL, 3 );
	
	chkSBNoLighting = new wxCheckBox( sbSizer16->GetStaticBox(), wxID_ANY, wxT("No Lighting"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( chkSBNoLighting, 0, wxALL, 3 );
	
	chkSBNoZBuffer = new wxCheckBox( sbSizer16->GetStaticBox(), wxID_ANY, wxT("No Z-Buffer"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( chkSBNoZBuffer, 0, wxALL, 3 );
	
	chkSBForceClamp = new wxCheckBox( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Force Clamp"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( chkSBForceClamp, 0, wxALL, 3 );
	
	chkSBTransparent = new wxCheckBox( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Transparent"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( chkSBTransparent, 0, wxALL, 3 );
	
	
	bSizer55->Add( fgSizer19, 0, wxEXPAND, 5 );
	
	
	sbSizer16->Add( bSizer55, 1, wxEXPAND, 5 );
	
	
	bSizer48->Add( sbSizer16, 1, wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer17;
	sbSizer17 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Misc.") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer20;
	fgSizer20 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer20->AddGrowableCol( 1 );
	fgSizer20->SetFlexibleDirection( wxBOTH );
	fgSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText186 = new wxStaticText( sbSizer17->GetStaticBox(), wxID_ANY, wxT("Number of Stars:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText186->Wrap( -1 );
	fgSizer20->Add( m_staticText186, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	sldNumStars = new wxSlider( sbSizer17->GetStaticBox(), wxID_ANY, 500, 0, 2000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	fgSizer20->Add( sldNumStars, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	m_spinCtrl43 = new wxSpinCtrl( sbSizer17->GetStaticBox(), wxID_ANY, wxT("500"), wxDefaultPosition, wxSize( 62,-1 ), wxSP_ARROW_KEYS, 0, 2000, 500 );
	fgSizer20->Add( m_spinCtrl43, 0, wxALIGN_CENTER|wxALL, 3 );
	
	
	sbSizer17->Add( fgSizer20, 0, wxEXPAND, 5 );
	
	m_checkBox48 = new wxCheckBox( sbSizer17->GetStaticBox(), wxID_ANY, wxT("Takes place inside Subspace"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer17->Add( m_checkBox48, 0, wxALL, 3 );
	
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer21->AddGrowableCol( 1 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	btnEnvMap = new wxButton( sbSizer17->GetStaticBox(), wxID_ANY, wxT("Environment Map"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( btnEnvMap, 0, wxALL|wxEXPAND, 3 );
	
	txtEnvMap = new wxTextCtrl( sbSizer17->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( txtEnvMap, 0, wxALL|wxEXPAND, 3 );
	
	
	sbSizer17->Add( fgSizer21, 0, wxEXPAND, 5 );
	
	
	bSizer48->Add( sbSizer17, 0, wxEXPAND, 3 );
	
	
	bSizer39->Add( bSizer48, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer39 );
	this->Layout();
	bSizer39->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgBackgroundEditor::~dlgBackgroundEditor()
{
}

dlgReinforcementsEditor::dlgReinforcementsEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridBagSizer* gbSizer7;
	gbSizer7 = new wxGridBagSizer( 0, 0 );
	gbSizer7->SetFlexibleDirection( wxBOTH );
	gbSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblReinforcements = new wxStaticText( this, wxID_ANY, wxT("Reinforced Wings:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblReinforcements->Wrap( -1 );
	gbSizer7->Add( lblReinforcements, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	lstReinforcements = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB ); 
	gbSizer7->Add( lstReinforcements, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxVERTICAL );
	
	btnAdd = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( btnAdd, 0, wxALL, 3 );
	
	btnDelete = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( btnDelete, 0, wxALL, 3 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer56->Add( m_staticline3, 0, wxEXPAND|wxALL, 3 );
	
	btnOk = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( btnOk, 0, wxALL, 3 );
	
	btnCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( btnCancel, 0, wxALL, 3 );
	
	
	gbSizer7->Add( bSizer56, wxGBPosition( 0, 1 ), wxGBSpan( 2, 1 ), 0, 5 );
	
	wxFlexGridSizer* fgSizer22;
	fgSizer22 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer22->SetFlexibleDirection( wxBOTH );
	fgSizer22->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblUses = new wxStaticText( this, wxID_ANY, wxT("Uses:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblUses->Wrap( -1 );
	fgSizer22->Add( lblUses, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 3 );
	
	spnUses = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 64,-1 ), wxSP_ARROW_KEYS, 0, 1000, 0 );
	fgSizer22->Add( spnUses, 0, wxALL, 3 );
	
	
	fgSizer22->Add( 50, 0, 1, wxEXPAND, 5 );
	
	lblDelayAfterArrival = new wxStaticText( this, wxID_ANY, wxT("Delay After Arrival:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDelayAfterArrival->Wrap( -1 );
	fgSizer22->Add( lblDelayAfterArrival, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnDelayAfterArrival = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 64,-1 ), wxSP_ARROW_KEYS, 0, 1000, 0 );
	fgSizer22->Add( spnDelayAfterArrival, 0, wxALL, 3 );
	
	
	gbSizer7->Add( fgSizer22, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	
	gbSizer7->AddGrowableCol( 0 );
	gbSizer7->AddGrowableRow( 0 );
	
	this->SetSizer( gbSizer7 );
	this->Layout();
	gbSizer7->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgReinforcementsEditor::~dlgReinforcementsEditor()
{
}

dlgReinforcementsPicker::dlgReinforcementsPicker( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxHORIZONTAL );
	
	lstReincforcements = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 200,200 ), wxLC_LIST );
	bSizer57->Add( lstReincforcements, 0, wxALL|wxEXPAND, 8 );
	
	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxVERTICAL );
	
	btnOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer58->Add( btnOK, 0, wxALL, 3 );
	
	btnCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer58->Add( btnCancel, 0, wxALL, 3 );
	
	
	bSizer57->Add( bSizer58, 1, wxALIGN_BOTTOM|wxBOTTOM|wxRIGHT, 8 );
	
	
	this->SetSizer( bSizer57 );
	this->Layout();
	bSizer57->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgReinforcementsPicker::~dlgReinforcementsPicker()
{
}

dlgAsteroidFieldEditor::dlgAsteroidFieldEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxVERTICAL );
	
	chkAsteroidsEnabled = new wxCheckBox( this, wxID_ANY, wxT("Enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( chkAsteroidsEnabled, 1, wxALL, 5 );
	
	wxBoxSizer* bSizer60;
	bSizer60 = new wxBoxSizer( wxHORIZONTAL );
	
	pFieldProperties = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer18;
	sbSizer18 = new wxStaticBoxSizer( new wxStaticBox( pFieldProperties, wxID_ANY, wxT("Field Properties") ), wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer19;
	sbSizer19 = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, wxT("Mode") ), wxHORIZONTAL );
	
	optFieldActive = new wxRadioButton( sbSizer19->GetStaticBox(), wxID_ANY, wxT("Active Field"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	optFieldActive->SetValue( true ); 
	sbSizer19->Add( optFieldActive, 1, wxALL|wxEXPAND, 3 );
	
	optFieldPassive = new wxRadioButton( sbSizer19->GetStaticBox(), wxID_ANY, wxT("Passive Field"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer19->Add( optFieldPassive, 1, wxALL|wxEXPAND, 3 );
	
	
	sbSizer18->Add( sbSizer19, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer20;
	sbSizer20 = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, wxT("Content") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer8;
	gbSizer8 = new wxGridBagSizer( 0, 0 );
	gbSizer8->SetFlexibleDirection( wxBOTH );
	gbSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	optFieldtypeAsteroid = new wxRadioButton( sbSizer20->GetStaticBox(), wxID_ANY, wxT("Asteroid"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	gbSizer8->Add( optFieldtypeAsteroid, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	optFieldTypeShip = new wxRadioButton( sbSizer20->GetStaticBox(), wxID_ANY, wxT("Ship"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer8->Add( optFieldTypeShip, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	chkBrownRocks = new wxCheckBox( sbSizer20->GetStaticBox(), wxID_ANY, wxT("Brown"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer8->Add( chkBrownRocks, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboObjType1Choices;
	cboObjType1 = new wxChoice( sbSizer20->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboObjType1Choices, 0 );
	cboObjType1->SetSelection( 0 );
	gbSizer8->Add( cboObjType1, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	chkBlueRocks = new wxCheckBox( sbSizer20->GetStaticBox(), wxID_ANY, wxT("Blue"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer8->Add( chkBlueRocks, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboObjType2Choices;
	cboObjType2 = new wxChoice( sbSizer20->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboObjType2Choices, 0 );
	cboObjType2->SetSelection( 0 );
	gbSizer8->Add( cboObjType2, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	chkOrangeRocks = new wxCheckBox( sbSizer20->GetStaticBox(), wxID_ANY, wxT("Orange"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer8->Add( chkOrangeRocks, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboObjType3Choices;
	cboObjType3 = new wxChoice( sbSizer20->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboObjType3Choices, 0 );
	cboObjType3->SetSelection( 0 );
	gbSizer8->Add( cboObjType3, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	m_staticline1 = new wxStaticLine( sbSizer20->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	gbSizer8->Add( m_staticline1, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxALL, 5 );
	
	lblNumberObjects = new wxStaticText( sbSizer20->GetStaticBox(), wxID_ANY, wxT("Number:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblNumberObjects->Wrap( -1 );
	gbSizer8->Add( lblNumberObjects, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnObjects = new wxSpinCtrl( sbSizer20->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	gbSizer8->Add( spnObjects, wxGBPosition( 5, 1 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	m_staticText68 = new wxStaticText( sbSizer20->GetStaticBox(), wxID_ANY, wxT("Avg. Speed:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText68->Wrap( -1 );
	gbSizer8->Add( m_staticText68, wxGBPosition( 6, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	numAvgSpeed = new wxTextCtrl( sbSizer20->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer8->Add( numAvgSpeed, wxGBPosition( 6, 1 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	
	sbSizer20->Add( gbSizer8, 1, wxEXPAND, 5 );
	
	
	sbSizer18->Add( sbSizer20, 0, wxALL|wxEXPAND, 3 );
	
	
	pFieldProperties->SetSizer( sbSizer18 );
	pFieldProperties->Layout();
	sbSizer18->Fit( pFieldProperties );
	bSizer60->Add( pFieldProperties, 1, wxEXPAND|wxALL, 3 );
	
	pBoundingBoxes = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( pBoundingBoxes, wxID_ANY, wxT("Outer Box") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer23;
	fgSizer23 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer23->SetFlexibleDirection( wxBOTH );
	fgSizer23->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer23->Add( 0, 0, 1, wxEXPAND, 5 );
	
	lblOuterMinimum = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, wxT("Minimum:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOuterMinimum->Wrap( -1 );
	fgSizer23->Add( lblOuterMinimum, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblOuterMaximum = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, wxT("Maximum:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOuterMaximum->Wrap( -1 );
	fgSizer23->Add( lblOuterMaximum, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblOuterX = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, wxT("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOuterX->Wrap( -1 );
	fgSizer23->Add( lblOuterX, 0, wxALIGN_CENTER|wxALL, 3 );
	
	txtOuterMinimumX = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer23->Add( txtOuterMinimumX, 0, wxALL, 3 );
	
	txtOuterMaximumX = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer23->Add( txtOuterMaximumX, 0, wxALL, 3 );
	
	lblOuterY = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, wxT("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOuterY->Wrap( -1 );
	fgSizer23->Add( lblOuterY, 0, wxALIGN_CENTER|wxALL, 3 );
	
	txtOuterMinimumY = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer23->Add( txtOuterMinimumY, 0, wxALL, 3 );
	
	txtOuterMaximumY = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer23->Add( txtOuterMaximumY, 0, wxALL, 3 );
	
	lblOuterZ = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, wxT("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOuterZ->Wrap( -1 );
	fgSizer23->Add( lblOuterZ, 0, wxALIGN_CENTER|wxALL, 3 );
	
	txtOuterMinimumZ = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer23->Add( txtOuterMinimumZ, 0, wxALL, 3 );
	
	txtOuterMaximumZ = new wxTextCtrl( sbSizer21->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer23->Add( txtOuterMaximumZ, 0, wxALL, 3 );
	
	
	sbSizer21->Add( fgSizer23, 0, wxEXPAND, 3 );
	
	
	bSizer61->Add( sbSizer21, 0, wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer22;
	sbSizer22 = new wxStaticBoxSizer( new wxStaticBox( pBoundingBoxes, wxID_ANY, wxT("Inner Box") ), wxVERTICAL );
	
	chkInnerBoxEnable = new wxCheckBox( sbSizer22->GetStaticBox(), wxID_ANY, wxT("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer22->Add( chkInnerBoxEnable, 0, wxALL, 3 );
	
	wxFlexGridSizer* fgSizer24;
	fgSizer24 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer24->SetFlexibleDirection( wxBOTH );
	fgSizer24->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer24->Add( 0, 0, 1, wxEXPAND, 3 );
	
	lblInnerMinimum = new wxStaticText( sbSizer22->GetStaticBox(), wxID_ANY, wxT("Minimum:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	lblInnerMinimum->Wrap( -1 );
	fgSizer24->Add( lblInnerMinimum, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblInnerMaximum = new wxStaticText( sbSizer22->GetStaticBox(), wxID_ANY, wxT("Maximum:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	lblInnerMaximum->Wrap( -1 );
	fgSizer24->Add( lblInnerMaximum, 0, wxALIGN_CENTER|wxALL, 3 );
	
	lblInnerX = new wxStaticText( sbSizer22->GetStaticBox(), wxID_ANY, wxT("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblInnerX->Wrap( -1 );
	fgSizer24->Add( lblInnerX, 0, wxALIGN_CENTER|wxALL, 3 );
	
	numInnerBoxMinX = new wxTextCtrl( sbSizer22->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( numInnerBoxMinX, 0, wxALL, 3 );
	
	numInnerBoxMaxX = new wxTextCtrl( sbSizer22->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( numInnerBoxMaxX, 0, wxALL, 3 );
	
	lblInnerY = new wxStaticText( sbSizer22->GetStaticBox(), wxID_ANY, wxT("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblInnerY->Wrap( -1 );
	fgSizer24->Add( lblInnerY, 0, wxALIGN_CENTER|wxALL, 3 );
	
	numInnerBoxMinY = new wxTextCtrl( sbSizer22->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( numInnerBoxMinY, 0, wxALL, 3 );
	
	numInnerBoxMaxY = new wxTextCtrl( sbSizer22->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( numInnerBoxMaxY, 0, wxALL, 3 );
	
	lblInnerZ = new wxStaticText( sbSizer22->GetStaticBox(), wxID_ANY, wxT("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblInnerZ->Wrap( -1 );
	fgSizer24->Add( lblInnerZ, 0, wxALIGN_CENTER|wxALL, 3 );
	
	numInnerBoxMinZ = new wxTextCtrl( sbSizer22->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( numInnerBoxMinZ, 0, wxALL, 3 );
	
	numInnerBoxMaxZ = new wxTextCtrl( sbSizer22->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( numInnerBoxMaxZ, 0, wxALL, 3 );
	
	
	sbSizer22->Add( fgSizer24, 0, wxEXPAND, 3 );
	
	
	bSizer61->Add( sbSizer22, 0, wxEXPAND, 3 );
	
	
	pBoundingBoxes->SetSizer( bSizer61 );
	pBoundingBoxes->Layout();
	bSizer61->Fit( pBoundingBoxes );
	bSizer60->Add( pBoundingBoxes, 1, wxEXPAND|wxALL, 3 );
	
	
	bSizer59->Add( bSizer60, 0, wxEXPAND, 5 );
	
	m_sdbSizer4 = new wxStdDialogButtonSizer();
	m_sdbSizer4OK = new wxButton( this, wxID_OK );
	m_sdbSizer4->AddButton( m_sdbSizer4OK );
	m_sdbSizer4Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer4->AddButton( m_sdbSizer4Cancel );
	m_sdbSizer4->Realize();
	
	bSizer59->Add( m_sdbSizer4, 1, wxALIGN_RIGHT|wxALL|wxEXPAND, 3 );
	
	
	this->SetSizer( bSizer59 );
	this->Layout();
	bSizer59->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgAsteroidFieldEditor::~dlgAsteroidFieldEditor()
{
}

dlgMissionSpecsEditor::dlgMissionSpecsEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer25;
	fgSizer25 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer25->AddGrowableCol( 0 );
	fgSizer25->AddGrowableCol( 1 );
	fgSizer25->AddGrowableCol( 2 );
	fgSizer25->SetFlexibleDirection( wxBOTH );
	fgSizer25->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer23;
	sbSizer23 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Meta Info") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer26;
	fgSizer26 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer26->AddGrowableCol( 1 );
	fgSizer26->AddGrowableRow( 0 );
	fgSizer26->SetFlexibleDirection( wxBOTH );
	fgSizer26->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblTitle = new wxStaticText( sbSizer23->GetStaticBox(), wxID_ANY, wxT("Title:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTitle->Wrap( 0 );
	fgSizer26->Add( lblTitle, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 3 );
	
	txtTitle = new wxTextCtrl( sbSizer23->GetStaticBox(), wxID_ANY, wxT("Untitled"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer26->Add( txtTitle, 1, wxALL|wxEXPAND, 3 );
	
	lblDesigner = new wxStaticText( sbSizer23->GetStaticBox(), wxID_ANY, wxT("Designer:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDesigner->Wrap( 0 );
	fgSizer26->Add( lblDesigner, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 3 );
	
	txtDesigner = new wxTextCtrl( sbSizer23->GetStaticBox(), wxID_ANY, wxT("wxFRED"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer26->Add( txtDesigner, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 3 );
	
	lblCreated = new wxStaticText( sbSizer23->GetStaticBox(), wxID_ANY, wxT("Created:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCreated->Wrap( -1 );
	fgSizer26->Add( lblCreated, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtCreated = new wxStaticText( sbSizer23->GetStaticBox(), wxID_ANY, wxT("xx/xx/xx at 00:00 AM"), wxDefaultPosition, wxDefaultSize, 0 );
	txtCreated->Wrap( -1 );
	fgSizer26->Add( txtCreated, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblModified = new wxStaticText( sbSizer23->GetStaticBox(), wxID_ANY, wxT("Last Modified:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblModified->Wrap( -1 );
	fgSizer26->Add( lblModified, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtModified = new wxStaticText( sbSizer23->GetStaticBox(), wxID_ANY, wxT("xx/xx/xx at 00:00 AM"), wxDefaultPosition, wxDefaultSize, 0 );
	txtModified->Wrap( -1 );
	fgSizer26->Add( txtModified, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	sbSizer23->Add( fgSizer26, 0, wxALL|wxEXPAND, 0 );
	
	
	bSizer63->Add( sbSizer23, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer24;
	sbSizer24 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Mission Type") ), wxVERTICAL );
	
	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxVERTICAL );
	
	optSinglePlayer = new wxRadioButton( sbSizer24->GetStaticBox(), wxID_ANY, wxT("Single Player"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	optSinglePlayer->SetValue( true ); 
	bSizer65->Add( optSinglePlayer, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND|wxRIGHT, 2 );
	
	optMultiPlayer = new wxRadioButton( sbSizer24->GetStaticBox(), wxID_ANY, wxT("Multi Player"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( optMultiPlayer, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 2 );
	
	optTraining = new wxRadioButton( sbSizer24->GetStaticBox(), wxID_ANY, wxT("Training"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( optTraining, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 2 );
	
	
	bSizer64->Add( bSizer65, 1, wxEXPAND, 5 );
	
	pnlMultiplayer = new wxPanel( sbSizer24->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pnlMultiplayer->Enable( false );
	
	wxBoxSizer* bSizer66;
	bSizer66 = new wxBoxSizer( wxVERTICAL );
	
	optCooperative = new wxRadioButton( pnlMultiplayer, wxID_ANY, wxT("Cooperative"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	optCooperative->SetValue( true ); 
	optCooperative->Enable( false );
	
	bSizer66->Add( optCooperative, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 2 );
	
	optTeamVsTeam = new wxRadioButton( pnlMultiplayer, wxID_ANY, wxT("Team Vs. Team"), wxDefaultPosition, wxDefaultSize, 0 );
	optTeamVsTeam->Enable( false );
	
	bSizer66->Add( optTeamVsTeam, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 2 );
	
	optDogfight = new wxRadioButton( pnlMultiplayer, wxID_ANY, wxT("Dogfight"), wxDefaultPosition, wxDefaultSize, 0 );
	optDogfight->Enable( false );
	
	bSizer66->Add( optDogfight, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 2 );
	
	
	pnlMultiplayer->SetSizer( bSizer66 );
	pnlMultiplayer->Layout();
	bSizer66->Fit( pnlMultiplayer );
	bSizer64->Add( pnlMultiplayer, 1, wxEXPAND|wxALL, 5 );
	
	
	sbSizer24->Add( bSizer64, 1, wxEXPAND, 0 );
	
	
	bSizer63->Add( sbSizer24, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer25;
	sbSizer25 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Multiplayer") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer27;
	fgSizer27 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer27->AddGrowableCol( 1 );
	fgSizer27->SetFlexibleDirection( wxBOTH );
	fgSizer27->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText75 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, wxT("Max Respawns:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText75->Wrap( -1 );
	fgSizer27->Add( m_staticText75, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxLEFT, 3 );
	
	spnMaxRespawns = new wxSpinCtrl( sbSizer25->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999, 0 );
	spnMaxRespawns->Enable( false );
	
	fgSizer27->Add( spnMaxRespawns, 0, wxALL, 3 );
	
	m_staticText76 = new wxStaticText( sbSizer25->GetStaticBox(), wxID_ANY, wxT("Max Respawn Delay:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText76->Wrap( -1 );
	fgSizer27->Add( m_staticText76, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxLEFT, 3 );
	
	spnMaxRespawnDelay = new wxSpinCtrl( sbSizer25->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -1, 999, 0 );
	spnMaxRespawnDelay->Enable( false );
	
	fgSizer27->Add( spnMaxRespawnDelay, 0, wxALL, 3 );
	
	
	sbSizer25->Add( fgSizer27, 1, wxSHAPED, 0 );
	
	
	bSizer63->Add( sbSizer25, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer26;
	sbSizer26 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Squadron Reassignment") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer28;
	fgSizer28 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer28->AddGrowableCol( 1 );
	fgSizer28->SetFlexibleDirection( wxBOTH );
	fgSizer28->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText74 = new wxStaticText( sbSizer26->GetStaticBox(), wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText74->Wrap( -1 );
	fgSizer28->Add( m_staticText74, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT, 3 );
	
	txtSquadronName = new wxTextCtrl( sbSizer26->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer28->Add( txtSquadronName, 0, wxALL|wxEXPAND, 3 );
	
	btnSquadronLogo = new wxButton( sbSizer26->GetStaticBox(), wxID_ANY, wxT("Logo"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	fgSizer28->Add( btnSquadronLogo, 1, wxALIGN_LEFT|wxALL|wxEXPAND, 3 );
	
	txtSquadronLogo = new wxTextCtrl( sbSizer26->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer28->Add( txtSquadronLogo, 0, wxALL|wxEXPAND, 3 );
	
	
	sbSizer26->Add( fgSizer28, 1, wxEXPAND, 0 );
	
	
	bSizer63->Add( sbSizer26, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 3 );
	
	
	fgSizer25->Add( bSizer63, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer27;
	sbSizer27 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Support Ships") ), wxVERTICAL );
	
	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxVERTICAL );
	
	chkDisallowSupportShips = new wxCheckBox( sbSizer27->GetStaticBox(), wxID_ANY, wxT("Disallow Support Ships"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer68->Add( chkDisallowSupportShips, 0, wxALL, 3 );
	
	chkSupportShipsRepairHull = new wxCheckBox( sbSizer27->GetStaticBox(), wxID_ANY, wxT("Support Ships repair hull"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer68->Add( chkSupportShipsRepairHull, 0, wxALL, 3 );
	
	
	sbSizer27->Add( bSizer68, 0, 0, 5 );
	
	pnlRepairHull = new wxPanel( sbSizer27->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pnlRepairHull->Enable( false );
	
	wxFlexGridSizer* fgSizer29;
	fgSizer29 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer29->AddGrowableCol( 2 );
	fgSizer29->SetFlexibleDirection( wxBOTH );
	fgSizer29->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer29->Add( 0, 0, 1, wxEXPAND, 5 );
	
	lblRepairCeiling = new wxStaticText( pnlRepairHull, wxID_ANY, wxT("Repair Ceiling:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblRepairCeiling->Wrap( -1 );
	lblRepairCeiling->Enable( false );
	
	fgSizer29->Add( lblRepairCeiling, 0, wxALIGN_CENTER|wxALL, 3 );
	
	
	fgSizer29->Add( 0, 0, 1, wxEXPAND, 5 );
	
	lblHullRepairCeiling = new wxStaticText( pnlRepairHull, wxID_ANY, wxT("Hull:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblHullRepairCeiling->Wrap( -1 );
	lblHullRepairCeiling->Enable( false );
	
	fgSizer29->Add( lblHullRepairCeiling, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALIGN_RIGHT|wxLEFT, 4 );
	
	spnHullRepairCeiling = new wxSpinCtrl( pnlRepairHull, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 96,-1 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	spnHullRepairCeiling->Enable( false );
	
	fgSizer29->Add( spnHullRepairCeiling, 0, wxALL, 3 );
	
	lblHullPercent = new wxStaticText( pnlRepairHull, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	lblHullPercent->Wrap( -1 );
	lblHullPercent->Enable( false );
	
	fgSizer29->Add( lblHullPercent, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 0 );
	
	lblSubsystemRepairCeiling = new wxStaticText( pnlRepairHull, wxID_ANY, wxT("Subsystem:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSubsystemRepairCeiling->Wrap( -1 );
	lblSubsystemRepairCeiling->Enable( false );
	
	fgSizer29->Add( lblSubsystemRepairCeiling, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxLEFT, 4 );
	
	spnSubsystemRepairCeiling = new wxSpinCtrl( pnlRepairHull, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 96,-1 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	spnSubsystemRepairCeiling->Enable( false );
	
	fgSizer29->Add( spnSubsystemRepairCeiling, 0, wxALL, 3 );
	
	lblSubstemPercent = new wxStaticText( pnlRepairHull, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSubstemPercent->Wrap( -1 );
	lblSubstemPercent->Enable( false );
	
	fgSizer29->Add( lblSubstemPercent, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 0 );
	
	
	pnlRepairHull->SetSizer( fgSizer29 );
	pnlRepairHull->Layout();
	fgSizer29->Fit( pnlRepairHull );
	sbSizer27->Add( pnlRepairHull, 1, wxEXPAND|wxALL, 5 );
	
	
	bSizer67->Add( sbSizer27, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer28;
	sbSizer28 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Ship Trails") ), wxVERTICAL );
	
	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxVERTICAL );
	
	chkToggleNebula = new wxCheckBox( sbSizer28->GetStaticBox(), wxID_ANY, wxT("Toggle (off in nebula; on elsewhere)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer69->Add( chkToggleNebula, 0, wxALL, 3 );
	
	wxBoxSizer* bSizer70;
	bSizer70 = new wxBoxSizer( wxHORIZONTAL );
	
	chkMinimumTrailSpeed = new wxCheckBox( sbSizer28->GetStaticBox(), wxID_ANY, wxT("Minimum Speed to display"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer70->Add( chkMinimumTrailSpeed, 0, wxALIGN_CENTER|wxALL, 3 );
	
	spnMinimumTrailSpeed = new wxSpinCtrl( sbSizer28->GetStaticBox(), wxID_ANY, wxT("45"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999, 45 );
	spnMinimumTrailSpeed->Enable( false );
	
	bSizer70->Add( spnMinimumTrailSpeed, 0, wxALL, 3 );
	
	
	bSizer69->Add( bSizer70, 1, wxEXPAND, 5 );
	
	
	sbSizer28->Add( bSizer69, 0, wxALIGN_CENTER_HORIZONTAL, 0 );
	
	
	bSizer67->Add( sbSizer28, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer29;
	sbSizer29 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Built-in Command Messages") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer30;
	fgSizer30 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer30->AddGrowableCol( 1 );
	fgSizer30->SetFlexibleDirection( wxBOTH );
	fgSizer30->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText71 = new wxStaticText( sbSizer29->GetStaticBox(), wxID_ANY, wxT("Sender:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	fgSizer30->Add( m_staticText71, 1, wxALIGN_CENTER_VERTICAL|wxALL, 0 );
	
	cboMessageSender = new wxComboBox( sbSizer29->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	fgSizer30->Add( cboMessageSender, 1, wxALL|wxEXPAND, 3 );
	
	m_staticText72 = new wxStaticText( sbSizer29->GetStaticBox(), wxID_ANY, wxT("Persona:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText72->Wrap( -1 );
	fgSizer30->Add( m_staticText72, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 0 );
	
	wxArrayString cboPersonaChoices;
	cboPersona = new wxChoice( sbSizer29->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboPersonaChoices, 0 );
	cboPersona->SetSelection( 0 );
	fgSizer30->Add( cboPersona, 1, wxALL|wxEXPAND, 3 );
	
	
	sbSizer29->Add( fgSizer30, 0, wxEXPAND, 5 );
	
	
	bSizer67->Add( sbSizer29, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer30;
	sbSizer30 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Music and Sound") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer31;
	fgSizer31 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer31->AddGrowableCol( 1 );
	fgSizer31->SetFlexibleDirection( wxBOTH );
	fgSizer31->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText73 = new wxStaticText( sbSizer30->GetStaticBox(), wxID_ANY, wxT("Default:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText73->Wrap( -1 );
	fgSizer31->Add( m_staticText73, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0 );
	
	wxArrayString cboMusicChoices;
	cboMusic = new wxChoice( sbSizer30->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboMusicChoices, 0 );
	cboMusic->SetSelection( 0 );
	fgSizer31->Add( cboMusic, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 3 );
	
	m_staticText741 = new wxStaticText( sbSizer30->GetStaticBox(), wxID_ANY, wxT("If Music pack is present:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText741->Wrap( 70 );
	fgSizer31->Add( m_staticText741, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0 );
	
	cboMusicPackPresent = new wxComboBox( sbSizer30->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	fgSizer31->Add( cboMusicPackPresent, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 3 );
	
	
	sbSizer30->Add( fgSizer31, 0, wxEXPAND, 5 );
	
	btnSoundEnvironment = new wxButton( sbSizer30->GetStaticBox(), wxID_ANY, wxT("Sound Environment"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer30->Add( btnSoundEnvironment, 0, wxALL|wxEXPAND, 3 );
	
	
	bSizer67->Add( sbSizer30, 0, wxALL|wxEXPAND, 3 );
	
	
	fgSizer25->Add( bSizer67, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer31;
	sbSizer31 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Flags") ), wxVERTICAL );
	
	wxString m_checkList4Choices[] = { wxT("All Teams at War"), wxT("Red Alert Mission"), wxT("Scramble Mission"), wxT("Disallow Promotion/Badges"), wxT("Disable Built-In Messages"), wxT("Disable Built-In Command Messages"), wxT("No Traitor"), wxT("All Ships Beam-Freed by Default"), wxT("Allow Daisy-Chained Docking"), wxT("No Briefing"), wxT("Toggle Debriefing (On/Off)"), wxT("Use Autopilot Cinematics"), wxT("Deactivate Hardcoded Autopilot"), wxT("Player Starts Under AI Control (NO MULTI)"), wxT("2D Mission") };
	int m_checkList4NChoices = sizeof( m_checkList4Choices ) / sizeof( wxString );
	m_checkList4 = new wxCheckListBox( sbSizer31->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,140 ), m_checkList4NChoices, m_checkList4Choices, wxLB_ALWAYS_SB|wxLB_HSCROLL );
	sbSizer31->Add( m_checkList4, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer71->Add( sbSizer31, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer32;
	sbSizer32 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("AI Options") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer32;
	fgSizer32 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer32->AddGrowableCol( 1 );
	fgSizer32->SetFlexibleDirection( wxBOTH );
	fgSizer32->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText771 = new wxStaticText( sbSizer32->GetStaticBox(), wxID_ANY, wxT("AI Profile:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText771->Wrap( -1 );
	fgSizer32->Add( m_staticText771, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 3 );
	
	wxArrayString cboAIProfileChoices;
	cboAIProfile = new wxChoice( sbSizer32->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboAIProfileChoices, 0 );
	cboAIProfile->SetSelection( 0 );
	fgSizer32->Add( cboAIProfile, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 3 );
	
	
	sbSizer32->Add( fgSizer32, 1, wxEXPAND, 5 );
	
	
	bSizer71->Add( sbSizer32, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer33;
	sbSizer33 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Loading Screen") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer33;
	fgSizer33 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer33->AddGrowableCol( 1 );
	fgSizer33->SetFlexibleDirection( wxBOTH );
	fgSizer33->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	btnLoadingScreen640x480 = new wxButton( sbSizer33->GetStaticBox(), wxID_ANY, wxT("640x480"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	fgSizer33->Add( btnLoadingScreen640x480, 1, wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	txtLoadingScreen640x480 = new wxTextCtrl( sbSizer33->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer33->Add( txtLoadingScreen640x480, 0, wxALL|wxEXPAND, 3 );
	
	btnLoadingScreen1024x768 = new wxButton( sbSizer33->GetStaticBox(), wxID_ANY, wxT("1024x768"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	fgSizer33->Add( btnLoadingScreen1024x768, 1, wxALIGN_CENTER|wxALL|wxEXPAND, 3 );
	
	txtLoadingScreen1024x768 = new wxTextCtrl( sbSizer33->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer33->Add( txtLoadingScreen1024x768, 0, wxALL|wxEXPAND, 3 );
	
	
	sbSizer33->Add( fgSizer33, 1, wxEXPAND, 0 );
	
	
	bSizer71->Add( sbSizer33, 0, wxALL|wxEXPAND, 3 );
	
	btnCustomWingNames = new wxButton( this, wxID_ANY, wxT("Custom Wing Names"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer71->Add( btnCustomWingNames, 0, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText159 = new wxStaticText( this, wxID_ANY, wxT("Player Entry Delay:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText159->Wrap( -1 );
	bSizer72->Add( m_staticText159, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	m_spinCtrl18 = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 30, 0 );
	bSizer72->Add( m_spinCtrl18, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer71->Add( bSizer72, 0, wxALL|wxEXPAND, 3 );
	
	
	fgSizer25->Add( bSizer71, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer62->Add( fgSizer25, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer73;
	bSizer73 = new wxBoxSizer( wxVERTICAL );
	
	lblMissionDescription = new wxStaticText( this, wxID_ANY, wxT("Mission Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMissionDescription->Wrap( -1 );
	bSizer73->Add( lblMissionDescription, 0, wxALIGN_BOTTOM|wxLEFT, 9 );
	
	txtMissionDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer73->Add( txtMissionDescription, 1, wxALL|wxEXPAND, 3 );
	
	lblDesignerNotes = new wxStaticText( this, wxID_ANY, wxT("Designer Notes:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDesignerNotes->Wrap( -1 );
	bSizer73->Add( lblDesignerNotes, 0, wxLEFT, 9 );
	
	txtDesignerNotes = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer73->Add( txtDesignerNotes, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer62->Add( bSizer73, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer62 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

dlgMissionSpecsEditor::~dlgMissionSpecsEditor()
{
}

dlgSoundEnvironment::dlgSoundEnvironment( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* bSizer74;
	bSizer74 = new wxBoxSizer( wxHORIZONTAL );
	
	wxGridBagSizer* gbSizer9;
	gbSizer9 = new wxGridBagSizer( 0, 0 );
	gbSizer9->SetFlexibleDirection( wxBOTH );
	gbSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblEnvironment = new wxStaticText( this, wxID_ANY, wxT("Environment:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblEnvironment->Wrap( -1 );
	gbSizer9->Add( lblEnvironment, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	cboEnvironment = new wxComboBox( this, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gbSizer9->Add( cboEnvironment, wxGBPosition( 0, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 3 );
	
	lblVolume = new wxStaticText( this, wxID_ANY, wxT("Volume:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblVolume->Wrap( -1 );
	gbSizer9->Add( lblVolume, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnVolume = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	gbSizer9->Add( spnVolume, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	lblDamping = new wxStaticText( this, wxID_ANY, wxT("Damping:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDamping->Wrap( -1 );
	gbSizer9->Add( lblDamping, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnDamping = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	gbSizer9->Add( spnDamping, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	lblDecayTime = new wxStaticText( this, wxID_ANY, wxT("Decay Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDecayTime->Wrap( -1 );
	gbSizer9->Add( lblDecayTime, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnDecayTime = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	gbSizer9->Add( spnDecayTime, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 3 );
	
	lblDecaySeconds = new wxStaticText( this, wxID_ANY, wxT("seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDecaySeconds->Wrap( -1 );
	gbSizer9->Add( lblDecaySeconds, wxGBPosition( 3, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer74->Add( gbSizer9, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer75;
	bSizer75 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer76;
	bSizer76 = new wxBoxSizer( wxVERTICAL );
	
	btnOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer76->Add( btnOK, 0, wxALL, 3 );
	
	btnCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer76->Add( btnCancel, 0, wxALL, 3 );
	
	
	bSizer75->Add( bSizer76, 1, wxALIGN_RIGHT, 5 );
	
	wxStaticBoxSizer* sbSizer34;
	sbSizer34 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Preview") ), wxHORIZONTAL );
	
	m_bpButton7 = new wxBitmapButton( sbSizer34->GetStaticBox(), wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 24,24 ), wxBU_AUTODRAW );
	sbSizer34->Add( m_bpButton7, 0, wxALIGN_CENTER|wxALL, 3 );
	
	m_filePicker2 = new wxFilePickerCtrl( sbSizer34->GetStaticBox(), wxID_ANY, wxT(",90,90,-1,70,0"), wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxSize( -1,24 ), wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	sbSizer34->Add( m_filePicker2, 0, wxALIGN_CENTER|wxALL, 3 );
	
	
	bSizer75->Add( sbSizer34, 1, wxALIGN_RIGHT|wxLEFT|wxTOP, 5 );
	
	
	bSizer74->Add( bSizer75, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer74 );
	this->Layout();
	bSizer74->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgSoundEnvironment::~dlgSoundEnvironment()
{
}

frmBriefingEditor::frmBriefingEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar8 = new wxMenuBar( 0 );
	mnuSelectTeam = new wxMenu();
	wxMenuItem* mnuTeam1;
	mnuTeam1 = new wxMenuItem( mnuSelectTeam, wxID_ANY, wxString( wxT("Team 1") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSelectTeam->Append( mnuTeam1 );
	
	wxMenuItem* mnuTeam2;
	mnuTeam2 = new wxMenuItem( mnuSelectTeam, wxID_ANY, wxString( wxT("Team 2") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSelectTeam->Append( mnuTeam2 );
	
	m_menubar8->Append( mnuSelectTeam, wxT("Select Team") ); 
	
	mnuOptions = new wxMenu();
	wxMenuItem* mnuBalanceTeams;
	mnuBalanceTeams = new wxMenuItem( mnuOptions, wxID_ANY, wxString( wxT("Balance Teams") ) , wxEmptyString, wxITEM_NORMAL );
	mnuOptions->Append( mnuBalanceTeams );
	
	m_menubar8->Append( mnuOptions, wxT("Options") ); 
	
	this->SetMenuBar( m_menubar8 );
	
	wxBoxSizer* bSizer77;
	bSizer77 = new wxBoxSizer( wxVERTICAL );
	
	m_panel13 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer78;
	bSizer78 = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* gbSizer10;
	gbSizer10 = new wxGridBagSizer( 0, 0 );
	gbSizer10->SetFlexibleDirection( wxBOTH );
	gbSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer79;
	bSizer79 = new wxBoxSizer( wxVERTICAL );
	
	lblStage = new wxStaticText( m_panel13, wxID_ANY, wxT("No stages"), wxDefaultPosition, wxDefaultSize, 0 );
	lblStage->Wrap( -1 );
	bSizer79->Add( lblStage, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer80;
	bSizer80 = new wxBoxSizer( wxHORIZONTAL );
	
	lblCameraTransisitonTime = new wxStaticText( m_panel13, wxID_ANY, wxT("Camera Transition Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCameraTransisitonTime->Wrap( -1 );
	bSizer80->Add( lblCameraTransisitonTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	m_spinCtrl53 = new wxSpinCtrl( m_panel13, wxID_ANY, wxT("505"), wxDefaultPosition, wxSize( 70,-1 ), wxSP_ARROW_KEYS, 0, 999999, 505 );
	bSizer80->Add( m_spinCtrl53, 0, wxALL, 3 );
	
	m_staticText192 = new wxStaticText( m_panel13, wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText192->Wrap( -1 );
	bSizer80->Add( m_staticText192, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer79->Add( bSizer80, 0, wxEXPAND, 5 );
	
	chkCutToNextStage = new wxCheckBox( m_panel13, wxID_ANY, wxT("Cut to Next Stage"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer79->Add( chkCutToNextStage, 0, wxALL, 3 );
	
	chkCutToPreviousStage = new wxCheckBox( m_panel13, wxID_ANY, wxT("Cut to Previous Stage"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer79->Add( chkCutToPreviousStage, 0, wxALL, 3 );
	
	
	gbSizer10->Add( bSizer79, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );
	
	lblText = new wxStaticText( m_panel13, wxID_ANY, wxT("Briefing Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblText->Wrap( -1 );
	gbSizer10->Add( lblText, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_BOTTOM|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	m_textCtrl75 = new wxTextCtrl( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,60 ), wxTE_MULTILINE );
	gbSizer10->Add( m_textCtrl75, wxGBPosition( 2, 0 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer82;
	bSizer82 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer83;
	bSizer83 = new wxBoxSizer( wxHORIZONTAL );
	
	btnPreviousStage = new wxButton( m_panel13, wxID_ANY, wxT("Prev"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer83->Add( btnPreviousStage, 0, wxALL|wxEXPAND, 2 );
	
	btnNextStage = new wxButton( m_panel13, wxID_ANY, wxT("Next"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer83->Add( btnNextStage, 0, wxALL|wxEXPAND, 2 );
	
	
	bSizer82->Add( bSizer83, 1, wxEXPAND, 3 );
	
	btnAddStage = new wxButton( m_panel13, wxID_ANY, wxT("Add Stage"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer82->Add( btnAddStage, 1, wxALL|wxEXPAND, 2 );
	
	btnInsertStage = new wxButton( m_panel13, wxID_ANY, wxT("Insert Stage"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer82->Add( btnInsertStage, 1, wxALL|wxEXPAND, 2 );
	
	btnDeleteStage = new wxButton( m_panel13, wxID_ANY, wxT("Delete Stage"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer82->Add( btnDeleteStage, 1, wxALL|wxEXPAND, 2 );
	
	
	bSizer81->Add( bSizer82, 1, 0, 5 );
	
	wxBoxSizer* bSizer84;
	bSizer84 = new wxBoxSizer( wxVERTICAL );
	
	btnSaveView = new wxButton( m_panel13, wxID_ANY, wxT("Save View"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer84->Add( btnSaveView, 1, wxALL|wxEXPAND, 2 );
	
	btnGoToView = new wxButton( m_panel13, wxID_ANY, wxT("Go To View"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer84->Add( btnGoToView, 1, wxALL|wxEXPAND, 2 );
	
	btnCopyView = new wxButton( m_panel13, wxID_ANY, wxT("Copy View"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer84->Add( btnCopyView, 1, wxALL|wxEXPAND, 2 );
	
	btnPasteView = new wxButton( m_panel13, wxID_ANY, wxT("Paste View"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer84->Add( btnPasteView, 1, wxALL|wxEXPAND, 2 );
	
	
	bSizer81->Add( bSizer84, 1, wxEXPAND, 5 );
	
	
	gbSizer10->Add( bSizer81, wxGBPosition( 0, 1 ), wxGBSpan( 2, 1 ), wxALIGN_RIGHT, 3 );
	
	
	gbSizer10->AddGrowableCol( 0 );
	gbSizer10->AddGrowableCol( 1 );
	
	bSizer78->Add( gbSizer10, 0, wxEXPAND|wxRIGHT, 3 );
	
	wxBoxSizer* bSizer85;
	bSizer85 = new wxBoxSizer( wxHORIZONTAL );
	
	lblVoiceFile = new wxStaticText( m_panel13, wxID_ANY, wxT("Voice File:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblVoiceFile->Wrap( -1 );
	bSizer85->Add( lblVoiceFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	m_filePicker1 = new wxFilePickerCtrl( m_panel13, wxID_ANY, wxT(",90,90,-1,70,0"), wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer85->Add( m_filePicker1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnPlayVoice = new wxBitmapButton( m_panel13, wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW );
	bSizer85->Add( btnPlayVoice, 0, wxALL, 3 );
	
	
	bSizer78->Add( bSizer85, 0, 0, 5 );
	
	wxStaticBoxSizer* sbSizer35;
	sbSizer35 = new wxStaticBoxSizer( new wxStaticBox( m_panel13, wxID_ANY, wxT("Briefing Music") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer34;
	fgSizer34 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer34->SetFlexibleDirection( wxBOTH );
	fgSizer34->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblDefaultMusic = new wxStaticText( sbSizer35->GetStaticBox(), wxID_ANY, wxT("Default:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDefaultMusic->Wrap( -1 );
	fgSizer34->Add( lblDefaultMusic, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxString m_choice42Choices[] = { wxT("None") };
	int m_choice42NChoices = sizeof( m_choice42Choices ) / sizeof( wxString );
	m_choice42 = new wxChoice( sbSizer35->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( 120,-1 ), m_choice42NChoices, m_choice42Choices, 0 );
	m_choice42->SetSelection( 0 );
	fgSizer34->Add( m_choice42, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnPlayMusic = new wxBitmapButton( sbSizer35->GetStaticBox(), wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW );
	fgSizer34->Add( btnPlayMusic, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	m_staticText196 = new wxStaticText( sbSizer35->GetStaticBox(), wxID_ANY, wxT("If music pack is present:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText196->Wrap( 70 );
	fgSizer34->Add( m_staticText196, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxString m_choice43Choices[] = { wxT("None") };
	int m_choice43NChoices = sizeof( m_choice43Choices ) / sizeof( wxString );
	m_choice43 = new wxChoice( sbSizer35->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( 120,-1 ), m_choice43NChoices, m_choice43Choices, 0 );
	m_choice43->SetSelection( 0 );
	fgSizer34->Add( m_choice43, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnPlayMusicFromPack = new wxBitmapButton( sbSizer35->GetStaticBox(), wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW );
	fgSizer34->Add( btnPlayMusicFromPack, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	sbSizer35->Add( fgSizer34, 1, wxEXPAND, 5 );
	
	
	bSizer78->Add( sbSizer35, 0, 0, 5 );
	
	wxBoxSizer* bSizer86;
	bSizer86 = new wxBoxSizer( wxVERTICAL );
	
	lblUsageFormula = new wxStaticText( m_panel13, wxID_ANY, wxT("Usage Formula:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblUsageFormula->Wrap( -1 );
	bSizer86->Add( lblUsageFormula, 0, wxALL, 5 );
	
	m_treeCtrl9 = new wxTreeCtrl( m_panel13, wxID_ANY, wxDefaultPosition, wxSize( -1,60 ), wxTR_DEFAULT_STYLE );
	bSizer86->Add( m_treeCtrl9, 0, wxEXPAND, 3 );
	
	chkDrawLines = new wxCheckBox( m_panel13, wxID_ANY, wxT("Draw Lines Between Marked Icons"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer86->Add( chkDrawLines, 0, wxALIGN_RIGHT|wxALL, 3 );
	
	
	bSizer78->Add( bSizer86, 0, wxEXPAND|wxLEFT|wxRIGHT, 2 );
	
	wxStaticBoxSizer* sbSizer36;
	sbSizer36 = new wxStaticBoxSizer( new wxStaticBox( m_panel13, wxID_ANY, wxT("Selected Icon Info") ), wxHORIZONTAL );
	
	wxGridBagSizer* gbSizer11;
	gbSizer11 = new wxGridBagSizer( 0, 0 );
	gbSizer11->SetFlexibleDirection( wxBOTH );
	gbSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblIconLabel = new wxStaticText( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Label:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblIconLabel->Wrap( -1 );
	gbSizer11->Add( lblIconLabel, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtIconLabel = new wxTextCtrl( sbSizer36->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	gbSizer11->Add( txtIconLabel, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblIconImage = new wxStaticText( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Icon Image:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblIconImage->Wrap( -1 );
	gbSizer11->Add( lblIconImage, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	cboIconImage = new wxComboBox( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 ); 
	gbSizer11->Add( cboIconImage, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblShipType = new wxStaticText( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Ship Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblShipType->Wrap( -1 );
	gbSizer11->Add( lblShipType, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	cboShipType = new wxComboBox( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 ); 
	gbSizer11->Add( cboShipType, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblIconTeam = new wxStaticText( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Team:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblIconTeam->Wrap( -1 );
	gbSizer11->Add( lblIconTeam, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	m_comboBox13 = new wxComboBox( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 ); 
	gbSizer11->Add( m_comboBox13, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblIconId = new wxStaticText( sbSizer36->GetStaticBox(), wxID_ANY, wxT("ID:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblIconId->Wrap( -1 );
	gbSizer11->Add( lblIconId, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	txtIconID = new wxTextCtrl( sbSizer36->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer11->Add( txtIconID, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxBoxSizer* bSizer87;
	bSizer87 = new wxBoxSizer( wxVERTICAL );
	
	chkHighlightIcon = new wxCheckBox( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Highlight"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer87->Add( chkHighlightIcon, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	chkChangeLocally = new wxCheckBox( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Change Locally"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer87->Add( chkChangeLocally, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	chkFlipIconLR = new wxCheckBox( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Flip Icon (L/R)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer87->Add( chkFlipIconLR, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	gbSizer11->Add( bSizer87, wxGBPosition( 1, 3 ), wxGBSpan( 3, 1 ), wxEXPAND, 5 );
	
	btnMakeIcon = new wxButton( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Make Icon"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer11->Add( btnMakeIcon, wxGBPosition( 0, 4 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	btnDeleteIcon = new wxButton( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Delete Icon"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer11->Add( btnDeleteIcon, wxGBPosition( 1, 4 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	btnPropagate = new wxButton( sbSizer36->GetStaticBox(), wxID_ANY, wxT("Propagate"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer11->Add( btnPropagate, wxGBPosition( 2, 4 ), wxGBSpan( 1, 1 ), wxALL, 3 );
	
	
	sbSizer36->Add( gbSizer11, 0, wxEXPAND, 3 );
	
	
	bSizer78->Add( sbSizer36, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer88;
	bSizer88 = new wxBoxSizer( wxVERTICAL );
	
	lblIconText = new wxStaticText( m_panel13, wxID_ANY, wxT("Icon Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblIconText->Wrap( -1 );
	bSizer88->Add( lblIconText, 0, wxALL, 3 );
	
	txtIconText = new wxTextCtrl( m_panel13, wxID_ANY, wxT("1\n2\n3"), wxDefaultPosition, wxSize( -1,60 ), wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer88->Add( txtIconText, 0, wxBOTTOM|wxEXPAND, 4 );
	
	
	bSizer78->Add( bSizer88, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 3 );
	
	
	m_panel13->SetSizer( bSizer78 );
	m_panel13->Layout();
	bSizer78->Fit( m_panel13 );
	bSizer77->Add( m_panel13, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer77 );
	this->Layout();
	bSizer77->Fit( this );
	
	this->Centre( wxBOTH );
}

frmBriefingEditor::~frmBriefingEditor()
{
}

frmDebriefingEditor::frmDebriefingEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer89;
	bSizer89 = new wxBoxSizer( wxVERTICAL );
	
	pnlMain = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer90;
	bSizer90 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer92;
	bSizer92 = new wxBoxSizer( wxHORIZONTAL );
	
	txtStages = new wxStaticText( pnlMain, wxID_ANY, wxT("No stages"), wxDefaultPosition, wxDefaultSize, 0 );
	txtStages->Wrap( -1 );
	bSizer92->Add( txtStages, 2, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	btnPrev = new wxButton( pnlMain, wxID_ANY, wxT("Prev"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer92->Add( btnPrev, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnNext = new wxButton( pnlMain, wxID_ANY, wxT("Next"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer92->Add( btnNext, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer91->Add( bSizer92, 0, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer93;
	bSizer93 = new wxBoxSizer( wxHORIZONTAL );
	
	btnAdd = new wxButton( pnlMain, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer93->Add( btnAdd, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnInsert = new wxButton( pnlMain, wxID_ANY, wxT("Insert"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer93->Add( btnInsert, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnDelete = new wxButton( pnlMain, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer93->Add( btnDelete, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer91->Add( bSizer93, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 3 );
	
	lblUsageFormula = new wxStaticText( pnlMain, wxID_ANY, wxT("Usage Formula:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblUsageFormula->Wrap( -1 );
	bSizer91->Add( lblUsageFormula, 0, wxALIGN_LEFT|wxALL|wxEXPAND|wxTOP, 3 );
	
	treeUsageFormula = new wxTreeCtrl( pnlMain, wxID_ANY, wxDefaultPosition, wxSize( 250,200 ), wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_MULTIPLE|wxSUNKEN_BORDER );
	bSizer91->Add( treeUsageFormula, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer90->Add( bSizer91, 0, wxALIGN_TOP|wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer94;
	bSizer94 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer95;
	bSizer95 = new wxBoxSizer( wxHORIZONTAL );
	
	lblVoiceWaveFile = new wxStaticText( pnlMain, wxID_ANY, wxT("Voice Wave File:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblVoiceWaveFile->Wrap( -1 );
	bSizer95->Add( lblVoiceWaveFile, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	txtVoiceWaveFile = new wxTextCtrl( pnlMain, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer95->Add( txtVoiceWaveFile, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnBrowse = new wxButton( pnlMain, wxID_ANY, wxT("Browse"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer95->Add( btnBrowse, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnPlayVoice = new wxBitmapButton( pnlMain, wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW|wxBU_EXACTFIT );
	bSizer95->Add( btnPlayVoice, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer94->Add( bSizer95, 0, wxEXPAND|wxALL, 0 );
	
	lblStageText = new wxStaticText( pnlMain, wxID_ANY, wxT("Stage Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblStageText->Wrap( -1 );
	bSizer94->Add( lblStageText, 0, wxALIGN_LEFT|wxALL|wxEXPAND, 3 );
	
	txtStageText = new wxTextCtrl( pnlMain, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 320,100 ), wxTE_MULTILINE );
	bSizer94->Add( txtStageText, 0, wxALL|wxEXPAND, 3 );
	
	lblRecommendationText = new wxStaticText( pnlMain, wxID_ANY, wxT("Recommendation Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblRecommendationText->Wrap( -1 );
	bSizer94->Add( lblRecommendationText, 0, wxALIGN_LEFT|wxALL|wxEXPAND, 3 );
	
	txtRecommendationText = new wxTextCtrl( pnlMain, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 320,100 ), wxTE_MULTILINE );
	bSizer94->Add( txtRecommendationText, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer90->Add( bSizer94, 1, wxALIGN_TOP|wxALL|wxEXPAND, 3 );
	
	
	pnlMain->SetSizer( bSizer90 );
	pnlMain->Layout();
	bSizer90->Fit( pnlMain );
	bSizer89->Add( pnlMain, 0, wxEXPAND, 0 );
	
	pnlMusic = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer96;
	bSizer96 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer37;
	sbSizer37 = new wxStaticBoxSizer( new wxStaticBox( pnlMusic, wxID_ANY, wxT("Debriefing Music") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer35;
	fgSizer35 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer35->SetFlexibleDirection( wxBOTH );
	fgSizer35->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblMusicSuccess = new wxStaticText( sbSizer37->GetStaticBox(), wxID_ANY, wxT("Success Music:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMusicSuccess->Wrap( -1 );
	fgSizer35->Add( lblMusicSuccess, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cbMusicSuccessChoices;
	cbMusicSuccess = new wxChoice( sbSizer37->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cbMusicSuccessChoices, 0 );
	cbMusicSuccess->SetSelection( 0 );
	fgSizer35->Add( cbMusicSuccess, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	btnPlaySuccess = new wxBitmapButton( sbSizer37->GetStaticBox(), wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW|wxBU_EXACTFIT );
	fgSizer35->Add( btnPlaySuccess, 0, wxALL, 3 );
	
	m_staticText210 = new wxStaticText( sbSizer37->GetStaticBox(), wxID_ANY, wxT("Nuetral Music:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText210->Wrap( -1 );
	fgSizer35->Add( m_staticText210, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString m_choice45Choices;
	m_choice45 = new wxChoice( sbSizer37->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice45Choices, 0 );
	m_choice45->SetSelection( 0 );
	fgSizer35->Add( m_choice45, 0, wxALL, 5 );
	
	btnPlayNuetral = new wxBitmapButton( sbSizer37->GetStaticBox(), wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW|wxBU_EXACTFIT );
	fgSizer35->Add( btnPlayNuetral, 0, wxALL, 3 );
	
	m_staticText211 = new wxStaticText( sbSizer37->GetStaticBox(), wxID_ANY, wxT("Failure Music:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	fgSizer35->Add( m_staticText211, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString m_choice46Choices;
	m_choice46 = new wxChoice( sbSizer37->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice46Choices, 0 );
	m_choice46->SetSelection( 0 );
	fgSizer35->Add( m_choice46, 0, wxALL, 5 );
	
	btnPlayFailure = new wxBitmapButton( sbSizer37->GetStaticBox(), wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW|wxBU_EXACTFIT );
	fgSizer35->Add( btnPlayFailure, 0, wxALL, 3 );
	
	
	sbSizer37->Add( fgSizer35, 1, wxEXPAND, 5 );
	
	
	bSizer96->Add( sbSizer37, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	pnlMusic->SetSizer( bSizer96 );
	pnlMusic->Layout();
	bSizer96->Fit( pnlMusic );
	bSizer89->Add( pnlMusic, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer89 );
	this->Layout();
	bSizer89->Fit( this );
	mnbDebriefingEditor = new wxMenuBar( 0 );
	mnuSelectTeam = new wxMenu();
	wxMenuItem* mnuSelectTeamTeam1;
	mnuSelectTeamTeam1 = new wxMenuItem( mnuSelectTeam, wxID_ANY, wxString( wxT("Team 1") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSelectTeam->Append( mnuSelectTeamTeam1 );
	
	wxMenuItem* mnuSelectTeamTeam2;
	mnuSelectTeamTeam2 = new wxMenuItem( mnuSelectTeam, wxID_ANY, wxString( wxT("Team 2") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSelectTeam->Append( mnuSelectTeamTeam2 );
	
	mnbDebriefingEditor->Append( mnuSelectTeam, wxT("Select Team") ); 
	
	mnuOptions = new wxMenu();
	wxMenuItem* mnuOptionsBalanceTeams;
	mnuOptionsBalanceTeams = new wxMenuItem( mnuOptions, wxID_ANY, wxString( wxT("Balance Teams") ) , wxEmptyString, wxITEM_NORMAL );
	mnuOptions->Append( mnuOptionsBalanceTeams );
	
	mnbDebriefingEditor->Append( mnuOptions, wxT("Options") ); 
	
	this->SetMenuBar( mnbDebriefingEditor );
	
	
	this->Centre( wxBOTH );
}

frmDebriefingEditor::~frmDebriefingEditor()
{
}

frmCommandBriefingEditor::frmCommandBriefingEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar6 = new wxMenuBar( 0 );
	mnuSelectTeam = new wxMenu();
	wxMenuItem* mnuTeam1;
	mnuTeam1 = new wxMenuItem( mnuSelectTeam, wxID_ANY, wxString( wxT("Team 1") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSelectTeam->Append( mnuTeam1 );
	
	wxMenuItem* mnuTeam2;
	mnuTeam2 = new wxMenuItem( mnuSelectTeam, wxID_ANY, wxString( wxT("Team 2") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSelectTeam->Append( mnuTeam2 );
	
	m_menubar6->Append( mnuSelectTeam, wxT("Select Team") ); 
	
	mnuOptions = new wxMenu();
	wxMenuItem* mnuBalanceTeams;
	mnuBalanceTeams = new wxMenuItem( mnuOptions, wxID_ANY, wxString( wxT("Balance Teams") ) , wxEmptyString, wxITEM_NORMAL );
	mnuOptions->Append( mnuBalanceTeams );
	
	m_menubar6->Append( mnuOptions, wxT("Options") ); 
	
	this->SetMenuBar( m_menubar6 );
	
	wxBoxSizer* bSizer97;
	bSizer97 = new wxBoxSizer( wxVERTICAL );
	
	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer99;
	bSizer99 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer100;
	bSizer100 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxHORIZONTAL );
	
	txtNumCBStages = new wxStaticText( m_panel5, wxID_ANY, wxT("No stages"), wxDefaultPosition, wxDefaultSize, 0 );
	txtNumCBStages->Wrap( -1 );
	bSizer101->Add( txtNumCBStages, 2, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	btnPrev = new wxButton( m_panel5, wxID_ANY, wxT("Prev"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer101->Add( btnPrev, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnNext = new wxButton( m_panel5, wxID_ANY, wxT("Next"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer101->Add( btnNext, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer100->Add( bSizer101, 0, wxEXPAND, 3 );
	
	wxBoxSizer* bSizer102;
	bSizer102 = new wxBoxSizer( wxHORIZONTAL );
	
	btnAdd = new wxButton( m_panel5, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer102->Add( btnAdd, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnInsert = new wxButton( m_panel5, wxID_ANY, wxT("Insert"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer102->Add( btnInsert, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxLEFT|wxRIGHT, 3 );
	
	btnDelete = new wxButton( m_panel5, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer102->Add( btnDelete, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer100->Add( bSizer102, 0, wxALIGN_CENTER_HORIZONTAL, 3 );
	
	
	bSizer99->Add( bSizer100, 0, wxALIGN_TOP, 3 );
	
	
	bSizer99->Add( 5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxBoxSizer* bSizer103;
	bSizer103 = new wxBoxSizer( wxVERTICAL );
	
	btnOK = new wxButton( m_panel5, wxID_ANY, wxT("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer103->Add( btnOK, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	btnCancel = new wxButton( m_panel5, wxID_ANY, wxT("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer103->Add( btnCancel, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer99->Add( bSizer103, 1, wxEXPAND, 1 );
	
	
	bSizer98->Add( bSizer99, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 3 );
	
	wxID_STATIC1 = new wxStaticText( m_panel5, wxID_ANY, wxT("Stage Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	wxID_STATIC1->Wrap( -1 );
	bSizer98->Add( wxID_STATIC1, 0, wxALIGN_LEFT|wxALL, 3 );
	
	txtStageText = new wxTextCtrl( m_panel5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer98->Add( txtStageText, 2, wxALL|wxEXPAND, 3 );
	
	wxFlexGridSizer* fgSizer36;
	fgSizer36 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer36->AddGrowableCol( 1 );
	fgSizer36->SetFlexibleDirection( wxBOTH );
	fgSizer36->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblAniFile = new wxStaticText( m_panel5, wxID_ANY, wxT("Ani File:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAniFile->Wrap( -1 );
	fgSizer36->Add( lblAniFile, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	fpAniFile = new wxFilePickerCtrl( m_panel5, wxID_ANY, wxT(",90,90,-1,70,0"), wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	fgSizer36->Add( fpAniFile, 0, wxALL|wxEXPAND, 3 );
	
	
	fgSizer36->Add( 0, 0, 1, wxEXPAND, 5 );
	
	lblVoiceWaveFile = new wxStaticText( m_panel5, wxID_ANY, wxT("Voice Wave File:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblVoiceWaveFile->Wrap( -1 );
	fgSizer36->Add( lblVoiceWaveFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	fpVoiceWave = new wxFilePickerCtrl( m_panel5, wxID_ANY, wxT(",90,90,-1,70,0"), wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	fgSizer36->Add( fpVoiceWave, 0, wxALL|wxEXPAND, 3 );
	
	btnVoicePlay = new wxBitmapButton( m_panel5, wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW|wxBU_EXACTFIT );
	fgSizer36->Add( btnVoicePlay, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer98->Add( fgSizer36, 1, wxEXPAND, 3 );
	
	
	m_panel5->SetSizer( bSizer98 );
	m_panel5->Layout();
	bSizer98->Fit( m_panel5 );
	bSizer97->Add( m_panel5, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer97 );
	this->Layout();
	bSizer97->Fit( this );
	
	this->Centre( wxBOTH );
}

frmCommandBriefingEditor::~frmCommandBriefingEditor()
{
}

dlgFictionViewer::dlgFictionViewer( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* bSizer104;
	bSizer104 = new wxBoxSizer( wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer37;
	fgSizer37 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer37->SetFlexibleDirection( wxBOTH );
	fgSizer37->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblStoryFile = new wxStaticText( this, wxID_ANY, wxT("Story File:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblStoryFile->Wrap( -1 );
	fgSizer37->Add( lblStoryFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	fpStoryFile = new wxFilePickerCtrl( this, wxID_ANY, wxT(",90,90,-1,70,0"), wxT("Select a story file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	fgSizer37->Add( fpStoryFile, 0, wxALL, 3 );
	
	lblFontFile = new wxStaticText( this, wxID_ANY, wxT("Font File:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblFontFile->Wrap( -1 );
	fgSizer37->Add( lblFontFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	fpFontFile = new wxFilePickerCtrl( this, wxID_ANY, wxT(",90,90,-1,70,0"), wxT("Select a font file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	fgSizer37->Add( fpFontFile, 0, wxALL, 3 );
	
	lblMusic = new wxStaticText( this, wxID_ANY, wxT("Music:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMusic->Wrap( -1 );
	fgSizer37->Add( lblMusic, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxBoxSizer* bSizer105;
	bSizer105 = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString cbMusicChoices;
	cbMusic = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( -1,23 ), cbMusicChoices, 0 );
	cbMusic->SetSelection( 0 );
	bSizer105->Add( cbMusic, 1, wxALL|wxEXPAND, 3 );
	
	btnPlayMusic = new wxBitmapButton( this, wxID_ANY, wxBitmap( wxT("../res/play.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxSize( 23,23 ), wxBU_AUTODRAW );
	bSizer105->Add( btnPlayMusic, 0, wxALL, 2 );
	
	
	fgSizer37->Add( bSizer105, 1, wxEXPAND, 5 );
	
	
	bSizer104->Add( fgSizer37, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer106;
	bSizer106 = new wxBoxSizer( wxVERTICAL );
	
	btnOK = new wxButton( this, wxID_ANY, wxT("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer106->Add( btnOK, 0, wxALL, 3 );
	
	btnCancel = new wxButton( this, wxID_ANY, wxT("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer106->Add( btnCancel, 0, wxALL, 3 );
	
	
	bSizer104->Add( bSizer106, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer104 );
	this->Layout();
	bSizer104->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgFictionViewer::~dlgFictionViewer()
{
}

dlgShieldSystemEditor::dlgShieldSystemEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer107;
	bSizer107 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer108;
	bSizer108 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer38;
	sbSizer38 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("All ships of type") ), wxVERTICAL );
	
	wxArrayString cboShipTypeChoices;
	cboShipType = new wxChoice( sbSizer38->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboShipTypeChoices, 0 );
	cboShipType->SetSelection( 0 );
	sbSizer38->Add( cboShipType, 0, wxEXPAND|wxALL, 3 );
	
	optShipTypeHasShieldSystem = new wxRadioButton( sbSizer38->GetStaticBox(), wxID_ANY, wxT("Have shield systems"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	optShipTypeHasShieldSystem->SetValue( true ); 
	sbSizer38->Add( optShipTypeHasShieldSystem, 0, wxALIGN_LEFT|wxALL, 3 );
	
	optShipTypeNoShieldSystem = new wxRadioButton( sbSizer38->GetStaticBox(), wxID_ANY, wxT("No shield systems"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer38->Add( optShipTypeNoShieldSystem, 0, wxALIGN_LEFT|wxALL, 3 );
	
	
	bSizer108->Add( sbSizer38, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxStaticBoxSizer* sbSizer39;
	sbSizer39 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("All ships on team") ), wxVERTICAL );
	
	wxArrayString cboShipTeamChoices;
	cboShipTeam = new wxChoice( sbSizer39->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboShipTeamChoices, 0 );
	cboShipTeam->SetSelection( 0 );
	sbSizer39->Add( cboShipTeam, 0, wxEXPAND|wxALL, 3 );
	
	optShipTeamHasShieldSystem = new wxRadioButton( sbSizer39->GetStaticBox(), wxID_ANY, wxT("Have shield systems"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	optShipTeamHasShieldSystem->SetValue( true ); 
	sbSizer39->Add( optShipTeamHasShieldSystem, 0, wxALIGN_LEFT|wxALL, 3 );
	
	optShipTeamNoShieldSystem = new wxRadioButton( sbSizer39->GetStaticBox(), wxID_ANY, wxT("No shield systems"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer39->Add( optShipTeamNoShieldSystem, 0, wxALIGN_LEFT|wxALL, 3 );
	
	
	bSizer108->Add( sbSizer39, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer107->Add( bSizer108, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 3 );
	
	m_sdbSizer5 = new wxStdDialogButtonSizer();
	m_sdbSizer5OK = new wxButton( this, wxID_OK );
	m_sdbSizer5->AddButton( m_sdbSizer5OK );
	m_sdbSizer5Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer5->AddButton( m_sdbSizer5Cancel );
	m_sdbSizer5->Realize();
	
	bSizer107->Add( m_sdbSizer5, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer107 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

dlgShieldSystemEditor::~dlgShieldSystemEditor()
{
}

dlgSetGlobalShipFlagsEditor::dlgSetGlobalShipFlagsEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* bSizer109;
	bSizer109 = new wxBoxSizer( wxVERTICAL );
	
	btnGlobalNoShields = new wxButton( this, wxID_ANY, wxT("Global No-Shields"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer109->Add( btnGlobalNoShields, 0, wxEXPAND|wxALL, 5 );
	
	btnGlobalNoSubspaceDrive = new wxButton( this, wxID_ANY, wxT("Global No-Subspace-Drive"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer109->Add( btnGlobalNoSubspaceDrive, 0, wxEXPAND|wxALL, 5 );
	
	btnGlobalPrimitiveSensors = new wxButton( this, wxID_ANY, wxT("Global Primitive-Sensors"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer109->Add( btnGlobalPrimitiveSensors, 0, wxEXPAND|wxALL, 5 );
	
	btnGlobalAffectedByGravity = new wxButton( this, wxID_ANY, wxT("Global Affected-By-Gravity"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer109->Add( btnGlobalAffectedByGravity, 0, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizer109 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

dlgSetGlobalShipFlagsEditor::~dlgSetGlobalShipFlagsEditor()
{
}

dlgVoiceActingManager::dlgVoiceActingManager( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* bSizer110;
	bSizer110 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer38;
	fgSizer38 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer38->AddGrowableCol( 0 );
	fgSizer38->AddGrowableCol( 1 );
	fgSizer38->AddGrowableRow( 0 );
	fgSizer38->AddGrowableRow( 1 );
	fgSizer38->SetFlexibleDirection( wxBOTH );
	fgSizer38->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer40;
	sbSizer40 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("File Name Options") ), wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer41;
	sbSizer41 = new wxStaticBoxSizer( new wxStaticBox( sbSizer40->GetStaticBox(), wxID_ANY, wxT("Abbreviations") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer39;
	fgSizer39 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer39->SetFlexibleDirection( wxBOTH );
	fgSizer39->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblCampaign = new wxStaticText( sbSizer41->GetStaticBox(), wxID_ANY, wxT("Campaign:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCampaign->Wrap( -1 );
	fgSizer39->Add( lblCampaign, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtAbbrevCampaign = new wxTextCtrl( sbSizer41->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer39->Add( txtAbbrevCampaign, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3 );
	
	lblMission = new wxStaticText( sbSizer41->GetStaticBox(), wxID_ANY, wxT("Mission:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMission->Wrap( -1 );
	fgSizer39->Add( lblMission, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtAbbrevMission = new wxTextCtrl( sbSizer41->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer39->Add( txtAbbrevMission, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3 );
	
	lblCmdBriefingStage = new wxStaticText( sbSizer41->GetStaticBox(), wxID_ANY, wxT("Cmd. Briefing Stage:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCmdBriefingStage->Wrap( -1 );
	fgSizer39->Add( lblCmdBriefingStage, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtAbbrevCB = new wxTextCtrl( sbSizer41->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer39->Add( txtAbbrevCB, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3 );
	
	lblBriefingStage = new wxStaticText( sbSizer41->GetStaticBox(), wxID_ANY, wxT("Briefing Stage:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBriefingStage->Wrap( -1 );
	fgSizer39->Add( lblBriefingStage, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtAbbrevBriefing = new wxTextCtrl( sbSizer41->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer39->Add( txtAbbrevBriefing, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3 );
	
	lblDebriefingStage = new wxStaticText( sbSizer41->GetStaticBox(), wxID_ANY, wxT("Debriefing Stage:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDebriefingStage->Wrap( -1 );
	fgSizer39->Add( lblDebriefingStage, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtAbbrevDebrief = new wxTextCtrl( sbSizer41->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer39->Add( txtAbbrevDebrief, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3 );
	
	lblMessage = new wxStaticText( sbSizer41->GetStaticBox(), wxID_ANY, wxT("Message:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMessage->Wrap( -1 );
	fgSizer39->Add( lblMessage, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtAbbrevMessage = new wxTextCtrl( sbSizer41->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer39->Add( txtAbbrevMessage, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3 );
	
	
	sbSizer41->Add( fgSizer39, 1, wxEXPAND, 5 );
	
	
	sbSizer40->Add( sbSizer41, 0, wxALL, 3 );
	
	wxStaticBoxSizer* sbSizer42;
	sbSizer42 = new wxStaticBoxSizer( new wxStaticBox( sbSizer40->GetStaticBox(), wxID_ANY, wxT("Other") ), wxHORIZONTAL );
	
	lblAudioFileExtension = new wxStaticText( sbSizer42->GetStaticBox(), wxID_ANY, wxT("File Extension:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAudioFileExtension->Wrap( -1 );
	sbSizer42->Add( lblAudioFileExtension, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	wxArrayString cboVAFileExtChoices;
	cboVAFileExt = new wxChoice( sbSizer42->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cboVAFileExtChoices, 0 );
	cboVAFileExt->SetSelection( 0 );
	sbSizer42->Add( cboVAFileExt, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	sbSizer40->Add( sbSizer42, 0, wxALL, 3 );
	
	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText125 = new wxStaticText( sbSizer40->GetStaticBox(), wxID_ANY, wxT("Example"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText125->Wrap( -1 );
	bSizer111->Add( m_staticText125, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	txtExampleFileName = new wxTextCtrl( sbSizer40->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtExampleFileName->Enable( false );
	
	bSizer111->Add( txtExampleFileName, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	sbSizer40->Add( bSizer111, 0, wxALL|wxEXPAND, 3 );
	
	chkVANoReplaceExistingFiles = new wxCheckBox( sbSizer40->GetStaticBox(), wxID_ANY, wxT("Don't replace existing files"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer40->Add( chkVANoReplaceExistingFiles, 0, wxALL|wxEXPAND, 3 );
	
	
	sbSizer40->Add( 0, 21, 1, wxEXPAND, 5 );
	
	btnGenerateFileNames = new wxButton( sbSizer40->GetStaticBox(), wxID_ANY, wxT("Generate File Names"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer40->Add( btnGenerateFileNames, 0, wxALL|wxEXPAND, 3 );
	
	
	fgSizer38->Add( sbSizer40, 1, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer43;
	sbSizer43 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Script options") ), wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer44;
	sbSizer44 = new wxStaticBoxSizer( new wxStaticBox( sbSizer43->GetStaticBox(), wxID_ANY, wxT("Script Entry Format") ), wxHORIZONTAL );
	
	txtScriptEntryFormat = new wxTextCtrl( sbSizer44->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	sbSizer44->Add( txtScriptEntryFormat, 1, wxALL|wxEXPAND, 3 );
	
	lblScriptHelp = new wxStaticText( sbSizer44->GetStaticBox(), wxID_ANY, wxT("$filename - Name of the message file\n$message - Text of the message\n$persona - Persona of the sender\n$sender - Name of the sender\n\nNote: $persona and $sender will only appear for the Message section"), wxDefaultPosition, wxDefaultSize, 0 );
	lblScriptHelp->Wrap( 190 );
	sbSizer44->Add( lblScriptHelp, 1, wxALL, 3 );
	
	
	sbSizer43->Add( sbSizer44, 0, wxALL|wxEXPAND, 3 );
	
	wxStaticBoxSizer* sbSizer45;
	sbSizer45 = new wxStaticBoxSizer( new wxStaticBox( sbSizer43->GetStaticBox(), wxID_ANY, wxT("Export...") ), wxVERTICAL );
	
	optEverything = new wxRadioButton( sbSizer45->GetStaticBox(), wxID_ANY, wxT("Everything"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer45->Add( optEverything, 0, wxALL, 3 );
	
	optJustCommandBriefings = new wxRadioButton( sbSizer45->GetStaticBox(), wxID_ANY, wxT("Just Command Briefings"), wxDefaultPosition, wxDefaultSize, 0 );
	optJustCommandBriefings->SetValue( true ); 
	sbSizer45->Add( optJustCommandBriefings, 0, wxALL, 3 );
	
	optJustBriefings = new wxRadioButton( sbSizer45->GetStaticBox(), wxID_ANY, wxT("Just Briefings"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer45->Add( optJustBriefings, 0, wxALL, 3 );
	
	optJustDebriefings = new wxRadioButton( sbSizer45->GetStaticBox(), wxID_ANY, wxT("Just Debriefings"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer45->Add( optJustDebriefings, 0, wxALL, 3 );
	
	optJustMessages = new wxRadioButton( sbSizer45->GetStaticBox(), wxID_ANY, wxT("Just Messages"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer45->Add( optJustMessages, 0, wxALL, 3 );
	
	wxBoxSizer* bSizer112;
	bSizer112 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer112->Add( 21, 0, 1, wxEXPAND, 5 );
	
	chkGroupMessageList = new wxCheckBox( sbSizer45->GetStaticBox(), wxID_ANY, wxT("Group send-message-list messages before others"), wxDefaultPosition, wxDefaultSize, 0 );
	chkGroupMessageList->Enable( false );
	
	bSizer112->Add( chkGroupMessageList, 0, wxALL, 3 );
	
	
	sbSizer45->Add( bSizer112, 1, 0, 5 );
	
	
	sbSizer43->Add( sbSizer45, 0, wxALL|wxEXPAND, 3 );
	
	
	sbSizer43->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnGenerateScript = new wxButton( sbSizer43->GetStaticBox(), wxID_ANY, wxT("Generate Script"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer43->Add( btnGenerateScript, 0, wxALL|wxEXPAND, 3 );
	
	
	fgSizer38->Add( sbSizer43, 1, wxALL|wxEXPAND, 3 );
	
	
	bSizer110->Add( fgSizer38, 1, 0, 5 );
	
	
	this->SetSizer( bSizer110 );
	this->Layout();
	bSizer110->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgVoiceActingManager::~dlgVoiceActingManager()
{
}

frmCampaignEditor::frmCampaignEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 226, 226, 226 ) );
	
	wxBoxSizer* bSizer113;
	bSizer113 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->SetSashGravity( 0 );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( frmCampaignEditor::m_splitter1OnIdle ), NULL, this );
	
	pnlCampaign = new wxScrolledWindow( m_splitter1, wxID_ANY, wxDefaultPosition, wxSize( 400,-1 ), wxHSCROLL|wxSUNKEN_BORDER|wxVSCROLL );
	pnlCampaign->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer114;
	bSizer114 = new wxBoxSizer( wxVERTICAL );
	
	lblAvailableMissions = new wxStaticText( pnlCampaign, wxID_ANY, wxT("Available missions:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAvailableMissions->Wrap( -1 );
	bSizer114->Add( lblAvailableMissions, 0, wxALIGN_LEFT|wxALL|wxTOP, 3 );
	
	lstAvailableMissions = new wxListCtrl( pnlCampaign, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING );
	bSizer114->Add( lstAvailableMissions, 0, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer115;
	bSizer115 = new wxBoxSizer( wxHORIZONTAL );
	
	lblCampaignName = new wxStaticText( pnlCampaign, wxID_ANY, wxT("Campaign Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCampaignName->Wrap( -1 );
	bSizer115->Add( lblCampaignName, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	txtCampaignName = new wxTextCtrl( pnlCampaign, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer115->Add( txtCampaignName, 1, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblCampaignType = new wxStaticText( pnlCampaign, wxID_ANY, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCampaignType->Wrap( 0 );
	bSizer115->Add( lblCampaignType, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	wxString cbCampaignTypeChoices[] = { wxT("single"), wxT("multi coop"), wxT("multi teams") };
	int cbCampaignTypeNChoices = sizeof( cbCampaignTypeChoices ) / sizeof( wxString );
	cbCampaignType = new wxChoice( pnlCampaign, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbCampaignTypeNChoices, cbCampaignTypeChoices, 0 );
	cbCampaignType->SetSelection( 0 );
	bSizer115->Add( cbCampaignType, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	
	bSizer114->Add( bSizer115, 0, wxALL|wxEXPAND, 3 );
	
	lblCampaignDescription = new wxStaticText( pnlCampaign, wxID_ANY, wxT("Campaign Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCampaignDescription->Wrap( -1 );
	bSizer114->Add( lblCampaignDescription, 0, wxALIGN_LEFT|wxALL, 3 );
	
	txtCampaignDescription = new wxTextCtrl( pnlCampaign, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,55 ), wxTE_MULTILINE );
	bSizer114->Add( txtCampaignDescription, 0, wxALL|wxEXPAND, 3 );
	
	chkUsesCustomTechDatabase = new wxCheckBox( pnlCampaign, wxID_ANY, wxT("Uses custom tech database"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
	bSizer114->Add( chkUsesCustomTechDatabase, 0, wxALIGN_RIGHT|wxALL, 3 );
	
	wxStaticBoxSizer* sbSizer46;
	sbSizer46 = new wxStaticBoxSizer( new wxStaticBox( pnlCampaign, wxID_ANY, wxT("Mission options") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer40;
	fgSizer40 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer40->SetFlexibleDirection( wxBOTH );
	fgSizer40->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblBriefingCutscene = new wxStaticText( sbSizer46->GetStaticBox(), wxID_ANY, wxT("Briefing Cutscene:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBriefingCutscene->Wrap( -1 );
	fgSizer40->Add( lblBriefingCutscene, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	fpBriefingCutscene = new wxFilePickerCtrl( sbSizer46->GetStaticBox(), wxID_ANY, wxT(",90,90,-1,70,0"), wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	fgSizer40->Add( fpBriefingCutscene, 0, wxALL|wxEXPAND, 3 );
	
	
	fgSizer40->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer41;
	fgSizer41 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer41->SetFlexibleDirection( wxBOTH );
	fgSizer41->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblMainhallIndex = new wxStaticText( sbSizer46->GetStaticBox(), wxID_ANY, wxT("Mainhall Index:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMainhallIndex->Wrap( -1 );
	fgSizer41->Add( lblMainhallIndex, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	spnMainHallIndex = new wxSpinCtrl( sbSizer46->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 9, 0 );
	fgSizer41->Add( spnMainHallIndex, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	lblDebriefingPersonaIndex = new wxStaticText( sbSizer46->GetStaticBox(), wxID_ANY, wxT("Debriefing Persona Index:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDebriefingPersonaIndex->Wrap( -1 );
	fgSizer41->Add( lblDebriefingPersonaIndex, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	spnDebriefingPersonaIndex = new wxSpinCtrl( sbSizer46->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 9, 0 );
	fgSizer41->Add( spnDebriefingPersonaIndex, 0, wxALL, 3 );
	
	
	fgSizer40->Add( fgSizer41, 1, wxEXPAND, 5 );
	
	
	sbSizer46->Add( fgSizer40, 0, 0, 5 );
	
	
	bSizer114->Add( sbSizer46, 0, wxALIGN_CENTER|wxALL, 3 );
	
	wxBoxSizer* bSizer116;
	bSizer116 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer117;
	bSizer117 = new wxBoxSizer( wxVERTICAL );
	
	lblBranches = new wxStaticText( pnlCampaign, wxID_ANY, wxT("Branches:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBranches->Wrap( 0 );
	bSizer117->Add( lblBranches, 0, wxALIGN_LEFT|wxALL|wxLEFT|wxRIGHT|wxTOP, 3 );
	
	treeBranches = new wxTreeCtrl( pnlCampaign, wxID_ANY, wxDefaultPosition, wxSize( 200,200 ), wxTR_EDIT_LABELS|wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_SINGLE|wxSUNKEN_BORDER );
	bSizer117->Add( treeBranches, 0, wxALL|wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 3 );
	
	
	bSizer116->Add( bSizer117, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 3 );
	
	wxBoxSizer* bSizer118;
	bSizer118 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer47;
	sbSizer47 = new wxStaticBoxSizer( new wxStaticBox( pnlCampaign, wxID_ANY, wxT("Branch Options") ), wxVERTICAL );
	
	btnMoveUp = new wxButton( sbSizer47->GetStaticBox(), wxID_ANY, wxT("Move Up"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	sbSizer47->Add( btnMoveUp, 0, wxALL, 3 );
	
	btnMoveDown = new wxButton( sbSizer47->GetStaticBox(), wxID_ANY, wxT("Move Down"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	sbSizer47->Add( btnMoveDown, 0, wxALL, 3 );
	
	btnToggleLoop = new wxButton( sbSizer47->GetStaticBox(), wxID_ANY, wxT("Toggle Loop"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	sbSizer47->Add( btnToggleLoop, 0, wxALL, 3 );
	
	
	bSizer118->Add( sbSizer47, 0, wxALIGN_RIGHT|wxALL, 3 );
	
	btnRealignTree = new wxButton( pnlCampaign, wxID_ANY, wxT("Realign Tree"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer118->Add( btnRealignTree, 0, wxALIGN_RIGHT|wxALL, 3 );
	
	btnLoadMission = new wxButton( pnlCampaign, wxID_ANY, wxT("Load Mission"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer118->Add( btnLoadMission, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT, 3 );
	
	btnClose = new wxButton( pnlCampaign, wxID_ANY, wxT("Close"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer118->Add( btnClose, 0, wxALIGN_RIGHT|wxALL, 3 );
	
	
	bSizer116->Add( bSizer118, 0, wxALIGN_TOP|wxALL|wxEXPAND, 3 );
	
	
	bSizer114->Add( bSizer116, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 3 );
	
	lblDesignerNotes = new wxStaticText( pnlCampaign, wxID_ANY, wxT("Designer Notes:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDesignerNotes->Wrap( -1 );
	bSizer114->Add( lblDesignerNotes, 0, wxALL, 3 );
	
	txtDesignerNotes = new wxTextCtrl( pnlCampaign, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,50 ), wxTE_MULTILINE|wxTE_READONLY );
	bSizer114->Add( txtDesignerNotes, 0, wxEXPAND|wxALL, 3 );
	
	wxStaticBoxSizer* sbSizer48;
	sbSizer48 = new wxStaticBoxSizer( new wxStaticBox( pnlCampaign, wxID_ANY, wxT("Mission Loop Options") ), wxVERTICAL );
	
	lblMissionLoopDiscription = new wxStaticText( sbSizer48->GetStaticBox(), wxID_ANY, wxT("Discription:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMissionLoopDiscription->Wrap( -1 );
	sbSizer48->Add( lblMissionLoopDiscription, 0, wxALIGN_LEFT|wxALL, 3 );
	
	txtMissionLoopDescription = new wxTextCtrl( sbSizer48->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,50 ), wxTE_MULTILINE );
	sbSizer48->Add( txtMissionLoopDescription, 0, wxALL|wxEXPAND, 3 );
	
	wxFlexGridSizer* fgSizer42;
	fgSizer42 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer42->AddGrowableCol( 1 );
	fgSizer42->SetFlexibleDirection( wxBOTH );
	fgSizer42->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblLoopBriefAni = new wxStaticText( sbSizer48->GetStaticBox(), wxID_ANY, wxT("Briefing Animation:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblLoopBriefAni->Wrap( -1 );
	fgSizer42->Add( lblLoopBriefAni, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	fpLoopBriefAni = new wxFilePickerCtrl( sbSizer48->GetStaticBox(), wxID_ANY, wxT(",90,90,-1,70,0"), wxT("Select an animation file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	fgSizer42->Add( fpLoopBriefAni, 1, wxALL|wxEXPAND, 3 );
	
	lblBriefVoice = new wxStaticText( sbSizer48->GetStaticBox(), wxID_ANY, wxT("Briefing Voice:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBriefVoice->Wrap( -1 );
	fgSizer42->Add( lblBriefVoice, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 3 );
	
	fpLoopBriefVoice = new wxFilePickerCtrl( sbSizer48->GetStaticBox(), wxID_ANY, wxT(",90,90,-1,70,0"), wxT("Selec a voice file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	fgSizer42->Add( fpLoopBriefVoice, 1, wxALL|wxEXPAND, 3 );
	
	
	sbSizer48->Add( fgSizer42, 1, wxEXPAND, 5 );
	
	
	bSizer114->Add( sbSizer48, 1, wxEXPAND, 5 );
	
	
	pnlCampaign->SetSizer( bSizer114 );
	pnlCampaign->Layout();
	pnlCampaignGraph = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
	m_splitter1->SplitVertically( pnlCampaign, pnlCampaignGraph, 0 );
	bSizer113->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer113 );
	this->Layout();
	m_menubar2 = new wxMenuBar( 0 );
	mnuFile = new wxMenu();
	wxMenuItem* mnuFileNew;
	mnuFileNew = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("New") ) + wxT('\t') + wxT("Ctrl-N"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileNew );
	
	wxMenuItem* mnuFileOpen;
	mnuFileOpen = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Open") ) + wxT('\t') + wxT("Ctrl-O"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileOpen );
	
	wxMenuItem* mnuFileSave;
	mnuFileSave = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Save") ) + wxT('\t') + wxT("Ctrl-S"), wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileSave );
	
	wxMenuItem* mnuFileSaveAs;
	mnuFileSaveAs = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Save As...") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileSaveAs );
	
	mnuFile->AppendSeparator();
	
	wxMenuItem* mnuFileExit;
	mnuFileExit = new wxMenuItem( mnuFile, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuFileExit );
	
	m_menubar2->Append( mnuFile, wxT("File") ); 
	
	other = new wxMenu();
	wxMenuItem* errorChecker;
	errorChecker = new wxMenuItem( other, wxID_ANY, wxString( wxT("Error Checker") ) + wxT('\t') + wxT("Alt-H"), wxEmptyString, wxITEM_NORMAL );
	other->Append( errorChecker );
	
	m_menubar2->Append( other, wxT("Other") ); 
	
	initialStatus = new wxMenu();
	wxMenuItem* ships;
	ships = new wxMenuItem( initialStatus, wxID_ANY, wxString( wxT("Ships") ) , wxEmptyString, wxITEM_NORMAL );
	initialStatus->Append( ships );
	
	wxMenuItem* weapons;
	weapons = new wxMenuItem( initialStatus, wxID_ANY, wxString( wxT("Weapons") ) , wxEmptyString, wxITEM_NORMAL );
	initialStatus->Append( weapons );
	
	m_menubar2->Append( initialStatus, wxT("Initial Status") ); 
	
	this->SetMenuBar( m_menubar2 );
	
	
	this->Centre( wxBOTH );
}

frmCampaignEditor::~frmCampaignEditor()
{
}

dlgMissionStats::dlgMissionStats( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* bSizer119;
	bSizer119 = new wxBoxSizer( wxVERTICAL );
	
	txtMissionStats = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	txtMissionStats->Enable( false );
	
	bSizer119->Add( txtMissionStats, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer120;
	bSizer120 = new wxBoxSizer( wxHORIZONTAL );
	
	btnDumpToFile = new wxButton( this, wxID_ANY, wxT("Dump to File"), wxDefaultPosition, wxSize( -1,30 ), 0 );
	bSizer120->Add( btnDumpToFile, 0, wxALL, 3 );
	
	btnCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxSize( -1,30 ), 0 );
	bSizer120->Add( btnCancel, 0, wxALL, 3 );
	
	
	bSizer119->Add( bSizer120, 0, wxALIGN_CENTER, 5 );
	
	
	this->SetSizer( bSizer119 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

dlgMissionStats::~dlgMissionStats()
{
}

dlgAboutBox::dlgAboutBox( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( this->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );
	
	bmpLogo = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("../res/fred_splash.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER );
	bmpLogo->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer121->Add( bmpLogo, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer122;
	bSizer122 = new wxBoxSizer( wxVERTICAL );
	
	lblAppTitle = new wxStaticText( this, wxID_ANY, wxT("FRED2_OPEN - FreeSpace Editor, Version 3.6.19"), wxDefaultPosition, wxDefaultSize, 0 );
	lblAppTitle->Wrap( -1 );
	bSizer122->Add( lblAppTitle, 0, wxALL, 3 );
	
	lblCopywrite = new wxStaticText( this, wxID_ANY, wxT("Copyright 1999 Volition, Inc.  All Rights Reserved"), wxDefaultPosition, wxDefaultSize, 0 );
	lblCopywrite->Wrap( -1 );
	bSizer122->Add( lblCopywrite, 0, wxALL, 3 );
	
	
	bSizer122->Add( 0, 0, 1, wxALL|wxEXPAND, 5 );
	
	lblDevelopers = new wxStaticText( this, wxID_ANY, wxT("Bravely maintained by:\n\tGoober5000, taylor, Karajorma and the SCP Team.\n\nPorted to OpenGL by:\n\tRandomTiger, Phreak, and Fry_Day.\n\nPorted to wxWidgets by:\n\tGoober5000, taylor, The E, and z64555."), wxDefaultPosition, wxSize( 300,-1 ), 0 );
	lblDevelopers->Wrap( -1 );
	bSizer122->Add( lblDevelopers, 0, wxALL, 3 );
	
	
	bSizer122->Add( 0, 0, 1, wxALL|wxEXPAND, 5 );
	
	lblQuote = new wxStaticText( this, wxID_ANY, wxT("\"Fred2 is the omega of all giant unwieldy pieces of code. It's big, it's horrifying, and it just doesn't care. View it at your own risk\" - Dave Baranec"), wxDefaultPosition, wxDefaultSize, 0 );
	lblQuote->Wrap( 370 );
	bSizer122->Add( lblQuote, 0, wxALL, 3 );
	
	
	bSizer122->Add( 0, 0, 1, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer43;
	fgSizer43 = new wxFlexGridSizer( 0, 5, 0, 5 );
	fgSizer43->AddGrowableCol( 1 );
	fgSizer43->AddGrowableCol( 2 );
	fgSizer43->AddGrowableCol( 3 );
	fgSizer43->SetFlexibleDirection( wxBOTH );
	fgSizer43->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer43->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	btnOK->SetDefault(); 
	fgSizer43->Add( btnOK, 0, wxEXPAND, 3 );
	
	btnReportBug = new wxButton( this, wxID_ANY, wxT("Report a Bug"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer43->Add( btnReportBug, 0, wxEXPAND, 3 );
	
	btnVisitForums = new wxButton( this, wxID_ANY, wxT("Visit Forums"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer43->Add( btnVisitForums, 0, wxALIGN_CENTER|wxEXPAND, 3 );
	
	
	fgSizer43->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer122->Add( fgSizer43, 0, wxEXPAND, 3 );
	
	
	bSizer121->Add( bSizer122, 1, wxALL|wxEXPAND, 3 );
	
	
	this->SetSizer( bSizer121 );
	this->Layout();
	bSizer121->Fit( this );
	
	this->Centre( wxBOTH );
}

dlgAboutBox::~dlgAboutBox()
{
}

dlgSexpHelp::dlgSexpHelp( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer123;
	bSizer123 = new wxBoxSizer( wxVERTICAL );
	
	pnlSexpHelp = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer124;
	bSizer124 = new wxBoxSizer( wxVERTICAL );
	
	lblArgInfo = new wxStaticText( pnlSexpHelp, wxID_ANY, wxT("Argument Info:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArgInfo->Wrap( -1 );
	bSizer124->Add( lblArgInfo, 0, wxALL, 3 );
	
	txtArgInfo = new wxTextCtrl( pnlSexpHelp, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer124->Add( txtArgInfo, 0, wxALL|wxEXPAND, 3 );
	
	lblSexpInfo = new wxStaticText( pnlSexpHelp, wxID_ANY, wxT("Sexp Info:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSexpInfo->Wrap( -1 );
	bSizer124->Add( lblSexpInfo, 0, wxALL, 3 );
	
	txtSexpInfo = new wxTextCtrl( pnlSexpHelp, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer124->Add( txtSexpInfo, 1, wxALL|wxEXPAND, 3 );
	
	
	pnlSexpHelp->SetSizer( bSizer124 );
	pnlSexpHelp->Layout();
	bSizer124->Fit( pnlSexpHelp );
	bSizer123->Add( pnlSexpHelp, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer123 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

dlgSexpHelp::~dlgSexpHelp()
{
}

pnlSexpHelp::pnlSexpHelp( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer125;
	bSizer125 = new wxBoxSizer( wxVERTICAL );
	
	lblArgInfo = new wxStaticText( this, wxID_ANY, wxT("Argument Info:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblArgInfo->Wrap( -1 );
	bSizer125->Add( lblArgInfo, 0, wxALL, 3 );
	
	txtArgInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer125->Add( txtArgInfo, 0, wxALL|wxEXPAND, 3 );
	
	lblSexpInfo = new wxStaticText( this, wxID_ANY, wxT("Sexp Info:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSexpInfo->Wrap( -1 );
	bSizer125->Add( lblSexpInfo, 0, wxALL, 3 );
	
	txtSexpInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer125->Add( txtSexpInfo, 1, wxALL|wxEXPAND, 3 );
	
	
	this->SetSizer( bSizer125 );
	this->Layout();
	bSizer125->Fit( this );
}

pnlSexpHelp::~pnlSexpHelp()
{
}
