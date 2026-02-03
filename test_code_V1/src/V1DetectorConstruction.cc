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
    // G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *grapMat = nist->FindOrBuildMaterial("G4_GRAPHITE");
    G4Material *worldMat = new G4Material("Vacuum", 1., 1.01 * g / mole, 1.e-25 * g / cm3); // numerical vacuum

    G4double xWorld = 1. * m;
    G4double yWorld = 1. * m;
    G4double zWorld = 2. * m;

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    // logical vol takes over solid world/volume
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);
    // first arg is for rotation; G43vec is class that takes in xyz comp - 000 puts cube in the centre

    // graphite moderator
    G4double grapThickness = 152. * cm;
    G4double grapSize = 10. * cm;
    G4Box *solidGrap = new G4Box("solidGrap", 0.5 * grapSize, 0.5 * grapSize, 0.5 * grapThickness);
    // G4LogicalVolume *logicGrap = new G4LogicalVolume(solidGrap, grapMat, "logicGrapBlock");

    G4double holeRadius = 1.0 * cm;
    G4double holeLength = grapThickness;
    // Hole (cylinder)
    G4Tubs *solidHole = new G4Tubs("solidHole", 0., holeRadius, 0.5 * holeLength, 0., 360. * deg);
    // Graphite with hole
    G4SubtractionSolid *solidGrapWithHole = new G4SubtractionSolid("solidGrapWithHole", solidGrap, solidHole, nullptr, G4ThreeVector(0., 0., 0.));
    // Logical volume
    G4LogicalVolume *logicGrap = new G4LogicalVolume(solidGrapWithHole, grapMat, "logicGrapBlock");
    G4VPhysicalVolume *physGrap = new G4PVPlacement(0, G4ThreeVector(0., 0., 0. * cm), logicGrap, "physGrapBlock", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *grapVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
    grapVisAtt->SetForceSolid(true);
    logicGrap->SetVisAttributes(grapVisAtt);

    return physWorld;
}

// void test1DetectorConstruction::ConstructSDandField()

//{test1SensitiveDetector *sensDet = new test1SensitiveDetector("SensitiveDetector");
// logicDetector->SetSensitiveDetector(sensDet);
// G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);}