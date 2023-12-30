#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <io.h>
using namespace std;

typedef struct BoneArray {
	short BoneID;
	unsigned char Channel;
	unsigned long frameThing;
	unsigned char blank0;
	float float0;
} BoneArray;

//class MotFile {
//public:
//	char      id[4]; // "mot\0"
//	uint32_t    hash;
//	uint16_t    flag;
//	int16_t     frameCount;
//	uint32_t    recordOffset;
//	uint32_t    recordNumber;
//	uint32_t    unknown; // usually 0 or 0x003c0000, maybe two uint16
//	char    animName[12]; // found at most 12 bytes with terminating 0
//	BoneArray BoneStuff[60];
//};

class MotFile {
public:
	char          id[4]; // "mot\0"
	unsigned long hash;
	short         flag;
	short         frameCount;
	unsigned long recordOffset;
	unsigned long recordNumber;
	unsigned long unknown; // usually 0 or 0x003c0000, maybe two uint16
	char          animName[12]; // found at most 12 bytes with terminating 0
	BoneArray     BoneStuff[128];
};

void getFiles(std::string path, std::vector<string>& files) {
	//文件句柄  
	intptr_t hFile = 0;
	//文件信息，声明一个存储文件信息的结构体  
	struct _finddata_t fileinfo;
	std::string p;  //字符串，存放路径
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//若查找成功，则进入
	{
		do
		{
			//如果是目录,迭代之（即文件夹内还有文件夹）  
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				//文件名不等于"."&&文件名不等于".."
				//.表示当前目录
				//..表示当前目录的父目录
				//判断时，两者都要忽略，不然就无限递归跳不出去了！
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			//如果不是,加入列表  
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		//_findclose函数结束查找
		_findclose(hFile);
	}

}

void ReadMotFile(std::string path)
{
	std::string _path = path;
	std::ofstream outfile(path + "\\B_result.txt");
	int _firstFrame = 1;
	int _lastFrame = _firstFrame - 1;
	std::vector<string> _list = {};
	std::vector<string> _files = {};

	getFiles(_path, _files);
	
	for (auto _filePath : _files)
	{
		//1.获取不带路径的文件名
		string::size_type iPos = _filePath.find_last_of('\\') + 1;
		std::string filename = _filePath.substr(iPos, _filePath.size() - iPos);
		
		//2.获取不带后缀的文件名
		std::string _fileNameWithoutExtension = filename.substr(0, filename.rfind("."));

		//3.获取后缀名
		std::string _extension = filename.substr(filename.find_last_of('.'));

		if (_extension == ".mot")
		{
			MotFile s;
			ifstream inFile(_filePath, ios::in | ios::binary); //二进制读方式打开
			if (!inFile) {
				cout << "error" << endl;
				continue;
			}
			inFile.read((char*)&s, sizeof(s));
			cout << _fileNameWithoutExtension << endl;
			cout << "id: " <<  s.id << endl;
			cout << "hash: " << s.hash << endl;
			cout << "flag: " << s.flag << endl;
			cout << "frameCount: " << s.frameCount << endl;
			cout << "recordOffset: " << s.recordOffset << endl;
			cout << "recordNumber: " << s.recordNumber << endl;
			cout << "unknown: " << s.unknown << endl;
			cout << "animName: " << s.animName << endl;
			cout << endl;
			int _frameCount = s.frameCount;
			inFile.close();
			//读取动画片段总帧数

			_lastFrame += _frameCount;
			outfile << _firstFrame << "|" << _lastFrame << "|" << _fileNameWithoutExtension << std::endl;
			//_list.push_back(_firstFrame + "|" + _lastFrame + "|" + _fileNameWithoutExtension);
			_firstFrame += _frameCount;
		}
	}
	outfile.close();
	//File.WriteAllLines(_path + $"/{_directoryName}.txt", _list);
}

int main8() {
	//std::string path = "F:\\c_work\\code";
	std::string path = "E:\\Dat_Pack_Scripts\\Enermy\\Android\\em000f";

	ReadMotFile(path);
	return 0;
}
//\\wpf200_0000.mot
//s.id << " " << s.hash << " " << s.flag << " " <<  << " " << s.recordOffset << " " << s.recordNumber << " " << s.unknown << " " << s.animName