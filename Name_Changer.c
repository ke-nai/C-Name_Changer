#include <stdio.h>
#include <io.h>
#include <string>
#include <filesystem>

using namespace std;

int main() {
    intptr_t hFile;
    struct _finddata_t fName;
    if ((hFile = _findfirst("*-*.*.*.*-*.*.*.*.*", &fName)) != -1) { //해당 형식 파일 찾기
        do {
            //아래 조건문은 필요없지만 혹시 나중에 하위 폴더까지 보려면 필요할까봐 남겨둠
            if (fName.attrib & _A_SUBDIR) { 
                // directory 처리
            }
            else if (fName.attrib & _A_HIDDEN){
                // hidden file 처리
            }
            else {
                // 일반 파일 처리
                // 파일명에서 -찾고 다음 -가 13칸 차이인지 확인
                // 아니면 다음 -를 기준으로 반복
                printf("%s\n", fName.name);
                string nName = fName.name;
                int a;
                int b = nName.find("-");
                do {
                    a = b;
                    b = nName.find("-", a+1);
                } while (a+13 != b);
                nName.replace(a,26,"");//앞의 -부터 26칸 비우고
                rename(fName.name, nName.c_str());//파일명 변경
            }
        } while (_findnext(hFile, &fName) == 0); //같은 형식의 다음 파일 찾기
        _findclose(hFile);
    }

    system("pause"); //끝나고 콘솔창 안꺼지게
    return 0;
}