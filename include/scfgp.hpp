#ifndef _scfgp_hpp
#define _scfgp_hpp 1

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <bazinga.hpp>

class scfgp
{
  /* vector consists of config files */
  std::vector<std::string> cfgFile;

  template<class T>
    struct parameterPair {
      T value;
      T* variable;
    parameterPair( T _value, T*_variable ) : value(_value), variable(_variable) { }
    };

  template<class T>
    struct TMap {
      typedef std::map<std::string,T> Type;
    };
  
  template<class T>
    struct TMapPair {
      typedef std::map<std::string,parameterPair<T> > Type;
    };

  template<class T>
    T TGetTMap( );

  TMap<int>::Type paramsInt;
  TMap<double>::Type paramsDouble;
  TMap<std::string>::Type paramsString;

  TMapPair<int>::Type paramsIntStruct;
  TMapPair<double>::Type paramsDoubleStruct;
  TMapPair<std::string>::Type paramsStringStruct;

  TMap<std::string>::Type paramsInConfigFiles; /* values in config files */

  template<class T>
  void updateTypeRequests( );
  
  template<class T>
  void updateTypeAddedParameters( );
  
  template<class T>
  bool checkIfAlreadyAdded( std::string _name );

  template<class T>
  bool checkIfAlreadyRequested( std::string _name );
  
  template<class T>
  void listTypeAddedParameters( );

  template<class T>
  void listTypeRequestedParameters( );

 public:
  scfgp( );
  ~scfgp( );

  void addConfigFile( std::string _cfgFile );
  void listConfigFiles(  );

  void listAddedParameters( );  
  void listRequestedParameters( );  

  template<class T>
  void add( std::string _name, T _value, bool verbose=false );
  
  template<class T>
  void request( std::string _name, T _value, T* _variable, bool verbose=false );
  
  template< class T>
  T get( std::string _name );

  template< class T>
  void modify( std::string _name, T _value, bool verbose=false );
  
  bool updateAddedParameters( );
  bool updateRequests( );
};

template <class T>
bool scfgp::checkIfAlreadyAdded( std::string _name ) {
  bool return_value = true;
  for( typename TMap<T>::Type::iterator ii=( TGetTMap< typename TMap<T>::Type& >( ) ).begin( ); ii!=( TGetTMap< typename TMap<T>::Type& >( ) ).end(); ++ii )
    if( _name == (*ii).first )
      return_value = false;
  return return_value; }

template <class T>
bool scfgp::checkIfAlreadyRequested( std::string _name ) {
  bool return_value = true;
  for( typename TMapPair<T>::Type::iterator ii=( TGetTMap< typename TMapPair<T>::Type& >( ) ).begin( ); ii!=( TGetTMap< typename TMapPair<T>::Type& >( ) ).end(); ++ii )
    if( _name == (*ii).first )
      return_value = false;
  return return_value; }

template<class T>
void scfgp::request( std::string _name, T _value, T* _variable, bool verbose ) {
  //  if( !checkIfAlreadyRequested<T>( _name ) ) { bazinga::warning("SCFGP",_name,"already requested."); }
  if( verbose ) { 
    bazinga::debug("SCFGP","Requesting parameter",_name);
    bazinga::debug("SCFGP","Default value",_value); }
  ( TGetTMap< typename TMapPair<T>::Type& >( )  ).insert(std::make_pair(_name, parameterPair<T>(_value,_variable))); 
}

template<class T>
void scfgp::add( std::string _name, T _value, bool verbose ) {
  if( checkIfAlreadyAdded<T>( _name ) ) {
    if( verbose ) { 
      bazinga::debug("SCFGP","Adding parameter",_name);
      bazinga::debug("SCFGP","Default value",_value); }
    ( TGetTMap< typename TMap<T>::Type& >( ) ).insert(std::make_pair(_name, _value)); }
  else { bazinga::warning("SCFGP",_name,"already added. Skip."); }
}

template<class T>
void scfgp::modify( std::string _name, T _value, bool verbose ) {
  if( !checkIfAlreadyAdded<T>( _name ) ) {
    if( verbose ) { 
      bazinga::debug("SCFGP","Modifying parameter",_name );
      bazinga::debug("SCFGP","New value",_value); }
    for( typename TMap<T>::Type::iterator ii=( TGetTMap< typename TMap<T>::Type& >( ) ).begin(); ii!=( TGetTMap< typename TMap<T>::Type& >( ) ).end(); ++ii ) if( _name == (*ii).first ) { (*ii).second = _value; }
  }
  else { bazinga::warning("SCFGP",_name,"has not been added. Skip."); }
}

template< class T>
T scfgp::get( std::string _name ) {
  for( typename TMap<T>::Type::iterator ii=( TGetTMap< typename TMap<T>::Type& >( ) ).begin(); ii!=( TGetTMap< typename TMap<T>::Type& >( ) ).end(); ++ii ) if( _name == (*ii).first ) { return  (*ii).second; } 
  bazinga::error("SCFGP",_name,"does not exist. Quit."); }

#endif /* _scfgp_hpp */
