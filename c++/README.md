# C++ 연습 환경

C++20 / clang++ 기반 빌드 환경입니다.

## 빠른 실행 (Makefile)

단일 파일을 빠르게 컴파일하고 실행할 때 사용합니다.

```bash
make run FILE=src/main.cpp     # 컴파일 후 실행
make build FILE=src/main.cpp   # 컴파일만
make clean                     # build 디렉토리 정리
```

## CMake 빌드

`src/` 안의 각 `.cpp` 파일이 같은 이름의 실행 파일로 빌드됩니다.

```bash
cmake -S . -B build            # 최초 설정
cmake --build build            # 전체 빌드
./build/main                   # 실행
```

## 구조

```
.
├── CMakeLists.txt
├── Makefile
├── src/
│   └── main.cpp
└── build/        # 빌드 결과물 (git 무시)
```
