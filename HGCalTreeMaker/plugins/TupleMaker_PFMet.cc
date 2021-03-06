#include "HGCalAnalysis/HGCalTreeMaker/interface/TupleMaker_PFMet.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/Framework/interface/ESHandle.h"

TupleMaker_PFMet::TupleMaker_PFMet(const edm::ParameterSet& iConfig):
  inputTag    (iConfig.getUntrackedParameter<edm::InputTag>("source")),
  prefix      (iConfig.getUntrackedParameter<std::string>  ("Prefix")),
  suffix      (iConfig.getUntrackedParameter<std::string>  ("Suffix"))
  //bool_SlimmedMET (iConfig.getUntrackedParameter<bool>("SlimmedMET"))
{

  produces < double > (prefix + "MET" + suffix);
  produces < double > (prefix + "METPhi" + suffix);

  //if(bool_PackedCandidate){
  //pflowPackedToken_ = consumes<std::vector<pat::PackedCandidate> >(inputTag);
  //}else{
  pfMETsToken_ = consumes<reco::PFMETCollection> (inputTag);
  //}

  debug=false;}


void TupleMaker_PFMet::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){

  std::unique_ptr<double>              MET                  ( new double        ());
  std::unique_ptr<double>              METPhi               ( new double        ());

  //
  //-----
  //
  
  //if(bool_PackedCandidate){
  //  edm::Handle<std::vector<pat::PackedCandidate> > packedParticleFlow;
  //  iEvent.getByToken(pflowPackedToken_, packedParticleFlow);
  //
  //  for (unsigned int i = 0; i < packedParticleFlow->size(); i++) {
  //    const pat::PackedCandidate& c = packedParticleFlow->at(i);
  //

  //
 
  //    MET->push_back(c.MET());
  //  }
  //    
  //
  //-----
  //
  //} else {
  edm::Handle<reco::PFMETCollection> pfMETs;
  iEvent.getByToken(pfMETsToken_, pfMETs);
  if (!pfMETs.isValid()) return;

  reco::MET met;
  met = pfMETs->front();

  const double MetPt = met.pt();
  const double MetPhi = met.phi();


  *MET    =  MetPt;
  *METPhi =  MetPhi;
 
  //}
    
  //
  //-----
  //



  iEvent.put(move( MET                ) , prefix + "MET"        + suffix );
  iEvent.put(move( METPhi             ) , prefix + "METPhi"        + suffix );

}


