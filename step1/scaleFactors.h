#ifndef _scaleFactors_h_
#define _scaleFactors_h_


Float_t getEGammaGsfSF(double lepeta){// Gsf Tracking scale factor: http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/ichep2016_80X/resultsGsfID/egammaEffi.txt_egammaPlots.pdf
  Float_t EGammaGsfSF_=1.0;
  if(lepeta < -2.4) EGammaGsfSF_ = 1.170;
  else if(lepeta < -2.3) EGammaGsfSF_ = 1.009;
  else if(lepeta < -2.2) EGammaGsfSF_ = 1.010;
  else if(lepeta < -2.0) EGammaGsfSF_ = 1.005;
  else if(lepeta < -1.8) EGammaGsfSF_ = 0.998;
  else if(lepeta < -1.65) EGammaGsfSF_ = 0.992;
  else if(lepeta < -1.566) EGammaGsfSF_ = 0.986;
  else if(lepeta < -1.4442) EGammaGsfSF_ = 0.962;
  else if(lepeta < -1.2) EGammaGsfSF_ = 0.987;
  else if(lepeta < -1.0) EGammaGsfSF_ = 0.978;
  else if(lepeta < -0.6) EGammaGsfSF_ = 0.969;
  else if(lepeta < -0.4) EGammaGsfSF_ = 0.966;
  else if(lepeta < -0.2) EGammaGsfSF_ = 0.963;
  else if(lepeta < 0.0) EGammaGsfSF_ = 0.960;
  else if(lepeta < 0.2) EGammaGsfSF_ = 0.966;
  else if(lepeta < 0.4) EGammaGsfSF_ = 0.980;
  else if(lepeta < 0.6) EGammaGsfSF_ = 0.977;
  else if(lepeta < 1.0) EGammaGsfSF_ = 0.981;
  else if(lepeta < 1.2) EGammaGsfSF_ = 0.987;
  else if(lepeta < 1.4442) EGammaGsfSF_ = 0.987;
  else if(lepeta < 1.566) EGammaGsfSF_ = 0.971;
  else if(lepeta < 1.65) EGammaGsfSF_ = 0.990;
  else if(lepeta < 1.8) EGammaGsfSF_ = 0.996;
  else if(lepeta < 2.0) EGammaGsfSF_ = 0.990;
  else if(lepeta < 2.2) EGammaGsfSF_ = 0.995;
  else if(lepeta < 2.3) EGammaGsfSF_ = 0.993;
  else if(lepeta < 2.4) EGammaGsfSF_ = 0.967;
  else EGammaGsfSF_ = 0.884;
  return EGammaGsfSF_;
}


Float_t getTrigEffWeight(double leppt, double lepeta){// Ele27_eta2p1 -- 80X DATA EFFICIENCIES
  Float_t TrigEffWeight_=1.0;
  if(leppt < 45){
		if(fabs(lepeta) < 0.8) TrigEffWeight_ = 0.811; // 
		else if(fabs(lepeta) < 1.442) TrigEffWeight_ = 0.832;
		else if(fabs(lepeta) < 1.566) TrigEffWeight_ = 0.758;
		else TrigEffWeight_ = 0.772;
	  }else if(leppt < 50){
	if(fabs(lepeta) < 0.8) TrigEffWeight_ = 0.844; // 
	else if(fabs(lepeta) < 1.442) TrigEffWeight_ = 0.860;
	else if(fabs(lepeta) < 1.566) TrigEffWeight_ = 0.776;
	else TrigEffWeight_ = 0.789;
  }else if(leppt < 60){
	if(fabs(lepeta) < 0.8) TrigEffWeight_ = 0.861; // 
	else if(fabs(lepeta) < 1.442) TrigEffWeight_ = 0.873;
	else if(fabs(lepeta) < 1.566) TrigEffWeight_ = 0.782;
	else TrigEffWeight_ = 0.796;
  }else if(leppt < 70){
	if(fabs(lepeta) < 0.8) TrigEffWeight_ = 0.877; // 
	else if(fabs(lepeta) < 1.442) TrigEffWeight_ = 0.885;
	else if(fabs(lepeta) < 1.566) TrigEffWeight_ = 0.779;
	else TrigEffWeight_ = 0.798;
  }else if(leppt < 90){
	if(fabs(lepeta) < 0.8) TrigEffWeight_ = 0.887; // 
	else if(fabs(lepeta) < 1.442) TrigEffWeight_ = 0.893;
	else if(fabs(lepeta) < 1.566) TrigEffWeight_ = 0.750;
	else TrigEffWeight_ = 0.799;
  }else if(leppt < 130){
	if(fabs(lepeta) < 0.8) TrigEffWeight_ = 0.900; // 
	else if(fabs(lepeta) < 1.442) TrigEffWeight_ = 0.901;
	else if(fabs(lepeta) < 1.566) TrigEffWeight_ = 0.774;
	else TrigEffWeight_ = 0.809;
  }else{
	if(fabs(lepeta) < 0.8) TrigEffWeight_ = 0.909; // 
	else if(fabs(lepeta) < 1.442) TrigEffWeight_ = 0.912;
	else if(fabs(lepeta) < 1.566) TrigEffWeight_ = 0.797;
	else TrigEffWeight_ = 0.816;
  }
  return TrigEffWeight_;
}


Float_t getElIsoSF(double leppt, double lepeta){//miniIso < 0.1 scale factors from SUSYLepSF: http://tomc.web.cern.ch/tomc/tagAndProbe/20160726/output/scaleFactors.root
  Float_t isoSF_=1.0;
  if(fabs(lepeta) < 0.8){
	if(leppt < 30) isoSF_ = 0.991;
	else if(leppt < 40) isoSF_ = 0.993;
	else if(leppt < 50) isoSF_ = 0.996;
	else if(leppt < 100) isoSF_ = 0.996;
	else isoSF_ = 0.996;
  }
  else if(fabs(lepeta) < 1.4442){
	if(leppt < 30) isoSF_ = 0.989;
	else if(leppt < 40) isoSF_ = 0.993;
	else if(leppt < 50) isoSF_ = 0.995;
	else if(leppt < 100) isoSF_ = 0.996;
	else isoSF_ = 0.998;
  }
  else if(fabs(lepeta) < 1.566){
	if(leppt < 30) isoSF_ = 1.007;
	else if(leppt < 40) isoSF_ = 0.998;
	else if(leppt < 50) isoSF_ = 0.995;
	else if(leppt < 100) isoSF_ = 1.004;
	else isoSF_ = 0.988;
  }
  else if(fabs(lepeta) < 2.0){
	if(leppt < 30) isoSF_ = 0.990;
	else if(leppt < 40) isoSF_ = 0.999;
	else if(leppt < 50) isoSF_ = 0.998;
	else if(leppt < 100) isoSF_ = 0.999;
	else isoSF_ = 1.000;
  }
  else {
	if(leppt < 30) isoSF_ = 0.978;
	else if(leppt < 40) isoSF_ = 0.991;
	else if(leppt < 50) isoSF_ = 0.995;
	else if(leppt < 100) isoSF_ = 0.999;
	else isoSF_ = 1.001;
  }
  return isoSF_;
}


Float_t getMuIsoSF(double leppt, double lepeta){//Mini-iso < 0.2 SFs from SUSY Lepton SF: https://jrgonzal.web.cern.ch/jrgonzal/MuonSF/4.MiniIso0.2_Loose/TnP_MuonID_NUM_MiniIsoTight_DENOM_LooseID_VAR_map_pt_eta.png
  Float_t isoSF_=1.0;
  if(leppt < 40){
	if(fabs(lepeta) < 0.9) isoSF_= 0.999;
	else if(fabs(lepeta) <  1.2) isoSF_= 1.000;
	else if(fabs(lepeta) <  2.1) isoSF_= 0.999;
	else if(fabs(lepeta) <  2.4) isoSF_= 1.000;
  }
  else if(leppt < 50){
	if(fabs(lepeta) < 0.9) isoSF_= 1.000;
	else if(fabs(lepeta) <  1.2) isoSF_= 1.000;
	else if(fabs(lepeta) <  2.1) isoSF_= 0.999;
	else if(fabs(lepeta) <  2.4) isoSF_= 1.000;
  }
  else if(leppt < 60){
	if(fabs(lepeta) < 0.9) isoSF_= 1.000;
	else if(fabs(lepeta) <  1.2) isoSF_= 1.000;
	else if(fabs(lepeta) <  2.1) isoSF_= 1.000;
	else if(fabs(lepeta) <  2.4) isoSF_= 1.000;
  }
  else{
	if(fabs(lepeta) < 0.9) isoSF_= 1.000;
	else if(fabs(lepeta) <  1.2) isoSF_= 0.999;
	else if(fabs(lepeta) <  2.1) isoSF_= 1.000;
	else if(fabs(lepeta) <  2.4) isoSF_= 0.999;
  }
  return isoSF_;
}


Float_t getElIdSF(double leppt, double lepeta){//MVA-based ID scale factors (non-triggering): http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/ichep2016_80X//resultsEleID/runBCD/passingMVA80/egammaEffi.txt_egammaPlots.pdf
  Float_t lepIdSF_=1.0;
  if(lepeta < -2.0){
	if(leppt < 30) lepIdSF_ = 0.863;
	else if(leppt < 40) lepIdSF_ = 0.915;
	else if(leppt < 50) lepIdSF_ = 0.930;
	else lepIdSF_ = 0.936;
  }
  else if(lepeta < -1.566){
	if(leppt < 30) lepIdSF_ = 0.871;
	else if(leppt < 40) lepIdSF_ = 0.916;
	else if(leppt < 50) lepIdSF_ = 0.939;
	else lepIdSF_ = 0.950;
  }
  else if(lepeta < -1.4442){
	if(leppt < 30) lepIdSF_ = 0.891;
	else if(leppt < 40) lepIdSF_ = 0.920;
	else if(leppt < 50) lepIdSF_ = 0.953;
	else lepIdSF_ = 0.965;
  }
  else if(lepeta < -0.8){
	if(leppt < 30) lepIdSF_ = 0.923;
	else if(leppt < 40) lepIdSF_ = 0.949;
	else if(leppt < 50) lepIdSF_ = 0.956;
	else lepIdSF_ = 0.957;
  }
  else if(lepeta < 0.0){
	if(leppt < 30) lepIdSF_ = 0.920;
	else if(leppt < 40) lepIdSF_ = 0.941;
	else if(leppt < 50) lepIdSF_ = 0.951;
	else lepIdSF_ = 0.957;
  }
  else if(lepeta < 0.8){
	if(leppt < 30) lepIdSF_ = 0.945;
	else if(leppt < 40) lepIdSF_ = 0.961;
	else if(leppt < 50) lepIdSF_ = 0.965;
	else lepIdSF_ = 0.971;
  }
  else if(lepeta < 1.4442){
	if(leppt < 30) lepIdSF_ = 0.919;
	else if(leppt < 40) lepIdSF_ = 0.945;
	else if(leppt < 50) lepIdSF_ = 0.954;
	else lepIdSF_ = 0.964;
  }
  else if(lepeta < 1.566){
	if(leppt < 30) lepIdSF_ = 0.865;
	else if(leppt < 40) lepIdSF_ = 0.918;
	else if(leppt < 50) lepIdSF_ = 0.932;
	else lepIdSF_ = 0.944;
  }
  else if(lepeta < 2.0){
	if(leppt < 30) lepIdSF_ = 0.866;
	else if(leppt < 40) lepIdSF_ = 0.919;
	else if(leppt < 50) lepIdSF_ = 0.943;
	else lepIdSF_ = 0.958;
  }
  else{
	if(leppt < 30) lepIdSF_ = 0.892;
	else if(leppt < 40) lepIdSF_ = 0.927;
	else if(leppt < 50) lepIdSF_ = 0.943;
	else lepIdSF_ = 0.954;
  }
  return lepIdSF_;
}


Float_t getMuIdSF(double leppt, double lepeta){//Cut-based ID scale factors from POG TWiki 7.6/fb: https://cmsdoc.cern.ch/cms/Physics/muon/ReferenceEfficiencies/Run2016/25ns/proviSFs_7p65/MuonID_Z_RunBCD_prompt80X_7p65.root
  Float_t lepIdSF_=1.0;
  if(fabs(lepeta) < 0.9){
	if(leppt < 30) lepIdSF_ = 0.971;
	else if(leppt < 40) lepIdSF_ = 0.976;
	else if(leppt < 50) lepIdSF_ = 0.976;
	else if(leppt < 60) lepIdSF_ = 0.972;
	else if(leppt < 100) lepIdSF_ = 0.974;
	else lepIdSF_ = 0.988;
  }
  else if(fabs(lepeta) < 1.2){
	if(leppt < 30) lepIdSF_ = 0.967;
	else if(leppt < 40) lepIdSF_ = 0.972;
	else if(leppt < 50) lepIdSF_ = 0.971;
	else if(leppt < 60) lepIdSF_ = 0.971;
	else if(leppt < 100) lepIdSF_ = 0.968;
	else lepIdSF_ = 1.027;
  }
  else if(fabs(lepeta) < 2.1){
	if(leppt < 30) lepIdSF_ = 0.990;
	else if(leppt < 40) lepIdSF_ = 0.990;
	else if(leppt < 50) lepIdSF_ = 0.991;
	else if(leppt < 60) lepIdSF_ = 0.992;
	else if(leppt < 100) lepIdSF_ = 0.990;
	else lepIdSF_ = 1.013;
  }
  else {
	if(leppt < 30) lepIdSF_ = 0.976;
	else if(leppt < 40) lepIdSF_ = 0.974;
	else if(leppt < 50) lepIdSF_ = 0.970;
	else if(leppt < 60) lepIdSF_ = 0.981;
	else if(leppt < 100) lepIdSF_ = 0.975;
	else lepIdSF_ = 0.918;
  }
  return lepIdSF_;
}

#endif
