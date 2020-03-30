//T5PhysicsList.hh

#ifndef T5PhysicsList_h
#define T5PhysicsList_h 1

#include "QBBC.hh"

#include "G4Types.hh"

#include "G4OpWLS.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"

#include "G4OpRayleigh.hh"
#include "G4OpAbsorption.hh"
#include "G4OpBoundaryProcess.hh"

class T5PhysicsList : public QBBC
{
    public:
    T5PhysicsList();
    ~T5PhysicsList(){};
    void ConstructParticle();
    void ConstructProcess();

    protected:
    void ConstructOp();
    //G4OpWLS*                theWLSProcess;
    G4Cerenkov*             theCerenkovProcess;
    G4Scintillation*        theScintillationProcess;
    G4OpAbsorption*         theAbsorptionProcess;
    //G4OpRayleigh*           theRayleighScatteringProcess;
    G4OpBoundaryProcess*    theBoundaryProcess;

    G4bool AbsorptionOn;

};

#endif