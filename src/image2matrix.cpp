#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string.h>

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

typedef std::vector<std::string> stringvec;

void read_directory(const std::string& name, stringvec& v)
{
  DIR* dirp = opendir(name.c_str());
  if(dirp == NULL){
    cerr << "no folder " << name << endl;
    exit(EXIT_FAILURE);
  }
  struct dirent * dp;

  while ((dp = readdir(dirp)) != NULL)
    if(dp->d_name[0] != '.')
      v.push_back(dp->d_name);

  sort(v.begin(), v.end());
  closedir(dirp);
}

string init_file(){
  return "#include <stdlib.h>\n#include <stdint.h>\n\nuint16_t** get_char_table()\n{\n\tuint16_t** chars = malloc(256*sizeof(uint16_t*));\n\tuint16_t* default_char = malloc(2*sizeof(uint16_t));\n\tdefault_char[0] = 1, default_char[1] = 0;\n\tfor(int i = 0; i < 256; i++){\n\t\tchars[i] = default_char;\n\t}\n\n";
  // return "";
}

void get_name(char* path, char* name){
  int i1 = strlen(path) - 1;
  int i2 = i1;
  while(path[--i2] != '.');
  while(path[--i1] != '/');
  i1++;
  int i = 0;
  for(; i1 < i2; i1++, i++){
    name[i] = path[i1];
  }
  name[i] = '\0';
}

char get_index(char* path, int* first_available_index, char* returned_name) {
  char name[strlen(path)];
  get_name(path, name);
  strcpy(returned_name, name);

  // printf("%s %s\n", name, returned_name);
  if(strlen(name) == 1 && '!' <= name[0] && name[0] <= '~'){
    return name[0];
  }
  if(strcmp(name,"Space") == 0){
    return 32;
  }
  if(strcmp(name,"Dot") == 0){
    return 46;
  }
  if(strcmp(name,"Slash") == 0){
    return 47;
  }
  if(*first_available_index == 31 /* before the space char code*/){
    *first_available_index = 127;
    return 31;
  }
  if(*first_available_index < 255){
    return (*first_available_index)++;
  }
  return 0;
}

int get_leds(Mat ims, int c, int rows){
  int val = 0;
  for(int r = 0; r < rows; r++) {
    if(ims.at<uchar>(r, c) == 0){
      val += pow(2, rows-r-1);
    }
  }
  return val;
}

string scan_img(char* path, int* first_available_index) {
  Mat ims;
  ims = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
  int cols = ims.cols;
  int rows = ims.rows;

  if(rows != 16 || cols > 8) {
    printf("Bad image: %s\n", path);
    return "";
  }

  char name[32];
  char index = get_index(path, first_available_index, name);
  // printf("index: %c %d\n", index, index);
  if(index == 0)
    return "";

  // worst case : 8*Oxffff : chars[%s]=malloc(9*sizeof(int));\nchars[%s][0]=8;\nchars[%s][1]=Oxffff;\nchars[%s][2]=Oxffff;\nchars[%s][3]=Oxffff;\nchars[%s][4]=Oxffff;\nchars[%s][5]=Oxffff;\nchars[%s][6]=Oxffff;\nchars[%s][7]=Oxffff;\nchars[%s][8]=Oxffff;
  char s[350] = {0};
  s[0] = '\0';
  sprintf(s, "\t// %s\n", name);
  sprintf(s, "%s\tchars[%d]=malloc(%d*sizeof(uint16_t));\n\tchars[%d][0]=%d;\n", s, index, cols+1, index, cols);
  for(int c = 0; c < cols; c++){
    int val = get_leds(ims, c, rows);
    sprintf(s, "%s\tchars[%d][%d]=0x%x;\n", s, index, c+1, val);
  }

  sprintf(s, "%s\n", s);
  return s;
}

void process(const char* dirname, const char* filename)
{
  int len = strlen(dirname);
  char dir[len+2];
  strcpy(dir, dirname);
  if (dirname[len-1] != '/') {
    dir[len]='/';
    dir[len+1]='\0';
  }

  std::ofstream outfile;
  outfile.open(filename);
  outfile << init_file();
  outfile.close();
  outfile.open(filename, std::ios_base::app); // append instead of overwrite

  stringvec v;
  read_directory(dirname, v);

  int first_available_index = 1;

  stringvec::iterator it = v.begin(), itEnd = v.end();
  for(; it != itEnd; it++) {
    char path[len+(*it).length()+2];
    sprintf(path, "%s%s", dir, (*it).c_str());
    outfile << scan_img(path, &first_available_index);;
  }
  outfile << "\treturn chars;\n}";
  outfile.close();
}

void usage (const char *s)
{
  cout << "Usage: " << s << " dir output-file"<< endl;
  exit(EXIT_FAILURE);
}

#define param 2
int main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2]);
  return EXIT_SUCCESS;
}
