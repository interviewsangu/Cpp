* lambda 함수
- 이름이 없는 함수를 바로 선언하여 사용할 수 있게 하는 기능
- 함수를 한정된 곳에서만 사용하는 경우에 사용
- 다른 함수의 파라미터로 전달 가능

* lambda 함수의 구조
#include <algorithm>
#include <cmath>

void abssort(float* x, unsigned n) {
    std::sort(x, x + n,
        // Lambda expression begins
        [](float a, float b) {
            return (std::abs(a) < std::abs(b));
        } // end of lambda expression
    );
}

(1) 선언하자마자 호출하는 형태 
- [변수 캡쳐](파라미터 변수 및 타입선언)->리턴타입{return 연산;}(넘길 인자) 형태
- [변수 캡쳐](파라미터 변수 및 타입선언){return 연산;}(넘길 인자) - 반환이 void

(2) 선언만 하는 경우
- [변수 캡쳐](파라미터 변수 및 타입선언){return 연산;} 형태로 사용(넘길 인자x)

* 변수 캡쳐
- 현재 함수에서 사용할 외부 변수들을 의미
- [] ; 비워진 형태, 변수를 사용하지 않겠다.
- [변수] ; 외부의 해당 변수만 사용, 읽기만 가능하고 값의 변경 불가
- [=] ; 외부의 모든 지역 변수를 사용하겠다.읽기만 가능하고 변경 불가
- [&] ; 외부의 모든 지역변수를 참조형으로 사용하겠다. 값 수정 가능
- [=, &변수] ; 특정 변수만 참조형으로 사용하는 것도 가능하다.

* ->리턴타입
- 함수의 반환 값의 타입을 지정
- 반환값이 void일 경우 화살표와 함께 생략

#include <iostream>

using namespace std;

int main(void)
{
    int a = 5;
    int b = 2;

    // 변수캡쳐를 사용하지 않고, 인자를 직접 받는 예시
    int result1 = [](int n, int m)->int{return n + m;}(a, b);   // 7
    
    // 변수캡쳐에 지역변수를 사용한 예시
    int result2 = [a]()->int{return a;}();                      // 5
    int result3 = [a, b]()->int{return a + b;}();               // 7
    
    // 변수캡쳐에 =를 사용한 예시
    int result4 = [=]()->int{return a + b;}();                  // 7

    // 변수캡쳐에 &를 사용한 예시
    int result5 = [&]()->int{return a + b;}();                  // 7
    int result6 = [&]()->int{return a = a + b;}();              // 7, a = 7

    // 람다함수 내부에 람다함수를 포함시킨 예시
    int result7 = [&]()->int{                                   // 9
        return [&]()->int{return a + b;}();    
    }();         
}



#include <iostream>
#include <functional>
#include <ctime>
#include <vector>
#include <algorithm>
#define V_SIZE 1
 
std::vector<int> genRandomNum(int maximum, int size);
void printVector(std::vector<int> vector);
 
int main() 
{
    srand((unsigned int)time(NULL));
    auto genVector = std::bind(genRandomNum, 100, 10);
    std::vector<std::vector<int>> vInt(V_SIZE);
 
    for (int i = 0; i < V_SIZE; i++) {
        vInt[i] = genVector();
    }
  
    for (std::vector<int> v : vInt) {
        std::cout << "정렬 전: ";
        printVector(v);
 
        // Sort in a ascending order
        sort(v.begin(), v.end(),
            [](int first, int second) -> bool
        {
            return first < second;
        });
 
 
        std::cout << "정렬 후(오름차순): ";
        printVector(v);
 
        // Sort in a descending order
        sort(v.begin(), v.end(),
            [](int first, int second) -> bool
        {
            return first > second;
        });
 
        std::cout << "정렬 후(내림차순): ";
        printVector(v);
        std::cout << std::endl;
    }
    return 0;
}
 
std::vector<int> genRandomNum(int maximum, int size)
{
    std::vector<int> temp;
    for (int i = 0; i < size; i++) {
        temp.push_back(rand() % maximum + 1);
    }
    return temp;
}
 
void printVector(std::vector<int> vector)
{
    for (auto v : vector)
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;
}
