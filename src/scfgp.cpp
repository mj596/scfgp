#include <bazinga.hpp>
#include "scfgp.hpp"

scfgp::scfgp( ) {
  /* clean parameter std::maps */
  paramsInt.clear();  
  paramsDouble.clear();  
  paramsString.clear();
  paramsIntStruct.clear();
  paramsDoubleStruct.clear();
  paramsStringStruct.clear(); }

scfgp::~scfgp( ) { }

template<class T>
T scfgp::TGetTMap( ) { }

template<> scfgp::TMapPair<int>::Type& scfgp::TGetTMap< scfgp::TMapPair<int>::Type& >( ) { return paramsIntStruct; }
template<> scfgp::TMapPair<double>::Type& scfgp::TGetTMap< scfgp::TMapPair<double>::Type& >( ) { return paramsDoubleStruct; }
template<> scfgp::TMapPair<std::string>::Type& scfgp::TGetTMap< scfgp::TMapPair<std::string>::Type& >( ) { return paramsStringStruct; }
template<> scfgp::TMap<int>::Type& scfgp::TGetTMap< scfgp::TMap<int>::Type& >( ) { return paramsInt; }
template<> scfgp::TMap<double>::Type& scfgp::TGetTMap< scfgp::TMap<double>::Type& >( ) { return paramsDouble; }
template<> scfgp::TMap<std::string>::Type& scfgp::TGetTMap< scfgp::TMap<std::string>::Type& >( ) { return paramsString; }

void scfgp::addConfigFile( std::string _cfgFile ) {
  std::ifstream configFile( _cfgFile.c_str() );
  if( !configFile ) {
    bazinga::error("SCFGP","Error opening input file. Does it exist? Quit"); }
  else {
    bazinga::info("SCFGP","Adding",_cfgFile,"to config files list");
    cfgFile.push_back( _cfgFile ); }
}

void scfgp::listConfigFiles( ) {
  bazinga::print_header();
  bazinga::info("SCFGP","Available config files:");
  for( std::vector<std::string>::const_iterator i = cfgFile.begin(); i != cfgFile.end(); ++i) { bazinga::info("SCFGP",(*i)); }
  bazinga::print_header(); }

template<class T>
void scfgp::updateTypeRequests( ) {
  bool parameter_found = false;
  for( typename TMapPair<T>::Type::iterator ii=( TGetTMap< typename TMapPair<T>::Type& >( ) ).begin(); ii!=( TGetTMap< typename TMapPair<T>::Type& >( ) ).end(); ++ii ) {
    parameter_found = false;
    for( TMap<std::string>::Type::iterator jj=paramsInConfigFiles.begin(); jj!=paramsInConfigFiles.end(); ++jj ) {
      if( (*ii).first == (*jj).first ) {
	*( (*ii).second.variable ) = boost::lexical_cast<T>( (*jj).second );
	parameter_found = true;
	break; }
    }
    if( !parameter_found ) { *( (*ii).second.variable ) = (*ii).second.value; }
  }
  ( TGetTMap< typename TMapPair<T>::Type& >( ) ).clear( );
}

template<class T>
void scfgp::updateTypeAddedParameters( ) {
  bool parameter_found = false;
  for( typename TMap<T>::Type::iterator ii=( TGetTMap< typename TMap<T>::Type& >( ) ).begin(); ii!=( TGetTMap< typename TMap<T>::Type& >( ) ).end(); ++ii ) {
    parameter_found = false;
    for( TMap<std::string>::Type::iterator jj=paramsInConfigFiles.begin(); jj!=paramsInConfigFiles.end(); ++jj ) {
      if( (*ii).first == (*jj).first ) {
	(*ii).second = boost::lexical_cast<T>( (*jj).second );
	parameter_found = true;
	break; }
    }
  }
}

bool scfgp::updateRequests( ) {
  const std::string _comment = "#";
  const std::string _end = "END";
  
  /* go through all config files */
  for( std::vector<std::string>::const_iterator i = cfgFile.begin(); i != cfgFile.end(); ++i) {
    bazinga::info("SCFGP","Reading",*i);
    std::ifstream configFile( (*i).c_str() );
    /* Always test the file open. */
    if( !configFile ) { bazinga::error("SCFGP","Error opening input file. Does it exist? Quit"); }
    else {
      int inFileParams = 0;
      while( !configFile.eof() ) {
 	std::string data;
 	getline( configFile, data, '\n' );
 	std::vector<std::string> strs;
 	boost::split(strs, data, boost::is_any_of("\t "));
	
 	if( strs[0] == "END" ) { break; }
 	if( strs[0] != "#" ) { paramsInConfigFiles.insert(std::make_pair(strs[0], strs[1])); }
      }
    }
    configFile.close(); }
  
  updateTypeRequests<int>( );
  updateTypeRequests<double>( );
  updateTypeRequests<std::string>( );
  paramsInConfigFiles.clear( );
}

bool scfgp::updateAddedParameters( ) {
  const std::string _comment = "#";
  const std::string _end = "END";
  
  /* go through all config files */
  for( std::vector<std::string>::const_iterator i = cfgFile.begin(); i != cfgFile.end(); ++i) {
    bazinga::info("SCFGP","Reading",*i);
    std::ifstream configFile( (*i).c_str() );
    /* Always test the file open. */
    if( !configFile ) { bazinga::error("SCFGP","Error opening input file. Does it exist? Quit"); }
    else {
      int inFileParams = 0;
      while( !configFile.eof() ) {
	std::string data;
	getline( configFile, data, '\n' );
	std::vector<std::string> strs;
	boost::split(strs, data, boost::is_any_of("\t "));
	
	if( strs[0] == "END" ) { break; }
	if( strs[0] != "#" ) { paramsInConfigFiles.insert(std::make_pair(strs[0], strs[1])); }
      }
    }
  }

  updateTypeAddedParameters<int>( );
  updateTypeAddedParameters<double>( );
  updateTypeAddedParameters<std::string>( );
  paramsInConfigFiles.clear( );
}

template<class T>
void scfgp::listTypeAddedParameters( ) {
  for( typename TMap<T>::Type::iterator ii=( TGetTMap< typename TMap<T>::Type& >( ) ).begin(); ii!=( TGetTMap< typename TMap<T>::Type& >( ) ).end(); ++ii ) { bazinga::print_info((*ii).first,(*ii).second); }
}

template<class T>
void scfgp::listTypeRequestedParameters( ) {
  for( typename TMapPair<T>::Type::iterator ii=( TGetTMap< typename TMapPair<T>::Type& >( ) ).begin(); ii!=( TGetTMap< typename TMapPair<T>::Type& >( ) ).end(); ++ii ) { bazinga::print_info((*ii).first,(*ii).second.value); }
}

void scfgp::listAddedParameters( ) {
  bazinga::print_header();
  bazinga::info("SCFGP","Available parameters:");
  bazinga::info("SCFGP","Integer parameters");
  listTypeAddedParameters<int>( );
  bazinga::info("SCFGP","Double parameters");
  listTypeAddedParameters<double>( );
  bazinga::info("SCFGP","String parameters");
  listTypeAddedParameters<std::string>( );
  bazinga::print_header();
}

void scfgp::listRequestedParameters( ) {
  bazinga::print_header();
  bazinga::info("SCFGP","Available parameters:");
  bazinga::info("SCFGP","Integer parameters");
  listTypeRequestedParameters<int>( );
  bazinga::info("SCFGP","Double parameters");
  listTypeRequestedParameters<double>( );
  bazinga::info("SCFGP","String parameters");
  listTypeRequestedParameters<std::string>( );
  bazinga::print_header();
}
