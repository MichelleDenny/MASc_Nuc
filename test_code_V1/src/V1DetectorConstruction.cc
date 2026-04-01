#include "V1DetectorConstruction.hh"

V1DetectorConstruction::V1DetectorConstruction()
{
}

V1DetectorConstruction::~V1DetectorConstruction()
{
}

G4VPhysicalVolume *V1DetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;

    G4NistManager *nist = G4NistManager::Instance();

    G4Isotope *D = new G4Isotope("Deuteron", 1, 2, 2.0141018 * g / mole);
    G4Element *elD = new G4Element("Deuterium", "elD", 1);
    elD->AddIsotope(D, 1);
    G4Material *matD = new G4Material("matD", 0.00018 * g / cm3, 1);
    matD->AddElement(elD, 1);

    G4Element *elTi = new G4Element("Titanium", "Ti", 22., 47.867 * g / mole);

    G4double density = 4.0 * g / cm3;
    G4Material *TiD2 = new G4Material("TitaniumDeuteride", density, 2);

    TiD2->AddElement(elTi, 1);
    TiD2->AddElement(elD, 2); // creating ion target

    G4Material *grapMat = nist->FindOrBuildMaterial("G4_Al");
    G4Material *worldMat = new G4Material("Vacuum", 1., 1.01 * g / mole, 1.e-25 * g / cm3); // numerical vacuum
    // G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4double xWorld = 1. * m;
    G4double yWorld = 1. * m;
    G4double zWorld = 2. * m;

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    // logical vol takes over solid world/volume
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);
    // first arg is for rotation; G43vec is class that takes in xyz comp - 000 puts cube in the centre

    // constructing the Al hollow tube
    const G4int numZPlanes = 4;
    G4double fLength = 152 * cm;          // totallength of the tube
    G4double fRadius = 1.905 * cm;        // outer radius of the tube that will go inside the moderator
    G4double shroudThickness = 0.09 * cm; // thickness of tube

    const G4double zPlane[numZPlanes] = {-fLength * 0.5, (-fLength * 0.5 + shroudThickness), (-fLength * 0.5 + shroudThickness), fLength * 0.5};
    const G4double rInner[numZPlanes] = {0.0, 0.0, fRadius - shroudThickness, fRadius - shroudThickness};
    const G4double rOuter[numZPlanes] = {fRadius, fRadius, fRadius, fRadius};
    G4Polycone *AlTube = new G4Polycone("AlTubeInner", 0, 2 * CLHEP::pi, numZPlanes, zPlane, rInner, rOuter);

    G4LogicalVolume *logicAltube = new G4LogicalVolume(AlTube, grapMat, "logicalAlTube");
    G4VPhysicalVolume *physAlTube = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicAltube, "physAlTube", logicWorld, 0, checkOverlaps);

    G4VisAttributes *tubeVisAtt = new G4VisAttributes(G4Color(0.0, 0.0, 1.0, 0.8));
    tubeVisAtt->SetForceSolid(true);
    logicAltube->SetVisAttributes(tubeVisAtt);

    // fill tube/cyclinder with D2 gas
    G4Tubs *gasTube = new G4Tubs("maintube", 0., fRadius - shroudThickness, fLength * 0.5, 0.0 * deg, 360.0 * deg);
    G4LogicalVolume *logicGasTube = new G4LogicalVolume(gasTube, matD, "logicalGasTube");
    G4VPhysicalVolume *physGasTube = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicGasTube, "physGasTube", logicAltube, 0, checkOverlaps);

    G4VisAttributes *gasVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
    gasVisAtt->SetForceSolid(true);
    logicGasTube->SetVisAttributes(gasVisAtt);

    G4double iTargetRadius = 1.90 * cm;
    G4double iTargetThickness = 1.00 * mm; // dimensions of ion target
    G4Tubs *ionTarget = new G4Tubs("ionTarget", 0., iTargetRadius, iTargetThickness * 0.5, 0.0 * deg, 360.0 * deg);
    G4LogicalVolume *logicIonTarget = new G4LogicalVolume(ionTarget, TiD2, "logicIonTarget");
    G4VPhysicalVolume *physIonTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicIonTarget, "physIonTarget", logicGasTube, 0, checkOverlaps);

    G4VisAttributes *ionTargetVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 1.0, 1.0)); // ion target is purple
    ionTargetVisAtt->SetForceSolid(true);
    logicIonTarget->SetVisAttributes(ionTargetVisAtt);

    // graphite moderator
    // G4double grapThickness = 152. * cm;
    // G4double grapSize = 10. * cm;
    // G4Box *solidGrap = new G4Box("solidGrap", 0.5 * grapSize, 0.5 * grapSize, 0.5 * grapThickness);
    // G4LogicalVolume *logicGrap = new G4LogicalVolume(solidGrap, grapMat, "logicGrapBlock");

    return physWorld;
}

// void test1DetectorConstruction::ConstructSDandField()

//{test1SensitiveDetector *sensDet = new test1SensitiveDetector("SensitiveDetector");
// logicDetector->SetSensitiveDetector(sensDet);
// G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);}