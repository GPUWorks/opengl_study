
#include <iostream>
#include <string>
#include <io.h>
#include <direct.h>
#include <map>
#include <unordered_map>

struct  Vec3
{
	float x;
	float y;
	float z;
};

#define TEST_MACRO(X) a##X##b

void changeValue(Vec3* v)
{
	(*v).x = 100;
}

std::string ToString(const char* str)
{
	return str;
}

void dir(std::string path)
{
	
	intptr_t hFile = 0;
	struct _finddata_t fileInfo;
	std::string pathName, exdName;

	// \\* ����Ҫ�������е�����
	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) {
		return;
	}
	do
	{
		//�ж��ļ����������ļ��л����ļ�
		std::cout << fileInfo.name << (fileInfo.attrib&_A_SUBDIR ? "[folder]" : "[file]") << std::endl;
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return;
	

	intptr_t Handle;
	struct _finddata_t FileInfo;
	if ((Handle = _findfirst("D:\\*.txt", &FileInfo)) == -1L)
		printf("û���ҵ�ƥ�����Ŀ\n");
	else
	{
		printf("%s\n", FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0)
			printf("%s\n", FileInfo.name);
		_findclose(Handle);
	}
}

// ��str�ַ���spl�ָ�,����dst�У����������ַ�������
int split(char dst[][80], char* str, const char* spl)
{
	int n = 0;
	char *result = NULL;
	result = strtok(str, spl);
	while (result != NULL)
	{
		strcpy(dst[n++], result);
		result = strtok(NULL, spl);
	}
	return n;
}

class Father
{
protected:
	virtual void printSon()
	{

	}
	int iBase;
};

class Son : public Father
{
protected:

	void printSon() override
	{
		Father::printSon();
		iBase++;
	}
};

int main()
{
	Vec3 v = { 1, 2, 3 };
	changeValue(&v);

	std::cout << "v = (" << v.x << "," << v.y << "," << v.z << ")" << std::endl;

	char str[] = "what is you name?";
	char dst[10][80];
	int cnt = split(dst, str, " ");
	for (int i = 0; i < cnt; i++)
		puts(dst[i]);
	
	std::string string = ToString("123445");
	std::cout << string << std::endl;
	char cdir[255];
	char* path = _getcwd(cdir, 255);
	dir(path);

	char* a123b = "this is a test";
	puts(TEST_MACRO(123));

	int* i0 = new int(1);
	int* i1 = new int(-1);
	int* i2 = new int(23);
	int* i3 = new int(97);
	int* i4 = new int(101);

	std::unordered_map<void*, int> pointer_map;
	pointer_map.insert(std::pair<void*, int>(i0, *i0));
	pointer_map.insert(std::pair<void*, int>(i1, *i1));
	pointer_map.insert(std::pair<void*, int>(i2, *i2));
	pointer_map.insert(std::pair<void*, int>(i3, *i3));
	pointer_map.insert(std::pair<void*, int>(i4, 10086));

	std::cout << "sizeof(void*)=" << sizeof(void*) << std::endl;
	std::cout << "i0=" << pointer_map[i0] << std::endl;
	std::cout << "i1=" << pointer_map[i1] << std::endl;
	std::cout << "i2=" << pointer_map[i2] << std::endl;
	std::cout << "i3=" << pointer_map[i3] << std::endl;
	std::cout << "i4=" << pointer_map[i4] << std::endl;

	for (auto it : pointer_map)
	{
		delete it.first;
	}

	return 0;
}
