#ifndef V3DETECTORCONSTRUCTION_HH
#define V3DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "globals.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4SubtractionSolid.hh"
#include "G4Polycone.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Tubs.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh" //gives detectors certain color when multiple are present
#include "G4SDManager.hh"

#include "V3SensitiveDetector.hh"

class G4Material;

class V3DetectorConstruction : public G4VUserDetectorConstruction // inherits class frm GRVU
{
public:
    V3DetectorConstruction();
    virtual ~V3DetectorConstruction(); // has to be a virtual fucntion cause its already defined in class?

    virtual G4VPhysicalVolume *Construct();

private:
    G4LogicalVolume *logicsphDet; // scoring volume is vol of  detector
    //  write void when there is no return value
    virtual void ConstructSDandField(); // constructs any sensitive detector or any additional field
};

#endif