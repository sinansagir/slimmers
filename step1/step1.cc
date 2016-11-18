#define step1_cxx
#include "step1.h"
#include <fstream>
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <sstream>
#include <string>
#include <vector>
#include "scaleFactors.h"

using namespace std;

// ----------------------------------------------------------------------------
// Define functions
// ----------------------------------------------------------------------------

bool comparepair( const std::pair<double,int> a, const std::pair<double,int> b) { return a.first > b.first; }

TRandom3 Rand;

const double MTOP  = 173.5;
const double MW    = 80.4; 

bool step1::applySF(bool& isTagged, float tag_SF, float tag_eff){
  
  bool newTag = isTagged;
  if (tag_SF == 1) return newTag; //no correction needed 

  //throw die
  float coin = Rand.Uniform(1.);    

  if(tag_SF > 1){  // use this if SF>1

    if( !isTagged ) {

      //fraction of jets that need to be upgraded
      float mistagPercent = (1.0 - tag_SF) / (1.0 - (tag_SF/tag_eff) );

      //upgrade to tagged
      if( coin < mistagPercent ) {newTag = true;}
    }

  }else{  // use this if SF<1
      
    //downgrade tagged to untagged
    if( isTagged && coin > tag_SF ) {newTag = false;}

  }

  return newTag;
}

// ----------------------------------------------------------------------------
// MAIN EVENT LOOP
// ----------------------------------------------------------------------------

void step1::Loop() 
{

  // ----------------------------------------------------------------------------
  // Turn on input tree branches
  // ----------------------------------------------------------------------------

   if (inputTree == 0) return;
   
   inputTree->SetBranchStatus("*",0);

   //Event info

   inputTree->SetBranchStatus("event_CommonCalc",1);
   inputTree->SetBranchStatus("run_CommonCalc",1);
   inputTree->SetBranchStatus("lumi_CommonCalc",1);
   inputTree->SetBranchStatus("nPV_singleLepCalc",1);
   inputTree->SetBranchStatus("nTrueInteractions_singleLepCalc",1);
   inputTree->SetBranchStatus("MCWeight_singleLepCalc",1);

   inputTree->SetBranchStatus("isTHBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTHTH_TpTpCalc",1);
   inputTree->SetBranchStatus("isBWBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZTH_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZTZ_TpTpCalc",1);
   inputTree->SetBranchStatus("isBHTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBHBH_TpTpCalc",1);
   inputTree->SetBranchStatus("isTWTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZBH_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZBZ_TpTpCalc",1);
   inputTree->SetBranchStatus("NLeptonDecays_TpTpCalc",1);
   
   //triggers
   inputTree->SetBranchStatus("vsSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersMu_singleLepCalc",1);
   
   //electrons
   inputTree->SetBranchStatus("elPt_singleLepCalc",1);
   inputTree->SetBranchStatus("elEta_singleLepCalc",1);
   inputTree->SetBranchStatus("elPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("elEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("elMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elRelIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elDxy_singleLepCalc",1);
   inputTree->SetBranchStatus("elDZ_singleLepCalc",1);
   inputTree->SetBranchStatus("elCharge_singleLepCalc",1);
   inputTree->SetBranchStatus("elDEtaSCTkAtVtx_singleLepCalc",1);
   inputTree->SetBranchStatus("elDPhiSCTkAtVtx_singleLepCalc",1);
   inputTree->SetBranchStatus("elDR03TkSumPt_singleLepCalc",1);
   inputTree->SetBranchStatus("elSihih_singleLepCalc",1);
   inputTree->SetBranchStatus("elHoE_singleLepCalc",1);
   inputTree->SetBranchStatus("elEcalPFClusterIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elHcalPFClusterIso_singleLepCalc",1);
   
   //muons
   inputTree->SetBranchStatus("muPt_singleLepCalc",1);
   inputTree->SetBranchStatus("muEta_singleLepCalc",1);
   inputTree->SetBranchStatus("muPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("muEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("muMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("muRelIso_singleLepCalc",1);
   inputTree->SetBranchStatus("muDxy_singleLepCalc",1);
   inputTree->SetBranchStatus("muDz_singleLepCalc",1);
   inputTree->SetBranchStatus("muCharge_singleLepCalc",1);

   //missing et
   inputTree->SetBranchStatus("corr_met_singleLepCalc",1);
   inputTree->SetBranchStatus("corr_met_phi_singleLepCalc",1);

   // genParticles
   inputTree->SetBranchStatus("genPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("genStatus_singleLepCalc",1);
   inputTree->SetBranchStatus("genID_singleLepCalc",1);
   inputTree->SetBranchStatus("genMotherID_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEnergy_singleLepCalc",1);

   //boosted truth
   inputTree->SetBranchStatus("HadronicVHtPt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtEta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtEnergy_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtID_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0E_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1E_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2E_JetSubCalc",1);

   //jets
   inputTree->SetBranchStatus("theJetHFlav_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetPFlav_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetPt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetEta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetEnergy_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetCSV_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetBTag_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetBTag_bSFup_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetBTag_bSFdn_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetBTag_lSFup_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetBTag_lSFdn_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Mass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Energy_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau1_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau2_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau3_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8PrunedMass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8PrunedMassWtagUncerts_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDropMass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8PrunedTau21Tag_JetSubCalc",1);

   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVMSF_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVM_bSFdn_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVM_bSFup_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVM_lSFdn_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVM_lSFup_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetPt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetEta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetMass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetCSV_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetBTag_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetIndex_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetSize_JetSubCalc",1);
   
   //top
   inputTree->SetBranchStatus("ttbarMass_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topEnergy_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topEta_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topMass_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topPhi_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topPt_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topID_TTbarMassCalc",1);
   
   //LHE weights
   inputTree->SetBranchStatus("LHEweightids_singleLepCalc",1);
   inputTree->SetBranchStatus("LHEweights_singleLepCalc",1);

  // ----------------------------------------------------------------------------
  // Create output tree and define branches
  // ----------------------------------------------------------------------------
   
   // OUTPUT FILE
   outputFile->cd();
   TTree *outputTree = new TTree("ljmet","ljmet");

   outputTree->Branch("event_CommonCalc",&event_CommonCalc,"event_CommonCalc/I");
   outputTree->Branch("run_CommonCalc",&run_CommonCalc,"run_CommonCalc/I");
   outputTree->Branch("lumi_CommonCalc",&lumi_CommonCalc,"lumi_CommonCalc/I");
   outputTree->Branch("nPV_singleLepCalc",&nPV_singleLepCalc,"nPV_singleLepCalc/I");
   outputTree->Branch("nTrueInteractions_singleLepCalc",&nTrueInteractions_singleLepCalc,"nTrueInteractions_singleLepCalc/I");
   outputTree->Branch("isElectron",&isElectron,"isElectron/I");
   outputTree->Branch("isMuon",&isMuon,"isMuon/I");
   outputTree->Branch("MCPastTrigger",&MCPastTrigger,"MCPastTrigger/I");
   outputTree->Branch("MCPastTriggerAlt",&MCPastTriggerAlt,"MCPastTriggerAlt/I");
   outputTree->Branch("MCPastTriggerAlt2",&MCPastTriggerAlt2,"MCPastTriggerAlt2/I");
   outputTree->Branch("DataPastTrigger",&DataPastTrigger,"DataPastTrigger/I");
   outputTree->Branch("DataPastTriggerAlt",&DataPastTriggerAlt,"DataPastTriggerAlt/I");
   outputTree->Branch("DataPastTriggerAlt2",&DataPastTriggerAlt2,"DataPastTriggerAlt2/I");
   outputTree->Branch("isTHBW_TpTpCalc",&isTHBW_TpTpCalc,"isTHBW_TpTpCalc/O");
   outputTree->Branch("isTHTH_TpTpCalc",&isTHTH_TpTpCalc,"isTHTH_TpTpCalc/O");
   outputTree->Branch("isBWBW_TpTpCalc",&isBWBW_TpTpCalc,"isBWBW_TpTpCalc/O");
   outputTree->Branch("isTZBW_TpTpCalc",&isTZBW_TpTpCalc,"isTZBW_TpTpCalc/O");
   outputTree->Branch("isTZTH_TpTpCalc",&isTZTH_TpTpCalc,"isTZTH_TpTpCalc/O");
   outputTree->Branch("isTZTZ_TpTpCalc",&isTZTZ_TpTpCalc,"isTZTZ_TpTpCalc/O");
   outputTree->Branch("isBHTW_TpTpCalc",&isBHTW_TpTpCalc,"isBHTW_TpTpCalc/O");
   outputTree->Branch("isBHBH_TpTpCalc",&isBHBH_TpTpCalc,"isBHBH_TpTpCalc/O");
   outputTree->Branch("isTWTW_TpTpCalc",&isTWTW_TpTpCalc,"isTWTW_TpTpCalc/O");
   outputTree->Branch("isBZTW_TpTpCalc",&isBZTW_TpTpCalc,"isBZTW_TpTpCalc/O");
   outputTree->Branch("isBZBH_TpTpCalc",&isBZBH_TpTpCalc,"isBZBH_TpTpCalc/O");
   outputTree->Branch("isBZBZ_TpTpCalc",&isBZBZ_TpTpCalc,"isBZBZ_TpTpCalc/O");
   outputTree->Branch("NLeptonDecays_TpTpCalc",&NLeptonDecays_TpTpCalc,"NLeptonDecays_TpTpCalc/I");
   outputTree->Branch("MCWeight_singleLepCalc",&MCWeight_singleLepCalc,"MCWeight_singleLepCalc/D");
   outputTree->Branch("renormWeights",&renormWeights);
   outputTree->Branch("pdfWeights",&pdfWeights);
   outputTree->Branch("JetSF_pTNbwflat",&JetSF_pTNbwflat,"JetSF_pTNbwflat/F");
   outputTree->Branch("JetSFup_pTNbwflat",&JetSFup_pTNbwflat,"JetSFup_pTNbwflat/F");
   outputTree->Branch("JetSFdn_pTNbwflat",&JetSFdn_pTNbwflat,"JetSFdn_pTNbwflat/F");
   outputTree->Branch("JetSFupwide_pTNbwflat",&JetSFupwide_pTNbwflat,"JetSFupwide_pTNbwflat/F");
   outputTree->Branch("JetSFdnwide_pTNbwflat",&JetSFdnwide_pTNbwflat,"JetSFdnwide_pTNbwflat/F");
   outputTree->Branch("JetSF_80X",&JetSF_80X,"JetSF_80X/F");
   outputTree->Branch("JetSFup_80X",&JetSFup_80X,"JetSFup_80X/F");
   outputTree->Branch("JetSFdn_80X",&JetSFdn_80X,"JetSFdn_80X/F");
   outputTree->Branch("pileupWeight",&pileupWeight,"pileupWeight/F");
   outputTree->Branch("pileupWeightUp",&pileupWeightUp,"pileupWeightUp/F");
   outputTree->Branch("pileupWeightDown",&pileupWeightDown,"pileupWeightDown/F");
   outputTree->Branch("TrigEffAltWeight",&TrigEffAltWeight,"TrigEffAltWeight/F");
   outputTree->Branch("TrigEffWeight",&TrigEffWeight,"TrigEffWeight/F");
   outputTree->Branch("TrigEffWeightUncert",&TrigEffWeightUncert,"TrigEffWeightUncert/F");
   outputTree->Branch("isoSF",&isoSF,"isoSF/F");
   outputTree->Branch("lepIdSF",&lepIdSF,"lepIdSF/F");
   outputTree->Branch("EGammaGsfSF",&EGammaGsfSF,"EGammaGsfSF/F");
   outputTree->Branch("MuTrkSF",&MuTrkSF,"MuTrkSF/F");

   outputTree->Branch("ttbarMass_TTbarMassCalc",&ttbarMass_TTbarMassCalc,"ttbarMass_TTbarMassCalc/D");
   outputTree->Branch("corr_met_singleLepCalc",&corr_met_singleLepCalc,"corr_met_singleLepCalc/D");
   outputTree->Branch("corr_met_phi_singleLepCalc",&corr_met_phi_singleLepCalc,"corr_met_phi_singleLepCalc/D");
   outputTree->Branch("leptonPt_singleLepCalc",&leptonPt_singleLepCalc,"leptonPt_singleLepCalc/F");
   outputTree->Branch("leptonEta_singleLepCalc",&leptonEta_singleLepCalc,"leptonEta_singleLepCalc/F");
   outputTree->Branch("leptonPhi_singleLepCalc",&leptonPhi_singleLepCalc,"leptonPhi_singleLepCalc/F");
   outputTree->Branch("leptonEnergy_singleLepCalc",&leptonEnergy_singleLepCalc,"leptonEnergy_singleLepCalc/F");
   outputTree->Branch("leptonMiniIso_singleLepCalc",&leptonMiniIso_singleLepCalc,"leptonMiniIso_singleLepCalc/F");
   outputTree->Branch("leptonRelIso_singleLepCalc",&leptonRelIso_singleLepCalc,"leptonRelIso_singleLepCalc/F");
   outputTree->Branch("leptonDxy_singleLepCalc",&leptonDxy_singleLepCalc,"leptonDxy_singleLepCalc/F");
   outputTree->Branch("leptonDz_singleLepCalc",&leptonDz_singleLepCalc,"leptonDz_singleLepCalc/F");
   outputTree->Branch("leptonCharge_singleLepCalc",&leptonCharge_singleLepCalc,"leptonCharge_singleLepCalc/I");
   outputTree->Branch("elTrigPresel_singleLepCalc",&elTrigPresel_singleLepCalc,"elTrigPresel_singleLepCalc/I");
   outputTree->Branch("theJetPt_JetSubCalc_PtOrdered",&theJetPt_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetEta_JetSubCalc_PtOrdered",&theJetEta_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetPhi_JetSubCalc_PtOrdered",&theJetPhi_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetEnergy_JetSubCalc_PtOrdered",&theJetEnergy_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetCSV_JetSubCalc_PtOrdered",&theJetCSV_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetBTag_JetSubCalc_PtOrdered",&theJetBTag_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetBTag_bSFup_JetSubCalc_PtOrdered",&theJetBTag_bSFup_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetBTag_bSFdn_JetSubCalc_PtOrdered",&theJetBTag_bSFdn_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetBTag_lSFup_JetSubCalc_PtOrdered",&theJetBTag_lSFup_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetBTag_lSFdn_JetSubCalc_PtOrdered",&theJetBTag_lSFdn_JetSubCalc_PtOrdered);
   outputTree->Branch("HadronicVHtID_JetSubCalc",&HadronicVHtID_JetSubCalc);
   outputTree->Branch("HadronicVHtPt_JetSubCalc",&HadronicVHtPt_JetSubCalc);
   outputTree->Branch("HadronicVHtEta_JetSubCalc",&HadronicVHtEta_JetSubCalc);
   outputTree->Branch("HadronicVHtPhi_JetSubCalc",&HadronicVHtPhi_JetSubCalc);
   outputTree->Branch("HadronicVHtEnergy_JetSubCalc",&HadronicVHtEnergy_JetSubCalc);
   outputTree->Branch("theJetAK8Pt_JetSubCalc_PtOrdered",&theJetAK8Pt_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Eta_JetSubCalc_PtOrdered",&theJetAK8Eta_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Phi_JetSubCalc_PtOrdered",&theJetAK8Phi_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Energy_JetSubCalc_PtOrdered",&theJetAK8Energy_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8PrunedMass_JetSubCalc_PtOrdered",&theJetAK8PrunedMass_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered",&theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8SoftDropMass_JetSubCalc_PtOrdered",&theJetAK8SoftDropMass_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8MaxSubCSV_JetSubCalc_PtOrdered",&theJetAK8MaxSubCSV_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau1_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau1_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau2_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau2_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau3_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau3_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Wmatch_JetSubCalc_PtOrdered",&theJetAK8Wmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Tmatch_JetSubCalc_PtOrdered",&theJetAK8Tmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Zmatch_JetSubCalc_PtOrdered",&theJetAK8Zmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Hmatch_JetSubCalc_PtOrdered",&theJetAK8Hmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8MatchedPt_JetSubCalc_PtOrdered",&theJetAK8MatchedPt_JetSubCalc_PtOrdered);
   outputTree->Branch("genJetPt_singleLepCalc",&genJetPt_singleLepCalc);
   outputTree->Branch("genJetEta_singleLepCalc",&genJetEta_singleLepCalc);
   outputTree->Branch("genJetPhi_singleLepCalc",&genJetPhi_singleLepCalc);
   outputTree->Branch("genJetEnergy_singleLepCalc",&genJetEnergy_singleLepCalc);
   outputTree->Branch("BJetLeadPt",&BJetLeadPt,"BJetLeadPt/F");
   outputTree->Branch("BJetLeadPt_shifts",&BJetLeadPt_shifts);
   outputTree->Branch("WJetLeadPt",&WJetLeadPt,"WJetLeadPt/F");
   outputTree->Branch("WJetLeadPt_shifts",&WJetLeadPt_shifts);
   outputTree->Branch("TJetLeadPt",&TJetLeadPt,"TJetLeadPt/F");
   outputTree->Branch("TJetLeadPt_shifts",&TJetLeadPt_shifts);
   outputTree->Branch("AK4HTpMETpLepPt",&AK4HTpMETpLepPt,"AK4HTpMETpLepPt/F");
   outputTree->Branch("AK4HT",&AK4HT,"AK4HT/F");
   outputTree->Branch("NJets_JetSubCalc",&NJets_JetSubCalc,"NJets_JetSubCalc/I");
   outputTree->Branch("NJetsAK8_JetSubCalc",&NJetsAK8_JetSubCalc,"NJetsAK8_JetSubCalc/I");
   outputTree->Branch("NJetsCSV_JetSubCalc",&NJetsCSV_JetSubCalc,"NJetsCSV_JetSubCalc/I");
   outputTree->Branch("NJetsCSVwithSF_JetSubCalc",&NJetsCSVwithSF_JetSubCalc,"NJetsCSVwithSF_JetSubCalc/I");
   outputTree->Branch("NJetsCSVwithSF_JetSubCalc_shifts",&NJetsCSVwithSF_JetSubCalc_shifts);
   outputTree->Branch("NJetsHtagged",&NJetsHtagged,"NJetsHtagged/I");
   outputTree->Branch("NJetsHtagged_shifts",&NJetsHtagged_shifts);
   outputTree->Branch("topPt",&topPt,"topPt/F");
   outputTree->Branch("topPtGen",&topPtGen,"topPtGen/F");
   outputTree->Branch("topMass",&topMass,"topMass/F");
   outputTree->Branch("minMleppBjet",&minMleppBjet,"minMleppBjet/F");
   outputTree->Branch("minMleppBjet_shifts",&minMleppBjet_shifts);
   outputTree->Branch("minMleppJet",&minMleppJet,"mixnMleppJet/F");
   outputTree->Branch("genTopPt",&genTopPt,"genTopPt/F");
   outputTree->Branch("genAntiTopPt",&genAntiTopPt,"genAntiTopPt/F");
   outputTree->Branch("topPtWeight",&topPtWeight,"topPtWeight/F");
   outputTree->Branch("topPtWeightPast400",&topPtWeightPast400,"topPtWeightPast400/F");
   outputTree->Branch("topPtWeightHighPt",&topPtWeightHighPt,"topPtWeightHighPt/F");
   outputTree->Branch("deltaRlepJetInMinMljet",&deltaRlepJetInMinMljet,"deltaRlepJetInMinMljet/F");
   outputTree->Branch("deltaRlepbJetInMinMlb",&deltaRlepbJetInMinMlb,"deltaRlepbJetInMinMlb/F");
   outputTree->Branch("deltaRlepbJetInMinMlb_shifts",&deltaRlepbJetInMinMlb_shifts);
   outputTree->Branch("deltaPhilepJetInMinMljet",&deltaPhilepJetInMinMljet,"deltaPhilepJetInMinMljet/F");
   outputTree->Branch("deltaPhilepbJetInMinMlb",&deltaPhilepbJetInMinMlb,"deltaPhilepbJetInMinMlb/F");
   outputTree->Branch("deltaPhilepbJetInMinMlb_shifts",&deltaPhilepbJetInMinMlb_shifts);
   outputTree->Branch("deltaRtopWjet",&deltaRtopWjet,"deltaRtopWjet/F");
   outputTree->Branch("deltaRlepWjet",&deltaRlepWjet,"deltaRlepWjet/F");
   outputTree->Branch("deltaRlepTjet",&deltaRlepTjet,"deltaRlepTjet/F");
   outputTree->Branch("deltaPhitopWjet",&deltaPhitopWjet,"deltaPhitopWjet/F");
   outputTree->Branch("deltaPhilepWjet",&deltaPhilepWjet,"deltaPhilepWjet/F");
   outputTree->Branch("deltaPhilepTjet",&deltaPhilepTjet,"deltaPhilepTjet/F");
   outputTree->Branch("deltaRtopWjet_shifts",&deltaRtopWjet_shifts);
   outputTree->Branch("deltaRlepWjet_shifts",&deltaRlepWjet_shifts);
   outputTree->Branch("deltaRlepTjet_shifts",&deltaRlepTjet_shifts);
   outputTree->Branch("deltaPhitopWjet_shifts",&deltaPhitopWjet_shifts);
   outputTree->Branch("deltaPhilepWjet_shifts",&deltaPhilepWjet_shifts);
   outputTree->Branch("deltaPhilepTjet_shifts",&deltaPhilepTjet_shifts);
   outputTree->Branch("NJetsWtagged_0p6",&NJetsWtagged_0p6,"NJetsWtagged_0p6/I");
   outputTree->Branch("NJetsWtagged_0p6_shifts",&NJetsWtagged_0p6_shifts);
   outputTree->Branch("NJetsTtagged_0p81",&NJetsTtagged_0p81,"NJetsTtagged_0p81/I");
   outputTree->Branch("NJetsTtagged_0p81_shifts",&NJetsTtagged_0p81_shifts);
   outputTree->Branch("minDR_leadAK8otherAK8",&minDR_leadAK8otherAK8,"minDR_leadAK8otherAK8/F");
   outputTree->Branch("minDR_lepAK8",&minDR_lepAK8,"minDR_lepAK8/F");
   outputTree->Branch("minDR_lepJet",&minDR_lepJet,"minDR_lepJet/F");
   outputTree->Branch("ptRel_lepJet",&ptRel_lepJet,"ptRel_lepJet/F");
   outputTree->Branch("MT_lepMet",&MT_lepMet,"MT_lepMet/F");
   outputTree->Branch("deltaR_lepJets",&deltaR_lepJets);
   outputTree->Branch("deltaR_lepBJets",&deltaR_lepBJets);
   outputTree->Branch("deltaR_lepBJets_bSFup",&deltaR_lepBJets_bSFup);
   outputTree->Branch("deltaR_lepBJets_bSFdn",&deltaR_lepBJets_bSFdn);
   outputTree->Branch("deltaR_lepBJets_lSFup",&deltaR_lepBJets_lSFup);
   outputTree->Branch("deltaR_lepBJets_lSFdn",&deltaR_lepBJets_lSFdn);
   outputTree->Branch("deltaR_lepAK8s",&deltaR_lepAK8s);
   outputTree->Branch("deltaPhi_lepJets",&deltaPhi_lepJets);
   outputTree->Branch("deltaPhi_lepBJets",&deltaPhi_lepBJets);
   outputTree->Branch("deltaPhi_lepBJets_bSFup",&deltaPhi_lepBJets_bSFup);
   outputTree->Branch("deltaPhi_lepBJets_bSFdn",&deltaPhi_lepBJets_bSFdn);
   outputTree->Branch("deltaPhi_lepBJets_lSFup",&deltaPhi_lepBJets_lSFup);
   outputTree->Branch("deltaPhi_lepBJets_lSFdn",&deltaPhi_lepBJets_lSFdn);
   outputTree->Branch("deltaPhi_lepAK8s",&deltaPhi_lepAK8s);
   outputTree->Branch("mass_lepJets",&mass_lepJets);
   outputTree->Branch("mass_lepBJets",&mass_lepBJets);
   outputTree->Branch("mass_lepBJets_bSFup",&mass_lepBJets_bSFup);
   outputTree->Branch("mass_lepBJets_bSFdn",&mass_lepBJets_bSFdn);
   outputTree->Branch("mass_lepBJets_lSFup",&mass_lepBJets_lSFup);
   outputTree->Branch("mass_lepBJets_lSFdn",&mass_lepBJets_lSFdn);
   outputTree->Branch("mass_lepAK8s",&mass_lepAK8s);

  // ----------------------------------------------------------------------------
  // Define and initialize objects / cuts / efficiencies
  // ----------------------------------------------------------------------------

   // basic cuts
   float metCut=30;
   int   njetsCut=2;
   float JetLeadPtCut=50;
   float JetSubLeadPtCut=30;
   float lepPtCut=30;
   float elEtaCut=2.4; //relaxed from 2.1, needs to be adjusted downstream depending on the trigger choice!
   float jetEtaCut=2.4;
   float ak8EtaCut=2.4;
   float jetPtCut=30;

   // counters
   int npass_trigger      = 0;
   int npass_mu500        = 0;
   int npass_met          = 0;
   int npass_njets        = 0;
   int npass_nHjets       = 0;
   int npass_JetLeadPt    = 0;
   int npass_JetSubLeadPt = 0;
   int npass_lepPt        = 0;
   int npass_ElEta        = 0;
   int npass_all          = 0;
   int Nelectrons         = 0;
   int Nmuons             = 0;

   // Lorentz vectors
   TLorentzVector jet_lv;
   TLorentzVector bjet_lv;
   TLorentzVector wjet1_lv;
   TLorentzVector tjet1_lv;
   TLorentzVector lepton_lv;
   TLorentzVector ak8_lv;
   
   // Muon Trigger & tracking efficiencies
   float avePtPOG[4][6] = {
     {35.55,44.32,53.90,73.03,145.96,254.04},
     {35.56,44.41,53.84,72.79,144.55,254.16},
     {35.36,44.38,53.83,71.70,144.44,230.07},
     {35.69,44.31,53.95,73.08,145.84,270.32},
   };
   float mueffs[4][6] = {
     {0.906,0.926,0.930,0.929,0.926,0.922},
     {0.904,0.928,0.932,0.931,0.912,0.889},
     {0.859,0.884,0.889,0.888,0.874,0.851},
     {0.786,0.817,0.820,0.823,0.774,0.675}
   };
   float tracksf[10] = {0.9824, 0.9918, 0.9959, 0.9934, 0.9915, 0.9947, 0.9967, 0.9949, 0.9912, 0.9768};

   // B tagging efficiencies. This will not be needed after 8/1/16 LJMet
   std::vector<float> ptRangeSF, ptRangeEff;
   float SFerr[7]  = {0.011629186570644379, 0.011501740664243698, 0.01121238712221384, 0.016118986532092094, 0.016830746084451675, 0.032492130994796753, 0.036446873098611832};
   float ptmin16[7] = {30, 50, 70, 100, 140, 200, 300};
   for (int i=0;i<7;++i) ptRangeSF.push_back(ptmin16[i]);
   float ptminEff[19] = {30, 50, 70, 100, 140, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1400, 1600, 1800};
   for (int i=0;i<19;++i) ptRangeEff.push_back(ptminEff[i]);
   float BtagEff[19] = {0.598502,0.650253,0.675872,0.684356,0.681335,0.647372,0.607565,0.563892,0.536284,0.526137,0.511053,0.490886,0.482464,0.461109,0.447184,0.452516,0.455189,0.399306,0.367347};
   float MistagEff[19] = {0.014675,0.012310,0.012179,0.012088,0.013761,0.015344,0.021110,0.023148,0.023755,0.028529,0.030575,0.030955,0.034016,0.037446,0.034907,0.043372,0.052239,0.049661,0.073034};

   // W tagging efficiencies. Assumes each signal mass uses the same pT bins but has unique values.
   std::vector<float> ptRangeTpTp, ptRangeTTbar;
   float ptminTTbar[14] = {200, 250, 300, 350, 400, 450, 500, 550, 600, 700, 800, 1000, 1200, 1600};
   for (int i=0;i<14;++i) ptRangeTTbar.push_back(ptminTTbar[i]);
   float ptminTpTp[14] = {200, 250, 300, 350, 400, 450, 500, 550, 600, 700, 800, 1000, 1200, 1600};
   for (int i=0;i<14;++i) ptRangeTpTp.push_back(ptminTpTp[i]);

   float SignalEff[10][14] = {
   	 {0.573094702914,0.6256152513,0.639674370731,0.651190613137,0.666994515975,0.67895338395,0.672007272314,0.680115036976,0.677660324172,0.661182205972,0.628097438051,0.565891472868,0.478609625668,0.423076923077},
     {0.560585567666,0.609538876194,0.620004173069,0.634426368412,0.644278544226,0.647847317525,0.669665436756,0.672595033809,0.685763581667,0.682747907137,0.670092613508,0.63472281908,0.565006075334,0.506329113924},
     {0.553041988003,0.587548545988,0.592846060658,0.612931297046,0.626252334862,0.638259474634,0.652113070249,0.660036086784,0.67172337948,0.683965598492,0.690302248961,0.659890927119,0.6164053076,0.569620253165},
     {0.550951464614,0.581752029107,0.582304032297,0.596409162826,0.609367143165,0.624099679302,0.632683612367,0.644266315289,0.65574480002,0.680626732756,0.681103280907,0.686620240036,0.634629229662,0.551094890511},
     {0.560305658819,0.585755468882,0.576560972203,0.577316221714,0.59318306762,0.607188007947,0.617818223313,0.633948170232,0.644008110127,0.659394883781,0.676869965478,0.674549442166,0.661417322835,0.621730382294},
     {0.576545231273,0.597396847884,0.573274051253,0.570935418831,0.580016106765,0.594078346277,0.608792666747,0.61801980198,0.62885491546,0.643115733824,0.660655518395,0.667859147026,0.664663461538,0.656488549618},
     {0.565131478948,0.600897318242,0.574390687523,0.564512827511,0.573560241707,0.58366568915,0.593983841636,0.607425910507,0.622444376274,0.632659350037,0.648225469729,0.663827428053,0.65437292115,0.66496350365},
     {0.577161619847,0.602973977695,0.575503190967,0.561629684724,0.560623473639,0.576076872101,0.59030330148,0.603029814666,0.611726175643,0.62520076566,0.637715761177,0.651125974591,0.662885857861,0.654933068914},
     {0.587200832466,0.612443201678,0.580659561408,0.569772334159,0.557922287095,0.566110535529,0.574055648952,0.59487281663,0.600710614371,0.615823507037,0.62815226485,0.638296579795,0.648243209569,0.638770840144},
     {0.592668269231,0.626061397779,0.591862471791,0.578188963485,0.562082027779,0.56067531398,0.574402730375,0.576154874129,0.596625849364,0.609177246431,0.62194413287,0.631415557648,0.643831898891,0.647893772894},
   };
   float TTbarEff[14] = {0.682439, 0.738105, 0.707007, 0.676506, 0.655480, 0.647157, 0.640495, 0.631280, 0.629425, 0.588845, 0.572383,  0.631179, 0.528302, 0.333333};
   float STEff[14] = {0.721371, 0.799146, 0.782680, 0.762160, 0.743905, 0.729174, 0.727657, 0.709333, 0.724403, 0.717466, 0.690385,  0.666667, 0.483333, 0.600000};
   float WVEff[14] = {0.712598, 0.791459, 0.756127, 0.723847, 0.705318, 0.674699, 0.718884, 0.626923, 0.662162, 0.656250, 0.564356,  0.454545, 0.285714, 0.285714};
   float TTVEff[14] = {0.605128, 0.633895, 0.614585, 0.602014, 0.588748, 0.569500, 0.557702, 0.571873, 0.539608, 0.537893, 0.540462,  0.444444, 0.189189, 0.600000};

   // Top tagging efficiencies
   std::vector<float> ptRangeTpTpTop, ptRangeTTbarTop;
   float ptminTTbarTop[10] = {400, 450, 500, 550, 600, 700, 800, 1000, 1200, 1600};
   for (int i=0;i<10;++i) ptRangeTTbarTop.push_back(ptminTTbarTop[i]);
   float ptminTpTpTop[9] = {400, 450, 500, 550, 600, 700, 800, 1000, 1200};
   for (int i=0;i<10;++i) ptRangeTpTpTop.push_back(ptminTpTpTop[i]);
   float TTbarEffTop[10] = {0.656721, 0.842644, 0.864036, 0.851990, 0.824271, 0.782050, 0.738981, 0.699812, 0.676243, 0.646388};
   float SignalEffTop[10][9] = {
     {0.626589846722,0.788803818236,0.821436690157,0.83299166325,0.814103839268,0.796526054591,0.764510412051,0.713063763608,0.672222222222},
     {0.59937178755,0.771837349398,0.79634647321,0.805258510743,0.80379704074,0.786826880285,0.76442124029,0.728626116546,0.701960784314},
     {0.582046241692,0.737903837403,0.772717287838,0.779493012675,0.781115879828,0.770558946354,0.756872118832,0.742128545407,0.684916201117},
     {0.55254206123,0.705446778213,0.74973347548,0.763656479049,0.757925901558,0.752818224519,0.739709940696,0.734190057491,0.731333106035},
     {0.530547853523,0.682381255751,0.719713038054,0.741442733337,0.741114957959,0.733250263587,0.723482393606,0.722846012832,0.725552721088},
     {0.510508849558,0.665290865197,0.691520467836,0.713848651349,0.719849289262,0.714700234692,0.711302785265,0.707148481932,0.706388206388},
     {0.501381533502,0.637913426035,0.666926272066,0.692849404117,0.698998068566,0.696041234161,0.698471358979,0.700360098553,0.690650406504},
     {0.493620414673,0.62583965803,0.654378862135,0.679696580412,0.682118019282,0.679147922731,0.677579776212,0.677719574836,0.685437912418},
     {0.469200524246,0.602987346589,0.633072336757,0.650726354511,0.663486481812,0.665406827321,0.666500498504,0.669037858693,0.683899556869},
     {0.455502549761,0.596854744448,0.62799647238,0.629449181215,0.645783558977,0.651082836238,0.654582093488,0.655073335338,0.667690236823},
   }; 

   // Pileup distributions
   double pileup_central[38] = {7.892e-03, 1.846e-02, 1.858e-02, 2.098e-02, 3.207e-02, 2.484e-02, 2.326e-02, 3.721e-02, 7.012e-02, 1.266e-01, 2.280e-01, 3.998e-01, 5.895e-01, 7.439e-01, 8.700e-01, 8.940e-01, 8.630e-01, 9.238e-01, 8.971e-01, 9.710e-01, 8.868e-01, 8.635e-01, 9.279e-01, 1.027e+00, 1.066e+00, 1.256e+00, 1.250e+00, 1.425e+00, 1.414e+00, 1.557e+00, 1.665e+00, 1.801e+00, 2.588e+00, 3.449e+00, 6.530e+00, 1.510e+01, 4.634e+01, 9.928e+01};
   double pileup_down[38]    = {8.176e-03, 2.356e-02, 1.953e-02, 2.397e-02, 3.574e-02, 2.725e-02, 2.694e-02, 5.769e-02, 1.033e-01, 1.926e-01, 3.514e-01, 5.697e-01, 7.846e-01, 9.493e-01, 1.083e+00, 1.068e+00, 9.832e-01, 1.014e+00, 9.614e-01, 1.030e+00, 9.352e-01, 8.958e-01, 9.406e-01, 1.019e+00, 1.037e+00, 1.195e+00, 1.163e+00, 1.296e+00, 1.255e+00, 1.344e+00, 1.391e+00, 1.451e+00, 2.006e+00, 2.568e+00, 4.665e+00, 1.032e+01, 3.013e+01, 6.090e+01};
   double pileup_up[38]      = {7.690e-03, 1.454e-02, 1.759e-02, 1.842e-02, 2.919e-02, 2.240e-02, 2.122e-02, 2.606e-02, 4.722e-02, 8.679e-02, 1.494e-01, 2.732e-01, 4.337e-01, 5.773e-01, 6.949e-01, 7.319e-01, 7.369e-01, 8.227e-01, 8.247e-01, 9.106e-01, 8.382e-01, 8.210e-01, 8.956e-01, 1.012e+00, 1.071e+00, 1.285e+00, 1.304e+00, 1.519e+00, 1.539e+00, 1.730e+00, 1.896e+00, 2.109e+00, 3.129e+00, 4.317e+00, 8.471e+00, 2.033e+01, 6.483e+01, 1.448e+02};

  // ----------------------------------------------------------------------------
  // RUN THE EVENT LOOP
  // ----------------------------------------------------------------------------

   cout << "RUN CONFIG: isMC = " << isMC << endl;
   cout << "isSig = " << isSig << ", SigMass = " << SigMass << endl;
   cout << "For W's: isTT = " << isTT << ", isST = " << isST << endl;
   cout << "Fot jets & PDF: isTOP = " << isTOP << ", isMadgraphBkg = " << isMadgraphBkg << endl;
   
   Long64_t nentries = inputTree->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = inputTree->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) != 1) continue;
      
      //      if (ientry > 5000) continue;
      
      if(jentry % 1000 ==0) std::cout<<"Completed "<<jentry<<" out of "<<nentries<<" events"<<std::endl;

      // ----------------------------------------------------------------------------
      // Filter input file by mass or decay
      // ----------------------------------------------------------------------------

      if(isTTincMtt0to700 && ttbarMass_TTbarMassCalc >= 700.) continue;
      if(isTTincMtt700to1000 && (ttbarMass_TTbarMassCalc >= 1000.||ttbarMass_TTbarMassCalc < 700.)) continue;
      if(isTTincMtt1000toInf && ttbarMass_TTbarMassCalc < 1000.) continue;
      if(outBWBW && !isBWBW_TpTpCalc) continue;
      if(outTZBW && !isTZBW_TpTpCalc) continue;
      if(outTHBW && !isTHBW_TpTpCalc) continue;
      if(outTZTH && !isTZTH_TpTpCalc) continue;
      if(outTZTZ && !isTZTZ_TpTpCalc) continue;
      if(outTHTH && !isTHTH_TpTpCalc) continue;
      if(outTWTW && !isTWTW_TpTpCalc) continue;
      if(outBZTW && !isBZTW_TpTpCalc) continue;
      if(outBHTW && !isBHTW_TpTpCalc) continue;
      if(outBZBH && !isBZBH_TpTpCalc) continue;
      if(outBZBZ && !isBZBZ_TpTpCalc) continue;
      if(outBHBH && !isBHBH_TpTpCalc) continue;

      // ----------------------------------------------------------------------------
      // Assign as electron or muon event
      // ----------------------------------------------------------------------------
     	     
      isElectron = 0;
      isMuon = 0;
      if(elPt_singleLepCalc->size()==0 && muPt_singleLepCalc->size()==0){std::cout << "got no leptons, something wrong" << std::endl; continue;}
      if(elPt_singleLepCalc->size()>0 && muPt_singleLepCalc->size()>0) std::cout << "got el and mu, something wrong" << std::endl;
      if(elPt_singleLepCalc->size()>1 && muPt_singleLepCalc->size()>1) std::cout << "got more than one el or mu, something wrong" << std::endl;
      if(elPt_singleLepCalc->size()>0 && muPt_singleLepCalc->size()==0) {isElectron = 1; isMuon = 0;}
      if(elPt_singleLepCalc->size()==0 && muPt_singleLepCalc->size()>0) {isElectron = 0; isMuon = 1;}
      if(isElectron==0 && isMuon==0){std::cout << "got no leptons, something wrong" << std::endl; continue;}

      double leppt = 0;
      double lepeta = 0;
      if(isElectron){leppt = elPt_singleLepCalc->at(0); lepeta = elEta_singleLepCalc->at(0);}
      if(isMuon){leppt = muPt_singleLepCalc->at(0); lepeta = muEta_singleLepCalc->at(0);}

      // ICHEP dataset: Endcap muons outside 500 GeV had to be rejected
      if(isMuon && leppt > 500 && fabs(lepeta) > 1.2) continue;
      npass_mu500 += 1.0;

      // ----------------------------------------------------------------------------
      // Pileup weight calculation
      // ----------------------------------------------------------------------------

      pileupWeight = 1.0;
      pileupWeightUp = 1.0;
      pileupWeightDown = 1.0;
	
      if(nTrueInteractions_singleLepCalc > 37) nTrueInteractions_singleLepCalc = 37;
      pileupWeight = pileup_central[nTrueInteractions_singleLepCalc];
      pileupWeightUp = pileup_down[nTrueInteractions_singleLepCalc];
      pileupWeightDown = pileup_up[nTrueInteractions_singleLepCalc];

      // ----------------------------------------------------------------------------
      // Assign Lepton scale factor or efficiency weights, save trigger pass/fail
      // ----------------------------------------------------------------------------

      DataPastTrigger = 0;
      DataPastTriggerAlt  = 0;
      DataPastTriggerAlt2 = 0;
      MCPastTrigger = 0;
      MCPastTriggerAlt  = 0;
      MCPastTriggerAlt2 = 0;
      TrigEffAltWeight = 1.0;
      TrigEffWeight = 1.0;
      TrigEffWeightUncert = 1.0;
      isoSF = 1.0;
      lepIdSF = 1.0;
      EGammaGsfSF = 1.0;
      MuTrkSF = 1.0;

      if(isMC){ //MC triggers check
      	if(isElectron){
		  if(isSig){
			for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v1" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v2" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v3" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v4" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v5" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v1" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v2" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v3" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v4" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v5" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v1" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v2" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v3" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v4" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			  if(vsSelMCTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v5" && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			}
		  }else{
			MCPastTrigger = 1;
			MCPastTriggerAlt  = 1;
			MCPastTriggerAlt2 = 1;
		  }
		  
		  EGammaGsfSF = getEGammaGsfSF(lepeta); // Gsf Tracking scale factor: http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/ichep2016_80X/resultsGsfID/egammaEffi.txt_egammaPlots.pdf
		  TrigEffWeight = getTrigEffWeight(leppt,lepeta); // Ele27_eta2p1 -- 80X DATA EFFICIENCIES
		  TrigEffWeightUncert = TrigEffWeight;
		  isoSF = getElIsoSF(leppt,lepeta); //miniIso < 0.1 scale factors from SUSYLepSF: http://tomc.web.cern.ch/tomc/tagAndProbe/20160726/output/scaleFactors.root	  
		  lepIdSF = getElIdSF(leppt,lepeta); //MVA-based ID scale factors (non-triggering): http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/ichep2016_80X//resultsEleID/runBCD/passingMVA80/egammaEffi.txt_egammaPlots.pdf

		}
		if(isMuon){
		  if(isSig){
			for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
			  if(vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v1" && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if(vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v2" && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if(vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v3" && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if(vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v4" && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if(vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v5" && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v1" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v1") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v2" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v2") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v3" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v3") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v4" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v4") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v5" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v5") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v6" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v6") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v1" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v1") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v2" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v2") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v3" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v3") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v4" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v4") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v5" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v5") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			  if((vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v6" || vsSelMCTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v6") && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTriggerAlt2 = 1;
			}
		  }else{
			MCPastTrigger = 1;
			MCPastTriggerAlt  = 1;
			MCPastTriggerAlt2 = 1;
		  }
	  
		  // IsoMu24 || IsoTkMu24 Eff -- 80X DATA EFFICIENCIES
		  int ebin = -1;
		  int pbin = -1;
		  if(fabs(lepeta) < 0.9) ebin = 0;
		  else if(fabs(lepeta) < 1.6) ebin = 1;
		  else if(fabs(lepeta) < 2.1) ebin = 2;
		  else if(fabs(lepeta) < 2.4) ebin = 3;
		  else std::cout << "Found a muon out of eta range" << std::endl;
	  
		  if(leppt < 40) pbin = 0;
		  else if(leppt < 50) pbin = 1;
		  else if(leppt < 60) pbin = 2;
		  else if(leppt < 120) pbin = 3;
		  else if(leppt < 200) pbin = 4;
		  else pbin = 5;
	  
		  TrigEffWeight = mueffs[ebin][pbin];
	  
		  if(fabs(lepeta) > 1.2 && fabs(lepeta) <= 2.1){
			if(leppt < avePtPOG[2][3]) TrigEffWeightUncert = TrigEffWeight;
			else if(leppt < avePtPOG[2][4]){
			  TrigEffWeightUncert = mueffs[2][3] + (mueffs[2][4]-mueffs[2][3])*(leppt - avePtPOG[2][3])/(avePtPOG[2][4]-avePtPOG[2][3]);
			}
			else if(leppt < avePtPOG[2][5]){
			  TrigEffWeightUncert = mueffs[2][4] + (mueffs[2][5]-mueffs[2][4])*(leppt - avePtPOG[2][4])/(avePtPOG[2][5]-avePtPOG[2][4]);
			}
			else TrigEffWeightUncert = TrigEffWeight;
		  }
		  else if(fabs(lepeta) > 2.1 && fabs(lepeta) <= 2.4){
			if(leppt < avePtPOG[3][3]) TrigEffWeightUncert = TrigEffWeight;
			else if(leppt < avePtPOG[3][4]){
			  TrigEffWeightUncert = mueffs[3][3] + (mueffs[3][4]-mueffs[3][3])*(leppt - avePtPOG[3][3])/(avePtPOG[3][4]-avePtPOG[3][3]);
			}
			else if(leppt < avePtPOG[3][5]){
			  TrigEffWeightUncert = mueffs[3][4] + (mueffs[3][5]-mueffs[3][4])*(leppt - avePtPOG[3][4])/(avePtPOG[3][5]-avePtPOG[3][4]);
			}
			else TrigEffWeightUncert = TrigEffWeight;
		  }
		  else TrigEffWeightUncert = TrigEffWeight;

		  // Muon tracking SF
		  if(lepeta < -2.1) ebin = 0;
		  else if(lepeta < -1.6) ebin = 1;
		  else if(lepeta < -1.1) ebin = 2;
		  else if(lepeta < -0.6) ebin = 3;
		  else if(lepeta <  0.0) ebin = 4;
		  else if(lepeta <  0.6) ebin = 5;
		  else if(lepeta <  1.1) ebin = 6;
		  else if(lepeta <  1.6) ebin = 7;
		  else if(lepeta <  2.1) ebin = 8;
		  else if(lepeta <  2.4) ebin = 9;

		  MuTrkSF = tracksf[ebin];
		  isoSF = getMuIsoSF(leppt,lepeta); //Mini-iso < 0.2 SFs from SUSY Lepton SF: https://jrgonzal.web.cern.ch/jrgonzal/MuonSF/4.MiniIso0.2_Loose/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.png	  
		  lepIdSF = getMuIdSF(leppt,lepeta); //Cut-based ID scale factors from POG TWiki 7.6/fb: https://cmsdoc.cern.ch/cms/Physics/muon/ReferenceEfficiencies/Run2016/25ns/proviSFs_7p65/MuonID_Z_RunBCD_prompt80X_7p65.root
		}
      	DataPastTrigger = 1;
      	DataPastTriggerAlt  = 1;
      	DataPastTriggerAlt2 = 1;
      }
      else{ //Data triggers check
		if(isElectron){
		  for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
			if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT350_v1"||vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v1") && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT350_v2"||vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v2") && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT350_v3"||vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v3") && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT350_v4"||vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v4") && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT350_v5"||vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v5") && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT350_v6"||vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele15_IsoVVVL_PFHT400_v6") && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v1"  && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v2"  && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v3"  && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v4"  && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v5"  && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v6"  && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v7"  && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v8"  && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v9"  && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v10" && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v1" && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v2" && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v3" && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v4" && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v5" && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v6" && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v7" && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if(vsSelTriggersEl_singleLepCalc->at(itrig) == "HLT_Ele27_WPTight_Gsf_v8" && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
		  }
		}
		if(isMuon){
		  for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT350_v1"||vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v1") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT350_v2"||vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v2") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT350_v3"||vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v3") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT350_v4"||vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v4") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT350_v5"||vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v5") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT350_v6"||vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu15_IsoVVVL_PFHT400_v6") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v1" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v1") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v2" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v2") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v3" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v3") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v4" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v4") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v5" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v5") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoMu24_v6" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_IsoTkMu24_v6") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v1" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v1") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v2" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v2") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v3" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v3") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v4" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v4") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
			if((vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_Mu50_v5" || vsSelTriggersMu_singleLepCalc->at(itrig) == "HLT_TkMu50_v5") && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTriggerAlt2 = 1;
		  }
		}
		MCPastTrigger = 1;
		MCPastTriggerAlt  = 1;
		MCPastTriggerAlt2 = 1;
      }
      
      if(DataPastTrigger) npass_trigger+=1;

      // ----------------------------------------------------------------------------
      // Loop over AK4 jets for calculations and pt ordering pair
      // ----------------------------------------------------------------------------

      NJets_JetSubCalc = 0;
      NJetsCSV_JetSubCalc = 0;
      AK4HT = 0;
      vector<pair<double,int>> jetptindpair;
      JetSF_pTNbwflat = 1.0;
      JetSFup_pTNbwflat = 1.0;
      JetSFdn_pTNbwflat = 1.0;
      JetSFupwide_pTNbwflat = 1.0;
      JetSFdnwide_pTNbwflat = 1.0;
      JetSF_80X = 1.0;
      JetSFup_80X = 1.0;
      JetSFdn_80X = 1.0;

      for(unsigned int ijet=0; ijet < theJetPt_JetSubCalc->size(); ijet++){

	// ----------------------------------------------------------------------------
	// Basic cuts
	// ----------------------------------------------------------------------------

	if(theJetPt_JetSubCalc->at(ijet) < jetPtCut || fabs(theJetEta_JetSubCalc->at(ijet)) > jetEtaCut) continue;

	if(isMC){

	  // ----------------------------------------------------------------------------
	  // Jet Scale factor
	  // ----------------------------------------------------------------------------

	  float one = 1.0;	    
	  float jetpt = theJetPt_JetSubCalc->at(ijet);
	  float jetsf = 1.09383 - 0.000477777*jetpt;
	  float jetsferr = sqrt(0.00314541714554 + 2.18390370364e-08*jetpt*jetpt + 2*jetpt*(-7.85447860996e-06));	 
	  float wideup = min(one,max(float(0.747382 + 0.164524),jetsf+jetsferr));				    
	  float widedn = min(one,max(jetsf-jetsferr,float(0.747382 - 0.164524)));
	  
	  if(isTOP || isSig){
	    if(jetpt >= 200){
	      if(jetpt < 725){
		JetSF_pTNbwflat *= min(one,jetsf);
		JetSFup_pTNbwflat *= wideup;
		JetSFdn_pTNbwflat *= widedn;
		JetSFupwide_pTNbwflat *= wideup;
		JetSFdnwide_pTNbwflat *= widedn;
	      }else{
		JetSF_pTNbwflat *= 0.747382;
		JetSFup_pTNbwflat *= wideup;
		JetSFdn_pTNbwflat *= widedn;
		JetSFupwide_pTNbwflat *= wideup;
		JetSFdnwide_pTNbwflat *= widedn;
	      }
	    }
	  }else{
	    jetsf = 1.24507 - 0.000664768*jetpt;
	    jetsferr = sqrt(0.000506216376592 + 3.1532423475e-09*jetpt*jetpt + 2*jetpt*(-1.17981363543e-06));
	    if(jetpt < 1020){
	      JetSF_pTNbwflat *= min(one,jetsf);
	      JetSFup_pTNbwflat *= min(one,max(jetsf+jetsferr,float(0.568135+0.0522921)));
	      JetSFdn_pTNbwflat *= min(one,max(jetsf-jetsferr,float(0.568135-0.0522921)));
	      JetSFupwide_pTNbwflat *= max(wideup,min(one,max(jetsf+jetsferr,float(0.568135+0.0522921))));
	      JetSFdnwide_pTNbwflat *= min(widedn,min(one,max(jetsf-jetsferr,float(0.568135-0.0522921))));
	    }else{
	      JetSF_pTNbwflat *= 0.568135;
	      JetSFup_pTNbwflat *= min(one,max(jetsf+jetsferr,float(0.568135+0.0522921)));
	      JetSFdn_pTNbwflat *= min(one,max(jetsf-jetsferr,float(0.568135-0.0522921)));
	      JetSFupwide_pTNbwflat *= max(wideup,min(one,max(jetsf+jetsferr,float(0.568135+0.0522921))));
	      JetSFdnwide_pTNbwflat *= min(widedn,min(one,max(jetsf-jetsferr,float(0.568135-0.0522921))));
	    }
	    jetsf = 1.09502 - 0.00045995*jetpt;
	    jetsferr = sqrt(2.41563501145e-05 + 3.64859173927e-10*jetpt*jetpt + 2*jetpt*(-8.66909413702e-08));
	    if(jetpt < 801.75){
	      JetSF_80X *= min(one,jetsf);
	      JetSFup_80X *= min(one,max(jetsf+jetsferr,float(0.726255+0.0190384)));
	      JetSFdn_80X *= min(one,max(jetsf-jetsferr,float(0.726255-0.0190384)));
	    }else{
	      JetSF_80X *= 0.726255;
	      JetSFup_80X *= min(one,max(jetsf+jetsferr,float(0.726255+0.0190384)));
	      JetSFdn_80X *= min(one,max(jetsf-jetsferr,float(0.726255-0.0190384)));
	    }
	  }

	  // ----------------------------------------------------------------------------
	  // B TAGGING fix -- not needed after LJMet from 8/1/16 (efficiency had a typo)
	  // ----------------------------------------------------------------------------

	  float bSF = 1.0;
	  float bSFup = 1.0;
	  float bSFdn = 1.0;
	  double bEff = 1.0;
	  float lSF = 1.0;
	  float lSFup = 1.0;
	  float lSFdn = 1.0;
	  double lEff = 1.0;

	  // Set the initial tagged/untagged state
	  bool istagged = theJetCSV_JetSubCalc->at(ijet) > 0.800;
	  NJetsCSV_JetSubCalc+=istagged;

	  if(theJetHFlav_JetSubCalc->at(ijet) == 5 || theJetHFlav_JetSubCalc->at(ijet) == 4){	    

	    int binSF = (std::upper_bound(ptRangeSF.begin(), ptRangeSF.end(), theJetPt_JetSubCalc->at(ijet))-ptRangeSF.begin())-1;
	    float err = SFerr[binSF];
	    if(theJetHFlav_JetSubCalc->at(ijet) == 4) err *= 2;
	    bSF = 0.901114+(1.32145e-05*theJetPt_JetSubCalc->at(ijet));	    
	    bSFup = bSF + err;
	    bSFdn = bSF - err;
	  
	    int bin = (std::upper_bound(ptRangeEff.begin(), ptRangeEff.end(), theJetPt_JetSubCalc->at(ijet))-ptRangeEff.begin())-1;
	    bEff = BtagEff[bin];
	    if(theJetHFlav_JetSubCalc->at(ijet) == 4) bEff *= 0.2;

	    int tag = applySF(istagged,bSF,bEff);
	    int tag_up = applySF(istagged,bSFup,bEff);
	    int tag_dn = applySF(istagged,bSFdn,bEff);

	    theJetBTag_JetSubCalc->at(ijet) = tag;
	    theJetBTag_bSFup_JetSubCalc->at(ijet) = tag_up;
	    theJetBTag_bSFdn_JetSubCalc->at(ijet) = tag_dn;
	    theJetBTag_lSFup_JetSubCalc->at(ijet) = tag;
	    theJetBTag_lSFdn_JetSubCalc->at(ijet) = tag;

	  }else{

	    int binSF = (std::upper_bound(ptRangeSF.begin(), ptRangeSF.end(), theJetPt_JetSubCalc->at(ijet))-ptRangeSF.begin())-1;
	    float pt = theJetPt_JetSubCalc->at(ijet);
	    lSF = 0.980777+(-0.00109334*pt)+(4.2909e-06*pt*pt)+(-2.78512e-09*pt*pt*pt);
	    lSFdn = lSF*(1-(0.0672836+(0.000102309*pt)+(-1.01558e-07*pt*pt)));
	    lSFup = lSF*(1+(0.0672836+(0.000102309*pt)+(-1.01558e-07*pt*pt)));

	    int bin = (std::upper_bound(ptRangeEff.begin(), ptRangeEff.end(), theJetPt_JetSubCalc->at(ijet))-ptRangeEff.begin())-1;
	    lEff = MistagEff[bin];

	    int tag = applySF(istagged,lSF,lEff);
	    int tag_up = applySF(istagged,lSFup,lEff);
	    int tag_dn = applySF(istagged,lSFdn,lEff);

	    theJetBTag_JetSubCalc->at(ijet) = tag;
	    theJetBTag_bSFup_JetSubCalc->at(ijet) = tag;
	    theJetBTag_bSFdn_JetSubCalc->at(ijet) = tag;
	    theJetBTag_lSFup_JetSubCalc->at(ijet) = tag_up;
	    theJetBTag_lSFdn_JetSubCalc->at(ijet) = tag_dn;

	  }
	  
	  // ----------------------------------------------------------------------------
	  // Counts and pt ordering pair
	  // ----------------------------------------------------------------------------

	  jetptindpair.push_back(std::make_pair(theJetPt_JetSubCalc->at(ijet),ijet));
	  NJets_JetSubCalc+=1;
	  AK4HT+=theJetPt_JetSubCalc->at(ijet);
	  
	}else{
	  jetptindpair.push_back(std::make_pair(theJetPt_JetSubCalc->at(ijet),ijet));
	  NJets_JetSubCalc+=1;
	  AK4HT+=theJetPt_JetSubCalc->at(ijet);
	}
      }
	
      // ----------------------------------------------------------------------------
      // Apply pt ordering to AK4 vectors
      // ----------------------------------------------------------------------------

      std::sort(jetptindpair.begin(), jetptindpair.end(), comparepair);
      theJetPt_JetSubCalc_PtOrdered.clear();
      theJetEta_JetSubCalc_PtOrdered.clear();
      theJetPhi_JetSubCalc_PtOrdered.clear();
      theJetEnergy_JetSubCalc_PtOrdered.clear();
      theJetCSV_JetSubCalc_PtOrdered.clear();
      theJetBTag_JetSubCalc_PtOrdered.clear();
      theJetBTag_bSFdn_JetSubCalc_PtOrdered.clear();
      theJetBTag_bSFup_JetSubCalc_PtOrdered.clear();
      theJetBTag_lSFdn_JetSubCalc_PtOrdered.clear();
      theJetBTag_lSFup_JetSubCalc_PtOrdered.clear();
      for(unsigned int ijet=0; ijet < jetptindpair.size(); ijet++){
      	theJetPt_JetSubCalc_PtOrdered.push_back(theJetPt_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetEta_JetSubCalc_PtOrdered.push_back(theJetEta_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetPhi_JetSubCalc_PtOrdered.push_back(theJetPhi_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetEnergy_JetSubCalc_PtOrdered.push_back(theJetEnergy_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetCSV_JetSubCalc_PtOrdered.push_back(theJetCSV_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetBTag_JetSubCalc_PtOrdered.push_back(theJetBTag_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetBTag_bSFdn_JetSubCalc_PtOrdered.push_back(theJetBTag_bSFdn_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetBTag_bSFup_JetSubCalc_PtOrdered.push_back(theJetBTag_bSFup_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetBTag_lSFdn_JetSubCalc_PtOrdered.push_back(theJetBTag_lSFdn_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetBTag_lSFup_JetSubCalc_PtOrdered.push_back(theJetBTag_lSFup_JetSubCalc->at(jetptindpair[ijet].second));
      }

      // ----------------------------------------------------------------------------
      // Apply kinematic cuts
      // ----------------------------------------------------------------------------
	                
      int isPastNJetsCut = 0;
      if(NJets_JetSubCalc >= njetsCut){npass_njets+=1;isPastNJetsCut=1;}
      
      int isPastJetLeadPtCut = 0;
      if(theJetPt_JetSubCalc_PtOrdered.size() > 0 && theJetPt_JetSubCalc_PtOrdered[0] > JetLeadPtCut){npass_JetLeadPt+=1;isPastJetLeadPtCut=1;}
      
      int isPastJetSubLeadPtCut = 0;
      if(theJetPt_JetSubCalc_PtOrdered.size() > 1 && theJetPt_JetSubCalc_PtOrdered[1] > JetSubLeadPtCut){npass_JetSubLeadPt+=1;isPastJetSubLeadPtCut=1;}
      
      int isPastMETcut = 0;
      if(corr_met_singleLepCalc > metCut){npass_met+=1;isPastMETcut=1;}

      int isPastLepPtCut = 0;
      if(leppt > lepPtCut){npass_lepPt+=1;isPastLepPtCut=1;}
      
      int isPastElEtaCut = 0;
      if(isElectron && fabs(lepeta) < elEtaCut){npass_ElEta+=1;isPastElEtaCut=1;}
      if(isMuon){Nmuons+=1;isPastElEtaCut=1;}
      if(isElectron){Nelectrons+=1;}
      
      AK4HTpMETpLepPt = 0;
      AK4HTpMETpLepPt = AK4HT + corr_met_singleLepCalc + leppt;

      // ----------------------------------------------------------------------------
      // Loop over AK8 jets for calculations and pt ordering pair
      // ----------------------------------------------------------------------------
      
      NJetsHtagged = 0;      
      int NJetsHtagged_bSFup = 0;      
      int NJetsHtagged_bSFdn = 0;      
      int NJetsHtagged_lSFup = 0;      
      int NJetsHtagged_lSFdn = 0;      
      NJetsAK8_JetSubCalc = 0;
      vector<float> maxsubcsv;
      NJetsHtagged_shifts.clear();
      vector<pair<double,int>> jetak8ptindpair;

      for(unsigned int ijet=0; ijet < theJetAK8Pt_JetSubCalc->size(); ijet++){

	// ----------------------------------------------------------------------------
	// Basic cuts
	// ----------------------------------------------------------------------------

	maxsubcsv.push_back(-99.0);
	if(fabs(theJetAK8Eta_JetSubCalc->at(ijet)) > ak8EtaCut) continue;
	if(theJetAK8NjettinessTau1_JetSubCalc->at(ijet)==0) continue;
	if(theJetAK8NjettinessTau2_JetSubCalc->at(ijet)==0) continue;

	// ----------------------------------------------------------------------------
	// Counter and pt ordering pair
	// ----------------------------------------------------------------------------

	NJetsAK8_JetSubCalc += 1; 
	jetak8ptindpair.push_back(std::make_pair(theJetAK8Pt_JetSubCalc->at(ijet),ijet));
	  
	// ----------------------------------------------------------------------------
	// Count Higgs tags
	// ----------------------------------------------------------------------------

	int firstsub = theJetAK8SDSubjetIndex_JetSubCalc->at(ijet);
	int nsubs = theJetAK8SDSubjetSize_JetSubCalc->at(ijet);
	double maxCSVsubjet = 0;
	TLorentzVector tempsubjet;
	TLorentzVector sumsubjets; sumsubjets.SetPtEtaPhiM(0,0,0,0);
	for(int isub = firstsub; isub < firstsub + nsubs; isub++){
	  tempsubjet.SetPtEtaPhiM(theJetAK8SDSubjetPt_JetSubCalc->at(isub),theJetAK8SDSubjetEta_JetSubCalc->at(isub),theJetAK8SDSubjetPhi_JetSubCalc->at(isub),theJetAK8SDSubjetMass_JetSubCalc->at(isub));
	  sumsubjets += tempsubjet;
	  if(theJetAK8SDSubjetCSV_JetSubCalc->at(isub) > maxCSVsubjet) maxCSVsubjet = theJetAK8SDSubjetCSV_JetSubCalc->at(isub);
	  if(isub != firstsub && theJetAK8SDSubjetPt_JetSubCalc->at(isub) == theJetAK8SDSubjetPt_JetSubCalc->at(firstsub)) cout << "subjets have matching pT, something's wrong" << endl;
	}
	maxsubcsv.at(ijet) = maxCSVsubjet;
	if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVMSF_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged += 1;
	if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVM_bSFup_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged_bSFup += 1;
	if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVM_bSFdn_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged_bSFdn += 1;
	if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVM_lSFup_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged_lSFup += 1;
	if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVM_lSFdn_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged_lSFdn += 1;
      }
      NJetsHtagged_shifts.push_back(NJetsHtagged_bSFup);
      NJetsHtagged_shifts.push_back(NJetsHtagged_bSFdn);
      NJetsHtagged_shifts.push_back(NJetsHtagged_lSFup);
      NJetsHtagged_shifts.push_back(NJetsHtagged_lSFdn);

      // ----------------------------------------------------------------------------
      // Skip failing events
      // ----------------------------------------------------------------------------

      int isPastNHjetsCut = 0;
      if(NJetsHtagged >= 0){npass_nHjets += 1; isPastNHjetsCut = 1; }

      if(!(isPastMETcut && isPastNJetsCut && isPastJetLeadPtCut && isPastLepPtCut && isPastElEtaCut && isPastJetSubLeadPtCut)) continue;
      npass_all+=1;

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /////////////// ONLY ON SELECTED EVENTS ////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // ----------------------------------------------------------------------------
      // Combine lepton variables into one set
      // ----------------------------------------------------------------------------
           
      if(isElectron){
	leptonPt_singleLepCalc = leppt;
	leptonEta_singleLepCalc = lepeta;
	leptonPhi_singleLepCalc = elPhi_singleLepCalc->at(0);
	leptonEnergy_singleLepCalc = elEnergy_singleLepCalc->at(0);
	leptonMiniIso_singleLepCalc = elMiniIso_singleLepCalc->at(0);
	leptonRelIso_singleLepCalc = elRelIso_singleLepCalc->at(0);
	leptonDxy_singleLepCalc = elDxy_singleLepCalc->at(0);
	leptonDz_singleLepCalc = elDZ_singleLepCalc->at(0);
	leptonCharge_singleLepCalc = elCharge_singleLepCalc->at(0);
      }
      if(isMuon){
	leptonPt_singleLepCalc = leppt;
	leptonEta_singleLepCalc = lepeta;
	leptonPhi_singleLepCalc = muPhi_singleLepCalc->at(0);
	leptonEnergy_singleLepCalc = muEnergy_singleLepCalc->at(0);
	leptonMiniIso_singleLepCalc = muMiniIso_singleLepCalc->at(0);
	leptonRelIso_singleLepCalc = muRelIso_singleLepCalc->at(0);
	leptonDxy_singleLepCalc = muDxy_singleLepCalc->at(0);
	leptonDz_singleLepCalc = muDz_singleLepCalc->at(0);
	leptonCharge_singleLepCalc = muCharge_singleLepCalc->at(0);
      }

      // ----------------------------------------------------------------------------
      // Apply pt ordering to AK8 vectors 
      // ----------------------------------------------------------------------------

      //Pt ordering for AK8
      std::sort(jetak8ptindpair.begin(), jetak8ptindpair.end(), comparepair);
      theJetAK8Pt_JetSubCalc_PtOrdered.clear();
      theJetAK8Eta_JetSubCalc_PtOrdered.clear();
      theJetAK8Phi_JetSubCalc_PtOrdered.clear();
      theJetAK8Energy_JetSubCalc_PtOrdered.clear();
      theJetAK8Mass_JetSubCalc_PtOrdered.clear();
      theJetAK8PrunedMass_JetSubCalc_PtOrdered.clear();
      theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered.clear();
      theJetAK8SoftDropMass_JetSubCalc_PtOrdered.clear();
      theJetAK8MaxSubCSV_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.clear();
      for(unsigned int ijet=0; ijet < jetak8ptindpair.size(); ijet++){
      	theJetAK8Pt_JetSubCalc_PtOrdered.push_back(theJetAK8Pt_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Eta_JetSubCalc_PtOrdered.push_back(theJetAK8Eta_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Phi_JetSubCalc_PtOrdered.push_back(theJetAK8Phi_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Energy_JetSubCalc_PtOrdered.push_back(theJetAK8Energy_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Mass_JetSubCalc_PtOrdered.push_back(theJetAK8Mass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8PrunedMass_JetSubCalc_PtOrdered.push_back(theJetAK8PrunedMass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered.push_back(theJetAK8PrunedMassWtagUncerts_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8SoftDropMass_JetSubCalc_PtOrdered.push_back(theJetAK8SoftDropMass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8MaxSubCSV_JetSubCalc_PtOrdered.push_back(maxsubcsv.at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau1_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau2_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau3_JetSubCalc->at(jetak8ptindpair[ijet].second));
      }

      // ----------------------------------------------------------------------------
      // Lepton 4-vectors, calculate MT and electron trigger presel value
      // ----------------------------------------------------------------------------

      // Set lepton 4-vectors
      double lepM;
      double lepphi;
      elTrigPresel_singleLepCalc = false;
      if (isMuon){ 
	lepM = 0.105658367;
	lepphi = muPhi_singleLepCalc->at(0);
	lepton_lv.SetPtEtaPhiM(muPt_singleLepCalc->at(0),muEta_singleLepCalc->at(0),muPhi_singleLepCalc->at(0),lepM);
      }
      else{
	lepM = 0.00051099891;
	lepphi = elPhi_singleLepCalc->at(0);
	lepton_lv.SetPtEtaPhiM(elPt_singleLepCalc->at(0),elEta_singleLepCalc->at(0),elPhi_singleLepCalc->at(0),lepM);

	if(elEta_singleLepCalc->at(0) < 1.442){
	  if(elSihih_singleLepCalc->at(0) < 0.012 &&
	     elHoE_singleLepCalc->at(0) < 0.09 &&
	     elEcalPFClusterIso_singleLepCalc->at(0)/leppt < 0.37 &&
	     elHcalPFClusterIso_singleLepCalc->at(0)/leppt < 0.25 &&
	     elDR03TkSumPt_singleLepCalc->at(0)/leppt < 0.18 &&
	     fabs(elDEtaSCTkAtVtx_singleLepCalc->at(0)) < 0.0095 &&
	     fabs(elDPhiSCTkAtVtx_singleLepCalc->at(0)) < 0.065
	     ) elTrigPresel_singleLepCalc = true;
	}else{
	  if(elSihih_singleLepCalc->at(0) < 0.033 &&
	     elHoE_singleLepCalc->at(0) < 0.09 &&
	     elEcalPFClusterIso_singleLepCalc->at(0)/leppt < 0.45 &&
	     elHcalPFClusterIso_singleLepCalc->at(0)/leppt < 0.28 &&
	     elDR03TkSumPt_singleLepCalc->at(0)/leppt < 0.18
	     ) elTrigPresel_singleLepCalc = true;
	}	  
      }
      MT_lepMet = sqrt(2*leppt*corr_met_singleLepCalc*(1 - cos(lepphi - corr_met_phi_singleLepCalc)));

      // ----------------------------------------------------------------------------
      // 8TeV Top pT reweighting
      // ----------------------------------------------------------------------------

      genTopPt = -999;
      genAntiTopPt = -999;
      topPtWeight = 1.0;
      topPtWeightPast400 = 1.0;
      topPtWeightHighPt = 1.0;

      for(unsigned int ijet=0; ijet < topPt_TTbarMassCalc->size(); ijet++){
	if(genTopPt < 0 && topID_TTbarMassCalc->at(ijet) == 6) genTopPt = topPt_TTbarMassCalc->at(ijet);
	if(genAntiTopPt < 0 && topID_TTbarMassCalc->at(ijet) == -6) genAntiTopPt = topPt_TTbarMassCalc->at(ijet);
      }

      if(genTopPt > 0 && genAntiTopPt > 0){
	float toppt_temp = genTopPt;
	if(genTopPt > 400) toppt_temp = 400;
	float antitoppt_temp = genAntiTopPt;
	if(genAntiTopPt > 400) antitoppt_temp = 400;
	
	float SFtop = TMath::Exp(0.156-0.00137*toppt_temp); // using 8TeV TopPtReweighting: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting
	float SFantitop = TMath::Exp(0.156-0.00137*antitoppt_temp);
	topPtWeight = TMath::Sqrt(SFtop*SFantitop)/0.99277; //0.99277-->average weight
	
	float SFtopPast400 = TMath::Exp(0.156-0.00137*genTopPt);
	float SFantitopPast400 = TMath::Exp(0.156-0.00137*genAntiTopPt);
	topPtWeightPast400 = TMath::Sqrt(SFtopPast400*SFantitopPast400)/0.9927;
	
	float SFtopHighPt = 0.98  - 0.00026*genTopPt;  // 0.98 +- 0.24, 0.0026 +- 0.00039
	float SFantitopHighPt = 0.98  - 0.00026*genAntiTopPt;
	topPtWeightHighPt = TMath::Sqrt(SFtopHighPt*SFantitopHighPt);
      }
      
      // ----------------------------------------------------------------------------
      // W --> l nu with mass constraint
      // ----------------------------------------------------------------------------

      double metpx = corr_met_singleLepCalc*cos(corr_met_phi_singleLepCalc);
      double metpy = corr_met_singleLepCalc*sin(corr_met_phi_singleLepCalc);
      double metpt = corr_met_singleLepCalc;

      double Dtmp = (MW*MW)-(lepM*lepM)+2*((lepton_lv.Px())*(metpx)+(lepton_lv.Py())*(metpy));
      double Atmp = 4.0*((lepton_lv.Energy())*(lepton_lv.Energy())-(lepton_lv.Pz())*(lepton_lv.Pz()));
      double Btmp = -4.0*Dtmp*(lepton_lv.Pz());
      double Ctmp = 4.0*(lepton_lv.Energy())*(lepton_lv.Energy())*(metpt)*(metpt)-Dtmp*Dtmp;
      
      double nuPz_1;
      double nuPz_2;
      
      double DETtmp = Btmp*Btmp-4.0*Atmp*Ctmp;
      
      TLorentzVector Wlv_1, Wlv_2, Wlv,lvTop, lvXTF;
      if(DETtmp >= 0) {
	nuPz_1 = (-Btmp+TMath::Sqrt(DETtmp))/(2.0*Atmp);
	nuPz_2 = (-Btmp-TMath::Sqrt(DETtmp))/(2.0*Atmp);
	TLorentzVector Nulv_1(metpx,metpy,nuPz_1,TMath::Sqrt((metpt)*(metpt)+(nuPz_1)*(nuPz_1)));
	TLorentzVector Nulv_2(metpx,metpy,nuPz_2,TMath::Sqrt((metpt)*(metpt)+(nuPz_2)*(nuPz_2)));
	Wlv_1 = Nulv_1+lepton_lv;
	Wlv_2 = Nulv_2+lepton_lv;
      }
      if(DETtmp < 0) {
	nuPz_1 = (-Btmp)/(2.0*Atmp);
	nuPz_2 = (-Btmp)/(2.0*Atmp);
	double alpha = (lepton_lv.Px())*(metpx)/(metpt)+(lepton_lv.Py())*(metpy)/(metpt);
	double Delta = (MW*MW)-(lepM*lepM);
	Atmp = 4.0*((lepton_lv.Pz())*(lepton_lv.Pz())-(lepton_lv.Energy())*(lepton_lv.Energy())+(alpha*alpha));
	Btmp = 4.0*alpha*Delta;
	Ctmp = Delta*Delta;
	DETtmp = Btmp*Btmp-4.0*Atmp*Ctmp;
	double pTnu_1 = (-Btmp+TMath::Sqrt(DETtmp))/(2.0*Atmp);
	double pTnu_2 = (-Btmp-TMath::Sqrt(DETtmp))/(2.0*Atmp);
	TLorentzVector Nulv_1(metpx*(pTnu_1)/(metpt),metpy*(pTnu_1)/(metpt),nuPz_1,TMath::Sqrt((pTnu_1)*(pTnu_1)+(nuPz_1)*(nuPz_1)));
	TLorentzVector Nulv_2(metpx*(pTnu_2)/(metpt),metpy*(pTnu_2)/(metpt),nuPz_2,TMath::Sqrt((pTnu_2)*(pTnu_2)+(nuPz_2)*(nuPz_2)));
	Wlv_1 = Nulv_1+lepton_lv;
	Wlv_2 = Nulv_2+lepton_lv;
	if (fabs(Wlv_1.M()-MW) < fabs(Wlv_2.M()-MW)) Wlv_2 = Wlv_1;
	else Wlv_1 = Wlv_2;
      }
      
      // ----------------------------------------------------------------------------
      // top --> W b --> l nu b using W from above
      // ----------------------------------------------------------------------------

      double dMTOP = 1e8;
      unsigned int topIndex = 0;
      bool firstW = true;
      double MTop_1, MTop_2;
      for(unsigned int ijet=0; ijet < theJetPt_JetSubCalc_PtOrdered.size(); ijet++){
	jet_lv.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered.at(ijet),theJetEta_JetSubCalc_PtOrdered.at(ijet),theJetPhi_JetSubCalc_PtOrdered.at(ijet),theJetEnergy_JetSubCalc_PtOrdered.at(ijet));
	MTop_1 = (jet_lv + Wlv_1).M();
	MTop_2 = (jet_lv + Wlv_2).M();
	if(fabs(MTop_1 - MTOP) < dMTOP) {
	  if(fabs(MTop_1 - MTOP) < fabs(MTop_2 - MTOP)) {
	    firstW = true;
	    topIndex = ijet;
	    dMTOP = fabs(MTop_1 - MTOP);
	  }
	  else {
	    firstW = false;
	    topIndex = ijet;
	    dMTOP = fabs(MTop_2 - MTOP);
	  }
	}
	else if(fabs(MTop_2 - MTOP) < dMTOP) {
	  firstW = false;
	  topIndex = ijet;
	  dMTOP = fabs(MTop_2 - MTOP);
	}
      }

      if(firstW) {Wlv = Wlv_1;}
      else{Wlv = Wlv_2;}

      jet_lv.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered.at(topIndex),theJetEta_JetSubCalc_PtOrdered.at(topIndex),theJetPhi_JetSubCalc_PtOrdered.at(topIndex),theJetEnergy_JetSubCalc_PtOrdered.at(topIndex));
      lvTop = jet_lv + Wlv; //Top LV

      topPt = lvTop.Pt();
      topMass = lvTop.M();
      topPtGen = genTopPt;
      if(fabs(lvTop.Pt() - genTopPt) > fabs(lvTop.Pt() - genAntiTopPt)) topPtGen = genAntiTopPt;

      // ----------------------------------------------------------------------------
      // AK4 Jet - lepton associations
      // ----------------------------------------------------------------------------

      NJetsCSVwithSF_JetSubCalc = 0;
      BJetLeadPt = -99;
      minMleppBjet = 1e8;
      minMleppJet = 1e8;
      deltaRlepJetInMinMljet = -99;
      deltaPhilepJetInMinMljet = -99;
      deltaRlepbJetInMinMlb = -99;
      deltaPhilepbJetInMinMlb = -99;
      minDR_lepJet = 1e8;
      ptRel_lepJet = -99;
      BJetLeadPt_shifts.clear();
      deltaR_lepJets.clear();
      deltaR_lepBJets.clear();
      deltaR_lepBJets_bSFup.clear();
      deltaR_lepBJets_bSFdn.clear();
      deltaR_lepBJets_lSFup.clear();
      deltaR_lepBJets_lSFdn.clear();
      deltaPhi_lepJets.clear();
      deltaPhi_lepBJets.clear();
      deltaPhi_lepBJets_bSFup.clear();
      deltaPhi_lepBJets_bSFdn.clear();
      deltaPhi_lepBJets_lSFup.clear();
      deltaPhi_lepBJets_lSFdn.clear();
      mass_lepJets.clear();
      mass_lepBJets.clear();
      mass_lepBJets_bSFup.clear();
      mass_lepBJets_bSFdn.clear();
      mass_lepBJets_lSFup.clear();
      mass_lepBJets_lSFdn.clear();
      NJetsCSVwithSF_JetSubCalc_shifts.clear();
      minMleppBjet_shifts.clear();
      deltaRlepbJetInMinMlb_shifts.clear();
      deltaPhilepbJetInMinMlb_shifts.clear();
      for(int i = 0; i < 4; i++){
	BJetLeadPt_shifts.push_back(-99);
	NJetsCSVwithSF_JetSubCalc_shifts.push_back(0);
	minMleppBjet_shifts.push_back(1e8);
	deltaRlepbJetInMinMlb_shifts.push_back(-99);
	deltaPhilepbJetInMinMlb_shifts.push_back(-99);
      }	

      for(unsigned int ijet=0; ijet < theJetPt_JetSubCalc_PtOrdered.size(); ijet++){
        jet_lv.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered.at(ijet),theJetEta_JetSubCalc_PtOrdered.at(ijet),theJetPhi_JetSubCalc_PtOrdered.at(ijet),theJetEnergy_JetSubCalc_PtOrdered.at(ijet));
	if((lepton_lv + jet_lv).M() < minMleppJet) {
	  minMleppJet = fabs((lepton_lv + jet_lv).M());
	  deltaRlepJetInMinMljet = jet_lv.DeltaR(lepton_lv);
	  deltaPhilepJetInMinMljet = jet_lv.DeltaPhi(lepton_lv);
	}

	deltaR_lepJets.push_back(lepton_lv.DeltaR(jet_lv));
	deltaPhi_lepJets.push_back(lepton_lv.DeltaPhi(jet_lv));
	mass_lepJets.push_back((lepton_lv + jet_lv).M());

	if(theJetBTag_JetSubCalc_PtOrdered.at(ijet) == 1){
	  NJetsCSVwithSF_JetSubCalc += 1;
	  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt) BJetLeadPt = theJetPt_JetSubCalc_PtOrdered.at(ijet);
	  deltaR_lepBJets.push_back(lepton_lv.DeltaR(jet_lv));
	  deltaPhi_lepBJets.push_back(lepton_lv.DeltaPhi(jet_lv));
	  mass_lepBJets.push_back((lepton_lv + jet_lv).M());

	  if((lepton_lv + jet_lv).M() < minMleppBjet) {
	    minMleppBjet = fabs( (lepton_lv + jet_lv).M() );
	    deltaRlepbJetInMinMlb = jet_lv.DeltaR(lepton_lv);
	    deltaPhilepbJetInMinMlb = jet_lv.DeltaPhi(lepton_lv);
	  }
	}
	if(theJetBTag_bSFup_JetSubCalc_PtOrdered.at(ijet) == 1){
	  NJetsCSVwithSF_JetSubCalc_shifts.at(0) += 1;
	  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(0)) BJetLeadPt_shifts.at(0) = theJetPt_JetSubCalc_PtOrdered.at(ijet);
	  deltaR_lepBJets_bSFup.push_back(lepton_lv.DeltaR(jet_lv));
	  deltaPhi_lepBJets_bSFup.push_back(lepton_lv.DeltaPhi(jet_lv));
	  mass_lepBJets_bSFup.push_back((lepton_lv + jet_lv).M());

	  if((lepton_lv + jet_lv).M() < minMleppBjet_shifts.at(0)) {
	    minMleppBjet_shifts.at(0) = fabs( (lepton_lv + jet_lv).M() );
	    deltaRlepbJetInMinMlb_shifts.at(0) = jet_lv.DeltaR(lepton_lv);
	    deltaPhilepbJetInMinMlb_shifts.at(0) = jet_lv.DeltaPhi(lepton_lv);
	  }
	}
	if(theJetBTag_bSFdn_JetSubCalc_PtOrdered.at(ijet) == 1){
	  NJetsCSVwithSF_JetSubCalc_shifts.at(1) += 1;
	  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(1)) BJetLeadPt_shifts.at(1) = theJetPt_JetSubCalc_PtOrdered.at(ijet);
	  deltaR_lepBJets_bSFdn.push_back(lepton_lv.DeltaR(jet_lv));
	  deltaPhi_lepBJets_bSFdn.push_back(lepton_lv.DeltaPhi(jet_lv));
	  mass_lepBJets_bSFdn.push_back((lepton_lv + jet_lv).M());

	  if((lepton_lv + jet_lv).M() < minMleppBjet_shifts.at(1)) {
	    minMleppBjet_shifts.at(1) = fabs( (lepton_lv + jet_lv).M() );
	    deltaRlepbJetInMinMlb_shifts.at(1) = jet_lv.DeltaR(lepton_lv);
	    deltaPhilepbJetInMinMlb_shifts.at(1) = jet_lv.DeltaPhi(lepton_lv);
	  }
	}
	if(theJetBTag_lSFup_JetSubCalc_PtOrdered.at(ijet) == 1){
	  NJetsCSVwithSF_JetSubCalc_shifts.at(2) += 1;
	  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(2)) BJetLeadPt_shifts.at(2) = theJetPt_JetSubCalc_PtOrdered.at(ijet);
	  deltaR_lepBJets_lSFup.push_back(lepton_lv.DeltaR(jet_lv));
	  deltaPhi_lepBJets_lSFup.push_back(lepton_lv.DeltaPhi(jet_lv));
	  mass_lepBJets_lSFup.push_back((lepton_lv + jet_lv).M());

	  if((lepton_lv + jet_lv).M() < minMleppBjet_shifts.at(2)) {
	    minMleppBjet_shifts.at(2) = fabs( (lepton_lv + jet_lv).M() );
	    deltaRlepbJetInMinMlb_shifts.at(2) = jet_lv.DeltaR(lepton_lv);
	    deltaPhilepbJetInMinMlb_shifts.at(2) = jet_lv.DeltaPhi(lepton_lv);
	  }
	}
	if(theJetBTag_lSFdn_JetSubCalc_PtOrdered.at(ijet) == 1){
	  NJetsCSVwithSF_JetSubCalc_shifts.at(3) += 1;
	  if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(3)) BJetLeadPt_shifts.at(3) = theJetPt_JetSubCalc_PtOrdered.at(ijet);
	  deltaR_lepBJets_lSFdn.push_back(lepton_lv.DeltaR(jet_lv));
	  deltaPhi_lepBJets_lSFdn.push_back(lepton_lv.DeltaPhi(jet_lv));
	  mass_lepBJets_lSFdn.push_back((lepton_lv + jet_lv).M());

	  if((lepton_lv + jet_lv).M() < minMleppBjet_shifts.at(3)) {
	    minMleppBjet_shifts.at(3) = fabs( (lepton_lv + jet_lv).M() );
	    deltaRlepbJetInMinMlb_shifts.at(3) = jet_lv.DeltaR(lepton_lv);
	    deltaPhilepbJetInMinMlb_shifts.at(3) = jet_lv.DeltaPhi(lepton_lv);
	  }
	}

 	if(deltaR_lepJets[ijet] < minDR_lepJet) {
	  minDR_lepJet = deltaR_lepJets[ijet];
	  ptRel_lepJet = lepton_lv.P()*(jet_lv.Vect().Cross(lepton_lv.Vect()).Mag()/jet_lv.P()/lepton_lv.P());
	}
      }

      // ----------------------------------------------------------------------------
      // AK8 Jet - lepton associations, Top and W taggging
      // ----------------------------------------------------------------------------

      NJetsWtagged_0p6 = 0;
      NJetsTtagged_0p81 = 0;
      deltaR_lepAK8s.clear();
      deltaPhi_lepAK8s.clear();
      mass_lepAK8s.clear();
      minDR_lepAK8 = 1000;
      minDR_leadAK8otherAK8 = 1000;
      if(theJetAK8Pt_JetSubCalc_PtOrdered.size() < 1) minDR_lepAK8 = -99.0;      
      if(theJetAK8Pt_JetSubCalc_PtOrdered.size() < 2) minDR_leadAK8otherAK8 = -99.0;
      WJetLeadPt = -99.0;
      TJetLeadPt = -99.0;
      deltaRtopWjet = -99;     deltaPhitopWjet = -99;
      deltaRlepWjet = -99;     deltaPhilepWjet = -99;	  
      deltaRlepTjet = -99;     deltaPhilepTjet = -99;	  

      NJetsWtagged_0p6_shifts.clear();
      NJetsTtagged_0p81_shifts.clear();
      theJetAK8Wmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8Hmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8Zmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8Tmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8MatchedPt_JetSubCalc_PtOrdered.clear();
      WJetLeadPt_shifts.clear();
      TJetLeadPt_shifts.clear();
      deltaRtopWjet_shifts.clear();  deltaPhitopWjet_shifts.clear(); 
      deltaRlepWjet_shifts.clear();  deltaPhilepWjet_shifts.clear(); 
      deltaRlepTjet_shifts.clear();  deltaPhilepTjet_shifts.clear(); 

      wjet1_lv.SetPtEtaPhiM(0,0,0,0);
      tjet1_lv.SetPtEtaPhiM(0,0,0,0);
      ak8_lv.SetPtEtaPhiM(0,0,0,0);
      TLorentzVector leadak8;
      leadak8.SetPtEtaPhiM(0,0,0,0);

      for(int i = 0; i < 2; i++){
	NJetsWtagged_0p6_shifts.push_back(0);
	NJetsTtagged_0p81_shifts.push_back(0);
	WJetLeadPt_shifts.push_back(-99.0);
	TJetLeadPt_shifts.push_back(-99.0);
	deltaRtopWjet_shifts.push_back(-99.0);  deltaPhitopWjet_shifts.push_back(-99.0); 
	deltaRlepWjet_shifts.push_back(-99.0);  deltaPhilepWjet_shifts.push_back(-99.0); 
	deltaRlepTjet_shifts.push_back(-99.0);  deltaPhilepTjet_shifts.push_back(-99.0); 
      }

      for(unsigned int ijet=0; ijet < theJetAK8Pt_JetSubCalc_PtOrdered.size(); ijet++){

	// ----------------------------------------------------------------------------
	// AK8 - lepton and AK8 -- AK8 associations
	// ----------------------------------------------------------------------------
	
	ak8_lv.SetPtEtaPhiE(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),theJetAK8Energy_JetSubCalc_PtOrdered.at(ijet));
	if(ijet == 0) leadak8 = ak8_lv;

	deltaR_lepAK8s.push_back(lepton_lv.DeltaR(ak8_lv));
	deltaPhi_lepAK8s.push_back(lepton_lv.DeltaPhi(ak8_lv));
	mass_lepAK8s.push_back((lepton_lv+ak8_lv).M());

	if(lepton_lv.DeltaR(ak8_lv) < minDR_lepAK8) minDR_lepAK8 = lepton_lv.DeltaR(ak8_lv);

	if(ijet > 0){
	  float tempdr = leadak8.DeltaR(ak8_lv);
	  if(tempdr < minDR_leadAK8otherAK8){
	    minDR_leadAK8otherAK8 = tempdr;
	  }
	}

	// ----------------------------------------------------------------------------
	// W & top tagging on MC
	// ----------------------------------------------------------------------------

	float tau21 = theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.at(ijet)/theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.at(ijet);
	float tau32 = theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.at(ijet)/theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.at(ijet);
	float mass = theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered.at(ijet);
	float massSD = theJetAK8SoftDropMass_JetSubCalc_PtOrdered.at(ijet);

	// ------------------------------------------------------------------------------------------------------------------
	// MC Calculation first
	// ------------------------------------------------------------------------------------------------------------------

	if(isMC){

	  // ------------------------------------------------------------------------------------------------------------------
	  // TRUTH MATCHING
	  // ------------------------------------------------------------------------------------------------------------------
	  float minDR = 1000;
	  float matchedPt= -99;
	  int matchedID = 0;
	  bool isWmatched = false;
	  bool isHmatched = false;
	  bool isZmatched = false;
	  bool isTmatched = false;
	  TLorentzVector trueW,d1,d2,d3;

	  for(unsigned int iW = 0; iW < HadronicVHtPt_JetSubCalc->size(); iW++){
	    trueW.SetPtEtaPhiE(HadronicVHtPt_JetSubCalc->at(iW),HadronicVHtEta_JetSubCalc->at(iW),HadronicVHtPhi_JetSubCalc->at(iW),HadronicVHtEnergy_JetSubCalc->at(iW));

	    if(ak8_lv.DeltaR(trueW) < minDR){
	      minDR = ak8_lv.DeltaR(trueW);
	      matchedPt = HadronicVHtPt_JetSubCalc->at(iW);
	      matchedID = abs(HadronicVHtID_JetSubCalc->at(iW));	      
	      d1.SetPtEtaPhiE(HadronicVHtD0Pt_JetSubCalc->at(iW),HadronicVHtD0Eta_JetSubCalc->at(iW),HadronicVHtD0Phi_JetSubCalc->at(iW),HadronicVHtD0E_JetSubCalc->at(iW));
	      d2.SetPtEtaPhiE(HadronicVHtD1Pt_JetSubCalc->at(iW),HadronicVHtD1Eta_JetSubCalc->at(iW),HadronicVHtD1Phi_JetSubCalc->at(iW),HadronicVHtD1E_JetSubCalc->at(iW));
	      d3.SetPtEtaPhiE(HadronicVHtD2Pt_JetSubCalc->at(iW),HadronicVHtD2Eta_JetSubCalc->at(iW),HadronicVHtD2Phi_JetSubCalc->at(iW),HadronicVHtD2E_JetSubCalc->at(iW));
	    }
   	  }	 
  
	  bool WallDsInJet = false;
	  bool TallDsInJet = false;
	  if(matchedID != 6 && ak8_lv.DeltaR(d1) < 0.8 && ak8_lv.DeltaR(d2) < 0.8) WallDsInJet = true;
	  if(matchedID == 6 && ak8_lv.DeltaR(d1) < 0.8 && ak8_lv.DeltaR(d2) < 0.8 && ak8_lv.DeltaR(d3) < 0.8) TallDsInJet = true;
	  if(minDR < 0.8 && matchedID == 24 && WallDsInJet) isWmatched = true;
	  if(minDR < 0.8 && matchedID == 25 && WallDsInJet) isHmatched = true;
	  if(minDR < 0.8 && matchedID == 23 && WallDsInJet) isZmatched = true;
	  if(minDR < 0.8 && matchedID == 6 && TallDsInJet) isTmatched = true;

	  theJetAK8Wmatch_JetSubCalc_PtOrdered.push_back(isWmatched);
	  theJetAK8Hmatch_JetSubCalc_PtOrdered.push_back(isHmatched);
	  theJetAK8Zmatch_JetSubCalc_PtOrdered.push_back(isZmatched);
	  theJetAK8Tmatch_JetSubCalc_PtOrdered.push_back(isTmatched);
	  if(isWmatched || isZmatched || isHmatched || isTmatched) theJetAK8MatchedPt_JetSubCalc_PtOrdered.push_back(matchedPt);
	  else theJetAK8MatchedPt_JetSubCalc_PtOrdered.push_back(-99.0);
	  
	  // ------------------------------------------------------------------------------------------------------------------
	  // W TAGGING
	  // ------------------------------------------------------------------------------------------------------------------
	  
	  float tau0p6SF = 1.0;
	  float tau0p6SFup = 1.0;
	  float tau0p6SFdn = 1.0;
	  double tau0p6Eff = 1.0;
	  if(isWmatched && matchedPt>=200){	    
	    // VALUES FOR 76X FROM TWIKI 76X with JEC v2
	    tau0p6SF = 0.980;
	    tau0p6SFup = 1.014;
	    tau0p6SFdn = 0.946;
	  
	    // Use matched W to find the efficiency -- calculated for TpTp and ttbar, EWK/QCD will almost never pass here (use ttbar eff when they do)
	    if(isSig){
	      int bin = (std::upper_bound(ptRangeTpTp.begin(), ptRangeTpTp.end(), matchedPt)-ptRangeTpTp.begin())-1;
	      tau0p6Eff = SignalEff[SigMass][bin];
	    }else{
	      int bin = (std::upper_bound(ptRangeTTbar.begin(), ptRangeTTbar.end(), matchedPt)-ptRangeTTbar.begin())-1;
	      if(isTT) tau0p6Eff = TTbarEff[bin]; // ttbar
	      else if(isST) tau0p6Eff = STEff[bin]; // single top (s and t channel had 0 boosted tops)
	      else if(isTTV) tau0p6Eff = TTVEff[bin]; // tt+V
	      else tau0p6Eff = WVEff[bin]; // WW, WZ, etc. 
	    }
	  }

	  // Set the initial tagged/untagged state
	  bool isWtagged = (mass > 65) && (mass < 105) && (tau21 < 0.6) && theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 200;
 
	  // IF THE JET IS NOT TRUTH-MATCHED, THESE IFS WILL DO NOTHING, SF == 1
	  int tag_tau0p6 = applySF(isWtagged,tau0p6SF,tau0p6Eff);
	  int tag_tau0p6up = applySF(isWtagged,tau0p6SFup,tau0p6Eff);
	  int tag_tau0p6dn = applySF(isWtagged,tau0p6SFdn,tau0p6Eff);
	  
	  // Now increase the tag count in the right variable	  
	  NJetsWtagged_0p6 += tag_tau0p6;
	  NJetsWtagged_0p6_shifts[0] += tag_tau0p6up;
	  NJetsWtagged_0p6_shifts[1] += tag_tau0p6dn;

	  // ------------------------------------------------------------------------------------------------------------------
	  // Variables for W tagged jets
	  // ------------------------------------------------------------------------------------------------------------------

	  if(tag_tau0p6 == 1){
	    if(NJetsWtagged_0p6 == 1){
	      WJetLeadPt = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	      wjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
				    theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),mass);
	      deltaRtopWjet = wjet1_lv.DeltaR(lvTop);
	      deltaRlepWjet = wjet1_lv.DeltaR(lepton_lv);
	      deltaPhitopWjet = wjet1_lv.DeltaPhi(lvTop);
	      deltaPhilepWjet = wjet1_lv.DeltaPhi(lepton_lv);
	    }
	  }
	  if(tag_tau0p6up == 1){
	    if(NJetsWtagged_0p6_shifts[0] == 1){
	      WJetLeadPt_shifts.at(0) = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	      wjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
				    theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),mass);
	      deltaRtopWjet_shifts.at(0) = wjet1_lv.DeltaR(lvTop);
	      deltaRlepWjet_shifts.at(0) = wjet1_lv.DeltaR(lepton_lv);
	      deltaPhitopWjet_shifts.at(0) = wjet1_lv.DeltaPhi(lvTop);
	      deltaPhilepWjet_shifts.at(0) = wjet1_lv.DeltaPhi(lepton_lv);
	    }
	  }
	  if(tag_tau0p6dn == 1){
	    if(NJetsWtagged_0p6_shifts[1] == 1){
	      WJetLeadPt_shifts.at(1) = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	      wjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
				    theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),mass);
	      deltaRtopWjet_shifts.at(1) = wjet1_lv.DeltaR(lvTop);
	      deltaRlepWjet_shifts.at(1) = wjet1_lv.DeltaR(lepton_lv);
	      deltaPhitopWjet_shifts.at(1) = wjet1_lv.DeltaPhi(lvTop);
	      deltaPhilepWjet_shifts.at(1) = wjet1_lv.DeltaPhi(lepton_lv);
	    }
	  }

	  // ------------------------------------------------------------------------------------------------------------------
	  // TOP TAGGING
	  // ------------------------------------------------------------------------------------------------------------------
	  float topTau81SF = 1.0;
	  float topTau81SFup = 1.0;
	  float topTau81SFdn = 1.0;
	  double topTau81Eff = 1.0;
	  if(isTmatched && matchedPt >= 400){	    
	    // VALUES FOR 76X FROM PAS
	    topTau81SF = 0.96;
	    topTau81SFup = 1.04;
	    topTau81SFdn = 0.88;
	  
	    // Use matched T to find the efficiency -- calculated for TpTp and ttbar, EWK/QCD will almost never pass here (use ttbar eff when they do)
	    if(isSig){
	      int bin = (std::upper_bound(ptRangeTpTpTop.begin(), ptRangeTpTpTop.end(), matchedPt)-ptRangeTpTpTop.begin())-1;
	      topTau81Eff = SignalEffTop[SigMass][bin];
	    }else{
	      int bin = (std::upper_bound(ptRangeTTbarTop.begin(), ptRangeTTbarTop.end(), matchedPt)-ptRangeTTbarTop.begin())-1;
	      topTau81Eff = TTbarEffTop[bin];
	    }
	  }

	  // Set the initial tagged/untagged state
	  bool isTtagged = (massSD > 105) && (massSD < 220) && (tau32 < 0.81) && theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 400;

	  // IF THE JET IS NOT TRUTH-MATCHED, THESE IFS WILL DO NOTHING, SF == 1
	  int tag_topTau81 = applySF(isTtagged,topTau81SF,topTau81Eff);
	  int tag_topTau81up = applySF(isTtagged,topTau81SFup,topTau81Eff);
	  int tag_topTau81dn = applySF(isTtagged,topTau81SFdn,topTau81Eff);
 
	  // Now increase the tag count in the right variable	  
	  NJetsTtagged_0p81 += tag_topTau81;
	  NJetsTtagged_0p81_shifts[0] += tag_topTau81up;
	  NJetsTtagged_0p81_shifts[1] += tag_topTau81dn;

 	  // ------------------------------------------------------------------------------------------------------------------
	  // Variable for top tagged jets
	  // ------------------------------------------------------------------------------------------------------------------

	  if(tag_topTau81 == 1){
	    TJetLeadPt = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	    if(NJetsTtagged_0p81 == 1){
	      tjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
				    theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),massSD);
	      deltaRlepTjet = tjet1_lv.DeltaR(lepton_lv);
	      deltaPhilepTjet = tjet1_lv.DeltaPhi(lepton_lv);
	    }
	  }
	  if(tag_topTau81up == 1){
	    TJetLeadPt_shifts.at(0) = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	    if(NJetsTtagged_0p81_shifts[0] == 1){
	      tjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
				    theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),massSD);
	      deltaRlepTjet_shifts.at(0) = tjet1_lv.DeltaR(lepton_lv);
	      deltaPhilepTjet_shifts.at(0) = tjet1_lv.DeltaPhi(lepton_lv);
	    }
	  }
	  if(tag_topTau81dn == 1){
	    TJetLeadPt_shifts.at(1) = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	    if(NJetsTtagged_0p81_shifts[1] == 1){
	      tjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
				    theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),massSD);
	      deltaRlepTjet_shifts.at(1) = tjet1_lv.DeltaR(lepton_lv);
	      deltaPhilepTjet_shifts.at(1) = tjet1_lv.DeltaPhi(lepton_lv);
	    }
	  }
	}
	// ------------------------------------------------------------------------------------------------------------------
	// DATA Calculation second
	// ------------------------------------------------------------------------------------------------------------------
	else{
	 
	  theJetAK8Wmatch_JetSubCalc_PtOrdered.push_back(0);
	  theJetAK8Hmatch_JetSubCalc_PtOrdered.push_back(0);
	  theJetAK8Zmatch_JetSubCalc_PtOrdered.push_back(0);
	  theJetAK8Tmatch_JetSubCalc_PtOrdered.push_back(0);
 
	  if(tau21 < 0.6 && mass > 65.0 && mass < 105.0 && theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 200){

	    NJetsWtagged_0p6 += 1;
	    if(NJetsWtagged_0p6 == 1){
	      WJetLeadPt = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	      wjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
				    theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),mass);
	      deltaRtopWjet = wjet1_lv.DeltaR(lvTop);
	      deltaRlepWjet = wjet1_lv.DeltaR(lepton_lv);
	      deltaPhitopWjet = wjet1_lv.DeltaPhi(lvTop);
	      deltaPhilepWjet = wjet1_lv.DeltaPhi(lepton_lv);
	    }
	  }
	  if(tau32 < 0.81 && massSD > 105.0 && massSD < 220.0 && theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 400){

	    NJetsTtagged_0p81 += 1;
	    if(NJetsTtagged_0p81 == 1){
	      TJetLeadPt = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	      tjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
				    theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),massSD);
	      deltaRlepTjet = tjet1_lv.DeltaR(lepton_lv);
	      deltaPhilepTjet = tjet1_lv.DeltaPhi(lepton_lv);
	    }
	  }
	}
      }

      // ----------------------------------------------------------------------------
      // PDF and Matrix Element energy scale weights
      // ----------------------------------------------------------------------------

      std::vector<double> renorm;
      std::vector<double> pdf;
      renormWeights.clear();
      pdfWeights.clear();
      if(isSig){
	// SEEMS TO APPLY TO ALL B2G MG+PYTHIA SIGNALS. LEADING ORDER 4-FLAVOR PDF
	for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
	  if(LHEweightids_singleLepCalc->at(i) > 1 && LHEweightids_singleLepCalc->at(i) < 10){
	    if(LHEweightids_singleLepCalc->at(i) == 6 || LHEweightids_singleLepCalc->at(i) == 8) continue;
	    renorm.push_back(LHEweights_singleLepCalc->at(i));
	    renormWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	  if(LHEweightids_singleLepCalc->at(i) > 111 && LHEweightids_singleLepCalc->at(i) < 212){
	    pdf.push_back(LHEweights_singleLepCalc->at(i));	    
	    pdfWeights.push_back(LHEweights_singleLepCalc->at(i));	    
	  }
	}
      }
      else if(isMadgraphBkg){
	// SEEMS TO APPLY TO OTHER MG+PYTHIA BACKGROUNDS. LEADING ORDER 5-FLAVOR PDF
	for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
	  if(LHEweightids_singleLepCalc->at(i) > 1 && LHEweightids_singleLepCalc->at(i) < 10){
	    if(LHEweightids_singleLepCalc->at(i) == 6 || LHEweightids_singleLepCalc->at(i) == 8) continue;
	    renorm.push_back(LHEweights_singleLepCalc->at(i));
	    renormWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	  if(LHEweightids_singleLepCalc->at(i) > 10 && LHEweightids_singleLepCalc->at(i) < 111){
	    pdf.push_back(LHEweights_singleLepCalc->at(i));
	    pdfWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	}
      }
      else{
	// SEEMS TO APPLY TO ALL POWHEG AND MC@NLO BACKGROUNDS. NLO PDFs
	for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
	  if(LHEweightids_singleLepCalc->at(i) > 1001 && LHEweightids_singleLepCalc->at(i) < 1010){
	    if(LHEweightids_singleLepCalc->at(i) == 1006 || LHEweightids_singleLepCalc->at(i) == 1008) continue;
	    renorm.push_back(LHEweights_singleLepCalc->at(i));
	    renormWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	  if(LHEweightids_singleLepCalc->at(i) > 2000 && LHEweightids_singleLepCalc->at(i) < 2101){
	    pdf.push_back(LHEweights_singleLepCalc->at(i));
	    pdfWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	  if(LHEweightids_singleLepCalc->at(i) == 2101 || LHEweightids_singleLepCalc->at(i) == 2102){
	    alphaSWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	}
      }

      if(renormWeights.size() == 0){
	for(int irn = 0; irn < 6; irn++){
	  renormWeights.push_back(1.0);
	}
      }
      if(pdfWeights.size() == 0){
	for(int ipdf = 0; ipdf < 100; ipdf++){
	  pdfWeights.push_back(1.0);
	}
      }

      // ----------------------------------------------------------------------------
      // DONE!! Write the tree
      // ----------------------------------------------------------------------------
      
      outputTree->Fill();
   }
   std::cout<<"Nelectrons             = "<<Nelectrons<<" / "<<nentries<<std::endl;
   std::cout<<"Nmuons                 = "<<Nmuons<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_Mu500          = "<<npass_mu500<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_Trigger(DATA)  = "<<npass_trigger<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_MET            = "<<npass_met<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_nJets          = "<<npass_njets<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_JetLeadPt      = "<<npass_JetLeadPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_JetSubLeadPt   = "<<npass_JetSubLeadPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_lepPt          = "<<npass_lepPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_ElEta          = "<<npass_ElEta<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_ALL            = "<<npass_all<<" / "<<nentries<<std::endl;
   std::cout<<"DONE "<<nentries<<std::endl;
   outputTree->Write();

}
