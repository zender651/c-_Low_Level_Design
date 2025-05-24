#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

using namespace std;

class BlockingQueue {
    deque<int> q;
    int capacity;
    mutex m;

public:
    BlockingQueue(int cap) : capacity(cap) {}

    void add(int num) {
        lock_guard<mutex> lock(m);
        if (q.size() < capacity)
            q.push_back(num);
    }

    int remainingCapacity() {
        lock_guard<mutex> lock(m);
        return capacity - q.size();
    }

    void remove() {
        lock_guard<mutex> lock(m);
        if (!q.empty())
            q.pop_front();
    }
};

class LeakyBucket {
    BlockingQueue* q;

public:
    LeakyBucket(int cap) {
        q = new BlockingQueue(cap);
    }

    bool grantAccess() {
        if (q->remainingCapacity() > 0) {
            q->add(1);
            return true;
        }
        return false;
    }

    void leak() {
        q->remove();
    }
};

class UserBucketCreator {
    map<int, LeakyBucket*> bucket;

public:
    UserBucketCreator(int id) {
        int capacity = 10;
        bucket[id] = new LeakyBucket(capacity);
    }

    void accessApplication(int id) {
        if (bucket[id]->grantAccess()) {
            cout << "[Leaky] User Id " << id << " [Thread " << this_thread::get_id() << "] Accessed\n";
        } else {
            cout << "[Leaky] User Id " << id << " [Thread " << this_thread::get_id() << "] Too many requests\n";
        }
    }

    void leak(int id) {
        bucket[id]->leak();
    }
};

class TokenBucket {
    atomic<int> tokens;
    int capacity;
    int refreshRate;
    chrono::steady_clock::time_point last_refill_time;
    mutex m;

public:
    TokenBucket(int cap, int rate) : capacity(cap), tokens(cap), refreshRate(rate) {
        last_refill_time = chrono::steady_clock::now();
    }

    bool grantAccess() {
        refillTokens();
        if (tokens > 0) {
            tokens--;
            return true;
        }
        return false;
    }

    void refillTokens() {
        lock_guard<mutex> lock(m);
        auto currTime = chrono::steady_clock::now();
        auto timeElapsed = chrono::duration_cast<chrono::seconds>(currTime - last_refill_time);

        if (timeElapsed.count() > 0) {
            int newtokens = timeElapsed.count() * refreshRate;
            tokens = min(tokens.load() + newtokens, capacity);
            last_refill_time = currTime;
        }
    }

    int remainingTokens() {
        refillTokens();
        return tokens;
    }
};

class UserTokenCreator {
    map<int, TokenBucket*> bucket;

public:
    UserTokenCreator(int id, int refreshRate) {
        int capacity = 10;
        bucket[id] = new TokenBucket(capacity, refreshRate);
    }

    void accessApplication(int id) {
        if (bucket[id]->grantAccess()) {
            cout << "[Token] User Id " << id << " [Thread " << this_thread::get_id() << "] Accessed\n";
        } else {
            cout << "[Token] User Id " << id << " [Thread " << this_thread::get_id() << "] Too many requests\n";
        }
    }
};

// ----------- Simulations ------------

void simulateLeakyUser(UserBucketCreator* user, int id) {
    for (int i = 0; i < 30; i++) {
        user->accessApplication(id);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void leakContinuously(UserBucketCreator* user, int id) {
    while (true) {
        user->leak(id);
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void simulateTokenUser(UserTokenCreator* user, int id) {
    for (int i = 0; i < 30; i++) {
        user->accessApplication(id);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    // Leaky Bucket User
    UserBucketCreator* leakyUser = new UserBucketCreator(1);
    thread t1(simulateLeakyUser, leakyUser, 1);
    thread t2(leakContinuously, leakyUser, 1);

    // Token Bucket User
    UserTokenCreator* tokenUser = new UserTokenCreator(2, 1);
    thread t3(simulateTokenUser, tokenUser, 2);

    t1.join();
    t3.join();
    // t2 runs infinitely — detach it
    t2.detach();

    return 0;
}






#include <bits/stdc++.h>
using namespace std;
#include<thread>


class LeakyBucket{
  public:
   queue<int> q;
   int capacity;
   
   
   LeakyBucket(int n)
   {
     capacity=n;
   }
   
   void add(int id)
   {
     if(q.size()>=capacity)
      {
        cout<<"Too many requests"<<capacity<<endl;
      }
    else
    {
      q.push(id);
    }
   }
   
   void leak()
   {
      while(!q.empty())
      {  
         this_thread::sleep_for(chrono::seconds(1));
         cout<<" request of user "<<q.front()<<" processed"<<endl;
         q.pop();
      }
   }
  
};


class UserBucketCreate{
  public:
  int id;
  string ip;
  int bucketCapacity=1;
  map<pair<int,string>,LeakyBucket*> m;
  
  UserBucketCreate(int id,string ip)
  { 
    this->id=id;
    this->ip=ip;
    m[{id,ip}]=new LeakyBucket(bucketCapacity);
    
    
    thread(&LeakyBucket::leak,m[{id,ip}]).detach();
  }
  
  void simulate()
  {
     for(int i=0;i<20;i++)
     {
       m[{id,ip}]->add(id);
       this_thread::sleep_for(chrono::seconds(1));
     }
  }
  
};
int main() 
{
    UserBucketCreate* user1=new UserBucketCreate(1,"112.16.8.6");
    user1->simulate();
    return 0;
}