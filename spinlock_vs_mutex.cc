#include <thread>
#include <atomic>
#include <mutex>

class SpinLock{
 public:
    void lock() {
        while(flag.test_and_set()){}
    }
    void unlock() {
        flag.clear();
    }
 private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

SpinLock spin;
std::mutex mut;

void work_spin() {
    //spin.lock();
    mut.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    mut.unlock();
    //spin.unlock();
}

int main() {
    std::thread t(work_spin);
    std::thread t2(work_spin);
    t.join();
    t2.join();
    return 0;
}