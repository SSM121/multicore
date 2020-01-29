#include <unistd.h>
#include <iostream>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include "MathObj.hpp"


int main()
{
//  mq_unlink(problemQueueName.c_str());
//  mq_unlink(answerQueueuName.c_str());
  mqd_t pro = mq_open(problemQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);
  mqd_t ans = mq_open(answerQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);
  Problem problem;
  Answer answer;
  int n;
  unsigned int val = 0;
  while(true)
  {
    n = mq_receive(pro, (char *) &problem, 8192, &val);
    std::cout << n << std::endl;
    if( n == -1)
    {
         std::cout << "failed" << std::endl;
    }
    else
    {
    
      std::cout << "received a value" << std::endl;
      switch(problem.m_opcode)
      {
         case eADD:
           answer.m_answer = problem.m_op1 + problem.m_op2;
           break;
         case eSUB:
           answer.m_answer = problem.m_op1 - problem.m_op2;
           break;
         case eMUL:
           answer.m_answer = problem.m_op1 * problem.m_op2;
           break;
         case eDIV:
	   if(problem.m_op2 == 0)
           {
	   answer.m_answer = 100000; //outside the range of the random numbers and signifies a divide by 0 case
	   }
           else
	   {
           answer.m_answer = problem.m_op1 / problem.m_op2;
           }
           break;
	   

      }
      mq_send(ans, (const char *) &answer, sizeof(answer), 0);
    }






  }
}
