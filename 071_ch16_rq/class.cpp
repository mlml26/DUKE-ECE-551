#include <cstdio>
class Learn{
private :
  int attr;
public:
  Learn() : attr(0){
    printf("Calling the defaulf constructor\n");
  }
  Learn(int x) : attr(x){
    printf("Calling the constructor (%d)\n" , attr);
  }
  Learn(const Learn & rhs) : attr(rhs.attr) {
    printf("Calling the copy constructor (%d)\n", attr);
  }
  Learn & operator=(const Learn & rhs) {
    attr = rhs.attr;
    printf("Calling the assign operator\n");
    return * this;
  }
  ~Learn(){
    printf("Calling the destructor [with %d]\n" , attr);
  }
  void increase(int x) {
    attr += x;
  }
};
void foo(Learn & a, Learn b){
  printf("Inside foo\n");
  a.increase(10);
  b.increase(20);
}

int main(void) {
  printf("learn1:\n");
  Learn learn1;
  printf("learn2:\n");
  Learn learn2(4);
  printf("learn3:\n");
  Learn learn3 = learn2;
  learn3.increase(5);
  printf("foo:\n");
  foo(learn1,learn2);
  printf("back to main\n");
  return EXIT_SUCCESS;
}
