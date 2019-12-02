#pragma once
#include <string>
#include <fstream>
#include <iostream>
struct Config
{
	/*dict = 路径
	*hmm = 路径
	*userDict = 路径
	*idf = 路径
	*stopWord = 路径
	*maxWordNum = 
	*file1 = 
	*file2 = 
	*/
	Config(const char* configFile)
	{
		std::ifstream file(configFile);
		if (!file.is_open())
		{
			std::cerr << "config file open error" << std::endl;
			exit(-1);
		}
		std::pair<std::string, std::string> cfg;
		std::string dec;
		while (!file.eof())
		{
			file >> cfg.first >> dec >> cfg.second;
			if (cfg.first == "dict")
			{
				_dictPath = cfg.second;
			}
			if (cfg.first == "hmm")
			{
				_hmmModelPath = cfg.second;
			}
			if (cfg.first == "userDict")
			{
				_userDictPath = cfg.second;
			}
			if (cfg.first == "idf")
			{
				_idfPath = cfg.second;
			}
			if (cfg.first == "stopWord")
			{
				_stopWordPath = cfg.second;
			}
			if (cfg.first == "maxWordNum")
			{
				_maxWordNum = std::stoi(cfg.second);
			}
			if (cfg.first == "file1")
			{
				_file1 = cfg.second;
			}
			if (cfg.first == "file2")
			{
				_file2 = cfg.second;
			}
			//std::cout << _dictPath << std::endl;

		}
	}
	std::string _dictPath;
	std::string _hmmModelPath;
	std::string _userDictPath;
	std::string _idfPath;
	std::string _stopWordPath;
	int _maxWordNum;
	std::string _file1;
	std::string _file2;
};