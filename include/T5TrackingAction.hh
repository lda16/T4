#ifndef T5TrackingAction_h
#define T5TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class G4Track;
class T5DetectorConstruction;
class T5EventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class T5TrackingAction : public G4UserTrackingAction
{
  public:
    T5TrackingAction(T5DetectorConstruction*, T5EventAction*);
   ~T5TrackingAction();

  public:
    void PreUserTrackingAction(const G4Track*);
    void PostUserTrackingAction(const G4Track*);

  private:
    T5DetectorConstruction* T5DetCons;
    T5EventAction*      T5Event;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
