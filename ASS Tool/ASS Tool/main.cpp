#include "TextSimilar.h"
#include "config.h"
int main(int argc, char* argv[])
{
	if (argc == 4)
	{
		TextSimilar textSimilar(argv[1]);
		textSimilar.GetTextSimilar(argv[2], argv[3]);
	}
	else if (argc == 2)
	{
		Config cfg(argv[1]);
		TextSimilar textSimilar(cfg);
		textSimilar.GetTextSimilar(cfg._file1.c_str(), cfg._file2.c_str());
	}
	else
	{
		cout << "Usage: " << argv[0] << " dict_path" << " file1_path" << " file2_path" << endl;
		cout << "Usage: " << argv[0] << " config_path" << endl;
		return -1;
	}
	//testWordFreq();
	//system("pause");
}