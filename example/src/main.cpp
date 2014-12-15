#include <iostream>
#include <scfgp.hpp>

int main(int argc, char *argv[])
{
  /* initialize scfgp object */
  scfgp *config = new scfgp( );

  /* add configuration files to be read */
  config -> addConfigFile( "config/test1.cfg" );
  config -> addConfigFile( "config/test2.cfg" );

  /* show these files */
  config -> listConfigFiles( );

  /* ----------------------------------------------------------------------------------------- */
  /* Option 1:
     Parameters and their values are being stored in the scfgp object itself. To access a parameter you read values from scfgp object */
  
  /* Add parameters that will be used with their default values in case they are not found in configuration files */
  config -> add<int>("addInt",15,true);
  config -> add<double>("addDouble",25.0,true);
  config -> add<std::string>("addString","None",true);

  /* show which parameters were added */
  config -> listAddedParameters( );

  /* print values of these parameters before reading the configuration files */
  std::cout << " addInt: " << config -> get<int>("addInt") << std::endl;
  std::cout << " addDouble: " << config -> get<double>("addDouble") << std::endl;
  std::cout << " addString: " << config -> get<std::string>("addString") << std::endl;

  /* update parameters added - read configuration files */
  std::cout << " Updating added parameters." << std::endl;
  config -> updateAddedParameters( );

  /* print values of these parameters after reading the configuration files */
  std::cout << " addInt: " << config -> get<int>("addInt") << std::endl;
  std::cout << " addDouble: " << config -> get<double>("addDouble") << std::endl;
  std::cout << " addString: " << config -> get<std::string>("addString") << std::endl;

  /* parameters can be modified */
  config -> modify<int>("addInt",5,true);
  config -> modify<double>("addDouble",-18.3,true);
  config -> modify<std::string>("addstringWrong","test_bad",true);
  config -> modify<std::string>("addString","test_good",true);

  /* print values of these parameters after modyfing */
  std::cout << " addInt: " << config -> get<int>("addInt") << std::endl;
  std::cout << " addDouble: " << config -> get<double>("addDouble") << std::endl;
  std::cout << " addString: " << config -> get<std::string>("addString") << std::endl;

  /* read configuration files again - to refresh and cancel modified fields */
  std::cout << " Updating added parameters." << std::endl;
  config -> updateAddedParameters( );

  /* print values of these parameters after refreshing */
  std::cout << " addInt: " << config -> get<int>("addInt") << std::endl;
  std::cout << " addDouble: " << config -> get<double>("addDouble") << std::endl;
  std::cout << " addString: " << config -> get<std::string>("addString") << std::endl;

  /* show which parameters were added */
  config -> listAddedParameters( );

  /* ----------------------------------------------------------------------------------------- */
  /* Option 2:
     Parameters and their values are not being stored in the scfgp object itself. To access a parameter you initialize a local variable and make a request; once config files are read local variable is being updated */

  /* Initialize local variables that will be updated; no need to set default values here */
  int _reqInt;
  double _reqDouble;
  std::string _reqString;

  /* Request parameters that will be used with their default values in case they are not found in configuration files */
  config -> request<int>("reqInt",150,&_reqInt,true);
  config -> request<double>("reqDouble",250.0,&_reqDouble,true);
  config -> request<std::string>("reqString","NoneString",&_reqString,true);
  
  /* show which parameters were reqested */
  config -> listRequestedParameters( );

  /* print values of these parameters before reading the configuration files */
  std::cout << " reqInt: " << _reqInt << std::endl;
  std::cout << " reqDouble: " << _reqDouble << std::endl;
  std::cout << " reqString: " << _reqString << std::endl;

  /* update requested parameters - read configuration files */
  std::cout << " Updating requested parameters." << std::endl;
  config -> updateRequests( );

  /* print values of these parameters after reading the configuration files */
  std::cout << " reqInt: " << _reqInt << std::endl;
  std::cout << " reqDouble: " << _reqDouble << std::endl;
  std::cout << " reqString: " << _reqString << std::endl;

  /* show shich parameters were reqested */
  config -> listRequestedParameters( );

  config -> request<int>("reqInt",150,&_reqInt,true);
  config -> updateRequests( );
  config -> listRequestedParameters( );

  return 0;
}
