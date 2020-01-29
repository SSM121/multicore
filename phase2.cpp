#if 0
#include <unistd.h>
#include <iostream>
#include <sys/types.h> /* pid_t */
#include <unistd.h>  /* _exit, fork */
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include "MathObj.hpp"
#include <random>
#include <sys/mman.h>
#endif
#include "MathObj.hpp"
#include <random>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <iostream>
#include <semaphore.h>
#include <map>
#include <functional>
#include <mqueue.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{
  std::random_device rd;
  int x;
  mqd_t pro = mq_open(problemQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);
  mqd_t ans = mq_open(answerQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);
  int n, m;
  unsigned int val = 0;
  Problem problem;
  Answer answer;
  if(argc == 1)
  {
  std::cout << "expected an iterations value. defaulting to one iteration" << std::endl;
  m = 1;
  }
  else
  {
    m = atoi(argv[1]);
  }
  int pid = fork();
  if(pid == 0)
  {
    for(int i = 0; i < (ARRAY_SIZE * m); i++)
    {
//    std::cout << "test spot line 23" << std::endl;
      problem.m_op1 = rd() % 100;
      problem.m_op2 = rd() % 100;
      x = rd() % 4;
//    std::cout << "test spot line 27 " << x << std::endl;
      switch(x)
      {
        case 0:
          problem.m_opcode = eADD;
//        std::cout << "test add" << std::endl;
          break;
        case 1:
          problem.m_opcode = eSUB;
//        std::cout << "test sub" << std::endl;
          break;
        case 2:
          problem.m_opcode = eMUL;
//        std::cout << "test mul" << std::endl;
          break;
        case 3:
          problem.m_opcode = eDIV;
//        std::cout << "test div" << std::endl;
          break;
      }
//      std::cout << "test line 47" << std::endl; 
      mq_send(pro, (const char *) &problem, sizeof(problem), 0);
//      std::cout <<  "test line 49 " << std::endl;
      std::cout << problem.m_op1 << " " << problem.m_opcode << " " << problem.m_op2 <<  std::endl; //debug line for checking answers 
//      sleep(4); //dont use in timing but just is used to slow the timing way down to check functionality.
    }
    
  }
  else
  {
      for(int i = 0; i < (ARRAY_SIZE * m); i++)
      {
        n = mq_receive(ans, (char *) &answer, 8192, &val);

      
       if(n == -1)
       {}
       else
       {
         std::cout << answer.m_answer << std::endl;  //debug for consuming answer
       }
   
     }
    int status;
    waitpid(pid, &status, 0);

 }
}
