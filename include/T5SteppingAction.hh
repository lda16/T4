// T5SteppingAction.hh

#ifndef T5SteppingAction_h
#define T5SteppingAction_h 1

#include "G4UserSteppingAction.hh"

#include "G4Types.hh"

class T5DetectorConstruction;
class T5EventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class T5SteppingAction : public G4UserSteppingAction
{
  public:
    T5SteppingAction(T5DetectorConstruction*, T5EventAction*);
   ~T5SteppingAction(){};

    void UserSteppingAction(const G4Step*);

  private:
    T5DetectorConstruction* T5DetCons;
    T5EventAction*      T5Event;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
