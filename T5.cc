#include "T5DetectorConstruction.hh"
#include "T5PhysicsList.hh"
#include "T5RunAction.hh"
#include "T5EventAction.hh"
#include "T5TrackingAction.hh"
#include "T5SteppingAction.hh"
#include "T5PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#define G4VIS_USE
#define G4UI_USE

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

int main(int argc, char** argv)
{
    G4RunManager* T5RunManager = new G4RunManager;

    T5DetectorConstruction* T5DetCons = new T5DetectorConstruction();
    T5RunManager -> SetUserInitialization(T5DetCons);
    T5RunManager -> SetUserInitialization(new T5PhysicsList());

    T5RunManager -> SetUserAction(new T5PrimaryGeneratorAction());
    T5RunManager -> SetUserAction(new T5RunAction());
    T5EventAction* T5Event = new T5EventAction();
    T5RunManager -> SetUserAction(T5Event);
    T5RunManager -> SetUserAction(new T5TrackingAction(T5DetCons,T5Event));
	T5RunManager -> SetUserAction(new T5SteppingAction(T5DetCons,T5Event));


    T5RunManager -> Initialize();

    #ifdef G4VIS_USE
    G4VisManager* T5Vis = new G4VisExecutive;
    T5Vis -> Initialize();
    #endif

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/run/verbose 1");
    UImanager->ApplyCommand("/event/verbose 1");
    UImanager->ApplyCommand("/tracking/verbose 1");

    if (argc != 1){
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager -> ApplyCommand(command+fileName);
    }
    else {
        #ifdef G4UI_USE
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        #ifdef G4VIS_USE
        //UImanager -> ApplyCommand("/control/execute gps_def_03.mac");
        UImanager -> ApplyCommand("/control/execute init_vis.mac");
        #endif
        ui -> SessionStart();
        delete ui;
        #endif
    }

    #ifdef G4VIS_USE
    delete T5Vis;
    #endif
    
    delete T5RunManager;
    return 0;
}