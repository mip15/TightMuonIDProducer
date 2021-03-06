// -*- C++ -*-
//
// Package:    TightMuonIDProducer/TightMuonIDProducer
// Class:      TightMuonIDProducer
// 
/**\class TightMuonIDProducer TightMuonIDProducer.cc TightMuonIDProducer/TightMuonIDProducer/plugins/TightMuonIDProducer.cc

   Description: [one line class summary]

   Implementation:
   [Notes on implementation]
*/
//
// Original Author:  Mirena Ivova Rikova
//         Created:  Mon, 12 Jan 2015 17:40:23 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"



//
// class declaration
//

class TightMuonIDProducer : public edm::EDProducer {
public:
  explicit TightMuonIDProducer(const edm::ParameterSet&);
  ~TightMuonIDProducer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() override;
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
      
  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

  // ----------member data ---------------------------
  // input tags
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  edm::EDGetTokenT<edm::View<pat::Muon> > muonsToken_;

  // define collections
  typedef std::vector<pat::Muon> TightMuons;


};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
TightMuonIDProducer::TightMuonIDProducer(const edm::ParameterSet& iConfig):
  vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
  muonsToken_(consumes<edm::View<pat::Muon> >(iConfig.getParameter<edm::InputTag>("muons")))
{
  produces<TightMuons>("TightMuons");

  //register your products
  /* Examples
     produces<ExampleData2>();

     //if do put with a label
     produces<ExampleData2>("label");
 
     //if you want to put into the Run
     produces<ExampleData2,InRun>();
  */
  //now do what ever other initialization is needed
  
}


TightMuonIDProducer::~TightMuonIDProducer()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TightMuonIDProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;

  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(vtxToken_, vertices);
  if (vertices->empty()) return; // skip the event if no PV found
  const reco::Vertex &PV = vertices->front();
   
  // get muon collection
  edm::Handle<edm::View<pat::Muon> > muons;
  iEvent.getByToken(muonsToken_,muons);

  std::unique_ptr<TightMuons> tightmuons( new TightMuons);


  for(uint k=0; k<muons->size(); k++){
    if(muons->at(k).isTightMuon(PV)) tightmuons->push_back(muons->at(k));   
  }
  

  // and save the vectors
  iEvent.put( std::move(tightmuons), "TightMuons" );

  /* This is an event example
  //Read 'ExampleData' from the Event
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);

  //Use the ExampleData to create an ExampleData2 which 
  // is put into the Event
  std::unique_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
  iEvent.put(std::move(pOut));
  */

  /* this is an EventSetup example
  //Read SetupData from the SetupRecord in the EventSetup
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
  */
 
}

// ------------ method called once each job just before starting event loop  ------------
void 
TightMuonIDProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TightMuonIDProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
  void
  TightMuonIDProducer::beginRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
  void
  TightMuonIDProducer::endRun(edm::Run const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
  void
  TightMuonIDProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
  void
  TightMuonIDProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
  {
  }
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TightMuonIDProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TightMuonIDProducer);
