AliAnalysisTaskSE* AddTaskNanoAODFemtoDreamPion(
    bool isMC=false, float fSpherDown=0.7, float fdPhidEta=0.04,
    TString CentEst="kInt7")
{
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();

  if (!mgr)
  {
    printf("No analysis manager to connect to!\n");
    return nullptr;
  }
  if (!mgr->GetInputEventHandler()) {
    printf("This task requires an input event handler!\n");
    return nullptr;
  }

  AliFemtoDreamEventCuts *evtCuts=
      AliFemtoDreamEventCuts::StandardCutsRun2();
  //This sets the method we want to use to clean up events with negative or too
  //low multiplicity. Usually you use the matching multiplicity estiamtor in your
  //event collection
  // Not mention in AN oder Indico
  evtCuts->CleanUpMult(false,false,false,true);
  evtCuts->SetZVtxPosition(-10., 10.);
  // Only use those events where more than two primary tracks with |eta|<0.8 and pT>0.5 GeV/c see AN
  evtCuts->SetSphericityCuts(fSpherDown, 1.0);

  //Track Cuts are defined here
  //positive pions
  //Track Cuts tuned according to:
  //https://alice-notes.web.cern.ch/system/files/notes/analysis/911/2019-05-06-NotepPP_Spher_ver3.pdf
  //+ most recent Indico-Präsentation:
  //https://indico.cern.ch/event/761862/contributions/3594774/attachments/1922911/3181566/pipi_KK_Sep2019.pdf
  AliFemtoDreamTrackCuts *fTrackCutsPosPion=new AliFemtoDreamTrackCuts();
  fTrackCutsPosPion->SetIsMonteCarlo(isMC);
  fTrackCutsPosPion->SetCutCharge(1);
  fTrackCutsPosPion->SetFilterBit(128); // Indico Filterbit 7
  fTrackCutsPosPion->SetPtRange(0.14, 4.0);
  fTrackCutsPosPion->SetEtaRange(-0.8, 0.8);
  fTrackCutsPosPion->SetNClsTPC(80);
  // Not mention in AN oder Indico
  fTrackCutsPosPion->SetDCAReCalculation(true);//Get the dca from the PropagateToVetex
  fTrackCutsPosPion->SetDCAVtxZ(0.3);
  fTrackCutsPosPion->SetDCAVtxXY(0.3);
  // Cut on avrg. separation in TPC: <Dr> < 12 cm (10 cm, 3 cm); Share quality < 1.0; share fraction < 0.05
  fTrackCutsPosPion->SetCutSharedCls(true);
  fTrackCutsPosPion->SetNClsTPC(80); // In Indico + additional Chi²/NDF <4
  fTrackCutsPosPion->SetPID(AliPID::kPion, 0.);
  fTrackCutsPosPion->SetRejLowPtPionsTOF(false);
  fTrackCutsPosPion->SetChi2Cut(0., 4.0);
  //this checks if the sigma of the wanted hypothesis is the smallest, and if
  //another particle has a smaller sigma, the track is rejected.
  // Not mention in AN oder Indico
  //fTrackCutsPosPion->SetCutSmallestSig(true);

  //The same things for negative pions
  AliFemtoDreamTrackCuts *fTrackCutsNegPion=new AliFemtoDreamTrackCuts();
  fTrackCutsNegPion->SetIsMonteCarlo(isMC);
  fTrackCutsNegPion->SetCutCharge(-1);
  fTrackCutsNegPion->SetFilterBit(128);
  fTrackCutsNegPion->SetPtRange(0.14, 4.0);
  fTrackCutsNegPion->SetEtaRange(-0.8, 0.8);
  fTrackCutsNegPion->SetNClsTPC(80);
  fTrackCutsNegPion->SetDCAReCalculation(true);
  fTrackCutsNegPion->SetDCAVtxZ(0.3);
  fTrackCutsNegPion->SetDCAVtxXY(0.3);
  fTrackCutsNegPion->SetCutSharedCls(true);
  fTrackCutsNegPion->SetNClsTPC(80);
  fTrackCutsNegPion->SetPID(AliPID::kPion, 0.);
  fTrackCutsNegPion->SetRejLowPtPionsTOF(false);
  fTrackCutsNegPion->SetChi2Cut(0., 4.0);
  //fTrackCutsNegPion->SetCutSmallestSig(true);

  //Now we define stuff we want for our Particle collection
  //Thanks, CINT - will not compile due to an illegal constructor
  //std::vector<int> PDGParticles ={2212,2212,3122,3122,3312,3312};
  //First we need to tell him about the particles we mix, from the
  //PDG code the mass is obtained.
  //Order must mymik the order as the particles are added to the PairCleaner
  std::vector<int> PDGParticles;
  PDGParticles.push_back(211); // pi+
  PDGParticles.push_back(-211); // pi-

  //We need to set the ZVtx bins
  std::vector<float> ZVtxBins;
  ZVtxBins.push_back(-10);
  ZVtxBins.push_back(-8);
  ZVtxBins.push_back(-6);
  ZVtxBins.push_back(-4);
  ZVtxBins.push_back(-2);
  ZVtxBins.push_back(0);
  ZVtxBins.push_back(2);
  ZVtxBins.push_back(4);
  ZVtxBins.push_back(6);
  ZVtxBins.push_back(8);
  ZVtxBins.push_back(10);
  //The Multiplicity bins are set here
  std::vector<int> MultBins;
  MultBins.push_back(0);
  MultBins.push_back(14);
  MultBins.push_back(22);
  MultBins.push_back(31);
  MultBins.push_back(55);

  //The next part is for the result histograms. The order of hist. is the following:
  //                Particle1     Particle2
  //Particle 1       Hist 1         Hist2
  //
  //Particle 2                      Hist3
  //The same way the values for binning, minimum and maximum k* range have to be set!
  //Number of bins
  std::vector<int> NBins;
  NBins.push_back(750);
  NBins.push_back(750);
  NBins.push_back(750);
  std::vector<float> kMin;
  //minimum k* value
  kMin.push_back(0.);
  kMin.push_back(0.);
  kMin.push_back(0.);
  //maximum k* value
  std::vector<float> kMax;
  kMax.push_back(3.);
  kMax.push_back(3.);
  kMax.push_back(3.);
  //pair rejection
  std::vector<bool> closeRejection;
  closeRejection.push_back(true); // pi+ pi+
  closeRejection.push_back(false); // pi+ pi- 
  closeRejection.push_back(true); // pi- pi-
  //QA plots for tracks
  std::vector<int> pairQA;
  pairQA.push_back(11); // pi+ pi+
  pairQA.push_back(11); // pi+ pi-
  pairQA.push_back(11); // pi- pi-

  //To put all this into the task we add it to our collection config object in
  //the following way:
  AliFemtoDreamCollConfig *config=new AliFemtoDreamCollConfig("Femto","Femto");
  config->SetZBins(ZVtxBins);
  config->SetMultBins(MultBins);
  //Do you want to have an explicit binning of the correlation function for each multiplicity
  //bin set above?
  config->SetMultBinning(true);
  config->SetPDGCodes(PDGParticles);
  config->SetNBinsHist(NBins);
  config->SetMinKRel(kMin);
  config->SetMaxKRel(kMax);
  config->SetClosePairRejection(closeRejection);
  config->SetDeltaEtaMax(fdPhidEta); // https://alice-notes.web.cern.ch/system/files/notes/analysis/616/2018-08-10-NotepPb.pdf
  config->SetDeltaPhiMax(fdPhidEta);
  config->SetExtendedQAPairs(pairQA);
  //Here we set the mixing depth.
  config->SetMixingDepth(10); // AN
  config->SetkTBinning(true);
  config->SetmTBinning(true);
  config->SetMinimalBookingME(false);
  
  if (isMC) {
      config->SetMomentumResolution(true);
    } else {
      std::cout << "You are trying to request the Momentum Resolution without MC Info; fix it wont work! \n";
    }
    if (isMC) {
      config->SetPhiEtaBinnign(true);
    } else {
      std::cout << "You are trying to request the Eta Phi Plots without MC Info; fix it wont work! \n";
    }
  
  //now we create the task
  AliAnalysisTaskNanoAODFemtoDreamPion *task=
      new AliAnalysisTaskNanoAODFemtoDreamPion("NanoAODFemtoDreamPion",isMC);
  //THIS IS VERY IMPORTANT ELSE YOU DONT PROCESS ANY EVENTS
  //kINT7 == Minimum bias
  //kHighMultV0 high multiplicity triggered by the V0 detector
  if(CentEst == "kInt7"){
	task->SetTrigger(AliVEvent::kINT7);
    task->SelectCollisionCandidates(AliVEvent::kINT7);
    std::cout << "Added kINT7 Trigger \n";
  } else if (CentEst == "kHM") {
    task->SelectCollisionCandidates(AliVEvent::kHighMultV0);
    std::cout << "Added kHighMultV0 Trigger \n";
  }else{
    std::cout << "=====================================================================" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cout << "Centrality Estimator not set, fix it else your Results will be empty!" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cout << "=====================================================================" << std::endl;
  }

  //Throw all our settings to the task
  task->SetEventCuts(evtCuts);
  task->SetTrackCutsPosPion(fTrackCutsPosPion);
  task->SetTrackCutsNegPion(fTrackCutsNegPion);
  task->SetCollectionConfig(config);

  mgr->AddTask(task);

  TString file = AliAnalysisManager::GetCommonFileName();

  AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();

  mgr->ConnectInput(task, 0, cinput);

  AliAnalysisDataContainer *coutputQA;
  TString QAName = Form("MyTask");
  coutputQA = mgr->CreateContainer(
      QAName.Data(), TList::Class(),
      AliAnalysisManager::kOutputContainer,
      Form("%s:%s", file.Data(), QAName.Data()));
  mgr->ConnectOutput(task, 1, coutputQA);

  return task;
}

