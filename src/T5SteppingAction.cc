// T5SteppingAction.cc


#include "T5SteppingAction.hh"

#include "T5DetectorConstruction.hh"
#include "T5EventAction.hh"

#include "G4Track.hh"
#include "G4SteppingManager.hh"

#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T5SteppingAction::T5SteppingAction(T5DetectorConstruction* det,
				     T5EventAction* evt)
:T5DetCons(det),T5Event(evt)
{ }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T5SteppingAction::UserSteppingAction(const G4Step* aStep)
{ 

  auto volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  //G4cout<<volume<<G4endl;
  
  auto edep = aStep->GetTotalEnergyDeposit();
  //G4cout<<edep<<G4endl;
  //G4cout<<T5DetCons->GetCrystal(i)<<G4endl;
  if (volume == T5DetCons->GetCrystal()){
    T5Event->AddEnergyToCrystal(edep);
    //G4cout<<"True"<<G4endl;
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

