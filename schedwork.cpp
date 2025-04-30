#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please 
#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftsWorked,
    size_t day,
    size_t slot);

bool isValid(
    const AvailabilityMatrix& avail,
    const size_t maxShifts,
    const DailySchedule& sched,
    const vector<size_t>& shiftsWorked,
    size_t day,
    size_t slot,
    Worker_T worker);

// Add your implementation of schedule() and other helper functions here
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched) 
{
    if(avail.size() == 0U){
        return false;
    }
    
    sched.clear();
    

    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();
    
 
    sched.resize(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));
    

    vector<size_t> shiftsWorked(numWorkers, 0);
    
   
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, 0, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftsWorked,
    size_t day,
    size_t slot)
{
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();
    

    if (day == numDays) {
        return true;
    }
    

    if (slot == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, day + 1, 0);
    }
    
    // Try to assign each worker to the current slot
    for (Worker_T worker = 0; worker < numWorkers; worker++) {
        
        if (isValid(avail, maxShifts, sched, shiftsWorked, day, slot, worker)) {

            sched[day][slot] = worker;
            shiftsWorked[worker]++;
            

            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, day, slot + 1)) {
                return true;
            }
            

            shiftsWorked[worker]--;
            sched[day][slot] = INVALID_ID;
        }
    }
    
    // No valid worker found for this slot
    return false;
}


bool isValid(
    const AvailabilityMatrix& avail,
    const size_t maxShifts,
    const DailySchedule& sched,
    const vector<size_t>& shiftsWorked,
    size_t day,
    size_t slot,
    Worker_T worker)
{

    if (!avail[day][worker]) {
        return false;
    }
    

    if (shiftsWorked[worker] >= maxShifts) {
        return false;
    }
    

    for (size_t i = 0; i < slot; i++) {
        if (sched[day][i] == worker) {
            return false;
        }
    }
    

    return true;
}