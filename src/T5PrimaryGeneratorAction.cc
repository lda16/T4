#include "T5PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include "TMath.h"
#include "Randomize.hh"

T5PrimaryGeneratorAction::T5PrimaryGeneratorAction()
{
    T5GPS = new G4GeneralParticleSource();

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "gamma";
    T5GPS->SetParticleDefinition(particleTable->FindParticle(particleName));
}

T5PrimaryGeneratorAction::~T5PrimaryGeneratorAction()
{
    delete T5GPS;
}

void T5PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    T5GPS->GeneratePrimaryVertex(anEvent);
}