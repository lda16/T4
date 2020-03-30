//T5TrackingAction.cc

#include "T5TrackingAction.hh"
#include "T5DetectorConstruction.hh"
#include "T5EventAction.hh"

#include "G4Event.hh"
#include "G4Track.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
T5TrackingAction::T5TrackingAction(T5DetectorConstruction* det,
				     T5EventAction* evt):
    T5DetCons(det),T5Event(evt)
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
T5TrackingAction::~T5TrackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void T5TrackingAction::PreUserTrackingAction(const G4Track* trk)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void T5TrackingAction::PostUserTrackingAction(const G4Track* trk)
{
    auto volume = trk->GetVolume();
    auto next_volume = trk->GetNextVolume();
    for(G4int i=0; i<9; i++)
    {
        auto sipm = T5DetCons->GetSiPM(i);
        if((sipm==volume)||(sipm == next_volume)){
            G4cout<<"triggered"<<G4endl;
            G4cout<<sipm<<G4endl;
            G4cout<<volume<<G4endl;
            G4cout<<next_volume<<G4endl;
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
