///////////////////////////////////////////////////////////////////
//                                                               //            
// AddMyTask                                                     //
// Author: Erin Gauger                                           //
//                                                               //
///////////////////////////////////////////////////////////////////
class AliAnalysisDataContainer;

AliAnalysisTask* AddTaskTPCCalBeauty(
                                     Double_t centMin=0,
                                     Double_t centMax=10,
                                     Double_t m20Cut = 0.35,
                                     Double_t minEoPCut = 0.9,
                                     Double_t minNSig = -1.0,
                                     Double_t dcaBinSize = 0.002,
                                     Bool_t fillElecSprs = kFALSE,
                                     Bool_t isMC=kFALSE,
                                     Bool_t runStackLoop = kFALSE,
                                     Int_t nClsTPC=80,
                                     TString ContNameExt = " ",
                                     Double_t ptAsso = 0.3,
                                     Double_t minNSigAsso = -3.,
                                     Double_t trkMatch=0.05,
                                     Bool_t applyCentCut = kTRUE,
                                     Bool_t useM02 = kFALSE,
                                     Bool_t pileup1 = kFALSE,
                                     Bool_t pileup2 = kFALSE,
                                     Bool_t shiftEoP = kFALSE,
                                     Double_t maxEoPCut = 1.2,
                                     Bool_t timeCut = kFALSE,
                                     Int_t nTpcCrossRows=0,
                                     Int_t itsChi2 = -100,
                                     Int_t itsLayer = 0,
                                     Double_t zDCA = 3.2)
{
    // get the manager via the static access member
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        return 0x0;
    }
    
    // get the input event handler, again via a static method.
    if (!mgr->GetInputEventHandler()) {
        return 0x0;
    }
    
    ////////////
    //  INT7  //
    ////////////

    //FOR EMCAL CLUSTERS.......................................................................
    
    AliAnalysisTaskTPCCalBeauty* taskBFEemc = new AliAnalysisTaskTPCCalBeauty("bfeemc");
    if(!taskBFEemc) return 0x0;
    // add your task to the manager
    mgr->AddTask(taskBFEemc);
    taskBFEemc->UseLongAxis(useM02);
    taskBFEemc->SetPileUpCut1(pileup1);
    taskBFEemc->SetPileUpCut2(pileup2);
    taskBFEemc->SetEoPShift(shiftEoP);
    taskBFEemc->SetTimeCut(timeCut);
    taskBFEemc->SetITSLayer(itsLayer);
    taskBFEemc->SetTPCnCrossRows(nTpcCrossRows);
    taskBFEemc->SetITSChi2(itsChi2);
    taskBFEemc->SetSSCut(m20Cut);
    taskBFEemc->SetCentSelection(applyCentCut);
    taskBFEemc->SetFillSprs(fillElecSprs);
    taskBFEemc->SetMC(isMC);
    taskBFEemc->SetEoP(minEoPCut);
    taskBFEemc->SetEoPMax(maxEoPCut);
    taskBFEemc->SetNSig(minNSig);
    taskBFEemc->SetNSigAsso(minNSigAsso);
    taskBFEemc->SetTrkMatch(trkMatch);
    taskBFEemc->SetPtAsso(ptAsso);
    taskBFEemc->SetDCABinSize(dcaBinSize);
    taskBFEemc->SetStackLoop(runStackLoop);
    taskBFEemc->SetTPCClus(nClsTPC);
    taskBFEemc->SetDCAzCut(zDCA);
    taskBFEemc->SetClusterTypeEMC(kTRUE);
    taskBFEemc->SetClusterTypeDCAL(kFALSE);
    taskBFEemc->SetCentralitySelection(centMin,centMax);
    taskBFEemc->SelectCollisionCandidates(AliVEvent::kINT7);
    
    // Get the filename and make subfolders
    TString fileNameemc = mgr->AliAnalysisManager::GetCommonFileName();
    TString subContainerNameemc = ContNameExt;
    subContainerNameemc += "_INT7_EMCAL";
    AliAnalysisDataContainer *coutput3emc = mgr->CreateContainer(subContainerNameemc,TList::Class(),AliAnalysisManager::kOutputContainer,fileNameemc.Data());
        
    // connect the manager to task
    mgr->ConnectInput(taskBFEemc,0,mgr->GetCommonInputContainer());
    mgr->ConnectOutput(taskBFEemc,1,coutput3emc);
    
    //FOR DCAL CLUSTERS....................................................................
    
    AliAnalysisTaskTPCCalBeauty* taskBFEdc = new AliAnalysisTaskTPCCalBeauty("bfedc");
    if(!taskBFEdc) return 0x0;
    // add your task to the manager
    mgr->AddTask(taskBFEdc);
    taskBFEdc->UseLongAxis(useM02);
    taskBFEdc->SetPileUpCut1(pileup1);
    taskBFEdc->SetPileUpCut2(pileup2);
    taskBFEdc->SetEoPShift(shiftEoP);
    taskBFEdc->SetTimeCut(timeCut);
    taskBFEdc->SetITSLayer(itsLayer);
    taskBFEdc->SetTPCnCrossRows(nTpcCrossRows);
    taskBFEdc->SetITSChi2(itsChi2);
    taskBFEdc->SetSSCut(m20Cut);
    taskBFEdc->SetCentSelection(applyCentCut);
    taskBFEdc->SetFillSprs(fillElecSprs);
    taskBFEdc->SetMC(isMC);
    taskBFEdc->SetEoP(minEoPCut);
    taskBFEdc->SetEoPMax(maxEoPCut);
    taskBFEdc->SetNSig(minNSig);
    taskBFEdc->SetNSigAsso(minNSigAsso);
    taskBFEdc->SetTrkMatch(trkMatch);
    taskBFEdc->SetPtAsso(ptAsso);
    taskBFEdc->SetDCABinSize(dcaBinSize);
    taskBFEdc->SetStackLoop(runStackLoop);
    taskBFEdc->SetTPCClus(nClsTPC);
    taskBFEdc->SetDCAzCut(zDCA);
    taskBFEdc->SetClusterTypeEMC(kFALSE);
    taskBFEdc->SetClusterTypeDCAL(kTRUE);
    taskBFEdc->SetCentralitySelection(centMin,centMax);
    taskBFEdc->SelectCollisionCandidates(AliVEvent::kINT7);
    
    // Get the filename and make subfolders
    TString fileNamedc = mgr->AliAnalysisManager::GetCommonFileName();
    TString subContainerNamedc = ContNameExt;
    subContainerNamedc += "_INT7_DCAL";
    AliAnalysisDataContainer *coutput3dc = mgr->CreateContainer(subContainerNamedc,TList::Class(),AliAnalysisManager::kOutputContainer,fileNamedc.Data());
        
    // connect the manager to task
    mgr->ConnectInput(taskBFEdc,0,mgr->GetCommonInputContainer());
    mgr->ConnectOutput(taskBFEdc,1,coutput3dc);
   
    /*
    //////////
    //  MB  //
    //////////
    AliAnalysisTaskTPCCalBeauty* taskBFEmb = new AliAnalysisTaskTPCCalBeauty("bfemb");
    if(!taskBFEmb) return 0x0;
    // add your task to the manager
    mgr->AddTask(taskBFEmb);
    taskBFEmb->SetClusterTypeEMC(ClsTypeEMC);
    taskBFEmb->SetClusterTypeDCAL(ClsTypeDCAL);
    taskBFEmb->SetCentralitySelection(centMin,centMax);
    taskBFEmb->SelectCollisionCandidates(AliVEvent::kMB);
    
    // Get the filename and make subfolders
    TString fileName02 = mgr->AliAnalysisManager::GetCommonFileName();
    TString subContainerName02 = ContNameExt;
    subContainerName02 += "BFE_PbPb_MB";
    AliAnalysisDataContainer *coutput2 = mgr->CreateContainer(subContainerName02,TList::Class(),AliAnalysisManager::kOutputContainer,fileName02.Data());
    
    // connect the manager to task
    mgr->ConnectInput(taskBFEmb,0,mgr->GetCommonInputContainer());
    mgr->ConnectOutput(taskBFEmb,1,coutput2);
    */
    
    //if statement so trigger directories aren't made in MC
    
    if (isMC==kFALSE) {
        ///////////////
        //  EGA EG1  //
        ///////////////
        
        //EMCAL TRIGGERED, EMCAL CLUSTERS.........................................................
        
        
        AliAnalysisTaskTPCCalBeauty* taskBFEeg01emc = new AliAnalysisTaskTPCCalBeauty("bfeeg01emc");
        if(!taskBFEeg01emc) return 0x0;
        // add your task to the manager
        mgr->AddTask(taskBFEeg01emc);
        taskBFEeg01emc->UseLongAxis(useM02);
        taskBFEeg01emc->SetPileUpCut1(pileup1);
        taskBFEeg01emc->SetPileUpCut2(pileup2);
        taskBFEeg01emc->SetEoPShift(shiftEoP);
        taskBFEeg01emc->SetTimeCut(timeCut);
        taskBFEeg01emc->SetITSLayer(itsLayer);
        taskBFEeg01emc->SetTPCnCrossRows(nTpcCrossRows);
        taskBFEeg01emc->SetITSChi2(itsChi2);
        taskBFEeg01emc->SetSSCut(m20Cut);
        taskBFEeg01emc->SetCentSelection(applyCentCut);
        taskBFEeg01emc->SetFillSprs(fillElecSprs);
        taskBFEeg01emc->SetMC(isMC);
        taskBFEeg01emc->SetEoP(minEoPCut);
        taskBFEeg01emc->SetEoPMax(maxEoPCut);
        taskBFEeg01emc->SetNSig(minNSig);
        taskBFEeg01emc->SetNSigAsso(minNSigAsso);
        taskBFEeg01emc->SetTrkMatch(trkMatch);
        taskBFEeg01emc->SetPtAsso(ptAsso);
        taskBFEeg01emc->SetDCABinSize(dcaBinSize);
        taskBFEeg01emc->SetStackLoop(runStackLoop);
        taskBFEeg01emc->SetTPCClus(nClsTPC);
        taskBFEeg01emc->SetDCAzCut(zDCA);
        taskBFEeg01emc->SetClusterTypeEMC(kTRUE);
        taskBFEeg01emc->SetClusterTypeDCAL(kFALSE);
        taskBFEeg01emc->SetCentralitySelection(centMin,centMax);
        taskBFEeg01emc->SetEMCalTriggerEG1(kTRUE);
        taskBFEeg01emc->SetEMCalTriggerDG1(kFALSE);
        
        // Get the filename and make subfolders
        TString fileNameEG01emc = mgr->AliAnalysisManager::GetCommonFileName();
        TString subContainerNameEG01emc = ContNameExt;
        subContainerNameEG01emc += "_TrigEG1_EMCAL";
        AliAnalysisDataContainer *coutputEG01emc = mgr->CreateContainer(subContainerNameEG01emc,TList::Class(),AliAnalysisManager::kOutputContainer,fileNameEG01emc.Data());
        
        // connect the manager to task
        mgr->ConnectInput(taskBFEeg01emc,0,mgr->GetCommonInputContainer());
        mgr->ConnectOutput(taskBFEeg01emc,1,coutputEG01emc);
        
        //EMCAL TRIGGERED, DCAL CLUSTERS..........................................................
        
        /*AliAnalysisTaskTPCCalBeauty* taskBFEeg01dc = new AliAnalysisTaskTPCCalBeauty("bfeeg01dc");
         if(!taskBFEeg01dc) return 0x0;
         // add your task to the manager
         mgr->AddTask(taskBFEeg01dc);
         taskBFEeg01dc->SetClusterTypeEMC(kFALSE);
         taskBFEeg01dc->SetClusterTypeDCAL(kTRUE);
         taskBFEeg01dc->SetCentralitySelection(centMin,centMax);
         taskBFEeg01dc->SetEMCalTriggerEG1(kTRUE);
         taskBFEeg01emc->SetEMCalTriggerDG1(kFALSE);
         
         // Get the filename and make subfolders
         TString fileNameEG01dc = mgr->AliAnalysisManager::GetCommonFileName();
         TString subContainerNameEG01dc = ContNameExt;
         subContainerNameEG01dc += "BFE_PbPb_TrigEG1_DCClus";
         AliAnalysisDataContainer *coutputEG01dc = mgr->CreateContainer(subContainerNameEG01dc,TList::Class(),AliAnalysisManager::kOutputContainer,fileNameEG01dc.Data());
         
         // connect the manager to task
         mgr->ConnectInput(taskBFEeg01dc,0,mgr->GetCommonInputContainer());
         mgr->ConnectOutput(taskBFEeg01dc,1,coutputEG01dc);
         
         //DCAL TRIGGERED, EMCAL CLUSTERS.........................................................
         
         AliAnalysisTaskTPCCalBeauty* taskBFEdg01emc = new AliAnalysisTaskTPCCalBeauty("bfedg01emc");
         if(!taskBFEdg01emc) return 0x0;
         // add your task to the manager
         mgr->AddTask(taskBFEdg01emc);
         taskBFEdg01emc->SetClusterTypeEMC(kTRUE);
         taskBFEdg01emc->SetClusterTypeDCAL(kFALSE);
         taskBFEdg01emc->SetCentralitySelection(centMin,centMax);
         taskBFEdg01emc->SetEMCalTriggerEG1(kFALSE);
         taskBFEdg01emc->SetEMCalTriggerDG1(kTRUE);
         
         // Get the filename and make subfolders
         TString fileNameDG01emc = mgr->AliAnalysisManager::GetCommonFileName();
         TString subContainerNameDG01emc = ContNameExt;
         subContainerNameDG01emc += "BFE_PbPb_TrigDG1_EMCClus";
         AliAnalysisDataContainer *coutputDG01emc = mgr->CreateContainer(subContainerNameDG01emc,TList::Class(),AliAnalysisManager::kOutputContainer,fileNameDG01emc.Data());
         
         // connect the manager to task
         mgr->ConnectInput(taskBFEdg01emc,0,mgr->GetCommonInputContainer());
         mgr->ConnectOutput(taskBFEdg01emc,1,coutputDG01emc);
         */
        
        //DCAL TRIGGERED, DCAL CLUSTERS............................................................
        
        AliAnalysisTaskTPCCalBeauty* taskBFEdg01dc = new AliAnalysisTaskTPCCalBeauty("bfedg01dc");
        if(!taskBFEdg01dc) return 0x0;
        // add your task to the manager
        mgr->AddTask(taskBFEdg01dc);
        taskBFEdg01dc->UseLongAxis(useM02);
        taskBFEdg01dc->SetPileUpCut1(pileup1);
        taskBFEdg01dc->SetPileUpCut2(pileup2);
        taskBFEdg01dc->SetEoPShift(shiftEoP);
        taskBFEdg01dc->SetTimeCut(timeCut);
        taskBFEdg01dc->SetITSLayer(itsLayer);
        taskBFEdg01dc->SetTPCnCrossRows(nTpcCrossRows);
        taskBFEdg01dc->SetITSChi2(itsChi2);
        taskBFEdg01dc->SetSSCut(m20Cut);
        taskBFEdg01dc->SetCentSelection(applyCentCut);
        taskBFEdg01dc->SetFillSprs(fillElecSprs);
        taskBFEdg01dc->SetMC(isMC);
        taskBFEdg01dc->SetEoP(minEoPCut);
        taskBFEdg01dc->SetEoPMax(maxEoPCut);
        taskBFEdg01dc->SetNSig(minNSig);
        taskBFEdg01dc->SetNSigAsso(minNSigAsso);
        taskBFEdg01dc->SetTrkMatch(trkMatch);
        taskBFEdg01dc->SetPtAsso(ptAsso);
        taskBFEdg01dc->SetDCABinSize(dcaBinSize);
        taskBFEdg01dc->SetStackLoop(runStackLoop);
        taskBFEdg01dc->SetTPCClus(nClsTPC);
        taskBFEdg01dc->SetDCAzCut(zDCA);
        taskBFEdg01dc->SetClusterTypeEMC(kFALSE);
        taskBFEdg01dc->SetClusterTypeDCAL(kTRUE);
        taskBFEdg01dc->SetCentralitySelection(centMin,centMax);
        taskBFEdg01dc->SetEMCalTriggerEG1(kFALSE);
        taskBFEdg01dc->SetEMCalTriggerDG1(kTRUE);
        
        // Get the filename and make subfolders
        TString fileNameDG01dc = mgr->AliAnalysisManager::GetCommonFileName();
        TString subContainerNameDG01dc = ContNameExt;
        subContainerNameDG01dc += "_TrigDG1_DCAL";
        AliAnalysisDataContainer *coutputDG01dc = mgr->CreateContainer(subContainerNameDG01dc,TList::Class(),AliAnalysisManager::kOutputContainer,fileNameDG01dc.Data());
        
        // connect the manager to task
        mgr->ConnectInput(taskBFEdg01dc,0,mgr->GetCommonInputContainer());
        mgr->ConnectOutput(taskBFEdg01dc,1,coutputDG01dc);
    }
    
    return NULL;
}
