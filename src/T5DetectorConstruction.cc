#include "T5DetectorConstruction.hh"

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4String.hh"

#include "G4OpBoundaryProcess.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"

#include "TMath.h"


T5DetectorConstruction::T5DetectorConstruction():
    T5crystal_0(nullptr),
    sipm_0(nullptr),
    sipm_1(nullptr),
    sipm_2(nullptr),
    sipm_3(nullptr),
    sipm_4(nullptr),
    sipm_5(nullptr),
    sipm_6(nullptr),
    sipm_7(nullptr),
    sipm_8(nullptr)
{
}

T5DetectorConstruction::~T5DetectorConstruction()
{
}

G4VPhysicalVolume* T5DetectorConstruction::Construct()
{
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4String name,symbol;

  G4Element* elH=new G4Element(name="Hydrogen",symbol="H",z=1.,a=1.01*g/mole);
  G4Element* elC=new G4Element(name="Carbon",symbol="C",z=6.,a=12.01*g/mole);
  G4Element* elF=new G4Element(name="Fluorine",symbol="F",z=9.,a=18.9984032*g/mole);
  G4Element* elAr=new G4Element(name="ArgonGas",symbol="Ar",z=18.,a=39.95*g/mole);
  G4Element* elN=new G4Element(name="Nitrogen",symbol="N",z=7.,a=14.006747*g/mole);
  G4Element* elO=new G4Element(name="Oxygen",symbol="O",z=8.,a=15.9994*g/mole);
  G4Element* elAl=new G4Element(name="Aluminium",symbol="Al",z=13.,a=26.981539*g/mole);
  G4Element* elPb=new G4Element(name="Lead",symbol="Pb",z=82.,a=207.2*g/mole);
  G4Element* elCa=new G4Element(name="Calcium",symbol="Ca",z=20.,a=40.078*g/mole);
  G4Element* elMg=new G4Element(name="Magnesium",symbol="Mg",z=12.,a=24.3050*g/mole);
  G4Element* elFe=new G4Element(name="Iron",symbol="Fe",z=26.,a=55.847*g/mole);
  G4Element* elSi=new G4Element(name="Silicon",symbol="Si",z=14.,a=28.0855*g/mole);
  G4Element* elCe=new G4Element(name="Cerium",symbol="Ce",z=58.,a=140.116*g/mole);
  G4Element* elGd=new G4Element(name="Gadolinium",symbol="Gd",z=64.,a=157.25*g/mole);
  G4Element* elGa=new G4Element(name="Gallium",symbol="Ga",z=31.,a=69.723*g/mole);

//------------------------------------------------------ materials
  G4double density;
  G4int ncomponents,natoms;

//gas for chamber
  G4Material* gas=new G4Material(name="ArC2H6",density=1.563*mg/cm3,ncomponents=3);
  gas->AddElement(elH,natoms=6);
  gas->AddElement(elC,natoms=2);
  gas->AddElement(elAr,natoms=1);
    
//Al
  G4Material* al=new G4Material(name="Al",density=2.70*g/cm3,ncomponents=1);
  al->AddElement(elAl,natoms=1);
//Pb
  G4Material* pb=new G4Material(name="Pb",density=11.34*g/cm3,ncomponents=1);
  pb->AddElement(elPb,natoms=1);
//HDPE
  G4Material* hdpe=new G4Material(name="HDPE",density=0.96*g/cm3,ncomponents=2);
  hdpe->AddElement(elH,natoms=4);
  hdpe->AddElement(elC,natoms=2);
//PTFE
  G4Material* PTFE=new G4Material(name="PTFE",density=1.696*g/cm3,ncomponents=2);
  PTFE->AddElement(elF,natoms=4);
  PTFE->AddElement(elC,natoms=2);


//Concrete
  G4double fractionmass;
  G4Material* Concrete=new G4Material(name="Concrete",density=2.40*g/cm3,ncomponents=7); G4double fractiontotal=100.;

  Concrete->AddElement(elSi,fractionmass=2100./24.*28./60.*perCent); fractiontotal=fractiontotal-fractionmass/perCent;
  Concrete->AddElement(elCa,fractionmass=200./24.*40./56.*perCent); fractiontotal=fractiontotal-fractionmass/perCent;
  Concrete->AddElement(elFe,fractionmass=15./24.*112./160.*perCent); fractiontotal=fractiontotal-fractionmass/perCent;
  Concrete->AddElement(elAl,fractionmass=15./24.*54./102.*perCent); fractiontotal=fractiontotal-fractionmass/perCent;
  Concrete->AddElement(elMg,fractionmass=10./24.*24./40.*perCent); fractiontotal=fractiontotal-fractionmass/perCent;
  Concrete->AddElement(elH,fractionmass=60./24.*2./18.*perCent); fractiontotal=fractiontotal-fractionmass/perCent;
  Concrete->AddElement(elO,fractionmass=fractiontotal*perCent);
//EJ-301 or BC501 liquid scintillator(EJ-309//EJ-301)
  G4Material* ej301_m=new G4Material(name="EJ-301",density=/*0.874*/0.959*g/cm3,ncomponents=2);
  ej301_m->AddElement(elH,natoms=543);//4.82);
  ej301_m->AddElement(elC,natoms=435);//3.98);

//EJ-299-34A
  G4Material* ej299_m=new G4Material(name="EJ-299",density=1.08*g/cm3,ncomponents=2);
  ej299_m->AddElement(elH,natoms=513);//4.82);
  ej299_m->AddElement(elC,natoms=486);//3.98);

//SP-101
  G4Material* sp101_m=new G4Material(name="SP-101",density=1.05*g/cm3,ncomponents=2);
  sp101_m->AddElement(elH,natoms=517);//4.82);
  sp101_m->AddElement(elC,natoms=469);//3.98);
  const double hc=6.62606876*2.99792458*100./1.602176462;

const G4int NUMENTRIES = 3;
G4double Scnt_PP[NUMENTRIES] = { hc/422.*eV, hc/423.*eV, hc/424.*eV };
G4double Scnt_FAST[NUMENTRIES] = { 0., 1., 0. };
G4double Scnt_RefractiveIndex[NUMENTRIES] = { 1.58, 1.58, 1.58 };
G4double Scnt_AbsorptionLength[NUMENTRIES] = { 2.5*m, 2.5*m, 2.5*m };
G4MaterialPropertiesTable* Scnt_MPT = new G4MaterialPropertiesTable();
Scnt_MPT->AddProperty("FASTCOMPONENT", Scnt_PP, Scnt_FAST, NUMENTRIES);
Scnt_MPT->AddProperty("RINDEX", Scnt_PP, Scnt_RefractiveIndex, NUMENTRIES);
Scnt_MPT->AddProperty("ABSLENGTH", Scnt_PP, Scnt_AbsorptionLength, NUMENTRIES);
Scnt_MPT->AddConstProperty("SCINTILLATIONYIELD", 8000.*0.27*3.1415926*23.*23./50./60./MeV);
Scnt_MPT->AddConstProperty("RESOLUTIONSCALE", 2.0);
Scnt_MPT->AddConstProperty("FASTTIMECONSTANT", 2.8*ns);
Scnt_MPT->AddConstProperty("FASTSCINTILLATIONRISETIME", 1.0*ns);
Scnt_MPT->AddConstProperty("YIELDRATIO", 1.);
sp101_m->SetMaterialPropertiesTable(Scnt_MPT);

//GAGG
  G4Material* gagg=new G4Material(name="gagg",density=6.63*g/cm3,ncomponents=5);
  gagg->AddElement(elCe,natoms=1);
  gagg->AddElement(elGd,natoms=3);
  gagg->AddElement(elAl,natoms=2);
  gagg->AddElement(elGa,natoms=3);
  gagg->AddElement(elO,natoms=12);

const G4int NUMENTRIES_GAGG = 3;
G4double Scnt_PP_GAGG[NUMENTRIES_GAGG] = { hc/521.*eV, hc/520.*eV, hc/519.*eV };
G4double Scnt_FAST_GAGG[NUMENTRIES_GAGG] = { 0.91, 0.91, 0.91 };
G4double Scnt_SLOW_GAGG[NUMENTRIES_GAGG] = { 0.09, 0.09, 0.09 };
G4double Scnt_RefractiveIndex_GAGG[NUMENTRIES_GAGG] = { 1.87, 1.87, 1.87 };
G4double Scnt_AbsorptionLength_GAGG[NUMENTRIES_GAGG] = { 2.5*m, 2.5*m, 2.5*m };
G4MaterialPropertiesTable* Scnt_MPT_GAGG = new G4MaterialPropertiesTable();
Scnt_MPT_GAGG->AddProperty("FASTCOMPONENT", Scnt_PP_GAGG, Scnt_FAST_GAGG, NUMENTRIES_GAGG);
Scnt_MPT_GAGG->AddProperty("SLOWCOMPONENT", Scnt_PP_GAGG, Scnt_SLOW_GAGG, NUMENTRIES_GAGG);
Scnt_MPT_GAGG->AddProperty("RINDEX", Scnt_PP_GAGG, Scnt_RefractiveIndex_GAGG, NUMENTRIES_GAGG);
Scnt_MPT_GAGG->AddProperty("ABSLENGTH", Scnt_PP_GAGG, Scnt_AbsorptionLength_GAGG, NUMENTRIES_GAGG);
Scnt_MPT_GAGG->AddConstProperty("SCINTILLATIONYIELD", 57000./MeV);
Scnt_MPT_GAGG->AddConstProperty("RESOLUTIONSCALE", 1.0);
Scnt_MPT_GAGG->AddConstProperty("FASTTIMECONSTANT", 88.*ns);
Scnt_MPT_GAGG->AddConstProperty("SLOWTIMECONSTANT", 258.*ns);
Scnt_MPT_GAGG->AddConstProperty("YIELDRATIO", 1.);
gagg->SetMaterialPropertiesTable(Scnt_MPT_GAGG);

//PTFE Add
const G4int NUMENTRIES_PTFE = 3;
G4double ptfe_PP[NUMENTRIES_PTFE] = { hc/521.*eV, hc/520.*eV, hc/519.*eV };
G4double ptfe_RefractiveIndex[NUMENTRIES_PTFE] = { 1, 1, 1 };
G4double ptfe_AbsorptionLength[NUMENTRIES_PTFE] = { 2*um, 2*um, 2*um };
G4MaterialPropertiesTable* PTFE_MPT = new G4MaterialPropertiesTable();
  PTFE_MPT->AddProperty("RINDEX", ptfe_PP, ptfe_RefractiveIndex, NUMENTRIES_PTFE);
PTFE_MPT->AddProperty("ABSLENGTH", ptfe_PP, ptfe_AbsorptionLength, NUMENTRIES_PTFE);
PTFE->SetMaterialPropertiesTable(PTFE_MPT);

//silicone oil
  G4Material* silicone_oil=new G4Material(name="silicone oil",density=0.963*g/cm3,ncomponents=4);
  silicone_oil->AddElement(elC,natoms=2);
  silicone_oil->AddElement(elH,natoms=6);
  silicone_oil->AddElement(elSi,natoms=1);
  silicone_oil->AddElement(elO,natoms=1);
G4double Scnt_RefractiveIndex_silicone_oil[NUMENTRIES] = { 1.406, 1.406, 1.406 }; //{ 1.58, 1.58, 1.58 };//
G4MaterialPropertiesTable* Scnt_MPT_silicone_oil = new G4MaterialPropertiesTable();
Scnt_MPT_silicone_oil->AddProperty("RINDEX", Scnt_PP, Scnt_RefractiveIndex_silicone_oil, NUMENTRIES);
silicone_oil->SetMaterialPropertiesTable(Scnt_MPT_silicone_oil);


//air
  G4Material* air=new G4Material(name="air",density=1.293*mg/cm3,ncomponents=3);
  air->AddElement(elN,fractionmass=75.5*perCent);
  air->AddElement(elO,fractionmass=23.2*perCent);
  air->AddElement(elAr,fractionmass=1.3*perCent);
G4double Scnt_RefractiveIndex_air[NUMENTRIES] = { 1, 1, 1 };
G4MaterialPropertiesTable* Scnt_MPT_air = new G4MaterialPropertiesTable();
Scnt_MPT_air->AddProperty("RINDEX", Scnt_PP, Scnt_RefractiveIndex_air, NUMENTRIES);
air->SetMaterialPropertiesTable(Scnt_MPT_air);

//Vaccum for world
  G4Material* vacuum=new G4Material("Galactic",z=1.,a=1.01*g/mole,density=universe_mean_density,kStateGas,2.73*kelvin,3.e-18*pascal);  

//------------------------------------------------------ volumes
//experimental hall (world volume)
  G4Box* world=new G4Box("world",2000.*mm,2000.*mm,2000.*mm);
  G4LogicalVolume* world_log=new G4LogicalVolume(world,vacuum,"world_log");
  G4VPhysicalVolume* world_phys=new G4PVPlacement(0,G4ThreeVector(),world_log,"world_phys",0,false,0);

  world_log->SetVisAttributes(G4VisAttributes::Invisible);

//a scintillator  
  G4double len=10.*mm, wid=10.*mm, hig=5.*mm, wid_air=0.02*mm, wid_ptfe=0.03*mm;

  G4Box* chamber=new G4Box("chamber",len,wid,hig);
  G4LogicalVolume* chamber_log=new G4LogicalVolume(chamber,gagg,"chamber_log");
  G4VPhysicalVolume* chamber_phys=new G4PVPlacement(0,G4ThreeVector(),chamber_log,"chamber_phys",world_log,false,0);

  G4VisAttributes* chamber_visAttr=new G4VisAttributes(G4Color(1.0,1.0,1.0,0.2));
  chamber_visAttr->SetForceSolid(true);
  chamber_log->SetVisAttributes(chamber_visAttr);

  G4Box* air_1=new G4Box("air_1",len,wid,wid_air);
//   G4Box* air_2=new G4Box("air_2",len,wid_air,hig);
//   G4Box* air_3=new G4Box("air_3",wid_air,wid,hig);
//   G4LogicalVolume* air_log_1=new G4LogicalVolume(air_1,air,"air_log_1");
//   G4LogicalVolume* air_log_2=new G4LogicalVolume(air_2,air,"air_log_2");
//   G4LogicalVolume* air_log_3=new G4LogicalVolume(air_3,air,"air_log_3");
  G4LogicalVolume* si_oil_log=new G4LogicalVolume(air_1,silicone_oil,"silicon_oil_log");
//   G4VPhysicalVolume* air_phys_1=new G4PVPlacement(0,G4ThreeVector(0,0,hig+wid_air),air_log_1,"air_phys_1",world_log,false,0);
  G4VPhysicalVolume* sil_phys_2=new G4PVPlacement(0,G4ThreeVector(0,0,-hig-wid_air),si_oil_log,"si_oil_phys",world_log,false,0);
//   G4VPhysicalVolume* air_phys_3=new G4PVPlacement(0,G4ThreeVector(0,wid+wid_air,0),air_log_2,"air_phys_3",world_log,false,0);
//   G4VPhysicalVolume* air_phys_4=new G4PVPlacement(0,G4ThreeVector(0,-wid-wid_air,0),air_log_2,"air_phys_4",world_log,false,0);
//   G4VPhysicalVolume* air_phys_5=new G4PVPlacement(0,G4ThreeVector(wid+wid_air,0,0),air_log_3,"air_phys_5",world_log,false,0);
//   G4VPhysicalVolume* air_phys_6=new G4PVPlacement(0,G4ThreeVector(-wid-wid_air,0,0),air_log_3,"air_phys_6",world_log,false,0);

  //Teflon
  G4Box* teflon_1=new G4Box("teflon_1",len,wid,wid_ptfe);
  G4Box* teflon_2=new G4Box("teflon_2",len,wid_ptfe,hig);
  G4Box* teflon_3=new G4Box("teflon_3",wid_ptfe,wid,hig);
  G4LogicalVolume* teflon_log_1=new G4LogicalVolume(teflon_1,PTFE,"teflon_log_1");
  G4LogicalVolume* teflon_log_2=new G4LogicalVolume(teflon_2,PTFE,"teflon_log_2");
  G4LogicalVolume* teflon_log_3=new G4LogicalVolume(teflon_3,PTFE,"teflon_log_3");
  G4VPhysicalVolume* teflon_phys_1=new G4PVPlacement(0,G4ThreeVector(0,0,hig+wid_ptfe),teflon_log_1,"teflon_phys_1",world_log,false,0);
  
  G4VPhysicalVolume* teflon_phys_3=new G4PVPlacement(0,G4ThreeVector(0,wid+wid_ptfe,0),teflon_log_2,"teflon_phys_3",world_log,false,0);
  G4VPhysicalVolume* teflon_phys_4=new G4PVPlacement(0,G4ThreeVector(0,-wid-wid_ptfe,0),teflon_log_2,"teflon_phys_4",world_log,false,0);
  G4VPhysicalVolume* teflon_phys_5=new G4PVPlacement(0,G4ThreeVector(wid+wid_ptfe,0,0),teflon_log_3,"teflon_phys_5",world_log,false,0);
  G4VPhysicalVolume* teflon_phys_6=new G4PVPlacement(0,G4ThreeVector(-wid-wid_ptfe,0,0),teflon_log_3,"teflon_phys_6",world_log,false,0);

  //SiPM
  G4Material* chip = new G4Material(name = "chip", z = 14, a = 28.0855*g/mole, density = 2.33*g/cm3, kStateSolid);
    


    G4double SiPM_side = 3.065*mm, SiPM_thick = 0.23*mm;
    G4Box* SiPM_box = new G4Box("SiPM_box",SiPM_side, SiPM_side, SiPM_thick);
    G4LogicalVolume* SiPM_log = new G4LogicalVolume(SiPM_box, chip, "SiPM_log");
    G4VPhysicalVolume* SiPM_phys_0 = new G4PVPlacement(0, G4ThreeVector(-2*SiPM_side,2*SiPM_side,-hig-SiPM_thick),SiPM_log,"SiPM_Phys_0",world_log,false,0);
    G4VPhysicalVolume* SiPM_phys_1 = new G4PVPlacement(0, G4ThreeVector(0,2*SiPM_side,-hig-SiPM_thick),SiPM_log,"SiPM_Phys_1",world_log,false,0);
    G4VPhysicalVolume* SiPM_phys_2 = new G4PVPlacement(0, G4ThreeVector(2*SiPM_side,2*SiPM_side,-hig-SiPM_thick),SiPM_log,"SiPM_Phys_2",world_log,false,0);
    G4VPhysicalVolume* SiPM_phys_3 = new G4PVPlacement(0, G4ThreeVector(-2*SiPM_side,0,-hig-SiPM_thick),SiPM_log,"SiPM_Phys_3",world_log,false,0);
    G4VPhysicalVolume* SiPM_phys_4 = new G4PVPlacement(0, G4ThreeVector(0,0,-hig-SiPM_thick),SiPM_log,"SiPM_Phys_4",world_log,false,0);
    G4VPhysicalVolume* SiPM_phys_5 = new G4PVPlacement(0, G4ThreeVector(2*SiPM_side,0,-hig-SiPM_thick),SiPM_log,"SiPM_Phys_5",world_log,false,0);
    G4VPhysicalVolume* SiPM_phys_6 = new G4PVPlacement(0, G4ThreeVector(-2*SiPM_side,-2*SiPM_side,-hig-SiPM_thick),SiPM_log,"SiPM_Phys_6",world_log,false,0);
    G4VPhysicalVolume* SiPM_phys_7 = new G4PVPlacement(0, G4ThreeVector(0,-2*SiPM_side,-hig-SiPM_thick),SiPM_log,"SiPM_Phys_7",world_log,false,0);
    G4VPhysicalVolume* SiPM_phys_8 = new G4PVPlacement(0, G4ThreeVector(2*SiPM_side,-2*SiPM_side,-hig-SiPM_thick),SiPM_log,"SiPM_Phys_8",world_log,false,0);
    
    
    //Boundary Definition
    G4OpticalSurface* SiOil_SiPM_0 = new G4OpticalSurface("SiPM_SiOil_0");
    G4OpticalSurface* SiOil_SiPM_1 = new G4OpticalSurface("SiPM_SiOil_1");
    G4OpticalSurface* SiOil_SiPM_2 = new G4OpticalSurface("SiPM_SiOil_2");
    G4OpticalSurface* SiOil_SiPM_3 = new G4OpticalSurface("SiPM_SiOil_3");
    G4OpticalSurface* SiOil_SiPM_4 = new G4OpticalSurface("SiPM_SiOil_4");
    G4OpticalSurface* SiOil_SiPM_5 = new G4OpticalSurface("SiPM_SiOil_5");
    G4OpticalSurface* SiOil_SiPM_6 = new G4OpticalSurface("SiPM_SiOil_6");
    G4OpticalSurface* SiOil_SiPM_7 = new G4OpticalSurface("SiPM_SiOil_7");
    G4OpticalSurface* SiOil_SiPM_8 = new G4OpticalSurface("SiPM_SiOil_8");
    G4OpticalSurface* GAGG_Teflon_1 = new G4OpticalSurface("GAGG_Teflon_1");
    G4OpticalSurface* GAGG_Teflon_3 = new G4OpticalSurface("GAGG_Teflon_3");
    G4OpticalSurface* GAGG_Teflon_4 = new G4OpticalSurface("GAGG_Teflon_4");
    G4OpticalSurface* GAGG_Teflon_5 = new G4OpticalSurface("GAGG_Teflon_5");
    G4OpticalSurface* GAGG_Teflon_6 = new G4OpticalSurface("GAGG_Teflon_6");
    G4LogicalBorderSurface* SiOil_SiPM_LBS_0 = new G4LogicalBorderSurface("SiPM_SiOil_LBS_0",  sil_phys_2,SiPM_phys_0,SiOil_SiPM_0);
    G4LogicalBorderSurface* SiOil_SiPM_LBS_1 = new G4LogicalBorderSurface("SiPM_SiOil_LBS_1",  sil_phys_2,SiPM_phys_1,SiOil_SiPM_1);
    G4LogicalBorderSurface* SiOil_SiPM_LBS_2 = new G4LogicalBorderSurface("SiPM_SiOil_LBS_2",  sil_phys_2,SiPM_phys_2,SiOil_SiPM_2);
    G4LogicalBorderSurface* SiOil_SiPM_LBS_3 = new G4LogicalBorderSurface("SiPM_SiOil_LBS_3",  sil_phys_2,SiPM_phys_3,SiOil_SiPM_3);
    G4LogicalBorderSurface* SiOil_SiPM_LBS_4 = new G4LogicalBorderSurface("SiPM_SiOil_LBS_4",  sil_phys_2,SiPM_phys_4,SiOil_SiPM_4);
    G4LogicalBorderSurface* SiOil_SiPM_LBS_5 = new G4LogicalBorderSurface("SiPM_SiOil_LBS_5",  sil_phys_2,SiPM_phys_5,SiOil_SiPM_5);
    G4LogicalBorderSurface* SiOil_SiPM_LBS_6 = new G4LogicalBorderSurface("SiPM_SiOil_LBS_6",  sil_phys_2,SiPM_phys_6,SiOil_SiPM_6);
    G4LogicalBorderSurface* SiOil_SiPM_LBS_7 = new G4LogicalBorderSurface("SiPM_SiOil_LBS_7",  sil_phys_2,SiPM_phys_7,SiOil_SiPM_7);
    G4LogicalBorderSurface* SiOil_SiPM_LBS_8 = new G4LogicalBorderSurface("SiPM_SiOil_LBS_8",  sil_phys_2,SiPM_phys_8,SiOil_SiPM_8);
    G4LogicalBorderSurface* GAGG_Teflon_LBS_1 = new G4LogicalBorderSurface("GAGG_Teflon_LBS_1",  chamber_phys,teflon_phys_1,GAGG_Teflon_1);
    G4LogicalBorderSurface* GAGG_Teflon_LBS_3 = new G4LogicalBorderSurface("GAGG_Teflon_LBS_3",  chamber_phys,teflon_phys_3,GAGG_Teflon_3);
    G4LogicalBorderSurface* GAGG_Teflon_LBS_4 = new G4LogicalBorderSurface("GAGG_Teflon_LBS_4",  chamber_phys,teflon_phys_4,GAGG_Teflon_4);
    G4LogicalBorderSurface* GAGG_Teflon_LBS_5 = new G4LogicalBorderSurface("GAGG_Teflon_LBS_5",  chamber_phys,teflon_phys_5,GAGG_Teflon_5);
    G4LogicalBorderSurface* GAGG_Teflon_LBS_6 = new G4LogicalBorderSurface("GAGG_Teflon_LBS_6",  chamber_phys,teflon_phys_6,GAGG_Teflon_6);

    SiOil_SiPM_0 = dynamic_cast <G4OpticalSurface*>
        (SiOil_SiPM_LBS_0->GetSurface(sil_phys_2,SiPM_phys_0)->
                                                       GetSurfaceProperty());
    SiOil_SiPM_1 = dynamic_cast <G4OpticalSurface*>
        (SiOil_SiPM_LBS_1->GetSurface(sil_phys_2,SiPM_phys_1)->
                                                       GetSurfaceProperty());
    SiOil_SiPM_2 = dynamic_cast <G4OpticalSurface*>
        (SiOil_SiPM_LBS_2->GetSurface(sil_phys_2,SiPM_phys_2)->
                                                       GetSurfaceProperty());
    SiOil_SiPM_3 = dynamic_cast <G4OpticalSurface*>
        (SiOil_SiPM_LBS_3->GetSurface(sil_phys_2,SiPM_phys_3)->
                                                       GetSurfaceProperty());
    SiOil_SiPM_4 = dynamic_cast <G4OpticalSurface*>
        (SiOil_SiPM_LBS_4->GetSurface(sil_phys_2,SiPM_phys_4)->
                                                       GetSurfaceProperty());
    SiOil_SiPM_5 = dynamic_cast <G4OpticalSurface*>
        (SiOil_SiPM_LBS_5->GetSurface(sil_phys_2,SiPM_phys_5)->
                                                       GetSurfaceProperty());
    SiOil_SiPM_6 = dynamic_cast <G4OpticalSurface*>
        (SiOil_SiPM_LBS_6->GetSurface(sil_phys_2,SiPM_phys_6)->
                                                       GetSurfaceProperty());
    SiOil_SiPM_7 = dynamic_cast <G4OpticalSurface*>
        (SiOil_SiPM_LBS_7->GetSurface(sil_phys_2,SiPM_phys_7)->
                                                       GetSurfaceProperty());
    SiOil_SiPM_8 = dynamic_cast <G4OpticalSurface*>
        (SiOil_SiPM_LBS_8->GetSurface(sil_phys_2,SiPM_phys_8)->
                                                       GetSurfaceProperty());
    GAGG_Teflon_1 = dynamic_cast <G4OpticalSurface*>
        (GAGG_Teflon_LBS_1->GetSurface(chamber_phys,teflon_phys_1)->
                                                       GetSurfaceProperty());
    GAGG_Teflon_3 = dynamic_cast <G4OpticalSurface*>
        (GAGG_Teflon_LBS_3->GetSurface(chamber_phys,teflon_phys_3)->
                                                       GetSurfaceProperty());
    GAGG_Teflon_4 = dynamic_cast <G4OpticalSurface*>
        (GAGG_Teflon_LBS_4->GetSurface(chamber_phys,teflon_phys_4)->
                                                       GetSurfaceProperty());
    GAGG_Teflon_5 = dynamic_cast <G4OpticalSurface*>
        (GAGG_Teflon_LBS_5->GetSurface(chamber_phys,teflon_phys_5)->
                                                       GetSurfaceProperty());
    GAGG_Teflon_6 = dynamic_cast <G4OpticalSurface*>
        (GAGG_Teflon_LBS_6->GetSurface(chamber_phys,teflon_phys_6)->
                                                       GetSurfaceProperty());
    
    
    // if (SiOil_SiPM_0) SiOil_SiPM_0->DumpInfo();
    // if (SiOil_SiPM_1) SiOil_SiPM_1->DumpInfo();
    // if (SiOil_SiPM_2) SiOil_SiPM_2->DumpInfo();
    // if (SiOil_SiPM_3) SiOil_SiPM_3->DumpInfo();
    // if (SiOil_SiPM_4) SiOil_SiPM_4->DumpInfo();
    // if (SiOil_SiPM_5) SiOil_SiPM_5->DumpInfo();
    // if (SiOil_SiPM_6) SiOil_SiPM_6->DumpInfo();
    // if (SiOil_SiPM_7) SiOil_SiPM_7->DumpInfo();
    // if (SiOil_SiPM_8) SiOil_SiPM_8->DumpInfo();
    // if (GAGG_Teflon_1) GAGG_Teflon_1->DumpInfo();
    // if (GAGG_Teflon_3) GAGG_Teflon_3->DumpInfo();
    // if (GAGG_Teflon_4) GAGG_Teflon_4->DumpInfo();
    // if (GAGG_Teflon_5) GAGG_Teflon_5->DumpInfo();
    // if (GAGG_Teflon_6) GAGG_Teflon_6->DumpInfo();
    // G4cout<<GAGG_Teflon_6<<G4endl;

    SiOil_SiPM_0->SetType(dielectric_metal);
    SiOil_SiPM_1->SetType(dielectric_metal);
    SiOil_SiPM_2->SetType(dielectric_metal);
    SiOil_SiPM_3->SetType(dielectric_metal);
    SiOil_SiPM_4->SetType(dielectric_metal);
    SiOil_SiPM_5->SetType(dielectric_metal);
    SiOil_SiPM_6->SetType(dielectric_metal);
    SiOil_SiPM_7->SetType(dielectric_metal);
    SiOil_SiPM_8->SetType(dielectric_metal);
    GAGG_Teflon_1->SetType(dielectric_LUTDAVIS);
    GAGG_Teflon_3->SetType(dielectric_LUTDAVIS);
    GAGG_Teflon_4->SetType(dielectric_LUTDAVIS);
    GAGG_Teflon_5->SetType(dielectric_LUTDAVIS);
    GAGG_Teflon_6->SetType(dielectric_LUTDAVIS);
    SiOil_SiPM_0->SetModel(unified);
    SiOil_SiPM_1->SetModel(unified);
    SiOil_SiPM_2->SetModel(unified);
    SiOil_SiPM_3->SetModel(unified);
    SiOil_SiPM_4->SetModel(unified);
    SiOil_SiPM_5->SetModel(unified);
    SiOil_SiPM_6->SetModel(unified);
    SiOil_SiPM_7->SetModel(unified);
    SiOil_SiPM_8->SetModel(unified);
    GAGG_Teflon_1->SetModel(DAVIS);
    GAGG_Teflon_3->SetModel(DAVIS);
    GAGG_Teflon_4->SetModel(DAVIS);
    GAGG_Teflon_5->SetModel(DAVIS);
    GAGG_Teflon_6->SetModel(DAVIS);
    SiOil_SiPM_0->SetFinish(groundair);
    SiOil_SiPM_1->SetFinish(groundair);
    SiOil_SiPM_2->SetFinish(groundair);
    SiOil_SiPM_3->SetFinish(groundair);
    SiOil_SiPM_4->SetFinish(groundair);
    SiOil_SiPM_5->SetFinish(groundair);
    SiOil_SiPM_6->SetFinish(groundair);
    SiOil_SiPM_7->SetFinish(groundair);
    SiOil_SiPM_8->SetFinish(groundair);
    GAGG_Teflon_1->SetFinish(PolishedESR_LUT);
    GAGG_Teflon_3->SetFinish(PolishedESR_LUT);
    GAGG_Teflon_4->SetFinish(PolishedESR_LUT);
    GAGG_Teflon_5->SetFinish(PolishedESR_LUT);
    GAGG_Teflon_6->SetFinish(PolishedESR_LUT);




    const G4int NUMENTRIES_CHIP = 3;
    G4double sipm_pp[NUMENTRIES_CHIP] = {hc/521.*eV, hc/520.*eV, hc/519.*eV};
    G4double sipm_sl[NUMENTRIES_CHIP] = {0,0,0};
    G4double sipm_ss[NUMENTRIES_CHIP] = {0,0,0};
    G4double sipm_bs[NUMENTRIES_CHIP] = {0,0,0};
    G4double sipm_rindex[NUMENTRIES_CHIP] = {1.406,1.406,1.406};
    G4double sipm_reflectivity[NUMENTRIES_CHIP] = {0,0,0};
    G4double sipm_efficiency[NUMENTRIES_CHIP] = {0.4,0.4,0.4};

    G4MaterialPropertiesTable* SIPM_MPT_Surf = new G4MaterialPropertiesTable();
    SIPM_MPT_Surf->AddProperty("SPECULARLOBECONSTANT",sipm_pp,sipm_sl,NUMENTRIES_CHIP);
    SIPM_MPT_Surf->AddProperty("SPECULARSPIKECONSTANT",sipm_pp,sipm_ss,NUMENTRIES_CHIP);
    SIPM_MPT_Surf->AddProperty("BACKSCATTERCONSTANT",sipm_pp,sipm_bs,NUMENTRIES_CHIP);
    SIPM_MPT_Surf->AddProperty("REFLECTIVITY",sipm_pp,sipm_reflectivity,NUMENTRIES_CHIP);
    SIPM_MPT_Surf->AddProperty("EFFICIENCY",sipm_pp,sipm_efficiency,NUMENTRIES_CHIP);
    SIPM_MPT_Surf->AddProperty("RINDEX",sipm_pp,sipm_rindex,NUMENTRIES_CHIP);

    SiOil_SiPM_0->SetMaterialPropertiesTable(SIPM_MPT_Surf);
    SiOil_SiPM_1->SetMaterialPropertiesTable(SIPM_MPT_Surf);
    SiOil_SiPM_2->SetMaterialPropertiesTable(SIPM_MPT_Surf);
    SiOil_SiPM_3->SetMaterialPropertiesTable(SIPM_MPT_Surf);
    SiOil_SiPM_4->SetMaterialPropertiesTable(SIPM_MPT_Surf);
    SiOil_SiPM_5->SetMaterialPropertiesTable(SIPM_MPT_Surf);
    SiOil_SiPM_6->SetMaterialPropertiesTable(SIPM_MPT_Surf);
    SiOil_SiPM_7->SetMaterialPropertiesTable(SIPM_MPT_Surf);
    SiOil_SiPM_8->SetMaterialPropertiesTable(SIPM_MPT_Surf);

    const G4int NUMENTRIES_TEFLON = 3;
    G4double teflon_pp[NUMENTRIES_TEFLON] = {hc/521.*eV, hc/520.*eV, hc/519.*eV};
    G4double teflon_sl[NUMENTRIES_TEFLON] = {0.99,0.99,0.99};
    G4double teflon_ss[NUMENTRIES_TEFLON] = {0,0,0};
    G4double teflon_bs[NUMENTRIES_TEFLON] = {0,0,0};
    //G4double sipm_rindex[NUMENTRIES_CHIP] = {1,1,1};
    G4double teflon_reflectivity[NUMENTRIES_CHIP] = {0.99,0.99,0.99};
    //G4double sipm_efficiency[NUMENTRIES_CHIP] = {0,0,0};

    G4MaterialPropertiesTable* TEFLON_MPT_Surf = new G4MaterialPropertiesTable();
    TEFLON_MPT_Surf->AddProperty("SPECULARLOBECONSTANT",teflon_pp,teflon_sl,NUMENTRIES_TEFLON);
    TEFLON_MPT_Surf->AddProperty("SPECULARSPIKECONSTANT",teflon_pp,teflon_ss,NUMENTRIES_TEFLON);
    TEFLON_MPT_Surf->AddProperty("BACKSCATTERCONSTANT",teflon_pp,teflon_bs,NUMENTRIES_TEFLON);
    TEFLON_MPT_Surf->AddProperty("REFLECTIVITY",teflon_pp,teflon_reflectivity,NUMENTRIES_TEFLON);

    GAGG_Teflon_1->SetMaterialPropertiesTable(TEFLON_MPT_Surf);
    GAGG_Teflon_3->SetMaterialPropertiesTable(TEFLON_MPT_Surf);
    GAGG_Teflon_4->SetMaterialPropertiesTable(TEFLON_MPT_Surf);
    GAGG_Teflon_5->SetMaterialPropertiesTable(TEFLON_MPT_Surf);
    GAGG_Teflon_6->SetMaterialPropertiesTable(TEFLON_MPT_Surf);


    // if (SiOil_SiPM_0) SiOil_SiPM_0->DumpInfo();
    // if (SiOil_SiPM_1) SiOil_SiPM_1->DumpInfo();
    // if (SiOil_SiPM_2) SiOil_SiPM_2->DumpInfo();
    // if (SiOil_SiPM_3) SiOil_SiPM_3->DumpInfo();
    // if (SiOil_SiPM_4) SiOil_SiPM_4->DumpInfo();
    // if (SiOil_SiPM_5) SiOil_SiPM_5->DumpInfo();
    // if (SiOil_SiPM_6) SiOil_SiPM_6->DumpInfo();
    // if (SiOil_SiPM_7) SiOil_SiPM_7->DumpInfo();
    // if (SiOil_SiPM_8) SiOil_SiPM_8->DumpInfo();
    // if (GAGG_Teflon_1) GAGG_Teflon_1->DumpInfo();
    // if (GAGG_Teflon_3) GAGG_Teflon_3->DumpInfo();
    // if (GAGG_Teflon_4) GAGG_Teflon_4->DumpInfo();
    // if (GAGG_Teflon_5) GAGG_Teflon_5->DumpInfo();
    // if (GAGG_Teflon_6) GAGG_Teflon_6->DumpInfo();


    T5crystal_0 = chamber_phys;
    sipm_0 = SiPM_phys_0;
    sipm_1 = SiPM_phys_1;
    sipm_2 = SiPM_phys_2;
    sipm_3 = SiPM_phys_3;
    sipm_4 = SiPM_phys_4;
    sipm_5 = SiPM_phys_5;
    sipm_6 = SiPM_phys_6;
    sipm_7 = SiPM_phys_7;
    sipm_8 = SiPM_phys_8;
  return world_phys;
}

