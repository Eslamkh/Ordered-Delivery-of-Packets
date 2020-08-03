#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

//-------------------------------- Declarations ------------------------------------//
int seqNumbits ;
int maxRvalue ;
int winSize ;
int intiSeq ;
int Expected ;

template<class QueueElementType>
class Queue
{
    public:
        Queue();
        void Enq(QueueElementType e);
        bool Enq_p(QueueElementType e);
        QueueElementType Deq();
        QueueElementType Top();
        bool isEmpty();
        bool isFull();
        int QueueSize();
        void ClearQueue();
    private:
        int Front ;
        int Rear ;
        int cap;
        int maxSize ;
        QueueElementType* Data = (QueueElementType *)malloc(sizeof(QueueElementType)*winSize);


};

// ------------------------------ some used functions ---------------------------------- //

bool check_not_number(string number)
{
    int j =0;
   while(number[j]!='\0')
    {
        if(int(number[j])<48 || int(number[j]) > 57 )
        {
            return true;
        }
        j++;

    }
    return false ;

}
int get_priority (int e)
{
    int priority = 0 ;
    for(int i =1 ; i<winSize ; i++)
    {
        if( e == (Expected+i)% (maxRvalue+1) )
        {
            priority = i;
            break;
        }
    }
    return priority ;
}


// ------------------------------ main function ----------------------------------- //

int main(int argc , char* argv[])
{
    if(argc <= 4)
    {
        cout<<"Invalid number of arguments ";
    }
    bool Error_general = false;
    bool Error_seqNumbits_wrong_value = false;
    bool Error_seqNumbits_not_number = false;
    bool Error_winSize_wrong_value = false;
    bool Error_winSize_not_number = false;
    bool Error_initSeq = false;
    bool Error_packetID = false;
    seqNumbits = atoi(argv[1]);
    winSize = atoi(argv[2]);
    intiSeq = atoi(argv[3]);
    maxRvalue = pow(2,seqNumbits)-1;

    if(check_not_number(string(argv[1])))
    {
        cout<<"Invalid seqNumBits ";
        Error_general = true;
        Error_seqNumbits_not_number = true;
    }
    if(atoi(argv[1]) <1 && !(Error_seqNumbits_not_number))
    {
        cout<<"Invalid seqNumBits ";
        Error_general = true;
        Error_seqNumbits_wrong_value = true;
    }
    if(argc >= 3 && check_not_number(string(argv[2])))
    {
        cout<<"Invalid winSize ";
        Error_general = true;
        Error_winSize_not_number = true;
    }
    if( argc >= 3 && (winSize > maxRvalue )  && !(Error_winSize_not_number) && !(Error_seqNumbits_wrong_value) && !(Error_seqNumbits_not_number))
    {
        cout<<"Invalid winSize ";
        Error_general = true;
    }
    if(argc >= 3 && winSize <1 && !(Error_winSize_not_number))
    {
        cout<<"Invalid winSize ";
        Error_general = true;
        Error_winSize_wrong_value = true;
    }
    if(argc >= 4 && check_not_number(string(argv[3])))
    {
        cout<<"Invalid initSeq ";
        Error_general = true;
        Error_initSeq = true;
    }
    if(argc >= 4 && intiSeq > maxRvalue && !(Error_initSeq) && !(Error_seqNumbits_not_number) && !(Error_seqNumbits_wrong_value) )
    {
        cout<<"Invalid initSeq ";
        Error_general = true;
    }
    for(int i =4 ;i<= argc-1 ; i++)
    {
        if(argc >= 5 && check_not_number(string(argv[i])))
        {
            cout<<"Invalid packet ID ";
            Error_general = true;
            Error_packetID = true;
            break;
        }
    }

    if(argc >= 5 && !(Error_packetID) && !(Error_seqNumbits_not_number) && !(Error_seqNumbits_wrong_value))
    {
        for(int i =4 ;i<= argc-1 ; i++)
    {
        if(atoi(argv[i]) > maxRvalue || atoi(argv[i]) < 0 )
        {
            cout<<"Invalid packet ID ";
            Error_general = true;
            break;
        }
    }
    }


    if(Error_general)
        return 0;

    string R = "R ";
    string E = "E ";
    string W = "W ";
    string D = "D ";
    Queue<int>wait;
    Expected = intiSeq ;

    for(int i =4 ;i<= argc-1 ; i++)
    {
        if(wait.isEmpty())
        {
            if(atoi(argv[i]) == Expected)
            {
                R.append(argv[i]);
                R.append(" ");
                Expected = (Expected+1)%(maxRvalue+1);
            }
            else if(!wait.Enq_p(atoi(argv[i])))
            {
                D.append(argv[i]);
                D.append(" ");
            }

        }
        else
        {
            while(wait.Top() == Expected)
            {
                stringstream ss;
                ss << wait.Deq();
                string str = ss.str();
                R.append(str);
                R.append(" ");
                Expected = (Expected+1)%(maxRvalue+1);
            }

            if(atoi(argv[i]) == Expected)
            {
                R.append(argv[i]);
                R.append(" ");
                Expected = (Expected+1)%(maxRvalue+1);
            }
            else if(!wait.Enq_p(atoi(argv[i])))
            {
                D.append(argv[i]);
                D.append(" ");
            }
        }

    }
    while(! wait.isEmpty())
    {
        if(wait.Top() == Expected)
            {
                stringstream ss;
                ss << wait.Deq();
                string str = ss.str();
                R.append(str);
                R.append(" ");
                Expected = (Expected+1)%(maxRvalue+1);
            }
            else
            {
                break;
            }
    }

    while(! wait.isEmpty())
    {
        stringstream ss;
        ss << wait.Deq();
        string str = ss.str();
        W.append(str);
        W.append(" ");
    }
    stringstream ss;
    ss << Expected;
    string str = ss.str();
    cout<<R<<E.append(str)<<" "<<W<<D;


    return 0;
}

// ------------------------- Queue implementation ------------------------------ //

template<class QueueElementType>
Queue<QueueElementType>::Queue()
{
    Front = 0;
    Rear = -1;
    cap = 0;
    maxSize = winSize ;
}

template<class QueueElementType>
void Queue<QueueElementType>::Enq(QueueElementType e)
{
    Rear = (Rear+1)%maxSize;
    Data[Rear] = e;
    cap++;

}
template<class QueueElementType>
bool Queue<QueueElementType>::isEmpty()
{
    if(cap == 0)
        return true;
    else
        return false;

}
template<class QueueElementType>
bool Queue<QueueElementType>::isFull()
{
    if(cap == maxSize)
        return true;
    else
        return false;

}

template<class QueueElementType>
QueueElementType Queue<QueueElementType>::Deq()
{
    cap --;
    QueueElementType out = Data[Front];
     if(cap == 0)
    {
        Front = 0;
        Rear = -1;
        return out;
    }
    Front = (Front + 1)%maxSize ;

    return out;

}
template<class QueueElementType>
QueueElementType Queue<QueueElementType>::Top()
{
    return Data[Front];

}
template<class QueueElementType>
int Queue<QueueElementType>::QueueSize()
{
    return cap;
}
template<class QueueElementType>
void Queue<QueueElementType>::ClearQueue()
{
    Front = 0;
    Rear = -1;
    cap = 0;
}
template<class QueueElementType>
bool Queue<QueueElementType>::Enq_p(QueueElementType e)
{
    int added_priority = get_priority(e) ;
    if(cap == maxSize || added_priority == 0)
    {
        return false ;
    }


    if(cap == 0)
    {
        Rear = (Rear + 1)%maxSize ;
        Data[Rear] = e;
        cap ++;
        return true ;
    }
    if(Rear >= Front)
    {
        for(int i = Front ; i<= Rear ; i++)
        {
            if( e == Data[i])
            {
                return false ;
            }
        }
    }
    else
    {
        for( int i = Front ; i!= Rear+1 ; i = (i+1)%maxSize)
        {
            if(Data[i] == e)
            {
                return false ;
            }
        }
    }
    Rear = (Rear + 1)%maxSize ;
    Data[Rear] = e;
    int temp ;
    int j = Rear;

    if(cap != 0)
    {
        if(Rear >= Front)
        {
            for (int i = Rear-1 ; i>= Front ; i--)
            {
                if(i<0)
                {
                    break;
                }
                if( added_priority < get_priority(Data[i]) )
                {
                    temp = Data[i];
                    Data[i]= Data[j];
                    Data[j] = temp ;
                    j = i ;

                }
            }
        }
        if(Front > Rear)
        {
             for (int i = (Rear-1)%maxSize ; i!= Front-1 ; i= (i-1)%maxSize)
            {
                if(i ==-1)
                {
                    i = maxSize-1;
                }

                if(i<0)
                {
                    break;
                }
                if( added_priority < get_priority(Data[i]) )
                {
                    temp = Data[i];
                    Data[i]= Data[j];
                    Data[j] = temp ;
                    j = i ;

                }
            }
        }

    }
    cap++;
    return true ;
}
