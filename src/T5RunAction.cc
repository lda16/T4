//T5RunAction.cc
 
#include "T5RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
T5RunAction::T5RunAction()
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(0);
  
  analysisManager->CreateH1("T5H0","T5H0",50,0.01,3*MeV,"MeV");


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
T5RunAction::~T5RunAction()
{
  

  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void T5RunAction::BeginOfRunAction(const G4Run* aRun)
{
  auto analysisManager = G4AnalysisManager::Instance();
  //G4String fileName = "T5log";
  //analysisManager->OpenFile(fileName);
  G4cout<<"cccccccccccccccccccccccccccccccccccccccccccccccccccBegin Running ..." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void T5RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4cout<<"End Running ..."<<G4endl;
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager -> SetH1Plotting(0,true);


  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
