/* Name: Evan Raab
 * Project Name: CSC450-Portfolio Project: Part 1
 * Project Purpose: Use concurrency to update counter integer
 * Algorithm Used: Within two threads, have one method increment integer using while method and the other thread decrement. Use locks and conditions to ensure that counter is only changed by one thread at a single time.
 * Program Inputs: None
 * Program Outputs: Integer Counter
 * Program Errors: None
*/

#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
using namespace std;

// shared counter integer
int counter = 0;
// lock reference
mutex pm;
// condition to check for when using notify
condition_variable condition;


// increment integer value of counter
void thread_count_up() {

	// lock the thread while counting
	std::unique_lock<std::mutex> lk(pm);

	// if the value of counter is below 20, increment the value
	while (counter < 20) {
		counter++;
	}

}

// decrement the integer value of counter
void thread_count_down() {
	// lock the thread while counting
	std::unique_lock<std::mutex> lk(pm);
	// execute wait condition so that thread will not start counting until counter is equal 20
	condition.wait(lk, []{ return counter == 20  && counter > 0; });

	// if the value of counter is greater than 0, count down
	while (counter > 0) {
		counter--;
	}

	// notify thread1 that thread2 has completed its function
	condition.notify_one();


}

int main()
{
	// call thread_count_up in thread1
	thread thread1(thread_count_up);
	// call thread_count_down in thread2
	thread thread2(thread_count_down);

	// join both threads
	thread1.join();
	 cout << "Thread1: Counter reached: " << counter << endl;
	thread2.join();
	cout << "Thread2: Counter reached: " << counter << endl;

    return 0;
}
