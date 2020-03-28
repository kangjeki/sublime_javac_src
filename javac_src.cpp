#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <sstream>

using namespace std;

DIR* classBin;
DIR* srcPath;
DIR* dirRoot;
DIR* dir;

string mainSource;
string mainJavaClass;

bool rollCouner = true;

struct dirent *ent;

template<typename Prt>
void print(Prt x) {
	cout << x << endl;
}


/**
 * sorting character string
 * -----------------------------------------------------------------------------
 */
string sorting(string &str) {
	string w = "";
	for ( int i = 0; i < str.length(); i++ ) {
		if (str[i] != ' ' && str[i] != '"'  && str[i] != ';' && str[i] != '\t') {
			w += str[i];
		}
	}
	return w;
}


/**
 * read main file to get package name 
 * -----------------------------------------------------------------------------
 */
string getPackageName(string file) {
	fstream mainFile;
	mainFile.open(file.c_str(), ios::in);

	string buffer; 
	string package = "";

	while(true) {
		if ( ! mainFile.eof() ) {
			getline(mainFile, buffer);
			if ( buffer.substr(0, 7) == "package" ) {
				string n_pkg = sorting(buffer);
				package = n_pkg.substr(7, n_pkg.length());
			}
		}
		else {
			break;
		}
	}
	mainFile.close();
	return package;
}


/**
 * Read Setting
 * -----------------------------------------------------------------------------
 */
string readSetting() {
	string pull = "";

	if ( mainSource.length() != 0 ) {
		fstream settingFile;

		ostringstream __getSetting;
		__getSetting << mainSource << "\\setting.jc";
		string getSetting = __getSetting.str();

		settingFile.open(getSetting.c_str(), ios::in);
		if ( settingFile.fail() ) {
			settingFile.open(getSetting.c_str(), ios::out);
			string defConf = "ProjectRoot=";
			settingFile << defConf << '"' << '"' << "\n";

			string mainConf = "ActivityMain=";
			settingFile << mainConf << '"' << "Main" << '"'; 
		}
		else {
			string buffer;
			while (true) {
				if ( settingFile.eof() ) {
					break;
				}
				else {
					getline(settingFile, buffer);
					string __matchBfr = sorting(buffer);
					if ( __matchBfr.substr(0, 12) == "ProjectRoot=" ) {
						pull = __matchBfr.substr(12, __matchBfr.length());
					}
					if ( __matchBfr.substr(0, 13) == "ActivityMain=" ) {
						mainJavaClass = __matchBfr.substr(13, __matchBfr.length());
					}
				}
			}
		}
		settingFile.close();	
	}
	return pull;
}


/**
 * read source directory
 * -----------------------------------------------------------------------------
 */
int __readSrc(const char* path) {
	srcPath = opendir(path);
	return ( !srcPath ) ? false: true;
}

int __readRoot(const char* rootPath) {
	dirRoot = opendir(rootPath);
	return ( !dirRoot ) ? false: true;
}

string getSourcePath() {
	string 	pathSRC = "",
			mainsrc = ".\\src";
	string 	pull = "";

	for ( int i = 0; i < 9; i++ ) {
		ostringstream root_path;
		root_path << pathSRC << ".\\" << readSetting();
		string reroot_path = root_path.str();

		ostringstream c_path;
		c_path << pathSRC << mainsrc;
		string rec_path = c_path.str();

		if ( readSetting().length() != 0 ) {
			if ( __readRoot(reroot_path.c_str()) ) {

				ostringstream src_root;
				src_root << reroot_path << "\\src";
				string __srec_path = src_root.str();

				DIR* c_src_path = opendir(__srec_path.c_str());

				if ( c_src_path ) {
					string __spliter = src_root.str();
					pull = __spliter.substr(0,__spliter.length() - 4);
				}
				else {
					print("> Failed Directory Root Not! >> setting.jc");
					rollCouner = false;
				}
				break;
			}
			else {
				pathSRC += ".\\.";
			}
		}
		else {
			if ( __readSrc(rec_path.c_str()) ) {
				// system("dir");
				// pull = rec_path;
				// string __spliter = src_root.str();
				pull = rec_path.substr(0,rec_path.length() - 4);
				break;
			}
			else {
				pathSRC += ".\\.";
				// print(rec_path);
			}	
		}
	}
	mainSource = pull;
	return pull;
}


/**
 * Main method
 * -----------------------------------------------------------------------------
 */
int main(int argc, char const *argv[]) {
	
	if ( getSourcePath().length() == 0 ) {
		print("--------------------- ERROR! ---------------------");
		print("> Source Path Not Found!");
		rollCouner = false;

		return 0;
	}
	else {
		
		/* membuat directory bin */
		ostringstream __pathBin, __pathBinMake;
		//print(getSourcePath());

		__pathBin << getSourcePath() << "\\bin";
		__pathBinMake << "mkdir " << getSourcePath() << "\\bin";

		string createBin = __pathBin.str();
		string createMakeBin = __pathBinMake.str();

		classBin = opendir(createBin.c_str());
		if (! classBin) {
			system(createMakeBin.c_str());
		}
		

		/* membaca path java file > build.jc */
		print("--------------------- Membaca File ---------------------");
		ostringstream pathSrc;
		pathSrc << "dir /s /B " << getSourcePath() << "\\src\\*.java > " << getSourcePath() << "\\build.jc";

		string execCreateBuildpull = pathSrc.str();
		const char *commandCreateBuildpull = execCreateBuildpull.c_str();
		system(commandCreateBuildpull);


		/* membaca file build.jc */
		fstream buildFile;
		ostringstream __readerBuildFile;
		__readerBuildFile << getSourcePath() << "\\build.jc";
		string readerBuildFile = __readerBuildFile.str();

		buildFile.open(readerBuildFile.c_str(), ios::in);

		string buffer, package;
		string setMain = (mainJavaClass.length() == 0) ? "Main" : mainJavaClass;
		string _mainFile;

		while (true) {
			if ( ! buildFile.eof() ) {
				//buildFile >> buffer;
				getline(buildFile, buffer);
				string reBuffer = sorting(buffer);

				if ( reBuffer.length() != 0 ) {
					 _mainFile = reBuffer.substr( reBuffer.length() - (setMain.length() + 5), reBuffer.length());

					if ( _mainFile.substr(0, setMain.length()) == setMain ) {
						package = getPackageName(reBuffer);
						break;
					}	
				}
			}
			else {
				break;
			}
		}
		buildFile.close();

		/* running compiling */
		if ( rollCouner == false ) {
			print("> Error! Structur!");
			return 0;
		}

		print("Run Compiling..");
		ostringstream __setcmd_javac;

		__setcmd_javac << "javac @"<< getSourcePath() <<"\\build.jc -d " << getSourcePath() << "\\bin";
		string cmdjavac = __setcmd_javac.str();
		system(cmdjavac.c_str());

		cout << "package: ";
		print(package);

		ostringstream fileCommand;
		fileCommand << "java -classpath " << getSourcePath() << "\\bin "<< package << "." << setMain;
		string fileExec = fileCommand.str();
		const char *command = fileExec.c_str();
			
		print("Running Main Class..");
		print(">>>\n");

		system(command);

		print("\n");
	}

	return 0;
}

