#ifndef T5PrimaryGeneratorAction_h
#define T5PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;

class T5PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
private:
    G4GeneralParticleSource* T5GPS;
public:
    T5PrimaryGeneratorAction();
    ~T5PrimaryGeneratorAction();
    void GeneratePrimaries(G4Event* anEvent);

};

#endif