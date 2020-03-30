#ifndef T5DetectorConstruction_h
#define T5DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4String.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "TMath.h"
#include "G4GDMLParser.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;

class T5DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        T5DetectorConstruction();
        ~T5DetectorConstruction();
        const G4VPhysicalVolume* GetCrystal() const;
        const G4VPhysicalVolume* GetSiPM(G4int i) const;

        G4VPhysicalVolume* Construct();
    
    private:
        G4VPhysicalVolume* T5crystal_0;
        G4VPhysicalVolume* sipm_0;
        G4VPhysicalVolume* sipm_1;
        G4VPhysicalVolume* sipm_2;
        G4VPhysicalVolume* sipm_3;
        G4VPhysicalVolume* sipm_4;
        G4VPhysicalVolume* sipm_5;
        G4VPhysicalVolume* sipm_6;
        G4VPhysicalVolume* sipm_7;
        G4VPhysicalVolume* sipm_8;
        
};

inline const G4VPhysicalVolume* T5DetectorConstruction::GetCrystal() const
{
    return T5crystal_0;
}

inline const G4VPhysicalVolume* T5DetectorConstruction::GetSiPM(G4int i) const
{
    switch  (i){
        case 0:
        return sipm_0;
        break;
        case 1:
        return sipm_1;
        break;
        case 2:
        return sipm_2;
        break;
        case 3:
        return sipm_3;
        break;
        case 4:
        return sipm_4;
        break;
        case 5:
        return sipm_5;
        break;
        case 6:
        return sipm_6;
        break;
        case 7:
        return sipm_7;
        break;
        case 8:
        return sipm_8;
        break;
        default:
        break;
    }
}

#endif