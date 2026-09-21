#include "V3DetectorConstruction.hh"
#include "G4SDManager.hh"

V3DetectorConstruction::V3DetectorConstruction()
{
}

V3DetectorConstruction::~V3DetectorConstruction()
{
}

G4VPhysicalVolume *V3DetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;

    G4NistManager *nist = G4NistManager::Instance();

    // G4Material *matPoly = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    // Definining Elements needed for shielding materials
    auto *elH = nist->FindOrBuildElement("H");
    auto *elC = nist->FindOrBuildElement("C");
    G4Element *elO = nist->FindOrBuildElement("O");
    G4Element *elSi = nist->FindOrBuildElement("Si");
    G4Element *elAl = nist->FindOrBuildElement("Al");
    G4Element *elNa = nist->FindOrBuildElement("Na");
    G4Element *elB = nist->FindOrBuildElement("B");
    G4Element *elCa = nist->FindOrBuildElement("Ca");
    G4Element *elFe = nist->FindOrBuildElement("Fe");

    G4Material *matTest = nist->FindOrBuildMaterial("G4_WATER");

    //  Non-borated Polyethylene - PNNL (PNNL-15870 Rev.2)
    G4Material *polyEth = new G4Material("Non-Borated Polyethylene, (PNNL)", 0.93 * g / cm3, 2);
    polyEth->AddElement(elH, 0.143724);
    polyEth->AddElement(elC, 0.856276);
    // 5% Borated Polyethylene - PNNL
    // G4Material *borypoly = new G4Material("5% Borated Polyethylene", 1.01 * g / cm3, 3);
    // borypoly->AddElement(elH, 0.133);
    // borypoly->AddElement(elC, 0.817);
    // borypoly->AddElement(elB, 0.050);

    // 5% Borated Polyethylene - PNNL
    G4Element *ellH = new G4Element("Hydrogen", "H", 2); // for BPeth

    G4Isotope *H1 = new G4Isotope("H1", 1, 1, 1.00784 * g / mole);
    G4Isotope *H2 = new G4Isotope("H2", 1, 2, 2.01410 * g / mole);
    ellH->AddIsotope(H1, 0.9997686);
    ellH->AddIsotope(H2, 0.0002314);

    G4Element *ellB = new G4Element("Boron", "B", 2); // for BPeth
    G4Isotope *B10 = new G4Isotope("B10", 5, 10, 10.012937 * g / mole);
    G4Isotope *B11 = new G4Isotope("B11", 5, 11, 11.009305 * g / mole);

    ellB->AddIsotope(B10, 0.1843124);
    ellB->AddIsotope(B11, 0.8156876);

    G4Material *borypoly = new G4Material("5% Borated Polyethylene", 1.01, 3);
    borypoly->AddElement(ellH, 0.1323149);
    borypoly->AddElement(ellB, 0.0499899);
    borypoly->AddElement(elC, 0.817680833);

    // concrete

    G4Material *concrete = new G4Material("Concrete, LANL MCNP mix (PNNL)", 2.25, 7);

    concrete->AddElementByMassFraction(elH, 0.004530);
    concrete->AddElementByMassFraction(elO, 0.512600);
    concrete->AddElementByMassFraction(elSi, 0.360360);
    concrete->AddElementByMassFraction(elAl, 0.035550);
    concrete->AddElementByMassFraction(elNa, 0.015270);
    concrete->AddElementByMassFraction(elCa, 0.057910);
    concrete->AddElementByMassFraction(elFe, 0.013780);

    G4Material *coreGraphite = new G4Material("Graphite Core", 1.70, 2);

    coreGraphite->AddElementByMassFraction(elC, 0.999999);
    coreGraphite->AddElementByMassFraction(elB, 0.000001);

    // Neutron generator Materials

    G4Isotope *D = new G4Isotope("Deuteron", 1, 2, 2.0141018 * g / mole);
    G4Element *elD = new G4Element("Deuterium", "elD", 1);
    elD->AddIsotope(D, 1);
    G4Material *matD = new G4Material("matD", 0.00018 * g / cm3, 1);
    matD->AddElement(elD, 1);

    G4Isotope *Li6 = new G4Isotope("Lithium-6", 3, 3, 6.015 * g / mole);
    G4Element *elLi = new G4Element("Lithium", "elLi", 1);
    elLi->AddIsotope(Li6, 1);
    G4Material *matLi = new G4Material("matLi", 0.460 * g / cm3, 1);
    matLi->AddElement(elLi, 1);

    G4Element *elTi = new G4Element("Titanium", "Ti", 22., 47.867 * g / mole);
    G4double Tidensity = 4.0 * g / cm3;
    G4Material *TiD2 = new G4Material("TitaniumDeuteride", Tidensity, 2);

    TiD2->AddElement(elTi, 1);
    TiD2->AddElement(elD, 2); // creating ion target

    // Creating World material and box- cube
    G4Material *grapMat = nist->FindOrBuildMaterial("G4_Al");                               //-tube mat
    G4Material *worldMat = new G4Material("Vacuum", 1., 1.01 * g / mole, 1.e-25 * g / cm3); // numerical vacuum
    // G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4double xWorld = 5.0 * m;
    G4double yWorld = 5.0 * m;
    G4double zWorld = 5.0 * m;
    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);
    /*
        /// Outer Poly Shielding
        G4double xOuterpoly = 126.86 * cm; // half lengths
        G4double yOuterpoly = 126.86 * cm;
        G4double zOuterpoly = 126.86 * cm;

        G4double xOuterconc = 85.54 * cm;
        G4double yOuterconc = 85.54 * cm; // og106.54
        G4double zOuterconc = 85.54 * cm;

        G4Box *solidOuterpoly = new G4Box("solidOuterpoly", xOuterpoly, yOuterpoly, zOuterpoly);
        G4Box *outerPolyhole = new G4Box("outerPolyhole", xOuterconc, yOuterconc, zOuterconc);

        G4SubtractionSolid *shellOuterpoly = new G4SubtractionSolid("shellOuterpoly", solidOuterpoly, outerPolyhole, 0, G4ThreeVector(0., 0., 0.));

        G4LogicalVolume *logicOuterpoly = new G4LogicalVolume(shellOuterpoly, borypoly, "logicOuterpoly");
        G4VPhysicalVolume *physOuterpoly = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicOuterpoly, "physOuterpoly", logicWorld, false, 0, checkOverlaps);

        // Concrete Shielding
        G4double xInnerpoly = 45.82 * cm; // half lengths #o g60.82 * cm;
        G4double yInnerpoly = 45.82 * cm;
        G4double zInnerpoly = 45.82 * cm;

        G4Box *solidConcreteouter = new G4Box("solidConcreteouter", xOuterconc, yOuterconc, zOuterconc);
        G4Box *concreteHole = new G4Box("solidInnerpoly", xInnerpoly, yInnerpoly, zInnerpoly);

        G4SubtractionSolid *shellConcrete = new G4SubtractionSolid("shellConcrete", solidConcreteouter, concreteHole, 0, G4ThreeVector(0., 0., 0.));
        G4LogicalVolume *logicConcrete = new G4LogicalVolume(shellConcrete, concrete, "logicConcrete");
        G4VPhysicalVolume *physConcrete = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicConcrete, "physConcrete", logicWorld, false, 0, checkOverlaps);

    // Inner Poly/Graphite shielding

    // Concrete Shielding
    G4double xInnerpoly = 45.82 * cm; // half lengths #o g60.82 * cm;
    G4double yInnerpoly = 45.82 * cm;
    G4double zInnerpoly = 45.82 * cm;

    G4double xCentralVoid = 40.5 * cm; // half lengths
    G4double yCentralVoid = 40.5 * cm;
    G4double zCentralVoid = 40.5 * cm;

    G4Box *solidInnerpoly = new G4Box("solidInnerpoly", xInnerpoly, yInnerpoly, zInnerpoly);
    G4Box *innerPolyhole = new G4Box("innerPolyhole", xCentralVoid, yCentralVoid, zCentralVoid);

    G4SubtractionSolid *shellInnerpoly = new G4SubtractionSolid("shellInnerpoly", solidInnerpoly, innerPolyhole, 0, G4ThreeVector(0., 0., 0.));
    G4LogicalVolume *logicInnerpoly = new G4LogicalVolume(shellInnerpoly, coreGraphite, "logicInnerpoly");
    G4VPhysicalVolume *physInnerpoly = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicInnerpoly, "physInnerpoly", logicWorld, false, 0, checkOverlaps);

    // Inner void with point source
    G4Box *centralvoid = new G4Box("centralvoid", xCentralVoid, yCentralVoid, zCentralVoid);
    G4LogicalVolume *logicCentralvoid = new G4LogicalVolume(centralvoid, worldMat, "logicCentralvoid");
    // logical vol takes over solid world/volume
    G4VPhysicalVolume *physCentralvoid = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicCentralvoid, "physCentralvoid", logicInnerpoly, false, 0, checkOverlaps);

*/
    // spherical detector

    G4Sphere *sphDet = new G4Sphere("sphDet", 0 * cm, 10 * cm, 0, 360 * deg, 0, 180 * deg);
    logicsphDet = new G4LogicalVolume(sphDet, matTest, "logicDet");
    // logical vol takes over solid world/volume
    G4VPhysicalVolume *physsphDet = new G4PVPlacement(0, G4ThreeVector(0., 0., 20.0 * cm), logicsphDet, "physsphDet", logicWorld, false, 0, checkOverlaps);
    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(0.0, 0.0, 1.0, 0.95)); // det is blue
    detVisAtt->SetForceSolid(true);
    logicsphDet->SetVisAttributes(detVisAtt);

    G4double iTargetRadius = 1.70 * cm;    // initial was 1.9 cm
    G4double iTargetThickness = 3.00 * mm; // dimensions of ion target testing 3mm; initially 1mm
    G4RotationMatrix *rotMatrix = new G4RotationMatrix();
    rotMatrix->rotateY(45. * deg);
    G4Tubs *ionTarget = new G4Tubs("ionTarget", 0., iTargetRadius, iTargetThickness * 0.5, 0.0 * deg, 360.0 * deg);
    G4LogicalVolume *logicIonTarget = new G4LogicalVolume(ionTarget, TiD2, "logicIonTarget");
    G4VPhysicalVolume *physIonTarget = new G4PVPlacement(rotMatrix, G4ThreeVector(0., 0., 2. * cm), logicIonTarget, "physIonTarget", logicWorld, 0, checkOverlaps);
    // distance btw source and target is 6 cm
    G4VisAttributes *ionTargetVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 1.0, 1.0)); // ion target is purple
    ionTargetVisAtt->SetForceSolid(true);
    logicIonTarget->SetVisAttributes(ionTargetVisAtt);

    return physWorld;
}

void V3DetectorConstruction::ConstructSDandField()
{
    auto sdManager = G4SDManager::GetSDMpointer();

    auto detSD = new V3SensitiveDetector("DetSD");
    sdManager->AddNewDetector(detSD);

    logicsphDet->SetSensitiveDetector(detSD);
}

//{test1SensitiveDetector *sensDet = new test1SensitiveDetector("SensitiveDetector");
// logicDetector->SetSensitiveDetector(sensDet);
// G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);}