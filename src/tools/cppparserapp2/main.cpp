/*
 * main.cpp
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#include "Scanner.h"
#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <iostream>


int main(int argc, char **argv) {
	std::vector<std::string> extensions;
	extensions.push_back(".h");
	extensions.push_back(".hpp");


	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("input,I", boost::program_options::value<std::vector<std::string> >(), "adds a path or file to scan")
		("serialization,S", boost::program_options::value<bool>()->default_value(true), "enable serialization output")
		("extension,E", boost::program_options::value<std::vector<std::string> >(), "set extensions that must be scanned")
		("timecheck", boost::program_options::value<bool>()->default_value(true), "enable/disable the header time check to prevent bulding every time")
	;

	boost::program_options::positional_options_description p;
	p.add("input", -1);

	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
	boost::program_options::notify(vm);
	if(vm.count("help")) {
		std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
		std::cout << desc << std::endl;
		return 1;
	}


	std::vector<std::string> paths;
	bool serializationGen = false;
	bool timecheck = true;
	if(vm.count("input")) {
		paths = vm["input"].as<std::vector<std::string> >();
	}
	if(vm.count("serialization")) {
		serializationGen = vm["serialization"].as<bool>();
	}
	if(vm.count("extension")) {
		extensions = vm["extension"].as<std::vector<std::string> >();
	}
	if(vm.count("timecheck")) {
		timecheck = vm["timecheck"].as<bool>();
	}


	Scanner scanner(extensions, serializationGen, timecheck, argv[0]);
	for(unsigned int i=0; i<paths.size(); i++) {
		scanner.scan(paths[i]);
	}
}
