//T5EventAction.cc

#include "T5EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
T5EventAction::T5EventAction()
  : Energy_0(0.)
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
T5EventAction::~T5EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void T5EventAction::BeginOfEventAction(const G4Event* evt)
{
  Energy_0=0.;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void T5EventAction::EndOfEventAction(const G4Event* evt)
{

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager -> FillH1(0, Energy_0);


  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T5EventAction::AddEnergyToCrystal(G4double de)
{

    Energy_0 += de;

}
