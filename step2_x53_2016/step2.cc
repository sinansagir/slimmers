#define step2_cxx
#include "step2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <fstream>
#include <iostream>	// std::cout
#include <algorithm>	// std::sort
#include <TRandom.h>
#include <TRandom3.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void step2::Loop(){

  
  if (inputTree == 0) return;
  inputTree->SetBranchStatus("*",1);
  
  //TTree *outputTree = new TTree("ljmet","ljmet"); //No Copy of Input Tree

  //Event info

//    inputTree->SetBranchStatus("event_CommonCalc", 1);
//    inputTree->SetBranchStatus("run_CommonCalc", 1);
//    inputTree->SetBranchStatus("lumi_CommonCalc", 1);
//    inputTree->SetBranchStatus("isElectron", 1);
//    inputTree->SetBranchStatus("isMuon", 1);
//    inputTree->SetBranchStatus("MCPastTrigger", 1);
//    inputTree->SetBranchStatus("MCPastTriggerAlt", 1);
//    inputTree->SetBranchStatus("DataPastTrigger", 1);
//    inputTree->SetBranchStatus("DataPastTriggerAlt", 1);
//    inputTree->SetBranchStatus("MCWeight_singleLepCalc", 1);
//    inputTree->SetBranchStatus("renormWeights", 1);
//    inputTree->SetBranchStatus("pdfWeights", 1);
//    inputTree->SetBranchStatus("JetSF_pTNbwflat", 1);
//    inputTree->SetBranchStatus("JetSFup_pTNbwflat", 1);
//    inputTree->SetBranchStatus("JetSFdn_pTNbwflat", 1);
//    inputTree->SetBranchStatus("JetSFupwide_pTNbwflat", 1);
//    inputTree->SetBranchStatus("JetSFdnwide_pTNbwflat", 1);
//    inputTree->SetBranchStatus("pileupWeight", 1);
//    inputTree->SetBranchStatus("pileupWeightUp", 1);
//    inputTree->SetBranchStatus("pileupWeightDown", 1);
//    inputTree->SetBranchStatus("TrigEffAltWeight", 1);
//    inputTree->SetBranchStatus("TrigEffWeight", 1);
//    inputTree->SetBranchStatus("TrigEffWeightUncert", 1);
//    inputTree->SetBranchStatus("isoSF", 1);
//    inputTree->SetBranchStatus("lepIdSF", 1);
//    inputTree->SetBranchStatus("EGammaGsfSF", 1);
//    inputTree->SetBranchStatus("MuTrkSF", 1);
//    inputTree->SetBranchStatus("corr_met_singleLepCalc", 1);
//    inputTree->SetBranchStatus("leptonPt_singleLepCalc", 1);
//    inputTree->SetBranchStatus("theJetPt_JetSubCalc_PtOrdered", 1);
//    inputTree->SetBranchStatus("AK4HTpMETpLepPt", 1);
//    inputTree->SetBranchStatus("AK4HT", 1);
//    inputTree->SetBranchStatus("NJets_JetSubCalc", 1);
//    inputTree->SetBranchStatus("NJetsCSVwithSF_JetSubCalc", 1);
//    inputTree->SetBranchStatus("NJetsCSVwithSF_JetSubCalc_shifts", 1);
//    inputTree->SetBranchStatus("minMleppBjet", 1);
//    inputTree->SetBranchStatus("minMleppJet", 1);
//    inputTree->SetBranchStatus("NJetsWtagged_0p6", 1);
//    inputTree->SetBranchStatus("NJetsWtagged_0p6_shifts", 1);
//    inputTree->SetBranchStatus("NJetsTtagged_0p81", 1);
//    inputTree->SetBranchStatus("NJetsTtagged_0p81_shifts", 1);
//    inputTree->SetBranchStatus("minDR_lepJet", 1);
//    inputTree->SetBranchStatus("ptRel_lepJet", 1);
//    inputTree->SetBranchStatus("deltaR_lepJets", 1);
   
   inputTree->SetBranchStatus("isTHBW_TpTpCalc", 0);
   inputTree->SetBranchStatus("isTHTH_TpTpCalc", 0);
   inputTree->SetBranchStatus("isBWBW_TpTpCalc", 0);
   inputTree->SetBranchStatus("isTZBW_TpTpCalc", 0);
   inputTree->SetBranchStatus("isTZTH_TpTpCalc", 0);
   inputTree->SetBranchStatus("isTZTZ_TpTpCalc", 0);
   inputTree->SetBranchStatus("isBHTW_TpTpCalc", 0);
   inputTree->SetBranchStatus("isBHBH_TpTpCalc", 0);
   inputTree->SetBranchStatus("isTWTW_TpTpCalc", 0);
   inputTree->SetBranchStatus("isBZTW_TpTpCalc", 0);
   inputTree->SetBranchStatus("isBZBH_TpTpCalc", 0);
   inputTree->SetBranchStatus("isBZBZ_TpTpCalc", 0);
   
  outputFile->cd();
  TTree *outputTree = inputTree->CloneTree(0); //Copy of Input Tree
  outputTree->Branch("isTraining",&isTraining,"isTraining/I");

  // basic cuts
  float metCut=80;
  int   njetsCut=3;
  float JetLeadPtCut=200;
  float JetSubLeadPtCut=50;
  float lepPtCut=30;
  
//   double pileup_central[38] = {7.892e-03, 1.846e-02, 1.858e-02, 2.098e-02, 3.207e-02, 2.484e-02, 2.326e-02, 3.721e-02, 7.012e-02, 1.266e-01, 2.280e-01, 3.998e-01, 5.895e-01, 7.439e-01, 8.700e-01, 8.940e-01, 8.630e-01, 9.238e-01, 8.971e-01, 9.710e-01, 8.868e-01, 8.635e-01, 9.279e-01, 1.027e+00, 1.066e+00, 1.256e+00, 1.250e+00, 1.425e+00, 1.414e+00, 1.557e+00, 1.665e+00, 1.801e+00, 2.588e+00, 3.449e+00, 6.530e+00, 1.510e+01, 4.634e+01, 9.928e+01};
//   double pileup_down[38]    = {8.176e-03, 2.356e-02, 1.953e-02, 2.397e-02, 3.574e-02, 2.725e-02, 2.694e-02, 5.769e-02, 1.033e-01, 1.926e-01, 3.514e-01, 5.697e-01, 7.846e-01, 9.493e-01, 1.083e+00, 1.068e+00, 9.832e-01, 1.014e+00, 9.614e-01, 1.030e+00, 9.352e-01, 8.958e-01, 9.406e-01, 1.019e+00, 1.037e+00, 1.195e+00, 1.163e+00, 1.296e+00, 1.255e+00, 1.344e+00, 1.391e+00, 1.451e+00, 2.006e+00, 2.568e+00, 4.665e+00, 1.032e+01, 3.013e+01, 6.090e+01};
//   double pileup_up[38]      = {7.690e-03, 1.454e-02, 1.759e-02, 1.842e-02, 2.919e-02, 2.240e-02, 2.122e-02, 2.606e-02, 4.722e-02, 8.679e-02, 1.494e-01, 2.732e-01, 4.337e-01, 5.773e-01, 6.949e-01, 7.319e-01, 7.369e-01, 8.227e-01, 8.247e-01, 9.106e-01, 8.382e-01, 8.210e-01, 8.956e-01, 1.012e+00, 1.071e+00, 1.285e+00, 1.304e+00, 1.519e+00, 1.539e+00, 1.730e+00, 1.896e+00, 2.109e+00, 3.129e+00, 4.317e+00, 8.471e+00, 2.033e+01, 6.483e+01, 1.448e+02};

  Long64_t nentries = inputTree->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = inputTree->GetEntry(jentry);	  nbytes += nb;
    if (Cut(ientry) != 1) continue;  //Pre-selection

    if(jentry % 1000 ==0) std::cout<<"Completed "<<jentry<<" out of "<<nentries<<" events"<<std::endl;
    
    bool isPastMETcut=(corr_met_singleLepCalc > metCut);
    bool isPastNJetsCut=(NJets_JetSubCalc >= njetsCut);
    bool isPastJetLeadPtCut=(theJetPt_JetSubCalc_PtOrdered->at(0) > JetLeadPtCut);
    bool isPastJetSubLeadPtCut=(theJetPt_JetSubCalc_PtOrdered->at(1) > JetSubLeadPtCut);
    bool isPastLepPtCut=(leptonPt_singleLepCalc > lepPtCut);
    //Pre-selection
    if(!(isPastMETcut && isPastNJetsCut && isPastJetLeadPtCut && isPastJetSubLeadPtCut && isPastLepPtCut)) continue;

    NJetsCSV_JetSubCalc=0;
    for(unsigned int ijet=0; ijet < theJetCSV_JetSubCalc_PtOrdered->size(); ijet++){
	  bool istaggednosf = theJetCSV_JetSubCalc_PtOrdered->at(ijet) > 0.800;
	  NJetsCSV_JetSubCalc+=istaggednosf;
	}

    double coin = gRandom->Rndm();
    if(coin<0.5) isTraining = 1;
    else isTraining = 0;

    // ----------------------------------------------------------------------------
    // Re-calculate pileup weight
    // ----------------------------------------------------------------------------

//     pileupWeight = 1.0;
//     pileupWeightUp = 1.0;
//     pileupWeightDown = 1.0;
// 	
//     if(nTrueInteractions_singleLepCalc > 37) nTrueInteractions_singleLepCalc = 37;
//     pileupWeight = pileup_central[nTrueInteractions_singleLepCalc];
//     pileupWeightUp = pileup_down[nTrueInteractions_singleLepCalc];
//     pileupWeightDown = pileup_up[nTrueInteractions_singleLepCalc];

    outputTree->Fill();
  }
  std::cout<<"DONE "<<nentries<<std::endl;
  outputTree->Write();
}
