#include "globals.hh"

#include "T5PhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"

#include "G4OpWLS.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4OpticalPhoton.hh"

#include "G4SystemOfUnits.hh"




T5PhysicsList::T5PhysicsList() : QBBC(),
    theCerenkovProcess(nullptr),
    theScintillationProcess(nullptr),
    theBoundaryProcess(nullptr),
    theAbsorptionProcess(nullptr)
{
    void ConstructParticle();
    void ConstructProcess();
}

void T5PhysicsList::ConstructParticle()
{
    QBBC::ConstructParticle();
    G4OpticalPhoton::OpticalPhotonDefinition();   
}

void T5PhysicsList::ConstructProcess()
{
    QBBC::ConstructProcess();
    ConstructOp();
}

void T5PhysicsList::ConstructOp()
{
    AbsorptionOn = G4bool(true);
    theCerenkovProcess = new G4Cerenkov("Cerenkov");
    theScintillationProcess = new G4Scintillation("Scintillation");
    theBoundaryProcess = new G4OpBoundaryProcess();
    theAbsorptionProcess = new G4OpAbsorption();

    theCerenkovProcess -> SetVerboseLevel(0);
    theScintillationProcess -> SetVerboseLevel(0);
    theBoundaryProcess ->SetVerboseLevel(0);
    theAbsorptionProcess ->SetVerboseLevel(4);

    theCerenkovProcess->SetMaxNumPhotonsPerStep(300);
    theCerenkovProcess->SetMaxBetaChangePerStep(10.0);
    theCerenkovProcess->SetTrackSecondariesFirst(true);

    theScintillationProcess->SetTrackSecondariesFirst(true);
    theScintillationProcess->SetScintillationYieldFactor(1.0);
    //theScintillationProcess->SetScintillationExcitationRatio(0.0);
    //theScintillationProcess->SetFiniteRiseTime(true);

    G4ParticleTable::G4PTblDicIterator* theParticleIterator = GetParticleIterator();
    theParticleIterator->reset();
    while((*theParticleIterator)()){
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        //  G4cout<<particleName<<G4endl;
        //  G4cout<<(theCerenkovProcess->IsApplicable(*particle))<<G4endl;
        //  G4cout<<(theScintillationProcess->IsApplicable(*particle))<<G4endl;
        //  G4cout<<(theBoundaryProcess->IsApplicable(*particle))<<G4endl;
        //  G4cout<<(theAbsorptionProcess->IsApplicable(*particle))<<G4endl;
        if(theCerenkovProcess->IsApplicable(*particle)){
            pmanager->AddProcess(theCerenkovProcess);
            pmanager->SetProcessOrdering(theCerenkovProcess, idxPostStep);
        }
        if(theScintillationProcess->IsApplicable(*particle)){
            pmanager->AddProcess(theScintillationProcess);
            pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
            pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
        }
        if(theBoundaryProcess->IsApplicable(*particle)){
            pmanager->AddProcess(theBoundaryProcess);
            pmanager->SetProcessOrderingToLast(theBoundaryProcess, idxPostStep);
        }
        if(theAbsorptionProcess->IsApplicable(*particle)){
            pmanager->AddProcess(theAbsorptionProcess);
            pmanager->SetProcessOrderingToLast(theAbsorptionProcess, idxPostStep);
        }
    }

}