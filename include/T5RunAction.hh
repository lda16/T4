//T5RunAction.hh

#ifndef T5RunAction_h
#define T5RunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class T5RunAction : public G4UserRunAction
{
    public:
    T5RunAction();
    ~T5RunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};

#endif