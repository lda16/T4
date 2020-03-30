#ifndef T5EventAction_h
#define T5EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

class T5EventAction : public G4UserEventAction
{
  public:
    T5EventAction();
   ~T5EventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
    void AddEnergyToCrystal(G4double);

  private:
    G4double Energy_0;
};

#endif